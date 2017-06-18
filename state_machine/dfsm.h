#pragma once

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "state.h"
#include "queue.h"

typedef struct {
   STATE_ID initial_state;
   int size;
   int max_size;
   state_t* states;
} dfsm_t;

void initialize_dfsm(dfsm_t* dfsm);
STATE_ID insert_state(dfsm_t* dfsm);
void set_parent(dfsm_t* dfsm, STATE_ID state, STATE_ID parent_state);
void add_transition(dfsm_t*dfsm, STATE_ID from, char symbol, STATE_ID to);
bool state_exists(dfsm_t* dfsm, STATE_ID state_id);
bool transition_exists(dfsm_t* dfsm, STATE_ID from, char symbol);
STATE_ID next_free_id(dfsm_t* dfsm);
STATE_ID transit(dfsm_t* dfsm, STATE_ID from, char symbol);
queue_t children_states(dfsm_t* dfsm, STATE_ID state);
void print(dfsm_t* dfsm, char* path_to_file);
