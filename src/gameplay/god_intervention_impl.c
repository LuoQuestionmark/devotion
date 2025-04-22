#include "gameplay/god_intervention_impl.h"
#include "config.h"
#include "devotion.h"
#include "gameplay/game_event.h"
#include <stdio.h>
#include <stdlib.h>

int intervene_test(board *bd, game_event_list events, int row, int col, time_t timestamp) {
    puts("cast test intervention");
    return 0;
}

static void rain_stop(void *data) {
    board *board = ((game_data *)data)->board;
    rain_map_reset(board->rain_map);
}

static void feast_stop(void *data) {
    board *board = ((game_data *)data)->board;
    food_map_reset(board->food_map);
}

int small_rain(board *bd, game_event_list events, int row, int col, time_t timestamp) {
    // game_event_list list = ((game_data *)data)->events;
    rain_map_reset(bd->rain_map);
    rain_map_set_hot_point(bd->rain_map, row, col, (RAND_MAX * 0.7), 2);

    game_event_list_add(events, rain_stop, 10);
    return 0;
}

int big_rain(board *bd, game_event_list events, int row, int col, time_t timestamp) {
    // game_event_list list = ((game_data *)data)->events;
    rain_map_reset(bd->rain_map);
    rain_map_set_hot_point(bd->rain_map, row, col, (RAND_MAX * 0.7), 3);

    game_event_list_add(events, rain_stop, 10);
    return 0;
}

int small_feast(board *bd, game_event_list events, int row, int col, time_t timestamp) {
    food_map_reset(bd->food_map);
    food_map_set_hot_point(bd->food_map, row, col, (RAND_MAX * 0.7), 3);

    game_event_list_add(events, feast_stop, 10);
    return 0;
}

int build_temple(board *bd, game_event_list events, int row, int col, time_t timestamp) {
    printf("build temple at row %d col %d", row, col);
    bd->cells[row * BOARD_HEIGHT + col].type = CELL_UNFINISH_TEMPLE;
    bd->temple_to_build++;
    return 0;
}
