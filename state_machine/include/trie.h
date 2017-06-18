#pragma once

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "dfsm.h"
#include "queue.h"
#include "state.h"

dfsm_t* build_trie(char* path_to_dictionary);
void compute_fail_function(dfsm_t* trie);

//---kind of private---

void create_transitions_for(dfsm_t* trie, char* word);
STATE_ID find_fall_state(dfsm_t* trie, STATE_ID state);
