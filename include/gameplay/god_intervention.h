#ifndef GOD_INTERVENTION_H
#define GOD_INTERVENTION_H

#include "gameplay/board.h"
#include <stdbool.h>
#include <stddef.h>
#include <time.h>

#define INTERVENTION_MAX_COUNT 32

struct intervention {
    int id;
    char *name;
    char *description;
    int (*callback)(board *bd, int row, int col, time_t timestamp);
};
typedef struct intervention intervention;

static const intervention intervention_table[INTERVENTION_MAX_COUNT] = {
    { .id = 0, .name = "intervention 1", .description = "description 1", .callback = NULL },
    { .id = 1, .name = "intervention 2", .description = "description 2", .callback = NULL },
    { .id = 2, .name = "intervention 3", .description = "description 3", .callback = NULL },
    { .id = 3, .name = "intervention 4", .description = "description 4", .callback = NULL },
    { .id = 4, .name = "intervention 5", .description = "description 5", .callback = NULL },
    { .id = 5, .name = "intervention 6", .description = "description 6", .callback = NULL },
};

struct intervention_list {
    uint32_t available;
};
typedef struct intervention_list intervention_list;

intervention_list *init_intervention_list();
void intervention_list_add(intervention_list *list, int id);
void intervention_list_rm(intervention_list *list, int id);
void intervention_intervene(intervention_list *list, int id, board *bd, int row, int col,
                            time_t timestamp);
void intervention_list_free(intervention_list *list);

#endif
