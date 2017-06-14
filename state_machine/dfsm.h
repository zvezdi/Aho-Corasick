#pragma once

#include "state.h"

typedef struct {
   STATE_ID initial_state;
   int size;
   int max_size;
   state_t* states;
} dfsm_t;

void initialize_dfsm(dfsm_t* dfsm);
STATE_ID insert_state(dfsm_t* dfsm);
void add_transition(dfsm_t*dfsm, STATE_ID from, char symbol, STATE_ID to);
STATE_ID transit(dfsm_t* dfsm, STATE_ID from, char symbol);
// bool in_alphabet(char symbol);
bool state_exists(dfsm_t* dfsm, STATE_ID state_id);
bool transition_exists(dfsm_t* dfsm, STATE_ID from, char symbol);
STATE_ID next_free_id(dfsm_t* dfsm);
