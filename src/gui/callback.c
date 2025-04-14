#include "gui/callback.h"
#include "config.h"

void mouse_callback(SDL_Event event) {
    SDL_MouseButtonEvent button_event = event.button;
    if (button_event.button != 1) return; // only left click is processed for now

    if (button_event.x >= 0 && button_event.x < BOARD_EDGE_LEN * BOARD_WIDTH) {
        // within map
        int x_coord, y_coord;
        x_coord = button_event.x / BOARD_EDGE_LEN;
        y_coord = button_event.y / BOARD_EDGE_LEN;
        printf("map %d %d\n", x_coord, y_coord);
    } else if (button_event.y >= 0 && button_event.y < TITLE_HEIGHT) {
        // within title
        puts("title");
    } else {
        // within intervention selection
        int index;
        index = (button_event.y - GOD_INTERVENTION_HEIGHT_SHIFT) / GOD_INTERVENTION_UNITY_HEIGHT;
        printf("intervention %d\n", index);
    }
}
