#ifndef AMANT_H
#define AMANT_H

#include "gameplay/board.h"
#include <stdbool.h>

enum amant_state {
    AMANT_UNDEFINED,
    AMANT_THIRSTY,
    AMANT_HUNGRY,
    AMANT_REPRODUCTION,
    AMANT_DEAD,
};

struct amant {
    short row;
    short col;
    enum amant_state state;
    int completed_mission_count;
    int future_step_index;
    board_coord *future_steps;
};
typedef struct amant amant;

typedef amant **amant_list;

amant_list init_amant_list();
bool amant_list_add(amant_list list, short row, short col);
void amant_list_free(amant_list list);

bool amant_evolve(board *board, amant_list list, amant *amant);
void amant_list_evolve(board *board, amant_list list);
void amant_free(amant *amant);

#endif
