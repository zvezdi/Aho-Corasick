#pragma once

#include <stdlib.h>
#include <stdbool.h>

#define NULL_STATE -1
#define ALPHABET_SIZE 96 // support only ASCII text symbols (from 32 to 127)

typedef int STATE_ID;
typedef struct {
  int id; //redundant
  bool final;
  int transitions[ALPHABET_SIZE];
} state_t;


void initialize_state(state_t* state, STATE_ID id);
void connect_states(state_t* from, char symbol, int target_state_id);
void set_final(state_t* state);
int index_of(char symbol);
