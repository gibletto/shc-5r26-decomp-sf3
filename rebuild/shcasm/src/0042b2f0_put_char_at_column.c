#include "decls.h"
#include "imports.h"

// entry: 0042b2f0
// name : put_char_at_column
// size : 46
// sig  : void __cdecl put_char_at_column(short channel,char c,short column)


int __cdecl put_char_at_column(short channel,char c,short column)

{
  unsigned char _frec_8[8];
#define char_text (*(char (*)[4])(_frec_8 + 0))
  
  char_text[0] = c;
  char_text[1] = 0;
  put_text_at_column(channel,char_text,column);
  return;
#undef char_text
}
