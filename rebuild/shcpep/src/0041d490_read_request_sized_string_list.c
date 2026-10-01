#include "decls.h"
#include "imports.h"

// entry: 0041d490
// name : read_request_sized_string_list
// size : 318
// sig  : void read_request_sized_string_list(request_sized_string * * list, FILE * in)


int __cdecl read_request_sized_string_list(request_sized_string **list,FILE *in)

{
  unsigned char _frec_8[8];
#define n_entries (*(short *)(_frec_8 + 0))
#define str_len (*(short *)(_frec_8 + 2))
#define i (*(int *)(_frec_8 + 4))
  uint result;
  char *buf;
  request_sized_string *entry;
  request_sized_string *tail;
  request_sized_string *tail_next;
  
  *list = (request_sized_string *)0x0;
  result = read_file_bytes(in,(char *)&n_entries,2);
  check_request_read_result(result);
  i = 0;
  if (0 < n_entries) {
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
      entry = stock_malloc(0xc);
      if (entry == (request_sized_string *)0x0) {
        report_message_by_code((char *)0x0,0,0xbcd,(char *)0x0);
        stock_exit(9);
      }
      entry->str = buf;
      entry->len = str_len + -1;
      entry->next = (request_sized_string *)0x0;
      tail = *list;
      if (tail == (request_sized_string *)0x0) {
        *list = entry;
      }
      else {
        tail_next = tail->next;
        while (tail_next != (request_sized_string *)0x0) {
          tail = tail->next;
          tail_next = tail->next;
        }
        tail->next = entry;
      }
      i = i + 1;
    } while (i < n_entries);
  }
  return;
#undef n_entries
#undef str_len
#undef i
}



