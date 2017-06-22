#include "fail_automat.h"

void compute_fallback_states(dfsm_t* trie);
STATE_ID find_fall_state(dfsm_t* trie, STATE_ID state);
void set_fail_transitions(dfsm_t* trie, STATE_ID current_state);

void compute_fail_function(dfsm_t* trie) {
  compute_fallback_states(trie);
  queue_t* states_to_process = new_queue();
  enqueue(states_to_process, trie->initial_state);
  while (!empty_queue(states_to_process)) {
    STATE_ID current_state = dequeue(states_to_process);
    queue_t* children = children_states(trie, current_state);
    concatinate_queues(states_to_process, children);
    destroy_queue(children);
    set_fail_transitions(trie, current_state);
  }
  destroy_queue(states_to_process);
}

//------kind of private--------

void compute_fallback_states(dfsm_t* trie) {
  // root fails to itself
  trie->states[trie->initial_state].fall_state = trie->initial_state;

  queue_t* states_to_process = new_queue();
  enqueue(states_to_process, trie->initial_state);
  
  // find fall state iteratively using bfs to traverse the trie
  while (!empty_queue(states_to_process)) {
    STATE_ID current_state = dequeue(states_to_process);
    queue_t* children = children_states(trie, current_state);
    concatinate_queues(states_to_process, children);
    destroy_queue(children);
    STATE_ID fall_state = find_fall_state(trie, current_state);
    set_fall_state(&(trie->states[current_state]), fall_state);
  }
  destroy_queue(states_to_process);
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

void set_fail_transitions(dfsm_t* trie, STATE_ID current_state) {
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (trie->states[current_state].transitions[i] != NULL_STATE) {
      continue;
    }

    char symbol = char_at_index(i);
    STATE_ID fail_state = trie->states[current_state].fall_state;
    while (! transition_exists(trie, fail_state, symbol)) {
      // mostly the length of the word times
      if (fail_state == trie->initial_state) {
        break;
      }
      fail_state = trie->states[fail_state].fall_state;
    }

    if (transition_exists(trie, fail_state, symbol)) {
      add_transition(trie, current_state, symbol, transit(trie, fail_state, symbol));
    }
    else { // this sequence was not in the landuage
      add_transition(trie, current_state, symbol, trie->initial_state);
    }
  }
}
