#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))


// entry: 00407450
// name : mark_web_allocatable
// size : 183
// sig  : int mark_web_allocatable(il_node * node)


int __cdecl mark_web_allocatable(il_node *node)

{
  il_node *ref;
  byte type_class;
  dutbl *tail;
  ushort flag;
  node_list *link;
  dutbl *next_du;
  
  ref = node;
  if (node->duptr->kind == 2) {
    ref = node->child;
  }
  if ((g_leaf_table[ref->nleaf].flag & 0xe) == 0) {
    if (((((ref->type & 0xe0) != 0) && (type_class = ref->type & 0xf8, type_class != 0x40)) &&
        ((g_options->cpu != 4 || (type_class != 0x30)))) && (type_class != 0x28)) {
      return 0;
    }
    *(byte *)&node->flag = (byte)node->flag | 4;
    for (ref = node->refchn; ref != (il_node *)0x0; ref = ref->refchn) {
      *(byte *)&ref->flag = (byte)ref->flag | 4;
    }
    tail = node->duptr;
    for (link = tail->links; link != (node_list *)0x0; link = link->next) {
      flag = link->node->flag;
      if ((flag & 4) == 0) {
        link->node->flag = flag | 4;
        tail->next = link->node->duptr;
        mark_web_allocatable(link->node);
        next_du = tail->next;
        while (next_du != (dutbl *)0x0) {
          tail = tail->next;
          next_du = tail->next;
        }
      }
    }
    return 1;
  }
  return 0;
}



