#ifndef CALLBACK_H
#define CALLBACK_H

#include "gameplay/game_event.h"
#include <SDL2/SDL.h>

struct intervention_castor {
    int intervention_index;
};
typedef struct intervention_castor intervention_castor;

void mouse_callback(SDL_Event event, void *const data, game_event_list events);

#endif
