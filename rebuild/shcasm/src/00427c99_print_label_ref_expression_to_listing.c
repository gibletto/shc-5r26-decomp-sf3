#include "decls.h"
#include "imports.h"

// entry: 00427c99
// name : print_label_ref_expression_to_listing
// size : 251
// sig  : void __cdecl print_label_ref_expression_to_listing(label_ref *refs,short continued)


int __cdecl print_label_ref_expression_to_listing(label_ref *refs,short continued)

{
  short terms_written;
  bool at_end;
  
  terms_written = continued;
  if (refs->labno1 == 0) {
    at_end = true;
  }
  else {
    at_end = false;
  }
  while ((refs != (label_ref *)0x0 && (!at_end))) {
    if (refs->labno1 == 0) {
      at_end = true;
    }
    else {
      if ((terms_written != 0) && (0 < refs->labno1)) {
        put_char_at_column(3,'+',2);
      }
      write_label_name(3,refs->labno1,2);
      if (refs->labno2 != 0) {
        if (0 < refs->labno2) {
          put_char_at_column(3,'+',2);
        }
        write_label_name(3,refs->labno2,2);
      }
      refs = refs->next;
      terms_written = terms_written + 1;
    }
  }
  return;
}
