#include "decls.h"
#include "imports.h"

// entry: 0041c460
// name : write_request_string
// size : 135
// sig  : void write_request_string(char * * field, FILE * out)


int __cdecl write_request_string(char **field,FILE *out)

{
  unsigned char _frec_2[2];
#define str_len (*(ushort *)(_frec_2 + 0))
  uint result;
  int remaining;
  char *p;
  char ch;
  
  if (*field == (char *)0x0) {
    str_len = 0;
    result = write_file_bytes(out,(char *)&str_len,2);
    check_request_write_result(result);
    return;
  }
  remaining = -1;
  p = *field;
  do {
    if (remaining == 0) break;
    remaining = remaining + -1;
    ch = *p;
    p = p + 1;
  } while (ch != '\0');
  str_len = ~(ushort)remaining;
  result = write_file_bytes(out,(char *)&str_len,2);
  check_request_write_result(result);
  result = write_file_bytes(out,*field,(int)(short)str_len);
  check_request_write_result(result);
  return;
#undef str_len
}



