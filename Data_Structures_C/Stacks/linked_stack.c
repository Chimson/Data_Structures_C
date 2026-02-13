#ifndef _LINKED_STACK_C
#define _LINKED_STACK_C

#include "linked_stack.h"
#include <stdlib.h>

// ----- Node and Memory manager definitions -----

ls_node* ls_mng_get_node(ls_node_memory* nm) {
  ls_node* ret_node;
 
  // free list is empty, but more on the block
  if (nm->free_list == NULL && nm->nodes_left != 0) {
    ret_node = (nm->cur_block)++;
    --(nm->nodes_left);
  }
  // allocate more memory when the block is used up
  // add to the mallocs to free later
  else if (nm->free_list == NULL && nm->nodes_left == 0) {
    nm->cur_block = (ls_node*) malloc(BLOCKSIZE * sizeof(ls_node));
    
    // add to the list to destroy, newest on top
    ls_node* oldmallocs = nm->mallocs;
    nm->mallocs = (nm->cur_block)++;
    nm->mallocs->item = (ITYPE) nm->mallocs;  // since nodes are ITYPE for linked stack
    nm->mallocs->next = oldmallocs;
    
    ret_node = (nm->cur_block)++;
    nm->nodes_left = BLOCKSIZE - 2;  // header node and the returned node are gone
  }
  // whenever there are nodes on the free list
  else {
    ret_node = nm->free_list;
    nm->free_list = nm->free_list->next;
  }
  
  // give out a clean node
  ret_node->next = NULL;
  ret_node->item = NULL;
  return ret_node;
}

// return the node to the free list
void ls_mng_return_node(ls_node_memory* nm, ls_node* nd) {
  nd->next = nm->free_list;
  nm->free_list = nd;
}

// make the first node save its pointer to free later
ls_node_memory* init_ls_node_memory(void) {
  ls_node_memory* nm = (ls_node_memory*) malloc(sizeof(ls_node_memory));
  nm->cur_block = (ls_node*) malloc(BLOCKSIZE * sizeof(ls_node));
  nm->mallocs = (nm->cur_block)++;
  nm->mallocs->item = (ITYPE) nm->mallocs;
  nm->nodes_left = BLOCKSIZE - 1;
  nm->free_list = NULL;
  
  // set function pointers
  nm->get_node = ls_mng_get_node;
  nm->return_node = ls_mng_return_node;
  nm->destroy = ls_mng_destroy;
  return nm;
}

void ls_mng_destroy(ls_node_memory* nm) {
  // free all the allocations
  // freeing each cur's node, loses its next, so remember it before free
  // also each first node of a block contains its own address for the
  //     whole block to be used on free
  for (ls_node* cur = nm->mallocs; cur != NULL; ) {
    ls_node* next = cur->next;
    free(cur->item);   // lose cur
    cur = next;
  }
  free(nm);
}
// -----
// ----- linked stack

// first node is a placeholder node
//linked_stack* create_linked_stack(void) {
//  
//  return;
//}


#endif
