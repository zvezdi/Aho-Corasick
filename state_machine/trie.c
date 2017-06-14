#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "trie.h"

void delta_transitions(dfsm_t* trie, char* word){
  for(int i = 0; word[i] != 0; i++){
      if(word[i] == '\n')
        break;
    printf("%c", word[i]);
  }
}

void new_trie(char* path_to_dictionary, dfsm_t* trie){
  {
    FILE * fp;
    char * word = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(path_to_dictionary, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&word, &len, fp)) != -1) {
        delta_transitions(trie, word);
    }

    fclose(fp);
    if (word)
        free(word);
    exit(EXIT_SUCCESS);
}
}
