#ifndef AMANT_H
#define AMANT_H

/**
 * amant is the name of the creature that interact with the world
 * for now, it can:
 * - consume water & food
 * - reproduce itself
 * - die
 * the number of amants change the power of god
 */

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
    int life_cycle;
    int future_step_index;
    board_coord *future_steps;
};
typedef struct amant amant;

typedef amant **amant_list;

amant_list init_amant_list();
bool amant_list_add(amant_list list, short row, short col);
int amant_list_count(amant_list list);
void amant_list_free(amant_list list);

bool amant_evolve(board *board, amant_list list, amant *amant);
void amant_list_evolve(board *board, amant_list list);
void amant_free(amant *amant);

#endif
