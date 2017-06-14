#pragma once

#include <stdlib.h>
#include <stdbool.h>

#define NULL_STATE -1
#define ALPHABET_SIZE 256 // support only ASCII symbols

typedef int STATE_ID;
typedef struct {
  int id;
  bool final;
  int transitions[ALPHABET_SIZE];
} state_t;


void connect(state_t* from, char symbol, int target_state_id);
void initialize_state(state_t* state, STATE_ID id);
void set_final(state_t* state);
