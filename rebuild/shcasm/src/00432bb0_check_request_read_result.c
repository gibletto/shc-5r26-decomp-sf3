#include "decls.h"
#include "imports.h"

// entry: 00432bb0
// name : check_request_read_result
// size : 43
// sig  : void __cdecl check_request_read_result(int result)


int __cdecl check_request_read_result(int result)

{
  if ((result == 0) || (result == -1)) {
    report_message_by_code((char *)0x0,0,0xce6,(char *)0x0);
    stock_exit(9);
  }
  return;
}
