#include "decls.h"
#include "imports.h"

// entry: 00423f00
// name : read_counted_string
// size : 144
// sig  : void read_counted_string(char * * dst, FILE * fp)


int __cdecl read_counted_string(char **dst,FILE *fp)

{
  unsigned char _frec_2[2];
#define len (*(short *)(_frec_2 + 0))
  uint result;
  char *buf;
  
  result = read_bytes(fp,(char *)&len,2);
  check_read_result(result);
  if (len != 0) {
    buf = stock_malloc((int)len);
    if (buf == (char *)0x0) {
      write_error_record((char *)0x0,0,0xbcd,(char *)0x0);
      stock_exit(9);
    }
    result = read_bytes(fp,buf,(int)len);
    check_read_result(result);
    *dst = buf;
    return;
  }
  *dst = (char *)0x0;
  return;
#undef len
}



