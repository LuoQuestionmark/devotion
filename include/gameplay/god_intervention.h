#ifndef GOD_INTERVENTION_H
#define GOD_INTERVENTION_H

#include "gameplay/board.h"
#include "gameplay/game_event.h"
#include "gameplay/god_intervention_impl.h"
#include <stdbool.h>
#include <stddef.h>
#include <time.h>

#define INTERVENTION_MAX_COUNT 32

struct intervention {
    int id;
    char *name;
    char *description;
    int (*callback)(board *board, game_event_list events, int row, int col, time_t timestamp);
};
typedef struct intervention intervention;

static const intervention intervention_table[INTERVENTION_MAX_COUNT] = {
    { .id          = 0,
     .name        = "rain",
     .description = "small rain,    create waterpool",
     .callback    = small_rain                                                                            },
    { .id = 1,          .name = "tempete",        .description = "bigger rain",   .callback = big_rain    },
    { .id = 2,          .name = "feast",          .description = "create food",   .callback = small_feast },
    { .id = 3,          .name = "intervention 4", .description = "description 4", .callback = NULL        },
    { .id = 4,          .name = "intervention 5", .description = "description 5", .callback = NULL        },
    { .id = 5,          .name = "intervention 6", .description = "description 6", .callback = NULL        },
};

struct intervention_list {
    uint32_t available;
};
typedef struct intervention_list intervention_list;

intervention_list *init_intervention_list();
void intervention_list_add(intervention_list *list, int id);
void intervention_list_rm(intervention_list *list, int id);
void intervention_intervene(intervention_list *list, int id, board *bd, game_event_list events,
                            int row, int col, time_t timestamp);
void intervention_list_free(intervention_list *list);

#endif
