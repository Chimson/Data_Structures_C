#include <stdio.h>
#include <stdlib.h>

// fixed stack
#define ITEM_TYPE int
typedef struct {
  ITEM_TYPE *base;  // points to the beginning of the stack array
  ITEM_TYPE *top;
  int size;
} fixed_stack;

fixed_stack* create_stack(int size) {
  // allocates space for the stack fields and the array
  fixed_stack *st = (fixed_stack*) malloc(sizeof(fixed_stack));
  st->base = (ITEM_TYPE*) malloc(st->size * sizeof(ITEM_TYPE));
  st->top = st->base;
  st->size = size;
  return st;
}

int main(int argc, char **argv) {
  
  
}
