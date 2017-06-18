#include "dfsm.h"

void initialize_dfsm(dfsm_t* dfsm) {
  dfsm->max_size = 2;
  dfsm->states = malloc(dfsm->max_size * sizeof(state_t));
  initialize_state(&(dfsm->states[0]), 0);
  dfsm->initial_state = 0;
  dfsm->size = 1;
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

void set_parent(dfsm_t* dfsm, STATE_ID state, STATE_ID parent_state) {
  dfsm->states[state].parent_state = parent_state;
}

void add_transition(dfsm_t* dfsm, STATE_ID from, char symbol, STATE_ID to) {
  if (state_exists(dfsm, from) && state_exists(dfsm, to)) {
    connect_states(&dfsm->states[from], symbol, to);
    set_back_transition(&dfsm->states[to], symbol);
  }
}

bool state_exists(dfsm_t* dfsm, STATE_ID state_id){
  return state_id < dfsm->size;
}

bool transition_exists(dfsm_t* dfsm, STATE_ID from, char symbol){
  return dfsm->states[from].transitions[index_of(symbol)] != NULL_STATE;
}

STATE_ID transit(dfsm_t* dfsm, STATE_ID from, char symbol) {
  return dfsm->states[from].transitions[index_of(symbol)];
}

queue_t* children_states(dfsm_t* dfsm, STATE_ID state){
  queue_t* queue;
  initialize_queue(queue);

  if (!state_exists(dfsm, state))
    return queue;

  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (dfsm->states[state].transitions[i] != NULL_STATE) {
      STATE_ID child = dfsm->states[state].transitions[i];
      enqueue(queue, child);
    }
  }
  return queue;
}

void print(dfsm_t* dfsm, char* path_to_file) {
  FILE *f = fopen(path_to_file, "w");
  if (f == NULL)
  {
      printf("Error opening file!\n");
      exit(1);
  }

  fprintf(f, "digraph dfsa {\n");
  for(int i = 0; i < dfsm->size; i++) {
    state_t state = dfsm->states[i];
    if (state.final) {
      fprintf(f, "%d [style=filled, color=\"0.1 0.8 0.8\"];\n", state.id);
    }
    for(int j = 0; j < ALPHABET_SIZE; j++) {
      if (state.transitions[j] != NULL_STATE) {
        fprintf(f, "%d -> %d [label=\"%c\"];\n", state.id, state.transitions[j], (char) j + 32);
      }
    }
  }
  // 1 -> 3 [label="a"];
  fprintf(f, "}");
  fclose(f);
}

//----------kind of private---------

STATE_ID next_free_id(dfsm_t* dfsm){
  return dfsm->size;
}
