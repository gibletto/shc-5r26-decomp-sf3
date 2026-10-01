#include "decls.h"
#include "imports.h"

// entry: 00423f90
// name : read_named_record_list
// size : 279
// sig  : void read_named_record_list(int * head, FILE * fp)


int __cdecl read_named_record_list(int *head,FILE *fp)

{
  unsigned char _frec_6[6];
#define cnt (*(short *)(_frec_6 + 0))
#define i (*(int *)(_frec_6 + 2))
  uint uVar1;
  char *buf;
  char *name;
  int next;
  int tail;
  
  *head = 0;
  uVar1 = read_bytes(fp,(char *)&cnt,2);
  check_read_result(uVar1);
  i = 0;
  if (0 < cnt) {
    do {
      buf = stock_malloc(0x20);
      if (buf == (char *)0x0) {
        write_error_record((char *)0x0,0,0xbcd,(char *)0x0);
        stock_exit(9);
      }
      uVar1 = read_bytes(fp,buf,0x20);
      check_read_result(uVar1);
      if (*(short *)(buf + 2) == 0) {
        name = (char *)0x0;
      }
      else {
        uVar1 = (uint)(short)(*(short *)(buf + 2) + 1);
        name = stock_malloc(uVar1);
        if (name == (char *)0x0) {
          write_error_record((char *)0x0,0,0xbcd,(char *)0x0);
          stock_exit(9);
        }
        uVar1 = read_bytes(fp,name,uVar1);
        check_read_result(uVar1);
      }
      *(char **)(buf + 4) = name;
      buf[0x1c] = '\0';
      buf[0x1d] = '\0';
      buf[0x1e] = '\0';
      buf[0x1f] = '\0';
      buf[0x18] = '\0';
      buf[0x19] = '\0';
      buf[0x1a] = '\0';
      buf[0x1b] = '\0';
      tail = *head;
      if (tail == 0) {
        *head = (int)buf;
      }
      else {
        next = *(int *)(tail + 0x1c);
        while (next != 0) {
          tail = *(int *)(tail + 0x1c);
          next = *(int *)(tail + 0x1c);
        }
        *(char **)(tail + 0x1c) = buf;
      }
      i = i + 1;
    } while (i < cnt);
  }
  return;
#undef cnt
#undef i
}



