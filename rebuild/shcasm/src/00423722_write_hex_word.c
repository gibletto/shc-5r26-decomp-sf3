#include "decls.h"
#include "imports.h"

// entry: 00423722
// name : write_hex_word
// size : 58
// sig  : void __cdecl write_hex_word(short stream,int value,short field)


int __cdecl write_hex_word(short stream,int value,short field)

{
  unsigned char _frec_c[12];
#define hex_text (*(char (*)[4])(_frec_c + 0))
#define text_nul (*(undefined1 *)(_frec_c + 4))
  
  format_hex_digits(value,2,hex_text);
  text_nul = 0;
  put_text_at_column(stream,hex_text,field);
  return;
#undef hex_text
#undef text_nul
}
