#include "gameplay/elements/food.h"
#include "config.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

food_map *init_food_map() {
    food_map *ret = calloc(1, sizeof(food_map));
    ret->map      = calloc(BOARD_HEIGHT * BOARD_WIDTH, sizeof(int));
    return ret;
}

void food_map_reset(food_map *map) {
    assert(map != NULL);
    memset(map->map, 0, sizeof(int) * BOARD_WIDTH * BOARD_HEIGHT);
}

void food_map_set_hot_point(food_map *map, int row, int col, int value, int radius) {
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

void food_map_free(food_map *map) {
    assert(map != NULL);
    free(map->map);
    free(map);
}
