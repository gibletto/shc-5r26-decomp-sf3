#include "decls.h"
#include "imports.h"

// entry: 004250f0
// name : write_tagged_string_list
// size : 167
// sig  : void write_tagged_string_list(int * head, FILE * fp)


int __cdecl write_tagged_string_list(int *head,FILE *fp)

{
  unsigned char _frec_6[6];
#define cnt (*(short *)(_frec_6 + 0))
#define tag (*(undefined2 *)(_frec_6 + 2))
#define len (*(ushort *)(_frec_6 + 4))
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
      tag = *(undefined2 *)(item + 1);
      remaining = -1;
      p = (char *)item[2];
      do {
        if (remaining == 0) break;
        remaining = remaining + -1;
        ch = *p;
        p = p + 1;
      } while (ch != '\0');
      len = ~(ushort)remaining;
      result = write_bytes(fp,(char *)&tag,4);
      check_write_result(result);
      result = write_bytes(fp,(char *)item[2],(int)(short)len);
      check_write_result(result);
    }
  }
  return;
#undef cnt
#undef tag
#undef len
}



