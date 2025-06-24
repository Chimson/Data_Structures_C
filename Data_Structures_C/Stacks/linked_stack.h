#ifndef _LINKED_STACK_H
#define _LINKED_STACK_H

#include "node.h"

// this stack has its first node as a header node: st_node
// st_node->next is actually the top of the stack
typedef struct l_stk {
  node* st_node;
}
linked_stack;



#endif
