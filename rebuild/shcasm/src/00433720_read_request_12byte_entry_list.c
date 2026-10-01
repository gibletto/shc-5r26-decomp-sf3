#include "decls.h"
#include "imports.h"

// entry: 00433720
// name : read_request_12byte_entry_list
// size : 257
// sig  : void __cdecl read_request_12byte_entry_list(request_entry **list,FILE *in)


int __cdecl read_request_12byte_entry_list(request_entry **list,FILE *in)

{
  unsigned char _frec_e[14];
#define item_count (*(short *)(_frec_e + 0))
#define local_c (*(undefined4 *)(_frec_e + 2))
#define local_8 (*(uchar *)(_frec_e + 6))
#define local_7 (*(uchar *)(_frec_e + 7))
#define local_6 (*(uchar *)(_frec_e + 8))
#define local_5 (*(uchar *)(_frec_e + 9))
#define local_4 (*(uchar *)(_frec_e + 10))
#define local_3 (*(uchar *)(_frec_e + 11))
#define local_2 (*(uchar *)(_frec_e + 12))
#define local_1 (*(uchar *)(_frec_e + 13))
  uint result;
  request_entry *item;
  int i;
  request_entry *prev;
  
  i = 0;
  result = read_file_bytes(in,(char *)&item_count,2);
  check_request_read_result(result);
  prev = local_c;
  if (0 < item_count) {
    do {
      result = read_file_bytes(in,(char *)&local_c,0xc);
      check_request_read_result(result);
      item = stock_malloc(0x10);
      if (item == (request_entry *)0x0) {
        report_message_by_code((char *)0x0,0,0xbcd,(char *)0x0);
        stock_exit(9);
      }
      item->next = (request_entry *)0x0;
      item->b[0] = (uchar)local_c;
      item->b[1] = (*(unsigned char *)((char *)&local_c + 1));
      item->b[2] = (*(unsigned char *)((char *)&local_c + 2));
      item->b[3] = (*(unsigned char *)((char *)&local_c + 3));
      item->a[0] = local_8;
      item->a[1] = local_7;
      item->a[2] = local_6;
      item->a[3] = local_5;
      item->c[0] = local_4;
      item->c[1] = local_3;
      item->c[2] = local_2;
      item->c[3] = local_1;
      if (*list == (request_entry *)0x0) {
        *list = item;
      }
      else {
        prev->next = item;
      }
      i = i + 1;
      prev = item;
    } while (i < item_count);
  }
  return;
#undef item_count
#undef local_c
#undef local_8
#undef local_7
#undef local_6
#undef local_5
#undef local_4
#undef local_3
#undef local_2
#undef local_1
}
