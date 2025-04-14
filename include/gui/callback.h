#ifndef CALLBACK_H
#define CALLBACK_H

#include <SDL2/SDL.h>

struct intervention_castor {
    int intervention_id;
};
typedef struct intervention_castor intervention_castor;

void mouse_callback(SDL_Event event);

#endif
