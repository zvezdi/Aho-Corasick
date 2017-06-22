#pragma once

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "state.h"

typedef struct {
  STATE_ID* data;
  int size;
  int capacity;
  int first;
  int last;
} queue_t;

queue_t* new_queue();
void destroy_queue(queue_t* queue);
void enqueue(queue_t* queue, STATE_ID state);
STATE_ID dequeue(queue_t* queue);
bool empty_queue(queue_t* queue);
void concatinate_queues(queue_t* base_queue, queue_t* newcommers);

//private
void initialize_queue(queue_t* queue);
void resize_queue(queue_t* queue);
