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
    int (*callback)(board *bd, int row, int col, time_t timestamp);
};
typedef struct intervention intervention;

static const intervention intervention_table[INTERVENTION_MAX_COUNT] = {
    { .id = 0, .name = "INTERVENTION 1", .callback = NULL },
    { .id = 1, .name = "INTERVENTION 2", .callback = NULL },
    { .id = 2, .name = "INTERVENTION 3", .callback = NULL },
    { .id = 3, .name = "INTERVENTION 4", .callback = NULL },
    { .id = 4, .name = "INTERVENTION 5", .callback = NULL },
    { .id = 5, .name = "INTERVENTION 6", .callback = NULL },
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
