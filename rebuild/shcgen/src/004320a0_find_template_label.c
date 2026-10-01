#include "decls.h"
#include "imports.h"

// entry: 004320a0
// name : find_template_label
// size : 106
// sig  : short find_template_label(gen_node * node, short number)


short __cdecl find_template_label(gen_node *node,short number)

{
  short label_no;
  short found;
  short label;
  label_ref *ref;
  ushort sign;
  
  found = 0;
  sign = number >> 0xf;
  ref = node->desc->template_labels;
  label_no = 1;
  while ((ref != (label_ref *)0x0 && (found == 0))) {
    if (((number ^ sign) - sign & 1 ^ sign) == sign) {
      label_no = label_no + 1;
      label = ref->labno2;
    }
    else {
      label = ref->labno1;
    }
    if ((label != 0) && (label_no == number)) {
      found = label;
    }
    label_no = label_no + 2;
    ref = ref->next;
  }
  return found;
}



