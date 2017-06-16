#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "state.h"
#include "dfsm.h"
#include "trie.h"
#include "queue.h"

int main() {
  dfsm_t trie;
  initialize_trie("test_dict.txt", &trie);
  state_t state0 = trie.states[0];
  state_t state1 = trie.states[1];
  state_t state2 = trie.states[2];
  state_t state3 = trie.states[3];
  state_t state4 = trie.states[4];
  queue_t queue;
  initialize_queue(&queue);
  push(&queue, 3);
  push(&queue, 5);
  push(&queue, 7);
  int a = pop(&queue);
  push(&queue, 9);
  push(&queue, 11);
  push(&queue, 13);
  int b = pop(&queue);
  int c = pop(&queue);
  return 0;
}
