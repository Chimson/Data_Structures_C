#ifndef _NODE_C
#define _NODE_C

#include "node.h"
#include <stdlib.h>


node* nmng_get_node(node_memory* nm) {
  node* ret_node;
 
  // free list is empty, but more on the block
  if (nm->free_list == NULL && nm->nodes_left != 0) {
    ret_node = (nm->cur_block)++;
    --(nm->nodes_left);
  }
  // allocate more memory when the block is used up
  // add to the mallocs to free later
  else if (nm->free_list == NULL && nm->nodes_left == 0) {
    nm->cur_block = (node*) malloc(BLOCKSIZE * sizeof(node));
    
    // add to the list to destroy, newest on top
    node* oldmallocs = nm->mallocs;
    nm->mallocs = (nm->cur_block)++;
    nm->mallocs->item = nm->mallocs;
    nm->mallocs->next = oldmallocs;
    
    ret_node = nm->cur_block;
    nm->nodes_left = BLOCKSIZE - 1;
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

// add return the node to the free list
void nmng_return_node(node_memory* nm, node* nd) {
  nd->next = nm->free_list;
  nm->free_list = nd;
}

// make the first node save its pointer to free later
node_memory* init_node_memory(void) {
  node_memory* nm = malloc(sizeof(node_memory));
  nm->cur_block = (node*) malloc(BLOCKSIZE * sizeof(node));
  nm->mallocs = (nm->cur_block)++;
  nm->mallocs->item = (void*) nm->mallocs;
  nm->nodes_left = BLOCKSIZE - 1;
  nm->free_list = NULL;
  
  // set function pointers
  nm->get_node = nmng_get_node;
  nm->return_node = nmng_return_node;
  return nm;
}




#endif

