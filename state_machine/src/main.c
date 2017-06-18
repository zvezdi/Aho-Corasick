#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "state.h"
#include "dfsm.h"
#include "trie.h"
#include "queue.h"

bool test_concatinate() {
  queue_t base;
  queue_t newcommers;
  initialize_queue(&base);
  initialize_queue(&newcommers);

  enqueue(&base, 1);
  enqueue(&base, 2);  
  enqueue(&base, 3);
  dequeue(&base);

  enqueue(&newcommers, 4);
  enqueue(&newcommers, 5);
  enqueue(&newcommers, 6);
  enqueue(&newcommers, 7);
  dequeue(&newcommers);

  concatinate_queues(&base, &newcommers);

  int expected_result[5];
  expected_result[0] = 2;
  expected_result[1] = 3;
  expected_result[2] = 5;
  expected_result[3] = 6;
  expected_result[4] = 7;

  if (base.size != 5)
    return false;
  for (int i = 0; i < base.size; i++) {
    if (base.data[i] != expected_result[i])
      return false;
  }

  return true;
}

int main() {
  // test_concatinate();
  dfsm_t* trie = build_trie("test_dict.txt");
//  queue_t children = children_states(trie, 10);
//  queue_t newcommers;
//  bool test = test_concatinate();
  compute_fail_function(trie);
  print(trie, "output.dot");
  return 0;
}
