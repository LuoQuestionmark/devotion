#ifndef AMANT_H
#define AMANT_H

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
};
typedef struct amant amant;

typedef amant **amant_list;

amant_list init_amant_list();
bool amant_list_add(amant_list list, short row, short col);
void amant_list_free(amant_list list);

void amant_evolve(amant *amant);
void amant_list_evolve(amant_list list);

#endif
