#include "gui/callback.h"

void mouse_callback(SDL_Event event) {
    // puts("mouse event");
    SDL_MouseButtonEvent button_event = event.button;
    if (button_event.button != 1) return; // only left click is processed for now

    printf("mouse button %d %d \n", button_event.x, button_event.y);
}
