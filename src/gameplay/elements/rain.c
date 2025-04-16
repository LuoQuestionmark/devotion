#include "gameplay/elements/rain.h"
#include "config.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

rain_map *init_rain_map() {
    rain_map *ret = calloc(1, sizeof(rain_map));
    ret->map      = calloc(BOARD_HEIGHT * BOARD_WIDTH, sizeof(int));
    return ret;
}

void rain_map_reset(rain_map *map) {
    assert(map != NULL);
    memset(map->map, 0, sizeof(int) * BOARD_WIDTH * BOARD_HEIGHT);
}

void rain_map_set_hot_point(rain_map *map, int row, int col, int value, int radius) {
    assert(row < BOARD_HEIGHT);
    assert(col < BOARD_WIDTH);

    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            int dist_square = abs(i - row) * abs(i - row) + abs(j - col) * abs(j - col);
            if (dist_square < radius * radius) {
                map->map[i * BOARD_WIDTH + j] = value;
            }
        }
    }
}

void rain_map_free(rain_map *map) {
    assert(map != NULL);
    free(map->map);
    free(map);
}
