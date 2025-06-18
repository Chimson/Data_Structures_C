#ifndef _FIXED_STACKS_C
#define _FIXED_STACKS_C 

#include <stdlib.h>
#include "fixed_stacks.h"


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

// does not check for popping from an empty stack
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

// allocates space for the stack fields and the array
// base is a pointer to the first byte of the stack
// top is a pointer to the byte just after any element in the stack
//   like right at the first byte to insert a new item in the stack
// size is the initial memory size, not current size, so it should
//   never update
fixed_stack* create_fixed_stack(int size) {
  fixed_stack* st = (fixed_stack*) malloc(sizeof(fixed_stack));
  st->base = (ITEM_TYPE*) malloc(size * sizeof(ITEM_TYPE));
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
// =====
// here is are the functions for the  generic version using unsigned
//   char* and void*
// can only contain a stack of one type at a time

int gfs_empty(generic_stack* gfs) {
  return gfs->base == gfs->top;
}

int gfs_push(generic_stack* gfs, void* item) {
  if (gfs->top < gfs->base + gfs->size * gfs->tsize) {
    unsigned char* val = (unsigned char*) item;
    
    // copy byte by byte of the item's value into the top of the stack
    unsigned char* cbyte = gfs->top;
    for (; (void*) cbyte < gfs->top + gfs->tsize; ++cbyte, ++val) {
      *cbyte = *val;
    }
    
    // cbyte now points to the new top
    gfs->top = (void*) cbyte;
    return 0;
  }
  else {
    return -1;
  }
}

void* gfs_peek(generic_stack* gfs) {
  return gfs->top - gfs->tsize;
}

void gfs_remove(generic_stack* gfs) {
  free(gfs->base);
  free(gfs);
}

// does not check for popping from an empty stack
void* gfs_pop(generic_stack* gfs) {
  gfs->top -= gfs->tsize;
  return gfs->top;
}

generic_stack* create_generic_stack(int size, size_t tsize) {
  generic_stack* gst = (generic_stack*) malloc(sizeof(generic_stack));
  gst->base = malloc(size * tsize);
  gst->top = gst->base;
  gst->size = size;
  gst->tsize = tsize;
  
  // set the function pointers
  gst->push = gfs_push;
  gst->is_empty = gfs_empty;
  gst->peek = gfs_peek;
  gst->remove = gfs_remove;
  gst->pop = gfs_pop;
  
  return gst;
}


#endif
