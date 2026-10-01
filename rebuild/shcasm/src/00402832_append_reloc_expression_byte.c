#include "decls.h"
#include "imports.h"

// entry: 00402832
// name : append_reloc_expression_byte
// size : 25
// sig  : int append_reloc_expression_byte(int value)


int __cdecl append_reloc_expression_byte(int value)

{
  char *pcVar1;
  
  pcVar1 = append_reloc_expression_bytes((char *)&value,1);
  return (int)pcVar1;
}



