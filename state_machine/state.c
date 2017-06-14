#include "state.h"

void connect(state_t* current_state, char symbol, STATE_ID target_state_id){
  current_state->transitions[symbol] = target_state_id;
}

void initialize_state(state_t* state, int id){
  state->id = id;
  state->final = false;
  // make sure we have correct default data in transitions
  for(int i = 0; i < ALPHABET_SIZE; i++){
    state->transitions[i] = NULL_STATE;
  }
}
