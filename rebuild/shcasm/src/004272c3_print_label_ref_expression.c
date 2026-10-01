#include "decls.h"
#include "imports.h"

// entry: 004272c3
// name : print_label_ref_expression
// size : 229
// sig  : void __cdecl print_label_ref_expression(short stream,label_ref *refs,short continued)


int __cdecl print_label_ref_expression(short stream,label_ref *refs,short continued)

{
  short terms_written;
  
  terms_written = continued;
  while( true ) {
    if ((refs == (label_ref *)0x0) || (refs->labno1 == 0)) {
      return;
    }
    if ((terms_written != 0) && (0 < refs->labno1)) {
      put_char_at_column(stream,'+',2);
    }
    write_label_name(stream,refs->labno1,2);
    if (refs->labno2 == 0) break;
    if (0 < refs->labno2) {
      put_char_at_column(stream,'+',2);
    }
    write_label_name(stream,refs->labno2,2);
    refs = refs->next;
    terms_written = terms_written + 1;
  }
  return;
}
