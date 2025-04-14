#include "gameplay/board.h"
#include "config.h"
#include "olive.c"
#include <stdio.h>
#include <stdlib.h>

static void board_transform(board *board, enum cell_type src, enum cell_type tgt, float rate) {
    const int threshold = (int)(rate * RAND_MAX);
    for (int i = 0; i < board->row; i++) {
        for (int j = 0; j < board->col; j++) {
            if (board->cells[i * BOARD_WIDTH + j].type == src && rand() < threshold) {
                board->cells[i * BOARD_WIDTH + j].type = tgt;
            }
        }
    }
}

board *init_board() {
    srand(42); // DEBUG

    board *ret = calloc(1, sizeof(board));
    ret->col   = BOARD_WIDTH;
    ret->row   = BOARD_HEIGHT;
    ret->cells = calloc(BOARD_WIDTH * BOARD_HEIGHT, sizeof(cell));

    board_init_env(ret);
    board_stats(ret);
    return ret;
}

void board_init_env(board *board) {
    // init water
    int water_spawn_threshold = (int)(WATER_SPAWN_RATE * RAND_MAX);
    for (int i = 0; i < board->row; i++) {
        for (int j = 0; j < board->col; j++) {
            if (rand() < water_spawn_threshold) {
                board->cells[i * BOARD_WIDTH + j].type = CELL_WATER;
            }
        }
    }

    // init grass
    int grass_spawn_threshold = (int)(GRASS_SPAWN_RATE * RAND_MAX);
    for (int i = 0; i < board->row; i++) {
        for (int j = 0; j < board->col; j++) {
            if (board->cells[i * BOARD_WIDTH + j].type == CELL_WATER) {
                cell_list *c_list = board_cell_next(board, i, j);

                for (int k = 0; k < c_list->len; k++) {
                    if (rand() < grass_spawn_threshold) {
                        board->cells[c_list->indices[k]].type = CELL_GRASS;
                    }
                }

                cell_list_free(c_list);
            }
        }
    }
}

void board_update(board *board, float dt) {
    static float cumulative_time_lapse = 0;
    cumulative_time_lapse += dt;
    if (cumulative_time_lapse < REFRESHING_INTEVAL) return;

    cumulative_time_lapse -= 1;

    board_transform(board, CELL_GRASS, CELL_FIRE, GRASS_IGNITE_RATE);
    board_transform(board, CELL_FIRE, CELL_EMPTY, FIRE_EXTINGUISHMENT_RATE);
    board_transform(board, CELL_EMPTY, CELL_GRASS, GRASS_SPAWN_RATE);
}

void board_stats(board *board) {
    int water_count = 0;
    int grass_count = 0;
    int fire_count  = 0;

    for (int i = 0; i < board->row; i++) {
        for (int j = 0; j < board->col; j++) {
            switch (board->cells[i * BOARD_WIDTH + j].type) {
            case CELL_WATER:
                water_count += 1;
                break;
            case CELL_EMPTY:
                break;
            case CELL_GRASS:
                grass_count += 1;
                break;
            case CELL_FIRE:
                fire_count += 1;
                break;
            }
        }
    }

    printf("board row = %d, col = %d\n", board->row, board->col);
    printf("water: %d, grass: %d\n, fire: %d", water_count, grass_count, fire_count);
}

void board_free(board *board) {
    free(board->cells);
    free(board);
}

cell_list *board_cell_next(board *board, int cell_row, int cell_col) {
    int is_top, is_button, is_leftmost, is_rightmost;
    is_top       = cell_row == 0;
    is_button    = cell_row == BOARD_HEIGHT - 1;
    is_leftmost  = cell_col == 0;
    is_rightmost = cell_col == BOARD_WIDTH - 1;

    int neighbors = 8;
    switch (is_top + is_button + is_leftmost + is_rightmost) {
    case 0:
        neighbors = 8;
        break;
    case 1:
        neighbors = 5;
        break;
    case 2:
        if ((is_top && is_button) || (is_leftmost && is_rightmost)) {
            neighbors = 2;
        } else {
            neighbors = 3;
        }
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
    if (!is_top && !is_leftmost) {
        ret->indices[index++] = (cell_row - 1) * BOARD_WIDTH + cell_col - 1;
    }
    if (!is_top) {
        ret->indices[index++] = (cell_row - 1) * BOARD_WIDTH + cell_col + 0;
    }
    if (!is_top && !is_rightmost) {
        ret->indices[index++] = (cell_row - 1) * BOARD_WIDTH + cell_col + 1;
    }
    if (!is_leftmost) {
        ret->indices[index++] = (cell_row + 0) * BOARD_WIDTH + cell_col - 1;
    }
    if (!is_rightmost) {
        ret->indices[index++] = (cell_row + 0) * BOARD_WIDTH + cell_col + 1;
    }
    if (!is_leftmost && !is_button) {
        ret->indices[index++] = (cell_row + 1) * BOARD_WIDTH + cell_col - 1;
    }
    if (!is_button) {
        ret->indices[index++] = (cell_row + 1) * BOARD_WIDTH + cell_col + 0;
    }
    if (!is_rightmost && !is_button) {
        ret->indices[index++] = (cell_row + 1) * BOARD_WIDTH + cell_col + 1;
    }

    return ret;
}

void cell_list_free(cell_list *cell_list) {
    free(cell_list->indices);
    free(cell_list);
}
