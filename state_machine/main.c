#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "state.h"
#include "dfsm.h"
#include "trie.h"

int main(){
  dfsm_t dfsm;
  new_dfsm(&dfsm);
  int state_id1 = insert_state(&dfsm);
  int state_id2 = insert_state(&dfsm);
  int state_id3 = insert_state(&dfsm);
  
  add_transition(&dfsm, state_id1, 'a', state_id2);
  add_transition(&dfsm, state_id2, 'b', state_id1);
  add_transition(&dfsm, state_id1, 'c', state_id3);
  add_transition(&dfsm, state_id2, 'd', state_id3);

  state_t state1 = dfsm.states[state_id1];
  state_t state2 = dfsm.states[state_id2];
  state_t state3 = dfsm.states[state_id3];
  set_final(&state3);

  dfsm_t trie;
  new_trie("test_dict.txt", &trie);

  return 0;
}
