#include "stacks.h"
#include <assert.h>
#include <stdio.h>

// I can't exhaustively test everything
// test a few simple operations and check their states
// then do a mix of several operations and check its state at the end

int main(int argc, char** argv) {
  
  fixed_stack* fs = create_fixed_stack(5);
  assert(fs->is_empty(fs) == 1);
  fs->push(fs, 0);
  fs->push(fs, 1);
  fs->push(fs, 2);
  fs->push(fs, 3);
  fs->push(fs, 4);
  assert(fs->peek(fs) == 4);
  assert(fs->base[0] == 0);
  assert(fs->base[1] == 1);
  assert(fs->base[2] == 2);
  assert(fs->base[3] == 3);
  assert(fs->base[4] == 4);
  assert(fs->base + 5 == fs->top);
  assert(fs->size == 5);
  assert(fs->is_empty(fs) == 0);
  
  // push one past does nothing
  assert(fs->push(fs, 5) == -1);
  assert(fs->peek(fs) == 4);
  assert(fs->size == 5);
  assert(fs->base + 5 == fs->top);
  
  // remove this stack
  fs->remove(fs);
  
  // mixed pushs and pops
  fs = create_fixed_stack(10);
  for (int i = 10; i > 0; --i) {
    fs->push(fs, i);
  }
  assert(fs->base + 10 == fs->top);
  assert(fs->peek(fs) == 1);
  assert(fs->size == 10);
  // [10, 9, 8, 7, 6, 5, 4, 3, 2, 1];
  
  // pop 1 and check its returned value
  assert(fs->pop(fs) == 1);
  assert(fs->base + 9 == fs->top);
  assert(fs->peek(fs) == 2);
  assert(fs->size == 10);  // size is the alloc memory not cur size
  // [10, 9, 8, 7, 6, 5, 4, 3, 2]
  
  fs->push(fs, 11);
  assert(fs->size == 10);
  assert(fs->base + 10 == fs->top);
  assert(fs->peek(fs) == 11);
  fs->pop(fs);
  fs->pop(fs);
  fs->push(fs, 12);
  fs->push(fs, 13);
  fs->pop(fs);
  assert(fs->pop(fs) == 12);
  assert(fs->peek(fs) == 3);
  assert(fs->base + 8 == fs->top);
  assert(fs->size == 10);
  // [10, 9, 8, 7, 6, 5, 4, 3]
  
  fs->remove(fs);
  fs = NULL;
  
  printf("All tests pass!\n");
  
  // TODO:
  // maybe try to make a macro that will produce a stack of a type I
  //   want, possibly allow for more than one type
  
  printf("\n");
  return 0;
}
