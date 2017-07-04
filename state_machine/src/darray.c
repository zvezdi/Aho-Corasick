#include "darray.h"

void darray_resize(darray_t* darray);
void darray_initialize(darray_t* darray);

darray_t* darray_new() {
  darray_t* tmp = malloc(sizeof(darray_t));
  darray_initialize(tmp);
  return tmp;
}

void darray_add(darray_t* darray, int state_id) {
  if (darray->size >= darray->capacity)
    darray_resize(darray);
  
  darray->data[darray->size] = state_id;
  darray->size += 1;
}

void darray_destroy(darray_t* darray) {
  free(darray->data);
  free(darray);
}

// ---kind-of-private
void darray_initialize(darray_t* darray) {
  darray->size = 0;
  darray->capacity = 2;
  darray->data = malloc(darray->capacity * sizeof(int));
}

void darray_resize(darray_t* darray){
  darray->capacity *= 2;
  darray->data = realloc(darray->data, darray->capacity * sizeof(int));
}
