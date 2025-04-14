#include "gui/gui_board.h"
#include "config.h"
#include "olive.c"

void draw_board(Olivec_Canvas canvas, board *bd) {
    for (int i = 0; i < bd->row; i++) {
        for (int j = 0; j < bd->col; j++) {
            uint32_t color = LIGHT_BLUE;
            switch (bd->cells[i * BOARD_WIDTH + j].type) {
            case CELL_WATER:
                color = BLUE;
                break;
            case CELL_EMPTY:
                color = LIGHT_BLUE;
                break;
            case CELL_GRASS:
                color = GREEN;
                break;
            }

            olivec_rect(canvas, i * BOARD_EDGE_LEN, j * BOARD_EDGE_LEN, BOARD_EDGE_LEN,
                        BOARD_EDGE_LEN, color);
        }
    }
}
