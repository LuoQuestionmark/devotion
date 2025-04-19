#include "gameplay/player.h"
#include <stdio.h>

player *init_player() {
    player *ret = calloc(1, sizeof(player));
    return ret;
}

void player_update(player *player, board *board, title *title, intervention_list *interventions,
                   amant_list amants) {
    static int last_update_count = -1;

    int amant_count = amant_list_count(amants);
    if (amant_count == last_update_count) {
        return;
    } else {
        last_update_count = amant_count;
    }

    if (amant_count >= 4) {
        title_add_prefix(title, 10);
        intervention_list_rm(interventions, 0);
        intervention_list_add(interventions, 1);
    }
}

void player_free(player *player) {
    free(player);
}
