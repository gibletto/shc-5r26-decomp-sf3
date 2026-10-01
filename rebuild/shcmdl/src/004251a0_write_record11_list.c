#include "decls.h"
#include "imports.h"

// entry: 004251a0
// name : write_record11_list
// size : 190
// sig  : void write_record11_list(int * head, FILE * fp)


int __cdecl write_record11_list(int *head,FILE *fp)

{
  unsigned char _frec_e[14];
#define cnt (*(short *)(_frec_e + 0))
#define local_c (*(char *)(_frec_e + 2))
#define local_b (*(undefined1 *)(_frec_e + 3))
#define local_a (*(undefined1 *)(_frec_e + 4))
#define local_9 (*(undefined1 *)(_frec_e + 5))
#define local_8 (*(undefined1 *)(_frec_e + 6))
#define local_7 (*(undefined1 *)(_frec_e + 7))
#define local_6 (*(undefined1 *)(_frec_e + 8))
#define local_5 (*(undefined1 *)(_frec_e + 9))
#define local_4 (*(undefined1 *)(_frec_e + 10))
#define local_3 (*(undefined1 *)(_frec_e + 11))
#define local_2 (*(undefined1 *)(_frec_e + 12))
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
      local_c = *(char *)(item + 1);
      local_b = *(undefined1 *)((int)item + 5);
      local_a = *(undefined1 *)((int)item + 6);
      local_9 = *(undefined1 *)((int)item + 7);
      local_8 = *(undefined1 *)(item + 3);
      local_7 = *(undefined1 *)((int)item + 0xe);
      local_6 = *(undefined1 *)((int)item + 0xf);
      local_5 = *(undefined1 *)(item + 2);
      local_4 = *(undefined1 *)((int)item + 9);
      local_3 = *(undefined1 *)((int)item + 10);
      local_2 = *(undefined1 *)((int)item + 0xb);
      result = write_bytes(fp,&local_c,0xb);
      check_write_result(result);
    }
  }
  return;
#undef cnt
#undef local_c
#undef local_b
#undef local_a
#undef local_9
#undef local_8
#undef local_7
#undef local_6
#undef local_5
#undef local_4
#undef local_3
#undef local_2
}



