#include "decls.h"
#include "imports.h"

// entry: 00423453
// name : write_operand_offset
// size : 116
// sig  : void __cdecl write_operand_offset(short stream,int offset,short after_symbol)


int __cdecl write_operand_offset(short stream,int offset,short after_symbol)

{
  if (offset == 0) {
    if (after_symbol == 0) {
      write_decimal(stream,0,2);
    }
  }
  else {
    if ((after_symbol == 1) && (0 < offset)) {
      put_char_at_column(stream,'+',2);
    }
    write_decimal(stream,offset,2);
  }
  return;
}
