#include "decls.h"
#include "imports.h"

// entry: 00424470
// name : read_tagged_string_list
// size : 325
// sig  : void read_tagged_string_list(int * head, FILE * fp)


int __cdecl read_tagged_string_list(int *head,FILE *fp)

{
  unsigned char _frec_a[10];
#define cnt (*(short *)(_frec_a + 0))
#define tag (*(undefined2 *)(_frec_a + 2))
#define len (*(short *)(_frec_a + 4))
#define i (*(int *)(_frec_a + 6))
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
      result = read_bytes(fp,(char *)&tag,4);
      check_read_result(result);
      if (len == 0) {
        write_error_record((char *)0x0,0,0x12c4,(char *)0x0);
        stock_exit(0xb);
      }
      buf = stock_malloc((int)len);
      if (buf == (char *)0x0) {
        write_error_record((char *)0x0,0,0xbcd,(char *)0x0);
        stock_exit(9);
      }
      result = read_bytes(fp,buf,(int)len);
      check_read_result(result);
      item = stock_malloc(0xc);
      if (item == (undefined4 *)0x0) {
        write_error_record((char *)0x0,0,0xbcd,(char *)0x0);
        stock_exit(9);
      }
      item[2] = buf;
      *item = 0;
      *(undefined2 *)(item + 1) = tag;
      *(short *)((int)item + 6) = len;
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
#undef tag
#undef len
#undef i
}



