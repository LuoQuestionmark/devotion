#include "gameplay/elements/amant.h"
#include "config.h"
#include <assert.h>
#include <stdlib.h>

amant_list init_amant_list() {
    return calloc(AMANT_LIST_SIZE, sizeof(amant *));
}

bool amant_list_add(amant_list list, short row, short col) {
    for (int i = 0; i < AMANT_LIST_SIZE; i++) {
        if (list[i] == NULL) {
            list[i]      = calloc(1, sizeof(amant));
            list[i]->row = row;
            list[i]->col = col;
            return true;
        }
    }
    return false;
}

void amant_list_free(amant_list list) {
    for (int i = 0; i < AMANT_LIST_SIZE; i++) {
        if (list[i] == NULL) continue;
        free(list[i]);
    }
    free(list);
}

void amant_evolve(amant *amant) {
    assert(amant != NULL);
    switch (amant->state) {
    case AMANT_UNDEFINED: {
        int num = rand();
        if (num < RAND_MAX / 2) {
            amant->state = AMANT_HUNGRY;
        } else {
            amant->state = AMANT_THIRSTY;
        }
    } break;
    case AMANT_THIRSTY: {
        // TODO
    } break;
    case AMANT_HUNGRY: {
        // TODO
    } break;
    case AMANT_REPRODUCTION: {
        // TODO
    } break;
    case AMANT_DEAD: {
        free(amant);
    } break;
    }
}

void amant_list_evolve(amant_list list) {
    for (int i = 0; i < AMANT_LIST_SIZE; i++) {
        if (list[i] == NULL) continue;

        amant_evolve(list[i]);
    }
}
