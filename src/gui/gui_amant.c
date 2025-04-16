#include "gui/gui_amant.h"
#include "config.h"
#include <assert.h>

void draw_amants(Olivec_Canvas canvas, amant_list list) {
    assert(list != NULL);

    for (int i = 0; i < AMANT_LIST_SIZE; i++) {
        if (list[i] == NULL) continue;
        amant *amt = list[i];

        olivec_rect(canvas, amt->col * BOARD_EDGE_LEN, amt->row * BOARD_EDGE_LEN, BOARD_EDGE_LEN,
                    BOARD_EDGE_LEN, AMANT_COLOR);
    }
}
