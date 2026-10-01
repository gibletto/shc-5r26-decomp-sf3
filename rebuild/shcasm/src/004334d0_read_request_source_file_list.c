#include "decls.h"
#include "imports.h"

// entry: 004334d0
// name : read_request_source_file_list
// size : 325
// sig  : void __cdecl read_request_source_file_list(request_source_file **list,FILE *in)


int __cdecl read_request_source_file_list(request_source_file **list,FILE *in)

{
  unsigned char _frec_a[10];
#define item_count (*(short *)(_frec_a + 0))
#define file_filno (*(short *)(_frec_a + 2))
#define file_name_len (*(short *)(_frec_a + 4))
#define item_no (*(int *)(_frec_a + 6))
  uint result;
  char *buf;
  request_source_file *item;
  request_source_file *next_item;
  request_source_file *tail;
  
  *list = (request_source_file *)0x0;
  result = read_file_bytes(in,(char *)&item_count,2);
  check_request_read_result(result);
  item_no = 0;
  if (0 < item_count) {
    do {
      result = read_file_bytes(in,(char *)&file_filno,4);
      check_request_read_result(result);
      if (file_name_len == 0) {
        report_message_by_code((char *)0x0,0,0x12c4,(char *)0x0);
        stock_exit(0xb);
      }
      buf = stock_malloc((int)file_name_len);
      if (buf == (char *)0x0) {
        report_message_by_code((char *)0x0,0,0xbcd,(char *)0x0);
        stock_exit(9);
      }
      result = read_file_bytes(in,buf,(int)file_name_len);
      check_request_read_result(result);
      item = stock_malloc(0xc);
      if (item == (request_source_file *)0x0) {
        report_message_by_code((char *)0x0,0,0xbcd,(char *)0x0);
        stock_exit(9);
      }
      item->name = buf;
      item->next = (request_source_file *)0x0;
      item->filno = file_filno;
      item->name_len = file_name_len;
      tail = *list;
      if (tail == (request_source_file *)0x0) {
        *list = item;
      }
      else {
        next_item = tail->next;
        while (next_item != (request_source_file *)0x0) {
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
#undef file_filno
#undef file_name_len
#undef item_no
}
