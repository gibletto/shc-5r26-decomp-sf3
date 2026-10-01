#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cse_split_first
#define g_cse_split_first (*(il_node * *)(g_sd + 0x267d4))
#undef g_cse_split_head
#define g_cse_split_head (*(il_node * *)(g_sd + 0x26f04))


// entry: 0041e190
// name : cse_add_to_split_class
// size : 218
// sig  : void cse_add_to_split_class(il_node * node)


int __cdecl cse_add_to_split_class(il_node *node)

{
  il_node *piVar1;
  il_node *tail;
  
  if (g_cse_split_first == (il_node *)0x0) {
    g_cse_split_first = node;
    node->refcnt = 1;
    g_cse_split_first->cse_head = g_cse_split_first;
    return;
  }
  piVar1 = g_cse_split_first;
  if (g_cse_split_head == (il_node *)0x0) {
    g_cse_split_head = node;
    node->cse_next = g_cse_split_first;
    g_cse_split_head->cse_head = g_cse_split_head;
    g_cse_split_first->cse_head = g_cse_split_head;
    g_cse_split_head->refcnt = 2;
    g_cse_split_first->refcnt = 0;
    return;
  }
  do {
    tail = piVar1;
    if (tail == (il_node *)0x0) break;
    piVar1 = tail->cse_next;
  } while (tail->cse_next != (il_node *)0x0);
  tail->cse_next = g_cse_split_head;
  g_cse_split_head->cse_next = (il_node *)0x0;
  node->refcnt = g_cse_split_head->refcnt + 1;
  g_cse_split_head->refcnt = 0;
  g_cse_split_head = node;
  node->cse_next = g_cse_split_first;
  for (piVar1 = g_cse_split_head; piVar1 != (il_node *)0x0; piVar1 = piVar1->cse_next) {
    piVar1->cse_head = g_cse_split_head;
  }
  return;
}



