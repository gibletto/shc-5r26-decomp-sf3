#include "decls.h"
#include "imports.h"

// entry: 00423b50
// name : check_read_result
// size : 43
// sig  : void check_read_result(int result)


int __cdecl check_read_result(int result)

{
  if ((result == 0) || (result == -1)) {
    write_error_record((char *)0x0,0,0xce6,(char *)0x0);
    stock_exit(9);
  }
  return;
}



