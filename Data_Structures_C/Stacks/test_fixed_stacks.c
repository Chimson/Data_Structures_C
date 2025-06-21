#include "define_main.h"
#include "fixed_stacks.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// I can't exhaustively test everything
// test a few simple operations and check their states
// then do a mix of several operations and check its state at the end

// Here is the macro version for type
//   independent stacks, at least per type
// could also do this with Node's that have a void pointer

// macro to generate the code for two stacks of different
//   types
STACK(long)
STACK(double)

#ifdef FIXED_STACKS_MAIN

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
  
  // try the macro version
  
  long_fixed_stack* lfs = long_create_fixed_stack(10);
  lfs->push(lfs, 0xFFFFFFFFFF);
  assert(lfs->pop(lfs) == 0xFFFFFFFFFF);
  
  double_fixed_stack* dfs = double_create_fixed_stack(10);
  dfs->push(dfs, 0xFFFFFFFFFF);
  assert(dfs->pop(dfs) == 0xFFFFFFFFFF);
  
  // test the generic stack
  
  generic_stack* is = create_generic_stack(5, sizeof(int));
  assert(is->is_empty(is) == 1);
  int val = 0;
  is->push(is, &val);
  val = 1 ;
  is->push(is, &val);
  val = 2;
  is->push(is, &val);
  val = 3;
  is->push(is, &val);
  val = 4;
  is->push(is, &val);
  int* pval = is->peek(is);
  assert(*pval == 4);
  int* bptr = (int*) is->base;
  assert(*(bptr++) == 0);
  assert(*(bptr++) == 1);
  assert(*(bptr++) == 2);
  assert(*(bptr++) == 3);
  assert(*(bptr++) == 4);
  assert(is->size == 5);
  assert(is->tsize == sizeof(int));
  assert(is->is_empty(is) == 0);
  assert(is->base + is->size * is->tsize == is->top);

  // push one past does nothing
  val = 5;
  assert(is->push(is, &val) == -1);
  assert(*(int*)is->peek(is) == 4);
  assert(is->size == 5);
  assert(is->base + is->size * is->tsize == is->top);
  
  // remove
  is->remove(is);
  is = NULL;
  
  // mixed pushs and pops
  is = create_generic_stack(10, sizeof(int));
  for (int i = 10; i > 0; --i) {
    int* iptr = &i;
    is->push(is, iptr);
  }
  assert(is->base + is->size * is->tsize == is->top);
  assert(*(int*)is->peek(is) == 1);
  assert(is->size == 10);
  
  assert(*(int*)is->pop(is) == 1);
  assert(is->base + 9 * is->tsize == is->top);
  assert(*(int*)is->peek(is) == 2);
  assert(is->size == 10); // size ihe capacity not current size
  
  val = 11;
  is->push(is, &val);
  assert(is->size == 10);
  assert(is->base + 10 * is->tsize == is->top);
  assert(*(int*)is->peek(is) == 11);
  is->pop(is);
  is->pop(is);
  val = 12;
  is->push(is, &val);
  val = 13;
  is->push(is, &val);
  is->pop(is);
  assert(*(int*)is->pop(is) == 12);
  assert(*(int*)is->peek(is) == 3);
  assert(is->base + 8 * is->tsize == is->top);
  assert(is->size == 10);
  
  // remove
  is->remove(is);
  is = NULL;
  
  printf("All fixed_stacks tests pass!\n");
  printf("\n");
  return 0;
}

#endif
