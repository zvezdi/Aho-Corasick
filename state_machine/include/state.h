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
  // back transition to compute fall state easier
  STATE_ID parent_state;
  char backwords_symbol;
  // to traverse not loosing already read symbols
  STATE_ID fall_state;
} state_t;

state_t* new_state(STATE_ID state_id);
void initialize_state(state_t* state, STATE_ID id);
void destory_state(state_t* state);
void connect_states(state_t* from, char symbol, STATE_ID target_state_id);
void set_back_transition(state_t* target_state, char symbol);
void set_fall_state(state_t* state, STATE_ID fall_state);
void set_final(state_t* state);
int index_of(char symbol);
char char_at_index(int index);
