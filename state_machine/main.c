#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define ALPHABET_SIZE 256

typedef struct {
  int state;
  int symbol;
} transition_t;

void set_transition(transition_t* transition, char symbol, int target_state_id){
  transition->symbol = symbol;
  transition->state = target_state_id;
}
//*******************************************************************

typedef struct {
  int id;
  bool final;
  transition_t transitions[ALPHABET_SIZE];
} state_t;

void go_to(state_t* current_state, char symbol, int target_state_id){
  set_transition(&current_state->transitions[symbol], symbol, target_state_id);
}

void initialize_state(state_t* state, int id){
  state->id = id;
  state->final = false;

  transition_t null_transition = {-1,-1};

  for(int i = 0; i < ALPHABET_SIZE; i++){
    state->transitions[i] = null_transition;
  }
}

//*******************************************************************

typedef struct {
   int  initial_state;
   int size;
   int max_size;
   state_t* states;
  //  char* alphabet;
} finate_state_machine_t;

void initialize_fsm(finate_state_machine_t* fsm){
  fsm->initial_state = 0;
  fsm->size = 0;
  fsm->max_size = 2;
  fsm->states = malloc(fsm->max_size * sizeof(state_t));
}

int free_id(finate_state_machine_t* fsm){
  return fsm->size;
}

int insert_state(finate_state_machine_t* fsm){
  if(fsm->size >= fsm->max_size){
    fsm->max_size = 2 * fsm->size;
    fsm->states = realloc(fsm->states, fsm->max_size * sizeof(state_t));
  }

  int state_id = free_id(fsm);
  initialize_state(&fsm->states[fsm->size], state_id);
  fsm->size = fsm->size + 1;

  return state_id;
}

void add_transition(finate_state_machine_t* fsm, int from_state_id, char symbol, int to_state_id){
  go_to(&fsm->states[from_state_id], symbol, to_state_id);
}

int main(){
  finate_state_machine_t fsm;
  initialize_fsm(&fsm);
  int state_id = insert_state(&fsm);
  int state_id2 = insert_state(&fsm);
  add_transition(&fsm, state_id, 'a', state_id2);
  print(&fsm);
  return 0;
}
