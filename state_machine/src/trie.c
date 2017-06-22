#include "trie.h"

void create_transitions_for(dfsm_t* trie, char* word);
STATE_ID find_fall_state(dfsm_t* trie, STATE_ID state);

dfsm_t* build_trie(char* path_to_dictionary) {
  // fill the trie to recognize the words from the dictionary
  FILE* file_pointer;
  char* word = NULL;
  size_t word_length = 0;
  ssize_t read_symbols;

  file_pointer = fopen(path_to_dictionary, "r");
  if (!file_pointer)
    exit(EXIT_FAILURE);

  dfsm_t* trie = new_dfsm();
  while ((read_symbols = getline(&word, &word_length, file_pointer)) != -1) {
    create_transitions_for(trie, word);
  }

  fclose(file_pointer);
  free(word);
  
  return trie;
}

void compute_fail_function(dfsm_t* trie) {
  // root fails to itself
  trie->states[trie->initial_state].fall_state = trie->initial_state;

  queue_t states_to_process;
  initialize_queue(&states_to_process);
  enqueue(&states_to_process, trie->initial_state);
  
  // find fall state iteratively using bfs to traverse the trie
  while (!empty_queue(&states_to_process)) {
    STATE_ID current_state = dequeue(&states_to_process);
    queue_t* children = children_states(trie, current_state);
    concatinate_queues(&states_to_process, children);
    destroy_queue(children);
    STATE_ID fall_state = find_fall_state(trie, current_state);
    print_queue(&states_to_process);
    set_fall_state(&(trie->states[current_state]), fall_state);
  }
}

//------kind of private--------

void create_transitions_for(dfsm_t* trie, char* word) {
  STATE_ID start = trie->initial_state;
  for (int i = 0; word[i] != 0; i++) {
    if (word[i] == '\n') // || !in_alphabet(word[i])
      break;
    if (!transition_exists(trie, start, word[i])) {
      STATE_ID end = insert_state(trie);
      set_parent(trie, end, start);
      add_transition(trie, start, word[i], end);
      if (word[i+1] == '\n')
        set_final(&trie->states[end]);
    }
    start = transit(trie, start, word[i]);
  }
}

STATE_ID find_fall_state(dfsm_t* trie, STATE_ID state) {
  STATE_ID parent = trie->states[state].parent_state;
  if (state == trie->initial_state || parent == trie->initial_state)
    return trie->initial_state;
  
  char backwords_symbol = trie->states[state].backwords_symbol;
  STATE_ID fallback = trie->states[parent].fall_state;

  while (true) {
    // this will terminate eather when the longest sufix that is prefix of a word from L is found
    // or when we fall back to the initial_state (finate number of steps)
    if (transition_exists(trie, fallback, backwords_symbol))
      return transit(trie, fallback, backwords_symbol);
    
    if (fallback == trie->initial_state)
      return trie->initial_state;

    fallback = trie->states[fallback].fall_state;  
  }
}