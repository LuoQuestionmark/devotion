#ifndef CALLBACK_H
#define CALLBACK_H

#include "gameplay/board.h"
#include "gameplay/god_intervention.h"
#include <SDL2/SDL.h>

struct intervention_castor {
    int intervention_index;
};
typedef struct intervention_castor intervention_castor;

void mouse_callback(SDL_Event event, board *board, intervention_list *list);

#endif
