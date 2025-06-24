#include "define_main.h"
#include "linked_stack.h"
#include <stdio.h>
#include "node.h"  

#ifdef LINKED_STACK_MAIN

static node_memory* nm;

int main(int argc, char** argv) {
  
  // initialize the intermediate layer to get_node and return_node
  //   instead of many calls of free() and malloc()
  nm = init_node_memory();
  
  printf("All linked_stack tests pass!\n\n");
  return 0;
}

#endif
