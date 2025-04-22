#include "gui/gui_board.h"
#include "config.h"
#include "olive.c"

void draw_board(Olivec_Canvas canvas, board *bd) {
    for (int i = 0; i < bd->row; i++) {
        for (int j = 0; j < bd->col; j++) {
            uint32_t color = CALAMINE_BLUE;
            switch (bd->cells[i * BOARD_WIDTH + j].type) {
            case CELL_WATER:
                color = BLUE;
                break;
            case CELL_EMPTY:
                color = CALAMINE_BLUE;
                break;
            case CELL_GRASS:
                color = GREEN;
                break;
            case CELL_FIRE:
            case CELL_BURNT:
                color = POMEGRANATE_PURPLE;
                break;
            case CELL_FOOD:
                color = CINNAMON_BUFF;
                break;
            case CELL_UNFINISH_TEMPLE:
                color = WHITE;
                break;
            case CELL_TEMPLE:
                color = EUPATORIUM_PURPLE;
                break;
            }

            olivec_rect(canvas, j * BOARD_EDGE_LEN, i * BOARD_EDGE_LEN, BOARD_EDGE_LEN,
                        BOARD_EDGE_LEN, color);
        }
    }
}
