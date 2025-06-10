#ifndef _STACKS_H
#define _STACKS_H 1

// fixed stack
#define ITEM_TYPE int

typedef struct fs {
  ITEM_TYPE* base;  // points to the beginning of the stack array
  ITEM_TYPE* top;
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

// Macro that you can use to generate a fixed stack for any type
//   difficult to debug
// I do this once to show that it can be done, but I won't
//   do this for every data stucture
// I pre-append TYPE to all the names, for multiple stacks using ##
// may be better to just copy the code manually or use a node with a void*
#define STACK(TYPE) \
typedef struct TYPE##_fs { \
    TYPE *base;  \
    TYPE *top; \
    int size; \
  int (*is_empty)(struct TYPE##_fs*); \
  int (*push)(struct TYPE##_fs*, TYPE); \
  TYPE (*pop)(struct TYPE##_fs*); \
  TYPE (*peek)(struct TYPE##_fs*); \
  void (*remove)(struct TYPE##_fs*); \
  } TYPE##_fixed_stack; \
  TYPE##_fixed_stack* TYPE##_create_fixed_stack(int size); \
  int TYPE##_fs_empty(TYPE##_fixed_stack* fs); \
  int TYPE##_fs_push(TYPE##_fixed_stack* fs, TYPE x); \
  TYPE TYPE##_fs_pop(TYPE##_fixed_stack* fs); \
  TYPE TYPE##_fs_peek(TYPE##_fixed_stack* fs); \
  void TYPE##_fs_remove(TYPE##_fixed_stack* fs); \
  TYPE##_fixed_stack* TYPE##_create_fixed_stack(int size) { \
  TYPE##_fixed_stack *st = (TYPE##_fixed_stack*) malloc(sizeof(TYPE##_fixed_stack)); \
    st->base = (TYPE*) malloc(st->size * sizeof(TYPE)); \
    st->top = st->base; \
    st->size = size; \
  st->is_empty = TYPE##_fs_empty; \
  st->push = TYPE##_fs_push; \
  st->pop = TYPE##_fs_pop; \
  st->peek = TYPE##_fs_peek; \
  st->remove = TYPE##_fs_remove; \
    return st; \
  } \
  int TYPE##_fs_empty(TYPE##_fixed_stack* fs) { \
    return fs->base == fs->top; \
  } \
  int TYPE##_fs_push(TYPE##_fixed_stack* fs, TYPE x) { \
    if (fs->top < fs->base + fs->size) { \
      *(fs->top) = x; \
      fs->top += 1; \
      return 0; \
    } \
    else { \
      return -1; \
    } \
  } \
  TYPE TYPE##_fs_pop(TYPE##_fixed_stack* fs) { \
    fs->top -= 1; \
    return *(fs->top); \
  } \
  TYPE TYPE##_fs_peek(TYPE##_fixed_stack* fs) { \
    return *(fs->top - 1);  \
  } \
  void TYPE##_fs_remove(TYPE##_fixed_stack* fs) { \
    free(fs->base); \
    free(fs); \
  }

#endif

