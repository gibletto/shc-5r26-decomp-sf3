#include "decls.h"
#include "imports.h"

// entry: 00423589
// name : write_displacement_width_suffix
// size : 151
// sig  : void __cdecl write_displacement_width_suffix(short stream,short width)


int __cdecl write_displacement_width_suffix(short stream,short width)

{
  switch(width) {
  case 0:
    put_text_at_column(stream,&s_colon_8_00441db0,2);
    break;
  case 1:
    put_text_at_column(stream,&s_colon_16_00441db4,2);
    break;
  case 2:
    put_text_at_column(stream,&s_colon_32_00441db8,2);
    break;
  case 3:
    break;
  case 4:
    put_text_at_column(stream,&s_colon_4_00441dbc,2);
  }
  return;
}
