#include "decls.h"
#include "imports.h"

// entry: 00402874
// name : append_reloc_expression_long
// size : 41
// sig  : int append_reloc_expression_long(int value)


int __cdecl append_reloc_expression_long(int value)

{
  char *pcVar1;
  
  store_u32_big_endian((uint *)&value,(uint *)&value);
  pcVar1 = append_reloc_expression_bytes((char *)&value,4);
  return (int)pcVar1;
}



