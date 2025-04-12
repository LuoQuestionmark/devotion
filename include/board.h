#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>

#define REFRESHING_INTEVAL 1.0

enum cell_type {
    CELL_EMPTY = 0,
    CELL_GRASS,
    CELL_WATER,
};

enum cell_creature {
    CREATURE_EMPTY = 0,
    CREATURE_AMANT,
    CREATURE_BEAST
};

struct cell {
    enum cell_type type;
    enum cell_creature creature;
};
typedef struct cell cell;

struct board {
    cell *cells;
    uint8_t row;
    uint8_t col;
};
typedef struct board board;

struct cell_list {
    int len;
    int *indices;
};
typedef struct cell_list cell_list;

board *init_board();
void board_init_env(board *board);
void board_update(board *board, float dt);
void board_stats(board *board);
void board_free(board *board);

cell_list *board_cell_next(board *board, int cell_row, int cell_col);
void cell_list_free(cell_list *cell_list);

#endif
