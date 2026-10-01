#include "decls.h"
#include "imports.h"

// entry: 00404690
// name : defer_post_increments
// size : 185
// sig  : void defer_post_increments(code_node * node)


int __cdecl defer_post_increments(code_node *node)

{
  byte kind;
  char deferred;
  psd *next;
  int index;
  psd *rec;
  
  do {
    if (node == (code_node *)0x0) {
      return;
    }
    rec = node->psd;
    index = 0;
    do {
      if (rec == (psd *)0x0) break;
      if (((((rec->op == OP_MOV) && ((rec->misc & 0x20U) != 0)) && ((rec->ea2->type & 0x1f) == 1))
          && ((next = find_next_psd_record(node,rec), next != (psd *)0x0 &&
              ((next->misc & 0x20U) != 0)))) &&
         (((kind = rec->ea1->type & 0x1f, kind != 2 && ((kind < 8 || (0xc < kind)))) ||
          (deferred = defer_memory_post_increment(node,rec,index), deferred == '\0')))) {
        if (next->op == OP_MOVI) {
          if ((next->misc & 0x20U) != 0) {
            defer_movi_add_after_copy(node,rec,index);
          }
        }
        else if ((next->op == OP_ADD) && ((next->misc & 0x20U) != 0)) {
          defer_add_after_copy(node,rec,index);
        }
      }
      index = index + 1;
      rec = rec + 1;
    } while (index < 0xf);
    node = node->next;
  } while( true );
}



