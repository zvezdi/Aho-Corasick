#pragma once

typedef struct {
  int* data;
  int size;
  int capacity;
} darray_t;

darray_t* darray_new();
void darray_destroy();
void darray_add(darray_t* darray, int state_id);
int darray_remove(darray_t* darray, int at_index);
