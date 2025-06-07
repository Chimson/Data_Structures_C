#ifndef _STACKS_C
#define _STACKS_C 1

#include <stdlib.h>
#include "stacks.h"


// allocates space for the stack fields and the array
// base is a pointer to the first byte of the stack
// top is a pointer to the byte just after any element in the stack
//   like right at the first byte to insert a new item in the stack
// size is the initial memory size, not current size, so it should
//   never update
fixed_stack* create_fixed_stack(int size) {
  fixed_stack *st = (fixed_stack*) malloc(sizeof(fixed_stack));
  st->base = (ITEM_TYPE*) malloc(st->size * sizeof(ITEM_TYPE));
  st->top = st->base;
  st->size = size;
  
  // set the function pointers
  st->is_empty = fs_empty;
  st->push = fs_push;
  st->pop = fs_pop;
  st->peek = fs_peek;
  st->remove = fs_remove;
  return st;
}

// when the pointers haven't moved
int fs_empty(fixed_stack* fs) {
  return fs->base == fs->top;
}

int fs_push(fixed_stack* fs, ITEM_TYPE x) {
  // set the value in memory starting at current top pointer
  if (fs->top < fs->base + fs->size) {
    *(fs->top) = x;
    fs->top += 1;  // move up a sizeof(ITEM TYPE) for the next push
    return 0;
  }
  else {
    return -1;
  }
}

ITEM_TYPE fs_pop(fixed_stack* fs) {
  fs->top -= 1;
  return *(fs->top);
}

// does not remove the top
ITEM_TYPE fs_peek(fixed_stack* fs) {
  return *(fs->top - 1);  // temp looks at the value
}

// frees the heap memory
void fs_remove(fixed_stack* fs) {
  free(fs->base);
  free(fs);
}

#endif
