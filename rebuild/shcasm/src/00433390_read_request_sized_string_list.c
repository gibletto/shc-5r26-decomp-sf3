#include "decls.h"
#include "imports.h"

// entry: 00433390
// name : read_request_sized_string_list
// size : 318
// sig  : void __cdecl read_request_sized_string_list(request_sized_string **list,FILE *in)


int __cdecl read_request_sized_string_list(request_sized_string **list,FILE *in)

{
  unsigned char _frec_8[8];
#define item_count (*(short *)(_frec_8 + 0))
#define str_len (*(short *)(_frec_8 + 2))
#define item_no (*(int *)(_frec_8 + 4))
  uint result;
  char *buf;
  request_sized_string *item;
  request_sized_string *next_item;
  request_sized_string *tail;
  
  *list = (request_sized_string *)0x0;
  result = read_file_bytes(in,(char *)&item_count,2);
  check_request_read_result(result);
  item_no = 0;
  if (0 < item_count) {
    do {
      result = read_file_bytes(in,(char *)&str_len,2);
      check_request_read_result(result);
      if (str_len == 0) {
        report_message_by_code((char *)0x0,0,0x12c3,(char *)0x0);
        stock_exit(0xb);
      }
      buf = stock_malloc((int)str_len);
      if (buf == (char *)0x0) {
        report_message_by_code((char *)0x0,0,0xbcd,(char *)0x0);
        stock_exit(9);
      }
      result = read_file_bytes(in,buf,(int)str_len);
      check_request_read_result(result);
      item = stock_malloc(0xc);
      if (item == (request_sized_string *)0x0) {
        report_message_by_code((char *)0x0,0,0xbcd,(char *)0x0);
        stock_exit(9);
      }
      item->str = buf;
      item->len = str_len + -1;
      item->next = (request_sized_string *)0x0;
      tail = *list;
      if (tail == (request_sized_string *)0x0) {
        *list = item;
      }
      else {
        next_item = tail->next;
        while (next_item != (request_sized_string *)0x0) {
          tail = tail->next;
          next_item = tail->next;
        }
        tail->next = item;
      }
      item_no = item_no + 1;
    } while (item_no < item_count);
  }
  return;
#undef item_count
#undef str_len
#undef item_no
}
