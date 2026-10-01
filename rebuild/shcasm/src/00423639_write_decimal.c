#include "decls.h"
#include "imports.h"

// entry: 00423639
// name : write_decimal
// size : 175
// sig  : void __cdecl write_decimal(short stream,int value,short field)


int __cdecl write_decimal(short stream,int value,short field)

{
  if (value == -0x80000000) {
    put_text_at_column(stream,s__2147483648_00441dc0,field);
  }
  else {
    if (value < 0) {
      put_char_at_column(stream,'-',field);
      value = -value;
    }
    if (value / 10 != 0) {
      write_decimal(stream,value / 10,field);
    }
    put_char_at_column(stream,(char)(value % 10) + '0',field);
  }
  return;
}
