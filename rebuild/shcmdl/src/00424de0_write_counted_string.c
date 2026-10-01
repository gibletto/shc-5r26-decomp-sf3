#include "decls.h"
#include "imports.h"

// entry: 00424de0
// name : write_counted_string
// size : 135
// sig  : void write_counted_string(char * * src, FILE * fp)


int __cdecl write_counted_string(char **src,FILE *fp)

{
  unsigned char _frec_2[2];
#define len (*(ushort *)(_frec_2 + 0))
  uint result;
  int remaining;
  char *p;
  char ch;
  
  if (*src == (char *)0x0) {
    len = 0;
    result = write_bytes(fp,(char *)&len,2);
    check_write_result(result);
    return;
  }
  remaining = -1;
  p = *src;
  do {
    if (remaining == 0) break;
    remaining = remaining + -1;
    ch = *p;
    p = p + 1;
  } while (ch != '\0');
  len = ~(ushort)remaining;
  result = write_bytes(fp,(char *)&len,2);
  check_write_result(result);
  result = write_bytes(fp,*src,(int)(short)len);
  check_write_result(result);
  return;
#undef len
}



