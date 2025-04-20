#ifndef ELEMENT_RAIN
#define ELEMENT_RAIN

#include "gameplay/elements/common.h"

typedef map rain_map;

rain_map *init_rain_map();
void rain_map_reset(rain_map *map);
void rain_map_set_hot_point(rain_map *map, int row, int col, int value, int radius);
void rain_map_free(rain_map *map);

#endif
