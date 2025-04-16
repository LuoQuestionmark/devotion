#include "gameplay/elements/amant.h"
#include "config.h"
#include "gameplay/board.h"
#include <assert.h>
#include <stdlib.h>

static void amant_thirsty(board *board, amant *amant) {
    board_coord local  = { .row = amant->row, .col = amant->col };
    board_coord target = { 0 };

    bool found = false;
    found      = board_nearest_env(board, CELL_WATER, &local, &target, BOARD_MAX_SEARCHING_DEPTH);
    if (found) {
        if (target.row > local.row) {
            amant->row += 1;
            return;
        }

        if (target.col > amant->col) {
            amant->col += 1;
            return;
        }

        if (target.row < local.row) {
            amant->row -= 1;
            return;
        }

        if (target.col < amant->col) {
            amant->col -= 1;
            return;
        }

        amant->completed_mission_count += 1;
        if (amant->completed_mission_count > AMANT_MAX_MISSION_COUNT) {
            amant->state = AMANT_REPRODUCTION;
        } else {
            amant->state = AMANT_UNDEFINED;
        }

    } else {
        // random move
        // TODO
    }
}
static void amant_hungry(board *board, amant *amant) {
    // TODO
    amant->state = AMANT_THIRSTY;
}
static void amant_reproduction(board *board, amant *amant) {}

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

void amant_evolve(board *board, amant *amant) {
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
        amant_thirsty(board, amant);
    } break;
    case AMANT_HUNGRY: {
        amant_hungry(board, amant);
    } break;
    case AMANT_REPRODUCTION: {
        amant_reproduction(board, amant);
    } break;
    case AMANT_DEAD: {
        free(amant);
    } break;
    }
}

void amant_list_evolve(board *board, amant_list list) {
    for (int i = 0; i < AMANT_LIST_SIZE; i++) {
        if (list[i] == NULL) continue;

        amant_evolve(board, list[i]);
    }
}
