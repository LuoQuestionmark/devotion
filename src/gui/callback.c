#include "gui/callback.h"
#include "config.h"

static intervention_castor castor = { .intervention_id = -1 };

void mouse_callback(SDL_Event event) {
    SDL_MouseButtonEvent button_event = event.button;
    if (button_event.button != 1) return; // only left click is processed for now

    if (button_event.x >= 0 && button_event.x < BOARD_EDGE_LEN * BOARD_WIDTH) {
        // within map
        int x_coord, y_coord;
        x_coord = button_event.x / BOARD_EDGE_LEN;
        y_coord = button_event.y / BOARD_EDGE_LEN;

        if (castor.intervention_id == -1) return;

        printf("intervene id %d at map %d %d\n", castor.intervention_id, x_coord, y_coord);
        castor.intervention_id = -1;
    } else if (button_event.y >= 0 && button_event.y < TITLE_HEIGHT) {
        // within title
        puts("title");
    } else {
        // within intervention selection
        int id = (button_event.y - GOD_INTERVENTION_HEIGHT_SHIFT) / GOD_INTERVENTION_UNITY_HEIGHT;
        if (castor.intervention_id == id) {
            // double selection, cancel
            castor.intervention_id = -1;
        } else {
            // select
            castor.intervention_id = id;
        }
    }
}
