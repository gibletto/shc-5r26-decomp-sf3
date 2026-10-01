#include "decls.h"
#include "imports.h"

// entry: 00432f60
// name : read_request_string
// size : 144
// sig  : void __cdecl read_request_string(char **field,FILE *in)


int __cdecl read_request_string(char **field,FILE *in)

{
  unsigned char _frec_2[2];
#define str_len (*(short *)(_frec_2 + 0))
  uint result;
  char *buf;
  
  result = read_file_bytes(in,(char *)&str_len,2);
  check_request_read_result(result);
  if (str_len != 0) {
    buf = stock_malloc((int)str_len);
    if (buf == (char *)0x0) {
      report_message_by_code((char *)0x0,0,0xbcd,(char *)0x0);
      stock_exit(9);
    }
    result = read_file_bytes(in,buf,(int)str_len);
    check_request_read_result(result);
    *field = buf;
    return;
  }
  *field = (char *)0x0;
  return;
#undef str_len
}
