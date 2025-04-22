#ifndef BOARD_H
#define BOARD_H

/**
 * board contains the BOARD_HEIGHT * BOARD_WIDTH size of squares,
 * each cell has its own `cell_type` that is updated at each iteration with the function
 * `board_update`
 */

#include "gameplay/elements/food.h"
#include "gameplay/elements/rain.h"
#include <stdbool.h>
#include <stdint.h>

#define REFRESHING_INTEVAL 0.1

enum cell_type {
    CELL_EMPTY = 0,
    CELL_GRASS,
    CELL_WATER,
    CELL_FIRE,
    CELL_BURNT,
    CELL_FOOD,
    CELL_UNFINISH_TEMPLE,
    CELL_TEMPLE
};

struct cell {
    enum cell_type type;
    enum cell_type last_type;
    // enum cell_creature creature;
};
typedef struct cell cell;

struct board {
    cell *cells;
    uint8_t row;
    uint8_t col;
    short temple_to_build;

    rain_map *rain_map;
    food_map *food_map;
};
typedef struct board board;

struct board_coord {
    unsigned short row;
    unsigned short col;
};
typedef struct board_coord board_coord;

struct cell_list {
    int len;
    int *indices;
};
typedef struct cell_list cell_list;

board *init_board();
void board_init_env(board *board);
void board_update(board *board, float dt);
// void board_stats(board *board);
void board_free(board *board);

void board_transform(board *board, enum cell_type src, enum cell_type tgt, float rate);
void board_transform_if_neighbor(board *board, enum cell_type src, enum cell_type tgt,
                                 enum cell_type nbr, float rate);
void board_transform_from_map(board *board, enum cell_type src, enum cell_type tgt, map *map);

void board_backup_type(board *board);

bool board_nearest_env(board *board, enum cell_type env, board_coord *src, board_coord *tgt,
                       int depth, board_coord *steps);

cell_list *board_cell_next(board *board, int cell_row, int cell_col);
void cell_list_free(cell_list *cell_list);

#endif
