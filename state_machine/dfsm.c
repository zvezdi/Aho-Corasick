#include "dfsm.h"

void initialize_dfsm(dfsm_t* dfsm){
  dfsm->initial_state = 0;
  dfsm->size = 0;
  dfsm->max_size = 2;
  dfsm->states = malloc(dfsm->max_size * sizeof(state_t));
}

STATE_ID free_id(dfsm_t* dfsm){
  return dfsm->size;
}

STATE_ID insert_state(dfsm_t* dfsm){
  if(dfsm->size >= dfsm->max_size){
    dfsm->max_size = 2 * dfsm->size;
    dfsm->states = realloc(dfsm->states, dfsm->max_size * sizeof(state_t));
  }

  STATE_ID state_id = free_id(dfsm);
  initialize_state(&dfsm->states[state_id], state_id);
  dfsm->size = dfsm->size + 1;

  return state_id;
}

void add_transition(dfsm_t* dfsm, int from_state_id, char symbol, int to_state_id){
  connect(&dfsm->states[from_state_id], symbol, to_state_id);
}
