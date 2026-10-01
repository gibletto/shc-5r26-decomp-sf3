#include "decls.h"
#include "imports.h"

// entry: 004240b0
// name : read_string_list
// size : 307
// sig  : void read_string_list(int * head, FILE * fp)


int __cdecl read_string_list(int *head,FILE *fp)

{
  unsigned char _frec_8[8];
#define cnt (*(short *)(_frec_8 + 0))
#define len (*(short *)(_frec_8 + 2))
#define i (*(int *)(_frec_8 + 4))
  uint result;
  char *buf;
  undefined4 *item;
  int next;
  int *tail;
  
  *head = 0;
  result = read_bytes(fp,(char *)&cnt,2);
  check_read_result(result);
  i = 0;
  if (0 < cnt) {
    do {
      result = read_bytes(fp,(char *)&len,2);
      check_read_result(result);
      if (len == 0) {
        write_error_record((char *)0x0,0,0x12c2,(char *)0x0);
        stock_exit(0xb);
      }
      buf = stock_malloc((int)len);
      if (buf == (char *)0x0) {
        write_error_record((char *)0x0,0,0xbcd,(char *)0x0);
        stock_exit(9);
      }
      result = read_bytes(fp,buf,(int)len);
      check_read_result(result);
      item = stock_malloc(8);
      if (item == (undefined4 *)0x0) {
        write_error_record((char *)0x0,0,0xbcd,(char *)0x0);
        stock_exit(9);
      }
      item[1] = buf;
      *item = 0;
      tail = (int *)*head;
      if (tail == (int *)0x0) {
        *head = (int)item;
      }
      else {
        next = *tail;
        while (next != 0) {
          tail = (int *)*tail;
          next = *tail;
        }
        *tail = (int)item;
      }
      i = i + 1;
    } while (i < cnt);
  }
  return;
#undef cnt
#undef len
#undef i
}



