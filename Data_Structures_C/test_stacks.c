#include "stacks.h"
#include <assert.h>

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
  
  // finish a few more tests
  
  
  return 0;
}
