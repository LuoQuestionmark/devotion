#ifndef DEVOTION_H
#define DEVOTION_H

#include "gameplay/board.h"
#include "gameplay/elements/amant.h"
#include "gameplay/god_intervention.h"
#include "gameplay/title.h"

struct game_data {
    board *board;
    title *title;
    intervention_list *intervention_list;
    amant_list amant_list;
};
typedef struct game_data game_data;

#endif
