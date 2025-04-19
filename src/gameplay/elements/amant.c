#include "gameplay/elements/amant.h"
#include "config.h"
#include "gameplay/board.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static void random_move(amant *amant) {
    int choice   = rand();
    const int t1 = RAND_MAX / 4;
    const int t2 = RAND_MAX / 2;
    const int t3 = RAND_MAX / 4 * 3;

    for (int i = 0; i < 4; i++) {
        if (choice < t1) {
            if (amant->row < BOARD_HEIGHT - 1) {
                amant->row++;
                break;
            } else {
                continue;
            }
        } else if (choice < t2) {
            if (amant->row > 0) {
                amant->row--;
                break;
            } else {
                continue;
            }
        } else if (choice < t3) {
            if (amant->col < BOARD_WIDTH - 1) {
                amant->col++;
                break;
            } else {
                continue;
            }
        } else {
            if (amant->col > 1) {
                amant->col--;
                break;
            } else {
                continue;
            }
        }
    }
}

static void amant_target(board *board, amant *amant, enum cell_type tgt) {
    board_coord local = { .row = amant->row, .col = amant->col };
    board_coord dst   = { 0 };

    if (board->cells[amant->row * BOARD_WIDTH + amant->col].type == tgt) {
        board->cells[amant->row * BOARD_WIDTH + amant->col].type = CELL_EMPTY;
        amant->completed_mission_count += 1;
        amant->future_step_index = -1;
        if (amant->completed_mission_count > AMANT_MAX_MISSION_COUNT) {
            amant->state = AMANT_REPRODUCTION;
        } else {
            amant->state = AMANT_UNDEFINED;
        }
        return;
    }

    if (amant->future_step_index >= 0) {
        amant->row = amant->future_steps[amant->future_step_index].row;
        amant->col = amant->future_steps[amant->future_step_index].col;

        amant->future_step_index += 1;
        if (amant->future_step_index >= AMANT_MAX_FUTURE_STEPS) {
            // finish tour
            amant->future_step_index = -1;
        }
        return;
    }

    bool found = false;
    found =
        board_nearest_env(board, tgt, &local, &dst, BOARD_MAX_SEARCHING_DEPTH, amant->future_steps);
    if (found) {
        // set movement
        amant->future_step_index = 0;
    } else {
        // random move
        random_move(amant);
    }
}

static void amant_reproduction(board *board, amant_list list, amant *amant) {
    amant_list_add(list, amant->row, amant->col);
    amant_list_add(list, amant->row, amant->col);
    amant->state = AMANT_DEAD;
}

amant_list init_amant_list() {
    return calloc(AMANT_LIST_SIZE, sizeof(amant *));
}

bool amant_list_add(amant_list list, short row, short col) {
    for (int i = 0; i < AMANT_LIST_SIZE; i++) {
        if (list[i] == NULL) {
            list[i]                    = calloc(1, sizeof(amant));
            list[i]->row               = row;
            list[i]->col               = col;
            list[i]->future_step_index = -1;
            list[i]->future_steps      = calloc(AMANT_MAX_FUTURE_STEPS, sizeof(board_coord));
            return true;
        }
    }
    return false;
}

int amant_list_count(amant_list list) {
    int ret = 0;
    for (int i = 0; i < AMANT_LIST_SIZE; i++) {
        if (list[i] != NULL) {
            ret += 1;
        }
    }
    return ret;
}

void amant_list_free(amant_list list) {
    for (int i = 0; i < AMANT_LIST_SIZE; i++) {
        if (list[i] == NULL) continue;
        amant_free(list[i]);
    }
    free(list);
}

bool amant_evolve(board *board, amant_list list, amant *amant) {
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
        amant_target(board, amant, CELL_WATER);
    } break;
    case AMANT_HUNGRY: {
        amant_target(board, amant, CELL_GRASS);
    } break;
    case AMANT_REPRODUCTION: {
        amant_reproduction(board, list, amant);
    } break;
    case AMANT_DEAD: {
        return false;
    } break;
    }
    return true;
}

void amant_list_evolve(board *board, amant_list list) {
    for (int i = 0; i < AMANT_LIST_SIZE; i++) {
        if (list[i] == NULL) continue;

        bool state = amant_evolve(board, list, list[i]);
        if (!state) {
            amant_free(list[i]);
            list[i] = NULL;
        }
    }
}

void amant_free(amant *amant) {
    free(amant->future_steps);
    free(amant);
}
