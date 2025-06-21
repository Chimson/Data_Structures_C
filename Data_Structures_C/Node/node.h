#ifndef _NODE_H
#define _NODE_H

#define BLOCKSIZE 3

typedef struct nd {
  void* item;
  struct nd* next;
} node;

// intermediate layer to manage memory for nodes
typedef struct nmng {
  node* cur_block;   // nodes from the mem block
  int nodes_left;    // nodes left in the block
  node* free_list;   // freed nodes, that were once in the block
  node* mallocs;     // holds blocks that need freed on destroy, but the most recently added
  
  // function pointers
  node* (*get_node)(struct nmng* nmem);
  void (*return_node)(struct nmng* nm, node* nd);
} node_memory;

// forward declarations
node_memory* init_node_memory(void);
node* nmng_get_node(node_memory* nmem);
void nmng_return_node(node_memory* nm, node* nd);

#endif
