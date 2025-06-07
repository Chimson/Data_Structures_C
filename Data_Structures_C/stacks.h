#ifndef _STACKS_H
#define _STACKS_H 1

// fixed stack
#define ITEM_TYPE int

typedef struct fs {
  ITEM_TYPE *base;  // points to the beginning of the stack array
  ITEM_TYPE *top;
  int size;
  int (*is_empty)(struct fs*);
  int (*push)(struct fs*, ITEM_TYPE);
  ITEM_TYPE (*pop)(struct fs*);
  ITEM_TYPE (*peek)(struct fs*);
  void (*remove)(struct fs*);
} fixed_stack;

// functions used to set to the stack pointers
fixed_stack* create_fixed_stack(int size);
int fs_empty(fixed_stack* fs);
int fs_push(fixed_stack* fs, ITEM_TYPE x);
ITEM_TYPE fs_pop(fixed_stack* fs);
ITEM_TYPE fs_peek(fixed_stack* fs);
void fs_remove(fixed_stack* fs);

#endif

