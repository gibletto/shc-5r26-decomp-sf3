#include "decls.h"
#include "imports.h"

// entry: 00432030
// name : make_template_labels
// size : 109
// sig  : void make_template_labels(gen_node * node, tmpl_header * tmpl)


int __cdecl make_template_labels(gen_node *node,tmpl_header *tmpl)

{
  short label;
  label_ref *cell;
  tmpl_entry *entry;
  label_ref *prev;
  
  entry = tmpl->entries;
  prev = (label_ref *)0x0;
  do {
    if ((entry == (tmpl_entry *)0x0) || (entry->op == 0xff00)) {
      return;
    }
    cell = prev;
    if (entry->op == 0x18) {
      label = make_new_label_number();
      if (prev == (label_ref *)0x0) {
        cell = alloc_zeroed(8);
        node->desc->template_labels = cell;
      }
      else {
        if (prev->labno2 == 0) {
          prev->labno2 = label;
          goto LAB_00432093;
        }
        cell = alloc_zeroed(8);
        prev->next = cell;
      }
      cell->labno1 = label;
    }
LAB_00432093:
    entry = entry + 1;
    prev = cell;
  } while( true );
}



