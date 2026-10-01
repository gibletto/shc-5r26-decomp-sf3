#include "decls.h"
#include "imports.h"

// entry: 0040284b
// name : append_reloc_expression_word
// size : 41
// sig  : int append_reloc_expression_word(int value)


int __cdecl append_reloc_expression_word(int value)

{
  char *pcVar1;
  
  store_u16_big_endian((ushort *)&value,(ushort *)&value);
  pcVar1 = append_reloc_expression_bytes((char *)&value,2);
  return (int)pcVar1;
}



