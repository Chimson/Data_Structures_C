#include "define_main.h"
#include "linked_stack.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#ifdef LINKED_STACK_MAIN

int main(int argc, char** argv) {
  
  // ===== NODE MEMORY MANAGER CHECK =====
  
  // ITYPE is char*
  assert(BLOCKSIZE == 50);
  ls_node_memory* nm = init_ls_node_memory();
  
  // char[] will include the \0 and sizeof() counts it
  // memcpy copies exactly the num of bytes no matter the \0
  // may help cache if the node contain pointers across a block of string data
  
  char* sdata = (char*) malloc(50 * sizeof(char));
  char tempdata[] = "\0Ben\0Mags\0CheeseWeazel";  // temporarily on the stack
  memcpy(sdata, tempdata, sizeof(tempdata));
  
  ls_node* n0 = nm->get_node(nm);
  ls_node* n1 = nm->get_node(nm);
  ls_node* n2 = nm->get_node(nm);
  
  ls_node* nodes[] = {n0, n1, n2};  // temporarily on the stack
  
  char* cur = tempdata;
  int nctr = 0;
  while (nctr < sizeof(nodes)/sizeof(ls_node*)) {  // sizeof only return bytes
    if (*cur == '\0') {
      nodes[nctr++]->item = cur + 1;
    }
    ++cur;
  }
  
  n0->next = n1;
  n1->next = n2;
  
  // quick check on the linked list (full mem manager is in node)
  // this is nearly the same as in node.c , but items are char*
  // had to adjust the manager slightly for this
  
  assert(n0 + 1 == n1);
  assert(n0 + 2 == n2);
  assert(strcmp(n0->item, "Ben") == 0);
  assert(strcmp(n1->item, "Mags") == 0);
  assert(strcmp(n2->item, "CheeseWeazel") == 0);
  assert(n0->next == n1);
  assert(n1->next == n2);
  assert(n2->next == NULL);
  assert(nm->mallocs == n0 - 1);  // check the header node
  assert(nm->mallocs->item == (char*) nm->mallocs); // remembers the first block
  assert(nm->mallocs->next == NULL);  // only need one mallocd block
  assert(nm->free_list == NULL);  // nothing has been freed
  assert(nm->nodes_left == 46);  // check the nodes left
  
  // clean up the node memory manager
  nm->destroy(nm);
  nm = NULL;
  
  // clean up mallocs in main()
  free(sdata);
  sdata = NULL;
  // =====
  
  // TODO: write the linked list stack
  
  printf("All linked stack tests pass!\n\n");
  return 0;
  
  // ===== END NODE MEMORY MANAGER CHECK =====
  
}

#endif
