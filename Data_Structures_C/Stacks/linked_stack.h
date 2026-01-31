#ifndef _LINKED_STACK_H
#define _LINKED_STACK_H

// Not using an entire macro or char* for generic type implementation
// Only one macro for the current type of the list

// ----- Node and Memory manager -----

#define TYPE char
#define SSIZE 10   // size for num of chars embedded in node
#define BLOCKSIZE 50

typedef struct nd {
  TYPE item[SSIZE];
  struct nd* next;
} node;

// intermediate layer to manage memory for nodes
typedef struct nmng {
  node* cur_block;   // nodes from the mem block
  int nodes_left;    // nodes left in the block
  node* free_list;   // freed nodes, that were once in the block
  node* mallocs;     // holds blocks that need freed on destroy
  
  // function pointers
  node* (*get_node)(struct nmng* nmem);
  void (*return_node)(struct nmng* nm, node* nd);
  void (*destroy)(struct nmng* nm);
} node_memory;

// forward declarations
node_memory* init_node_memory(void);
node* nmng_get_node(node_memory* nmem);
void nmng_return_node(node_memory* nm, node* nd);
void nmng_destroy(node_memory* nm);

// -----

#endif
