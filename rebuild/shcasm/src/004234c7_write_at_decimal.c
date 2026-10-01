#include "decls.h"
#include "imports.h"

// entry: 004234c7
// name : write_at_decimal
// size : 47
// sig  : void __cdecl write_at_decimal(short stream,int value)


int __cdecl write_at_decimal(short stream,int value)

{
  put_char_at_column(stream,'@',2);
  write_decimal(stream,value,2);
  return;
}
