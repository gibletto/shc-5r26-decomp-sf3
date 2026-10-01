#include "decls.h"
#include "imports.h"

// entry: 0042b7e0
// name : copy_ea_into
// size : 64
// sig  : void copy_ea_into(ea * dst, ea * src)


int __cdecl copy_ea_into(ea *dst,ea *src)

{
  byte kind;
  label_ref *labels_copy;
  
  copy_words((uint *)dst,(uint *)src,3);
  kind = src->type & 0x1f;
  if (((((kind == 0xd) || (kind == 7)) || (kind == 2)) || (kind == 8)) &&
     (src->labels != (label_ref *)0x0)) {
    labels_copy = copy_label_ref_list(src->labels);
    dst->labels = labels_copy;
  }
  return;
}



