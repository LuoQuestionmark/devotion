
#ifndef GOD_INTERVENTION_IMPL_H
#define GOD_INTERVENTION_IMPL_H

#include "gameplay/board.h"
#include "gameplay/game_event.h"
#include <time.h>

// int (*callback)(board *bd, int row, int col, time_t timestamp);
int intervene_test(board *bd, game_event_list events, int row, int col, time_t timestamp);
int small_rain(board *bd, game_event_list events, int row, int col, time_t timestamp);
int big_rain(board *bd, game_event_list events, int row, int col, time_t timestamp);

#endif
