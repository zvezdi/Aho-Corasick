#pragma once

#include "state.h"

typedef struct {
   STATE_ID initial_state;
   int size;
   int max_size;
   state_t* states;
} dfsm_t;

void new_dfsm(dfsm_t* dfsm);
STATE_ID insert_state(dfsm_t* dfsm);
void add_transition(dfsm_t*dfsm, STATE_ID from, char symbol, STATE_ID to);

STATE_ID free_id(dfsm_t* dfsm);
