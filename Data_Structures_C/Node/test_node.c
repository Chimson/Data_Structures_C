#include "define_main.h"
#include <stdio.h>
#include <assert.h>
#include "node.h"
#include <unistd.h>

#ifdef NODE_MAIN

int main(int argc, char** argv) {
  
  // change the BLOCKSIZE to 3
  assert(BLOCKSIZE == 3);
  
  // init_node_memory
  node_memory* nm = init_node_memory();
  assert(nm->nodes_left == 2);
  assert(nm->free_list == NULL);
  assert(nm->mallocs == nm->cur_block - 1);
  assert(nm->mallocs->item == nm->mallocs);
  assert(nm->mallocs->next == NULL);
  
  // get_node first condition
  // check get_node grabbing nodes from the block only
  node* node1 = nm->get_node(nm);
  assert(node1->item == NULL);
  assert(node1->next == NULL);
  assert(nm->cur_block == node1 + 1);
  assert(nm->nodes_left == 1);
  assert(nm->free_list == NULL);
  assert(nm->mallocs == nm->cur_block - 2);
  assert(nm->mallocs->item == nm->mallocs);
  assert(nm->mallocs->next == NULL);
  node* node2 = nm->get_node(nm);
  assert(node2->item == NULL);
  assert(node2->next == NULL);
  assert(nm->cur_block == node2 + 1);
  assert(nm->nodes_left == 0);
  assert(nm->free_list == NULL);
  assert(nm->mallocs == nm->cur_block - 3);
  assert(nm->mallocs->item == nm->mallocs);
  assert(nm->mallocs->next == NULL);
  // block is maxed out
  
  // make a linked list of size 2
  node* first = node1;
  node1->item = (void*) "Ben";
  node1->next = node2;
  node2->item = (void*) "Mags";
  assert(node2->next == NULL);
  
  // return_node
  // remove the first from the list and return it
  first = first->next;
  nm->return_node(nm, node1);
  assert(nm->cur_block == node2 + 1);
  assert(nm->nodes_left == 0);     // does not check the free list
  assert(nm->free_list == node1);
  assert(nm->free_list->next == NULL);
  assert(nm->mallocs == nm->cur_block - 3);
  assert(nm->mallocs->item == nm->mallocs);
  assert(nm->mallocs->next == NULL);
  
  // get_node third condition, when cur_block maxed out
  // grab another node, should take from the free list
  node* node3 = nm->get_node(nm);  // actually node1 alias
  assert(node3->item == NULL);
  assert(node3->next == NULL);
  assert(nm->cur_block == node2 + 1);  // unchanged
  assert(nm->nodes_left == 0);
  assert(nm->free_list == NULL);   // taken from the free_list
  assert(nm->mallocs == nm->cur_block - 3);
  assert(nm->mallocs->item == nm->mallocs);
  assert(nm->mallocs->next == NULL);
 
  // (return_node already checked)
  // free the last node
  node* oldtwo = first;
  first = first->next;
  assert(first == NULL);
  nm->return_node(nm, oldtwo);
  assert(nm->nodes_left == 0);
  assert(nm->free_list == node2);
  assert(nm->mallocs == nm->cur_block - 3);
  assert(nm->mallocs->item == nm->mallocs);
  assert(nm->mallocs->next == NULL);
  
  // check destroy
  // clean up the ptr variables and destroy the node manager
  first = NULL;
  node1 = NULL;
  node2 = NULL;
  node3 = NULL;  // alias to node1
  nm->destroy(nm);
  nm = NULL;
  
  // (get_node 1st condition already checked above)
  // create another node memory manager, although this should never be necessary
  // max out the first block and test a new block;
  nm = init_node_memory();
  node1 = nm->get_node(nm);
  node2 = nm->get_node(nm);
  assert(nm->cur_block == node1 + 2);
  assert(nm->nodes_left == 0);
  assert(nm->free_list == NULL);
  assert(nm->mallocs == nm->cur_block - 3);
  assert(nm->mallocs->item == nm->mallocs);
  assert(nm->mallocs->next == NULL);
  // block maxed out
  
  // get_node second condition
  // make a new block, save its pointer in the mallocs list
  // nothing has been freed yet
  node3 = nm->get_node(nm);
  assert(node3->item == NULL);
  assert(node3->next == NULL);
  assert(nm->cur_block == node3 + 1);
  assert(nm->nodes_left == 1);  // header and prev node are used
  assert(nm->free_list == NULL);
  assert(nm->mallocs == nm->cur_block - 2);
  assert(nm->mallocs->item == nm->mallocs);
  assert(nm->mallocs->next == node1 - 1);  // remembers the old block
  assert(nm->mallocs->next->item == nm->mallocs->next);
  assert(nm->mallocs->next->next == NULL);

  // get_node third condition, when the block is not maxed out
  // grab from the free list when there still space on the block
  // return the node and get it back
  nm->return_node(nm, node3);
  node* node4 = nm->get_node(nm);
  assert(node4->item == NULL);
  assert(node4->next == NULL);
  assert(nm->cur_block == node3 + 1);  // unchanged, since its from the free
  assert(nm->nodes_left == 1);  // still space left on the block
  assert(nm->free_list == NULL);
  assert(nm->mallocs == nm->cur_block - 2);
  assert(nm->mallocs->item == nm->mallocs);
  assert(nm->mallocs->next == node1 - 1);  // remembers the old block
  assert(nm->mallocs->next->item == nm->mallocs->next);
  assert(nm->mallocs->next->next == NULL);
  
  // clean up the ptr variables and destroy the node manager
  first = NULL;
  node1 = NULL;
  node2 = NULL;
  node3 = NULL;
  node4 = NULL;  // alias to node3
  nm->destroy(nm);
  nm = NULL;
  
  
  
  
  
  
  
  
  
   
  printf("All node tests pass!\n\n");
  return 0;
}

#endif
