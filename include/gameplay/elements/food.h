#ifndef FOOD_H
#define FOOD_H

#include "gameplay/elements/common.h"

typedef map food_map;

food_map *init_food_map();
void food_map_reset(food_map *map);
void food_map_set_hot_point(food_map *map, int row, int col, int value, int radius);
void food_map_free(food_map *map);

#endif
