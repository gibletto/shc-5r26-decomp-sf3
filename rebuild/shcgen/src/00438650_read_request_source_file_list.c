#include "decls.h"
#include "imports.h"

// entry: 00438650
// name : read_request_source_file_list
// size : 325
// sig  : void read_request_source_file_list(request_source_file * * list, FILE * in)


int __cdecl read_request_source_file_list(request_source_file **list,FILE *in)

{
  unsigned char _frec_a[10];
#define n_entries (*(short *)(_frec_a + 0))
#define file_no (*(short *)(_frec_a + 2))
#define name_size (*(short *)(_frec_a + 4))
#define i (*(int *)(_frec_a + 6))
  uint result;
  char *buf;
  request_source_file *entry;
  request_source_file *tail;
  request_source_file *tail_next;
  
  *list = (request_source_file *)0x0;
  result = read_file_bytes(in,(char *)&n_entries,2);
  check_request_read_result(result);
  i = 0;
  if (0 < n_entries) {
    do {
      result = read_file_bytes(in,(char *)&file_no,4);
      check_request_read_result(result);
      if (name_size == 0) {
        report_message_by_code((char *)0x0,0,0x12c4,(char *)0x0);
        stock_exit(0xb);
      }
      buf = stock_malloc((int)name_size);
      if (buf == (char *)0x0) {
        report_message_by_code((char *)0x0,0,0xbcd,(char *)0x0);
        stock_exit(9);
      }
      result = read_file_bytes(in,buf,(int)name_size);
      check_request_read_result(result);
      entry = stock_malloc(0xc);
      if (entry == (request_source_file *)0x0) {
        report_message_by_code((char *)0x0,0,0xbcd,(char *)0x0);
        stock_exit(9);
      }
      entry->name = buf;
      entry->next = (request_source_file *)0x0;
      entry->filno = file_no;
      entry->name_len = name_size;
      tail = *list;
      if (tail == (request_source_file *)0x0) {
        *list = entry;
      }
      else {
        tail_next = tail->next;
        while (tail_next != (request_source_file *)0x0) {
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
#undef file_no
#undef name_size
#undef i
}



