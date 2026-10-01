#include "decls.h"
#include "imports.h"

// entry: 0042351c
// name : write_immediate_with_size
// size : 68
// sig  : void __cdecl write_immediate_with_size(short stream,int *value,short size)


int __cdecl write_immediate_with_size(short stream,int *value,short size)

{
  put_char_at_column(stream,'#',2);
  write_decimal(stream,*value,2);
  write_size_suffix(stream,size,2);
  return;
}
