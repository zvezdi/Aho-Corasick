#include "state.h"

state_t* new_state(STATE_ID state_id) {
  state_t* tmp = malloc(sizeof(state_t));
  initialize_state(tmp, state_id);
  return tmp;
}

void destory_state(state_t* state) {
  free(state);
}

void connect_states(state_t* from_state, char symbol, STATE_ID target_state_id) {
  from_state->transitions[index_of(symbol)] = target_state_id;
}

void set_back_transition(state_t* target_state, char symbol){
  target_state->backwords_symbol = symbol;
}

void set_fall_state(state_t* state, STATE_ID fall_state) {
  state->fall_state = fall_state;
}

void set_final(state_t* state) {
  state->final = true;
}

int index_of(char symbol) {
  // transform char to index of the transition with that symbol in the transitions array
  return (int) symbol - 32;
}

char char_at_index(int index) {
  return (char) index + 32;
}

void initialize_state(state_t* state, STATE_ID id) {
  state->id = id;
  state->final = false;
  state->parent_state = NULL_STATE;
  state->fall_state = NULL_STATE;
  // make sure we have correct default data in transitions
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    state->transitions[i] = NULL_STATE;
  }
}