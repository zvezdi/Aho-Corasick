#pragma once

#include "state.h"

typedef struct {
  STATE_ID* data;
  int size;
  int capacity;
  int first;
  int last;
} queue_t;

void push(queue_t* queue, STATE_ID state);
STATE_ID pop(queue_t* queue);

//private
void resize(queue_t* queue);
bool empty(queue_t* queue);
