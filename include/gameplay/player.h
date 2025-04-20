#ifndef PLAYER_H
#define PLAYER_H

/**
 * the player system tracks goals achieved by player.
 */

#include "gameplay/board.h"
#include "gameplay/elements/amant.h"
#include "gameplay/god_intervention.h"
#include "gameplay/title.h"

struct player_states {};
typedef struct player_states player;

player *init_player();
void player_update(player *player, board *board, title *title, intervention_list *interventions,
                   amant_list amants);
void player_free(player *player);

#endif
