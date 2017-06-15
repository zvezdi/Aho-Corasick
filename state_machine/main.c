#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "state.h"
#include "dfsm.h"
#include "trie.h"

int main() {
  dfsm_t trie;
  initialize_trie("test_dict.txt", &trie);
  state_t state0 = trie.states[0];
  state_t state1 = trie.states[1];
  state_t state2 = trie.states[2];
  state_t state3 = trie.states[3];
  state_t state4 = trie.states[4];
  return 0;
}
