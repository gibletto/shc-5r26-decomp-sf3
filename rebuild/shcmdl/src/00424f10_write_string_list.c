#include "decls.h"
#include "imports.h"

// entry: 00424f10
// name : write_string_list
// size : 158
// sig  : void write_string_list(int * head, FILE * fp)


int __cdecl write_string_list(int *head,FILE *fp)

{
  unsigned char _frec_4[4];
#define cnt (*(short *)(_frec_4 + 0))
#define len (*(ushort *)(_frec_4 + 2))
  uint result;
  int remaining;
  char *p;
  char ch;
  undefined4 *item;
  
  cnt = 0;
  for (item = (undefined4 *)*head; item != (undefined4 *)0x0; item = (undefined4 *)*item) {
    cnt = cnt + 1;
  }
  result = write_bytes(fp,(char *)&cnt,2);
  check_write_result(result);
  if (cnt != 0) {
    for (item = (undefined4 *)*head; item != (undefined4 *)0x0; item = (undefined4 *)*item) {
      remaining = -1;
      p = (char *)item[1];
      do {
        if (remaining == 0) break;
        remaining = remaining + -1;
        ch = *p;
        p = p + 1;
      } while (ch != '\0');
      len = ~(ushort)remaining;
      result = write_bytes(fp,(char *)&len,2);
      check_write_result(result);
      result = write_bytes(fp,(char *)item[1],(int)(short)len);
      check_write_result(result);
    }
  }
  return;
#undef cnt
#undef len
}



