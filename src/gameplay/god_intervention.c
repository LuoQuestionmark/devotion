#include "gameplay/god_intervention.h"
#include <assert.h>
#include <stdlib.h>

intervention_list *init_intervention_list() {
    intervention_list *list = calloc(1, sizeof(intervention_list));
    return list;
}

void intervention_list_add(intervention_list *table, int id) {
    uint32_t intervention = (1 << id);
    table->available |= intervention;
}

void intervention_list_rm(intervention_list *table, int id) {
    uint32_t intervention = (1 << id);
    uint32_t mask         = ~intervention;
    table->available &= intervention;
}

void intervention_intervene(intervention_list *list, int id, board *bd, game_event_list events,
                            int row, int col, time_t timestamp) {
    assert(list != NULL);
    assert(id < INTERVENTION_MAX_COUNT);

    uint32_t intervention = (1 << id);

    // if unavailable, return
    if ((list->available & intervention) == 0) return;
    if (intervention_table[id].callback == NULL) return;

    intervention_table[id].callback(bd, events, row, col, timestamp);
}

void intervention_list_free(intervention_list *list) {
    assert(list != NULL);
    free(list);
}
