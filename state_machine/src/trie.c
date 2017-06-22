#include "trie.h"

void create_transitions_for(dfsm_t* trie, char* word);

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
