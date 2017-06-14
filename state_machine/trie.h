#pragma once

#include "dfsm.h"

void initialize_trie(char* path_to_dictionary, dfsm_t* trie);
void delta_transitions(dfsm_t* trie, char* word);
