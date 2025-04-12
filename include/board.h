#ifndef BOARD_H
#define BOARD_H

#include "olive.c"
#include <stdint.h>

#define EDGE_LEN 50
#define BOARD_HEIGHT 10
#define BOARD_WIDTH 10

#define REFRESHING_INTEVAL 1.0

// ABGR
#define GREEN 0xFF73D900
#define LIGHT_BLUE 0xFFE6FFBF

struct cell {
    uint16_t data;
};
typedef struct cell cell;

struct board {
    cell *cells;
    uint8_t row;
    uint8_t col;
};
typedef struct board board;

board *init_board();
void board_init_env(board *board);
void board_update(board *board, float dt);
void draw_board(Olivec_Canvas canvas, board *board);

#endif
