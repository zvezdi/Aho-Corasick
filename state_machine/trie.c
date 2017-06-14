#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "trie.h"

void delta_transitions(dfsm_t* trie, char* word) {
  STATE_ID start = trie->initial_state;
  for (int i = 0; word[i] != 0; i++) {
    if (word[i] == '\n') // || !in_alphabet(word[i])
      break;
    if (!transition_exists(trie, start, word[i])) {
      STATE_ID end = insert_state(trie);
      add_transition(trie, start, word[i], end);
    }
    start = transit(trie, start, word[i]);
  }
}

void initialize_trie(char* path_to_dictionary, dfsm_t* trie) {
  initialize_dfsm(trie);
  FILE* file_pointer;
  char* word = NULL;
  size_t word_length = 0;
  ssize_t read_symbols;

  file_pointer = fopen(path_to_dictionary, "r");
  if (file_pointer == NULL)
      exit(EXIT_FAILURE);

  while ((read_symbols = getline(&word, &word_length, file_pointer)) != -1) {
      delta_transitions(trie, word);
  }

  fclose(file_pointer);
  if (word)
      free(word);
}
