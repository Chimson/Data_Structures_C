#include "define_main.h"
#include "linked_stack.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

#ifdef LINKED_STACK_MAIN

int main(int argc, char** argv) {
  
  assert(BLOCKSIZE == 50);
  node_memory* nm = init_node_memory();
  
  // char[] will include the \0 and sizeof() counts it
  // sizeof() may not copy \0 when deref a char*
  // memcpy copies exactly the num of bytes no matter the \0
  node* n0 = nm->get_node(nm);
  char copystr1[] = "Ben";
  memcpy(n0->item, copystr1, sizeof(copystr1));
  
  node* n1 = nm->get_node(nm);
  char copystr2[] = "Mags";
  memcpy(n1->item, copystr2, sizeof(copystr2));
  
  n0->next = n1;
  
  // FIX: n1's item is not correct
  
  return 0;
  
}

#endif
