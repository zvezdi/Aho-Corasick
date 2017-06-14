#include "dfsm.h"

void initialize_dfsm(dfsm_t* dfsm) {
  dfsm->initial_state = 0;
  dfsm->size = 0;
  dfsm->max_size = 2;
  dfsm->states = malloc(dfsm->max_size * sizeof(state_t));
}

STATE_ID insert_state(dfsm_t* dfsm) {
  if (dfsm->size >= dfsm->max_size) {
    dfsm->max_size = 2 * dfsm->size;
    dfsm->states = realloc(dfsm->states, dfsm->max_size * sizeof(state_t));
  }

  STATE_ID state_id = next_free_id(dfsm);
  initialize_state(&dfsm->states[state_id], state_id);
  dfsm->size = dfsm->size + 1;

  return state_id;
}

void add_transition(dfsm_t* dfsm, STATE_ID from, char symbol, STATE_ID to) {
  if (state_exists(dfsm, from) && state_exists(dfsm, to))
    connect_states(&dfsm->states[from], symbol, to);
}

STATE_ID transit(dfsm_t* dfsm, STATE_ID from, char symbol) {
  return dfsm->states[from].transitions[symbol];
}

// bool in_alphabet(char symbol){
//   return (int) symbol > 0 && (int) symbol < ALPHABET_SIZE;
// }

bool state_exists(dfsm_t* dfsm, STATE_ID state_id){
  return state_id < dfsm->size;
}

bool transition_exists(dfsm_t* dfsm, STATE_ID from, char symbol){
  return dfsm->states[from].transitions[symbol] != NULL_STATE;
}

//----------kind of private---------

STATE_ID next_free_id(dfsm_t* dfsm){
  return dfsm->size;
}
