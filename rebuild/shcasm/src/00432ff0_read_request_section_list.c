#include "decls.h"
#include "imports.h"

// entry: 00432ff0
// name : read_request_section_list
// size : 279
// sig  : void __cdecl read_request_section_list(request_section **list,FILE *in)


int __cdecl read_request_section_list(request_section **list,FILE *in)

{
  unsigned char _frec_6[6];
#define section_count (*(short *)(_frec_6 + 0))
#define section_no (*(int *)(_frec_6 + 2))
  uint result;
  request_section *buf;
  char *name_buf;
  request_section *next_sec;
  request_section *tail;
  
  *list = (request_section *)0x0;
  result = read_file_bytes(in,(char *)&section_count,2);
  check_request_read_result(result);
  section_no = 0;
  if (0 < section_count) {
    do {
      buf = stock_malloc(0x20);
      if (buf == (request_section *)0x0) {
        report_message_by_code((char *)0x0,0,0xbcd,(char *)0x0);
        stock_exit(9);
      }
      result = read_file_bytes(in,(char *)buf,0x20);
      check_request_read_result(result);
      if (buf->name_len == 0) {
        name_buf = (char *)0x0;
      }
      else {
        result = (uint)(short)(buf->name_len + 1);
        name_buf = stock_malloc(result);
        if (name_buf == (char *)0x0) {
          report_message_by_code((char *)0x0,0,0xbcd,(char *)0x0);
          stock_exit(9);
        }
        result = read_file_bytes(in,name_buf,result);
        check_request_read_result(result);
      }
      buf->name = name_buf;
      buf->next = (request_section *)0x0;
      buf->layout = (section_layout *)0x0;
      tail = *list;
      if (tail == (request_section *)0x0) {
        *list = buf;
      }
      else {
        next_sec = tail->next;
        while (next_sec != (request_section *)0x0) {
          tail = tail->next;
          next_sec = tail->next;
        }
        tail->next = buf;
      }
      section_no = section_no + 1;
    } while (section_no < section_count);
  }
  return;
#undef section_count
#undef section_no
}
