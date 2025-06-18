#ifndef _FIXED_STACKS_H
#define _FIXED_STACKS_H 

#include <stdlib.h>

// fixed stack
#define ITEM_TYPE int

typedef struct fs {
  ITEM_TYPE* base;  // points to the beginning of the stack array
  ITEM_TYPE* top;
  int size;
  
  // methods
  int (*is_empty)(struct fs*);
  int (*push)(struct fs*, ITEM_TYPE);
  ITEM_TYPE (*pop)(struct fs*);
  ITEM_TYPE (*peek)(struct fs*);
  void (*remove)(struct fs*);
} fixed_stack;

// function prototypes used to set to the stack pointers
// need these for main file
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
// function prototypes were removed by placing the create function
//   at the end, since this will be written in the main file
#define STACK(ITEM_TYPE) \
  typedef struct ITEM_TYPE##_fs { \
    ITEM_TYPE *base;  \
    ITEM_TYPE *top; \
    int size; \
    int (*is_empty)(struct ITEM_TYPE##_fs*); \
    int (*push)(struct ITEM_TYPE##_fs*, ITEM_TYPE); \
    ITEM_TYPE (*pop)(struct ITEM_TYPE##_fs*); \
    ITEM_TYPE (*peek)(struct ITEM_TYPE##_fs*); \
    void (*remove)(struct ITEM_TYPE##_fs*); \
  } ITEM_TYPE##_fixed_stack; \
  int ITEM_TYPE##_fs_empty(ITEM_TYPE##_fixed_stack* fs) { \
    return fs->base == fs->top; \
  } \
  int ITEM_TYPE##_fs_push(ITEM_TYPE##_fixed_stack* fs, ITEM_TYPE x) { \
    if (fs->top < fs->base + fs->size) { \
      *(fs->top) = x; \
      fs->top += 1; \
      return 0; \
    } \
    else { \
      return -1; \
    } \
  } \
  ITEM_TYPE ITEM_TYPE##_fs_pop(ITEM_TYPE##_fixed_stack* fs) { \
    fs->top -= 1; \
    return *(fs->top); \
  } \
  ITEM_TYPE ITEM_TYPE##_fs_peek(ITEM_TYPE##_fixed_stack* fs) { \
    return *(fs->top - 1);  \
  } \
  void ITEM_TYPE##_fs_remove(ITEM_TYPE##_fixed_stack* fs) { \
    free(fs->base); \
    free(fs); \
  }\
 ITEM_TYPE##_fixed_stack* ITEM_TYPE##_create_fixed_stack(int size) { \
   ITEM_TYPE##_fixed_stack *st = (ITEM_TYPE##_fixed_stack*) \
      malloc(sizeof(ITEM_TYPE##_fixed_stack)); \
   st->base = (ITEM_TYPE*) malloc(st->size * sizeof(ITEM_TYPE)); \
   st->top = st->base; \
   st->size = size; \
   st->is_empty = ITEM_TYPE##_fs_empty; \
   st->push = ITEM_TYPE##_fs_push; \
   st->pop = ITEM_TYPE##_fs_pop; \
   st->peek = ITEM_TYPE##_fs_peek; \
   st->remove = ITEM_TYPE##_fs_remove; \
   return st; \
 } \

// struct and prototypes for the generic stack
typedef struct gfs {
  void* base;
  void* top;
  int size;
  size_t tsize;
  
  // function pointers
  int (*push)(struct gfs*, void* item);
  int (*is_empty)(struct gfs*);
  void* (*peek)(struct gfs*);
  void (*remove)(struct gfs*);
  void* (*pop)(struct gfs*);
} generic_stack;

int gfs_empty(generic_stack* gfs);
int gfs_push(generic_stack* gfs, void* item);
void* gfs_peek(generic_stack* gfs);
void gfs_remove(generic_stack* gfs);
void* gfs_pop(generic_stack* gfs);
generic_stack* create_generic_stack(int size, size_t tsize);


#endif

