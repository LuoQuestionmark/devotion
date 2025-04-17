#ifndef GAME_EVENT_H
#define GAME_EVENT_H

// #include "devotion.h"

struct game_event {
    int countdown;
    void (*callback)(void *data);
};
typedef struct game_event game_event;

typedef game_event **game_event_list;

void game_event_free(game_event *event);
game_event_list init_game_event_list();
void game_event_list_free(game_event_list event_list);
int game_event_list_add(game_event_list event_list, void (*callback)(void *data), int countdown);
void game_event_list_update(game_event_list event_list, void *data);

#endif
