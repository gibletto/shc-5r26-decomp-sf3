#include "decls.h"
#include "imports.h"

// entry: 0042375c
// name : write_hex_long
// size : 58
// sig  : void __cdecl write_hex_long(short stream,int value,short field)


int __cdecl write_hex_long(short stream,int value,short field)

{
  unsigned char _frec_10[16];
#define hex_text (*(char (*)[8])(_frec_10 + 0))
#define text_nul (*(undefined1 *)(_frec_10 + 8))
  
  format_hex_digits(value,4,hex_text);
  text_nul = 0;
  put_text_at_column(stream,hex_text,field);
  return;
#undef hex_text
#undef text_nul
}
