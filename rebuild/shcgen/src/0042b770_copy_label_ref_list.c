#include "decls.h"
#include "imports.h"

// entry: 0042b770
// name : copy_label_ref_list
// size : 99
// sig  : label_ref * copy_label_ref_list(label_ref * src)


label_ref * __cdecl copy_label_ref_list(label_ref *src)

{
  label_ref *dst;
  label_ref *first;
  label_ref *prev;
  
  first = (label_ref *)0x0;
  prev = (label_ref *)0x0;
  for (; src != (label_ref *)0x0; src = src->next) {
    dst = alloc_zeroed(8);
    if (dst == (label_ref *)0x0) {
      report_codegen_message(0xbcd,1,0,0,(char *)0x0);
    }
    if (first == (label_ref *)0x0) {
      first = dst;
    }
    if (prev != (label_ref *)0x0) {
      prev->next = dst;
    }
    copy_words((uint *)dst,(uint *)src,2);
    dst->next = (label_ref *)0x0;
    prev = dst;
  }
  return first;
}



