#include "decls.h"
#include "imports.h"

// entry: 00433db0
// name : write_request_string
// size : 135
// sig  : void __cdecl write_request_string(char **field,FILE *out)


int __cdecl write_request_string(char **field,FILE *out)

{
  unsigned char _frec_2[2];
#define str_len (*(ushort *)(_frec_2 + 0))
  uint result;
  int scan_count;
  char *scan;
  char ch;
  
  if (*field == (char *)0x0) {
    str_len = 0;
    result = write_file_bytes(out,(char *)&str_len,2);
    check_request_write_result(result);
    return;
  }
  scan_count = -1;
  scan = *field;
  do {
    if (scan_count == 0) break;
    scan_count = scan_count + -1;
    ch = *scan;
    scan = scan + 1;
  } while (ch != '\0');
  str_len = ~(ushort)scan_count;
  result = write_file_bytes(out,(char *)&str_len,2);
  check_request_write_result(result);
  result = write_file_bytes(out,*field,(int)(short)str_len);
  check_request_write_result(result);
  return;
#undef str_len
}
