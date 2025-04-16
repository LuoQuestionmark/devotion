#include "gui/callback.h"
#include "config.h"
#include "gameplay/board.h"

static intervention_castor castor = { .intervention_index = -1 };

static void intervention_intervene_by_index(intervention_list *list, int index, board *board,
                                            int row, int col, time_t timestamp) {
    for (int id = 0; id < INTERVENTION_MAX_COUNT; id++) {
        int ivt = (1 << id);
        if ((list->available & ivt) == 0) continue;

        index -= 1;
        if (index >= 0) continue;

        intervention next_intervention = intervention_table[id];
        intervention_intervene(list, id, board, row, col, timestamp);
    }
}

void mouse_callback(SDL_Event event, board *board, intervention_list *list) {
    SDL_MouseButtonEvent button_event = event.button;
    if (button_event.button != 1) return; // only left click is processed for now

    if (button_event.x >= 0 && button_event.x < BOARD_EDGE_LEN * BOARD_WIDTH) {
        // within map
        int x_coord, y_coord;
        x_coord = button_event.x / BOARD_EDGE_LEN;
        y_coord = button_event.y / BOARD_EDGE_LEN;

        if (castor.intervention_index == -1) return;

        // printf("intervene index %d at map %d %d\n", castor.intervention_index, x_coord, y_coord);
        intervention_intervene_by_index(list, castor.intervention_index, board, x_coord, y_coord,
                                        time(NULL));
        castor.intervention_index = -1;
    } else if (button_event.y >= 0 && button_event.y < TITLE_HEIGHT) {
        // within title
        puts("title");
    } else {
        // within intervention selection
        int id = (button_event.y - GOD_INTERVENTION_HEIGHT_SHIFT) / GOD_INTERVENTION_UNITY_HEIGHT;
        if (castor.intervention_index == id) {
            // double selection, cancel
            castor.intervention_index = -1;
        } else {
            // select
            castor.intervention_index = id;
        }
    }
}
