#include "decls.h"
#include "imports.h"

// entry: 00438170
// name : read_request_section_list
// size : 279
// sig  : void read_request_section_list(request_section * * list, FILE * in)


int __cdecl read_request_section_list(request_section **list,FILE *in)

{
  unsigned char _frec_6[6];
#define n_entries (*(short *)(_frec_6 + 0))
#define i (*(int *)(_frec_6 + 2))
  uint uVar1;
  request_section *section;
  char *name;
  request_section *tail;
  request_section *tail_next;
  
  *list = (request_section *)0x0;
  uVar1 = read_file_bytes(in,(char *)&n_entries,2);
  check_request_read_result(uVar1);
  i = 0;
  if (0 < n_entries) {
    do {
      section = stock_malloc(0x20);
      if (section == (request_section *)0x0) {
        report_message_by_code((char *)0x0,0,0xbcd,(char *)0x0);
        stock_exit(9);
      }
      uVar1 = read_file_bytes(in,(char *)section,0x20);
      check_request_read_result(uVar1);
      if (section->name_len == 0) {
        name = (char *)0x0;
      }
      else {
        uVar1 = (uint)(short)(section->name_len + 1);
        name = stock_malloc(uVar1);
        if (name == (char *)0x0) {
          report_message_by_code((char *)0x0,0,0xbcd,(char *)0x0);
          stock_exit(9);
        }
        uVar1 = read_file_bytes(in,name,uVar1);
        check_request_read_result(uVar1);
      }
      section->name = name;
      section->next = (request_section *)0x0;
      section->unknown_18 = 0;
      tail = *list;
      if (tail == (request_section *)0x0) {
        *list = section;
      }
      else {
        tail_next = tail->next;
        while (tail_next != (request_section *)0x0) {
          tail = tail->next;
          tail_next = tail->next;
        }
        tail->next = section;
      }
      i = i + 1;
    } while (i < n_entries);
  }
  return;
#undef n_entries
#undef i
}



