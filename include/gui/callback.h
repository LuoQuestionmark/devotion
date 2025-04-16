#ifndef CALLBACK_H
#define CALLBACK_H

#include "devotion.h"
#include <SDL2/SDL.h>

struct intervention_castor {
    int intervention_index;
};
typedef struct intervention_castor intervention_castor;

void mouse_callback(SDL_Event event, game_data *const data);

#endif
