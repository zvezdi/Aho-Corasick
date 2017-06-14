#include "state.h"

void new_state(state_t* state, int id){
  state->id = id;
  state->final = false;
  // make sure we have correct default data in transitions
  for(int i = 0; i < ALPHABET_SIZE; i++){
    state->transitions[i] = NULL_STATE;
  }
}

void connect_states(state_t* from_state, char symbol, STATE_ID target_state_id){
  from_state->transitions[symbol] = target_state_id;
}

void set_final(state_t* state){
  state->final = true;
}
