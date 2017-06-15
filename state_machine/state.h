#pragma once

#include <stdlib.h>
#include <stdbool.h>

#define NULL_STATE -1
#define ALPHABET_SIZE 96 // support only ASCII text symbols (from 32 to 127)

typedef int STATE_ID;
typedef struct {
  STATE_ID id; //redundant
  bool final;
  int transitions[ALPHABET_SIZE];
  STATE_ID parent_state;
  STATE_ID fall_state;
} state_t;


void initialize_state(state_t* state, STATE_ID id);
void connect_states(state_t* from, char symbol, STATE_ID target_state_id);
void set_final(state_t* state);
int index_of(char symbol);
