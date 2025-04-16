#include "gameplay/god_intervention_impl.h"
#include <stdio.h>
#include <stdlib.h>

int intervene_test(board *bd, int row, int col, time_t timestamp) {
    puts("cast test intervention");
    return 0;
}

int small_rain(board *bd, int row, int col, time_t timestamp) {
    rain_map_reset(bd->rain_map);
    rain_map_set_hot_point(bd->rain_map, row, col, (RAND_MAX * 0.7), 2);
    return 0;
}
