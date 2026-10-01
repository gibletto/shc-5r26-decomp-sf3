#include "decls.h"
#include "imports.h"

// entry: 004236e8
// name : write_hex_byte
// size : 58
// sig  : void __cdecl write_hex_byte(short stream,int value,short field)


int __cdecl write_hex_byte(short stream,int value,short field)

{
  unsigned char _frec_8[8];
#define hex_text (*(char (*)[2])(_frec_8 + 0))
#define text_nul (*(undefined1 *)(_frec_8 + 2))
  
  format_hex_digits(value,1,hex_text);
  text_nul = 0;
  put_text_at_column(stream,hex_text,field);
  return;
#undef hex_text
#undef text_nul
}
