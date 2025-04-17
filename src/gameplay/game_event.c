#include "gameplay/game_event.h"
#include "config.h"
#include <stdlib.h>

void game_event_free(game_event *event) {
    free(event);
}

game_event_list init_game_event_list() {
    game_event_list ret = calloc(GAME_EVENT_MAX_COUNT, sizeof(game_event *));
    return ret;
}

void game_event_list_free(game_event_list event_list) {
    for (int i = 0; i < GAME_EVENT_MAX_COUNT; i++) {
        if (event_list[i] == NULL) continue;
        free(event_list[i]);
    }
    free(event_list);
}

int game_event_list_add(game_event_list event_list, void (*callback)(void *data), int countdown) {
    for (int i = 0; i < GAME_EVENT_MAX_COUNT; i++) {
        if (event_list[i] != NULL) continue;

        // insert event
        event_list[i]            = calloc(1, sizeof(game_event));
        event_list[i]->callback  = callback;
        event_list[i]->countdown = countdown;
        return 0;
    }

    return -1;
}

void game_event_list_update(game_event_list event_list, void *data) {
    for (int i = 0; i < GAME_EVENT_MAX_COUNT; i++) {
        if (event_list[i] == NULL) continue;

        event_list[i]->countdown -= 1;
        if (event_list[i]->countdown <= 0) {
            event_list[i]->callback(data);
            game_event_free(event_list[i]);
            event_list[i] = NULL;
        }
    }
}
