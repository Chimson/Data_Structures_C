#ifndef _LINKED_STACK_H
#define _LINKED_STACK_H

// Not using an entire macro or char* for generic type implementation
// Only one macro for the current type of the list

// ----- Node and Memory manager -----

#define BLOCKSIZE 50
#define ITYPE char*  // node item type

typedef struct lsnd {
  ITYPE item;
  struct lsnd* next;
} ls_node;

// intermediate layer to manage memory for nodes
typedef struct lsn_mng {
  ls_node* cur_block;   // nodes from the mem block
  int nodes_left;    // nodes left in the block
  ls_node* free_list;   // freed nodes, that were once in the block
  ls_node* mallocs;     // holds blocks that need freed on destroy
  
  // function pointers
  ls_node* (*get_node)(struct lsn_mng* nmem);
  void (*return_node)(struct lsn_mng* nm, ls_node* nd);
  void (*destroy)(struct lsn_mng* nm);
} ls_node_memory;

// forward declarations
ls_node_memory* init_ls_node_memory(void);
ls_node* ls_mng_get_node(ls_node_memory* nmem);
void ls_mng_return_node(ls_node_memory* nm, ls_node* nd);
void ls_mng_destroy(ls_node_memory* nm);

// -----
// ----- linked stack

typedef struct lstack {
  ITYPE item;
  struct lstack* next;
  // need to add a pointer to ls_node_memory
  
} linked_stack;



#endif
