#include "decls.h"
#include "imports.h"

// entry: 00412780
// name : dump_ea_label_list
// size : 78
// sig  : void __cdecl dump_ea_label_list(ea *op)


int __cdecl dump_ea_label_list(ea *op)

{
  int n;
  label_ref *ref;
  
  n = 1;
  for (ref = op->labels; ref != (label_ref *)0x0; ref = ref->next) {
    _printf(s_LABTBL_NO_d_004273c4,n);
    _printf(s_str_004273ac,(int)ref->labno1);
    _printf(s___labno2__x_0042739c,(int)ref->labno2);
    n = n + 1;
  }
  return;
}
