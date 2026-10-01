#include "decls.h"
#include "imports.h"

// entry: 004245c0
// name : read_record11_list
// size : 250
// sig  : void read_record11_list(int * head, FILE * fp)


int __cdecl read_record11_list(int *head,FILE *fp)

{
  unsigned char _frec_e[14];
#define cnt (*(short *)(_frec_e + 0))
#define local_c (*(undefined4 *)(_frec_e + 2))
#define local_8 (*(undefined1 *)(_frec_e + 6))
#define local_7 (*(undefined1 *)(_frec_e + 7))
#define local_6 (*(undefined1 *)(_frec_e + 8))
#define local_5 (*(undefined1 *)(_frec_e + 9))
#define local_4 (*(undefined1 *)(_frec_e + 10))
#define local_3 (*(undefined1 *)(_frec_e + 11))
#define local_2 (*(undefined1 *)(_frec_e + 12))
  uint result;
  undefined4 *item;
  int i;
  undefined4 *tail;
  
  i = 0;
  result = read_bytes(fp,(char *)&cnt,2);
  check_read_result(result);
  tail = local_c;
  if (0 < cnt) {
    do {
      result = read_bytes(fp,(char *)&local_c,0xb);
      check_read_result(result);
      item = stock_malloc(0x10);
      if (item == (undefined4 *)0x0) {
        write_error_record((char *)0x0,0,0xbcd,(char *)0x0);
        stock_exit(9);
      }
      *item = 0;
      *(char *)(item + 1) = (char)local_c;
      *(undefined1 *)((int)item + 5) = (*(unsigned char *)((char *)&local_c + 1));
      *(undefined1 *)((int)item + 6) = (*(unsigned char *)((char *)&local_c + 2));
      *(undefined1 *)((int)item + 7) = (*(unsigned char *)((char *)&local_c + 3));
      *(undefined1 *)(item + 3) = local_8;
      *(undefined1 *)((int)item + 0xe) = local_7;
      *(undefined1 *)((int)item + 0xf) = local_6;
      *(undefined1 *)(item + 2) = local_5;
      *(undefined1 *)((int)item + 9) = local_4;
      *(undefined1 *)((int)item + 10) = local_3;
      *(undefined1 *)((int)item + 0xb) = local_2;
      if (*head == 0) {
        *head = (int)item;
      }
      else {
        *tail = item;
      }
      i = i + 1;
      tail = item;
    } while (i < cnt);
  }
  return;
#undef cnt
#undef local_c
#undef local_8
#undef local_7
#undef local_6
#undef local_5
#undef local_4
#undef local_3
#undef local_2
}



