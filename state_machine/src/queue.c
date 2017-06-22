#include "queue.h"

void resize_queue(queue_t* queue);

queue_t* new_queue(){
  queue_t* tmp = malloc(sizeof(queue_t));
  initialize_queue(tmp);
  return tmp;
}

void initialize_queue(queue_t* queue) {
  queue->size = 0;
  queue->capacity = 2;
  queue->first = 0;
  queue->last = 0;
  queue->data = malloc(queue->capacity * sizeof(STATE_ID));
}

void destroy_queue(queue_t* queue) {
  free(queue->data);
  free(queue);
}

void enqueue(queue_t* queue, STATE_ID state) {
  if (queue->size >= queue->capacity)
    resize_queue(queue);

  // when size is 0 first and last point to the same empty box and it's usable
  if (! empty_queue(queue))
    queue->last = queue->last + 1;

  if (queue->last >= queue->capacity)
    // when end is reached circule to the beggining of the array
    queue->last = queue->last % queue->capacity;

  queue->data[queue->last] = state;
  queue->size = queue->size + 1;
}

STATE_ID dequeue(queue_t* queue) {
  if (empty_queue(queue))
    return NULL_STATE;

  if (queue->first == queue->last) {
    queue->size = queue->size - 1;
    return queue->data[queue->first];
  }

  int first_element_index = queue->first;
  queue->first = (queue->first + 1) % queue->capacity;
  queue->size = queue->size - 1;
  return queue->data[first_element_index];
}

bool empty_queue(queue_t* queue) {
  return queue->size == 0;
}

void concatinate_queues(queue_t* base_queue, queue_t* newcommers) {
  while(!empty_queue(newcommers)) {
    STATE_ID newcome = dequeue(newcommers);
    enqueue(base_queue, newcome);
  }
}


//--------kind of private-----------

void resize_queue(queue_t* queue) {
  queue->capacity = 2 * queue->capacity;
  // reallocate place for the data array
  // and allign the queue starting point index with the beggining of the new array
  STATE_ID* new_data = malloc(queue->capacity * sizeof(STATE_ID));
  int index_in_the_circular_buffer;
  for (int i = 0; i < queue->size; i++) {
    index_in_the_circular_buffer = (i + queue->first) % queue->size;
    new_data[i] = queue->data[index_in_the_circular_buffer];
  }
  free(queue->data);
  queue->data = new_data;
  // make sure the structure stays correct
  queue->first = 0;
  queue->last = queue->size - 1; //because it's an index
}
