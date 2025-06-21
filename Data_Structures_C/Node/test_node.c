#include "define_main.h"
#include <stdio.h>
#include <assert.h>
#include "node.h"

#ifdef NODE_MAIN

int main(int argc, char** argv) {
  
  // change the BLOCKSIZE to 3
  assert(BLOCKSIZE == 3);
  
  // grab a few nodes
  node_memory* nm = init_node_memory();
  assert(nm->nodes_left == 2);
  assert(nm->free_list == NULL);
  assert(nm->mallocs == nm->cur_block - 1);
  assert(nm->mallocs->item == nm->mallocs);
  node* node1 = nm->get_node(nm);
  assert(node1->item == NULL);
  assert(node1->next == NULL);
  assert(nm->cur_block == node1 + 1);
  assert(nm->nodes_left == 1);
  assert(nm->free_list == NULL);
  assert(nm->mallocs == nm->cur_block - 2);
  assert(nm->mallocs->item == nm->mallocs);
  node* node2 = nm->get_node(nm);
  assert(node2->item == NULL);
  assert(node2->next == NULL);
  assert(nm->cur_block == node2 + 1);
  assert(nm->nodes_left == 0);
  assert(nm->free_list == NULL);
  assert(nm->mallocs == nm->cur_block - 3);
  assert(nm->mallocs->item == nm->mallocs);
  // block is maxed out
  
  // make a linked list of size 2
  node* first = node1;
  node1->item = (void*) "Ben";
  node1->next = node2;
  node2->item = (void*) "Mags";
  assert(node2->next == NULL);
  
  // remove the first and free it
  first = first->next;
  nm->return_node(nm, node1);
  assert(nm->cur_block == node2 + 1);
  assert(nm->nodes_left == 0);     // does not check the free list
  assert(nm->free_list == node1);
  assert(nm->mallocs == nm->cur_block - 3);
  assert(nm->mallocs->item == nm->mallocs);
  
  // grab another node, should take from the free list
  node* node3 = nm->get_node(nm);
  assert(node3->item == NULL);
  assert(node3->next == NULL);
  assert(nm->cur_block == node2 + 1);
  assert(nm->nodes_left == 0);
  assert(nm->free_list == NULL);
  assert(nm->mallocs == nm->cur_block - 3);
  assert(nm->mallocs->item == nm->mallocs);
 
  // free the last node
  node* oldtwo = first;
  first = first->next;
  assert(first == NULL);
  nm->return_node(nm, oldtwo);
  assert(nm->nodes_left == 0);
  assert(nm->free_list == node2);
  assert(nm->mallocs == nm->cur_block - 3);
  assert(nm->mallocs->item == nm->mallocs);
  
  
  
  
   
  printf("All node tests pass!\n\n");
  return 0;
}

#endif
