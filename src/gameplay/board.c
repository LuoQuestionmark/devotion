#include "gameplay/board.h"
#include "config.h"
#include "gameplay/elements/rain.h"
#include "olive.c"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static void board_init_waterpool(board *board) {
    rain_map_reset(board->rain_map);
    for (int i = 0; i < WATERPOOL_INIT_COUNT; i++) {
        int row, col, radius;
        row    = rand() * 1.0 * BOARD_HEIGHT / RAND_MAX;
        col    = rand() * 1.0 * BOARD_WIDTH / RAND_MAX;
        radius = rand() * 1.0 * (WATERPOOL_MAX_RADIUS - WATERPOOL_MIN_RADIUS) / RAND_MAX +
                 WATERPOOL_MIN_RADIUS;

        rain_map_set_hot_point(board->rain_map, row, col, RAND_MAX, radius);
    }
}

board *init_board() {
    srand(42); // DEBUG

    board *ret           = calloc(1, sizeof(board));
    ret->col             = BOARD_WIDTH;
    ret->row             = BOARD_HEIGHT;
    ret->cells           = calloc(BOARD_WIDTH * BOARD_HEIGHT, sizeof(cell));
    ret->temple_to_build = 0;
    ret->rain_map        = init_rain_map();
    ret->food_map        = init_food_map();

    board_init_env(ret);
    // board_stats(ret);
    return ret;
}

void board_init_env(board *board) {
    // init water
    board_init_waterpool(board);
    board_transform_from_map(board, CELL_EMPTY, CELL_WATER, board->rain_map);
    rain_map_reset(board->rain_map);

    // init grass
    board_transform(board, CELL_EMPTY, CELL_GRASS, GRASS_SPAWN_RATE1);
}

void board_update(board *board, float dt) {
    static float cumulative_time_lapse = 0;
    cumulative_time_lapse += dt;
    if (cumulative_time_lapse < REFRESHING_INTEVAL) return;

    cumulative_time_lapse -= REFRESHING_INTEVAL;

    // fire to nothing
    board_transform(board, CELL_BURNT, CELL_EMPTY, FIRE_EXTINGUISHMENT_RATE);

    // nothing to grass
    board_transform(board, CELL_EMPTY, CELL_GRASS, GRASS_SPAWN_RATE1);
    board_transform_if_neighbor(board, CELL_EMPTY, CELL_GRASS, CELL_WATER, GRASS_SPAWN_RATE2);

    // nothing to rain
    board_transform_from_map(board, CELL_EMPTY, CELL_WATER, board->rain_map);

    // nothing to food
    board_transform_from_map(board, CELL_EMPTY, CELL_FOOD, board->food_map);

    // grass to fire
    board_transform(board, CELL_GRASS, CELL_FIRE, GRASS_IGNITE_RATE);
    board_transform_if_neighbor(board, CELL_GRASS, CELL_FIRE, CELL_BURNT, FIRE_TRANSMISSION_RATE);
    board_transform_if_neighbor(board, CELL_GRASS, CELL_FIRE, CELL_FIRE, FIRE_TRANSMISSION_RATE);

    // fire to burnt
    board_transform(board, CELL_FIRE, CELL_BURNT, FIRE_EXTINGUISHMENT_RATE);

    // update cached
    board_backup_type(board);
}

// void board_stats(board *board) {
//     int water_count = 0;
//     int grass_count = 0;
//     int fire_count  = 0;

//     for (int i = 0; i < board->row; i++) {
//         for (int j = 0; j < board->col; j++) {
//             switch (board->cells[i * BOARD_WIDTH + j].type) {
//             case CELL_WATER:
//                 water_count += 1;
//                 break;
//             case CELL_EMPTY:
//                 break;
//             case CELL_GRASS:
//                 grass_count += 1;
//                 break;
//             case CELL_FIRE:
//             case CELL_BURNT:
//                 fire_count += 1;
//                 break;
//             }
//         }
//     }

//     printf("board row = %d, col = %d\n", board->row, board->col);
//     printf("water: %d, grass: %d\n, fire: %d\n", water_count, grass_count, fire_count);
// }

void board_free(board *board) {
    free(board->cells);
    rain_map_free(board->rain_map);
    food_map_free(board->food_map);
    free(board);
}

void board_transform(board *board, enum cell_type src, enum cell_type tgt, float rate) {
    const int threshold = (int)(rate * RAND_MAX);
    for (int i = 0; i < board->row; i++) {
        for (int j = 0; j < board->col; j++) {
            cell *cell = board->cells + i * BOARD_WIDTH + j;
            if (cell->last_type == src && rand() <= threshold) {
                cell->type = tgt;
            }
        }
    }
}

void board_transform_if_neighbor(board *board, enum cell_type src, enum cell_type tgt,
                                 enum cell_type nbr, float rate) {
    int threshold = (int)(rate * RAND_MAX);
    for (int i = 0; i < board->row; i++) {
        for (int j = 0; j < board->col; j++) {
            // if the cell is not concerned, skip
            if (board->cells[i * BOARD_WIDTH + j].last_type != src) continue;

            // if no transform then skip
            if (rand() > threshold) continue;

            // transform if a neighbor is valid
            cell_list *c_list = board_cell_next(board, i, j);
            cell *cell;
            for (int k = 0; k < c_list->len; k++) {
                cell = board->cells + c_list->indices[k];
                if (cell->last_type == nbr) {
                    board->cells[i * BOARD_WIDTH + j].type = tgt;
                    break;
                }
            }
            cell_list_free(c_list);
        }
    }
}

void board_transform_from_map(board *board, enum cell_type src, enum cell_type tgt, map *map) {
    assert(board != NULL && map != NULL);
    int threshold;
    for (int i = 0; i < board->row; i++) {
        for (int j = 0; j < board->col; j++) {
            cell *cell = board->cells + i * BOARD_WIDTH + j;
            threshold  = map->map[i * BOARD_WIDTH + j];
            if (cell->last_type == src && rand() <= threshold) {
                cell->type = tgt;
            }
        }
    }
}

void board_backup_type(board *board) {
    for (int i = 0; i < board->row; i++) {
        for (int j = 0; j < board->col; j++) {
            cell *cell = board->cells + i * BOARD_WIDTH + j;

            cell->last_type = cell->type;
        }
    }
}

bool board_nearest_env(board *board, enum cell_type env, board_coord *src, board_coord *tgt,
                       int depth, board_coord *steps) {
    assert(src != NULL && tgt != NULL && steps != NULL);

    if (depth <= 0) return false;

    board_coord current_pos = { .row = src->row, .col = src->col };

    if (src->row > 0) {
        current_pos.row -= 1;

        steps[AMANT_MAX_FUTURE_STEPS - depth] = current_pos;
        if (board->cells[current_pos.row * BOARD_WIDTH + current_pos.col].type == env) {
            // find it!
            tgt->row = current_pos.row;
            tgt->col = current_pos.col;
            return true;
        }

        bool recursive_ans = board_nearest_env(board, env, &current_pos, tgt, depth - 1, steps);
        if (recursive_ans) return true;

        current_pos.row += 1;
    }

    if (src->row < BOARD_HEIGHT - 1) {
        current_pos.row += 1;

        steps[AMANT_MAX_FUTURE_STEPS - depth] = current_pos;
        if (board->cells[current_pos.row * BOARD_WIDTH + current_pos.col].type == env) {
            // find it!
            tgt->row = current_pos.row;
            tgt->col = current_pos.col;
            return true;
        }

        bool recursive_ans = board_nearest_env(board, env, &current_pos, tgt, depth - 1, steps);
        if (recursive_ans) return true;

        current_pos.row -= 1;
    }

    if (src->col > 0) {
        current_pos.col -= 1;

        steps[AMANT_MAX_FUTURE_STEPS - depth] = current_pos;
        if (board->cells[current_pos.row * BOARD_WIDTH + current_pos.col].type == env) {
            // find it!
            tgt->row = current_pos.row;
            tgt->col = current_pos.col;
            return true;
        }

        bool recursive_ans = board_nearest_env(board, env, &current_pos, tgt, depth - 1, steps);
        if (recursive_ans) return true;

        current_pos.col += 1;
    }

    if (src->col < BOARD_WIDTH - 1) {
        current_pos.col += 1;

        steps[AMANT_MAX_FUTURE_STEPS - depth] = current_pos;
        if (board->cells[current_pos.row * BOARD_WIDTH + current_pos.col].type == env) {
            // find it!
            tgt->row = current_pos.row;
            tgt->col = current_pos.col;
            return true;
        }

        bool recursive_ans = board_nearest_env(board, env, &current_pos, tgt, depth - 1, steps);
        if (recursive_ans) return true;

        current_pos.col -= 1;
    }

    return false;
}

cell_list *board_cell_next(board *board, int cell_row, int cell_col) {
    int is_top, is_button, is_leftmost, is_rightmost;
    is_top       = cell_row == 0;
    is_button    = cell_row == BOARD_HEIGHT - 1;
    is_leftmost  = cell_col == 0;
    is_rightmost = cell_col == BOARD_WIDTH - 1;

    int neighbors = 4;
    switch (is_top + is_button + is_leftmost + is_rightmost) {
    case 0:
        neighbors = 4;
        break;
    case 1:
        neighbors = 3;
        break;
    case 2:
        neighbors = 2;
        break;
    case 3:
        neighbors = 1;
        break;
    case 4:
        neighbors = 0;
        break;
    default:
        fprintf(stderr, "unexpected result at line %d\n", __LINE__);
    }

    cell_list *ret = calloc(1, sizeof(cell_list));
    ret->len       = neighbors;
    ret->indices   = calloc(neighbors, sizeof(int));

    int index = 0;
    // if (!is_top && !is_leftmost) {
    //     ret->indices[index++] = (cell_row - 1) * BOARD_WIDTH + cell_col - 1;
    // }
    if (!is_top) {
        ret->indices[index++] = (cell_row - 1) * BOARD_WIDTH + cell_col + 0;
    }
    // if (!is_top && !is_rightmost) {
    //     ret->indices[index++] = (cell_row - 1) * BOARD_WIDTH + cell_col + 1;
    // }
    if (!is_leftmost) {
        ret->indices[index++] = (cell_row + 0) * BOARD_WIDTH + cell_col - 1;
    }
    if (!is_rightmost) {
        ret->indices[index++] = (cell_row + 0) * BOARD_WIDTH + cell_col + 1;
    }
    // if (!is_leftmost && !is_button) {
    //     ret->indices[index++] = (cell_row + 1) * BOARD_WIDTH + cell_col - 1;
    // }
    if (!is_button) {
        ret->indices[index++] = (cell_row + 1) * BOARD_WIDTH + cell_col + 0;
    }
    // if (!is_rightmost && !is_button) {
    //     ret->indices[index++] = (cell_row + 1) * BOARD_WIDTH + cell_col + 1;
    // }

    return ret;
}

void cell_list_free(cell_list *cell_list) {
    free(cell_list->indices);
    free(cell_list);
}
