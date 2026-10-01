#include "decls.h"
#include "imports.h"

// entry: 00425050
// name : write_sized_string_list
// size : 148
// sig  : void write_sized_string_list(int * head, FILE * fp)


int __cdecl write_sized_string_list(int *head,FILE *fp)

{
  unsigned char _frec_4[4];
#define cnt (*(short *)(_frec_4 + 0))
#define len (*(short *)(_frec_4 + 2))
  uint result;
  undefined4 *item;
  
  cnt = 0;
  for (item = (undefined4 *)*head; item != (undefined4 *)0x0; item = (undefined4 *)*item) {
    cnt = cnt + 1;
  }
  result = write_bytes(fp,(char *)&cnt,2);
  check_write_result(result);
  if (cnt != 0) {
    for (item = (undefined4 *)*head; item != (undefined4 *)0x0; item = (undefined4 *)*item) {
      len = *(short *)(item + 2) + 1;
      result = write_bytes(fp,(char *)&len,2);
      check_write_result(result);
      result = write_bytes(fp,(char *)item[1],(int)len);
      check_write_result(result);
    }
  }
  return;
#undef cnt
#undef len
}



