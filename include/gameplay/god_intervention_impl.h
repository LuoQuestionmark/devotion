
#ifndef GOD_INTERVENTION_IMPL_H
#define GOD_INTERVENTION_IMPL_H

#include "gameplay/board.h"
#include <time.h>

// int (*callback)(board *bd, int row, int col, time_t timestamp);
int intervene_test(board *bd, int row, int col, time_t timestamp);

#endif
