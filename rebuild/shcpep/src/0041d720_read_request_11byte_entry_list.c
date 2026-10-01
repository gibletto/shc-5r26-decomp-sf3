#include "decls.h"
#include "imports.h"

// entry: 0041d720
// name : read_request_11byte_entry_list
// size : 250
// sig  : void read_request_11byte_entry_list(request_entry * * list, FILE * in)


int __cdecl read_request_11byte_entry_list(request_entry **list,FILE *in)

{
  unsigned char _frec_e[14];
#define n_entries (*(short *)(_frec_e + 0))
#define buf_a (*(undefined4 *)(_frec_e + 2))
#define buf_c0 (*(uchar *)(_frec_e + 6))
#define buf_c2 (*(uchar *)(_frec_e + 7))
#define buf_c3 (*(uchar *)(_frec_e + 8))
#define buf_b0 (*(uchar *)(_frec_e + 9))
#define buf_b1 (*(uchar *)(_frec_e + 10))
#define buf_b2 (*(uchar *)(_frec_e + 11))
#define buf_b3 (*(uchar *)(_frec_e + 12))
  uint result;
  request_entry *entry;
  int i;
  request_entry *tail;
  
  i = 0;
  result = read_file_bytes(in,(char *)&n_entries,2);
  check_request_read_result(result);
  tail = buf_a;
  if (0 < n_entries) {
    do {
      result = read_file_bytes(in,(char *)&buf_a,0xb);
      check_request_read_result(result);
      entry = stock_malloc(0x10);
      if (entry == (request_entry *)0x0) {
        report_message_by_code((char *)0x0,0,0xbcd,(char *)0x0);
        stock_exit(9);
      }
      entry->next = (request_entry *)0x0;
      entry->a[0] = (uchar)buf_a;
      entry->a[1] = (*(unsigned char *)((char *)&buf_a + 1));
      entry->a[2] = (*(unsigned char *)((char *)&buf_a + 2));
      entry->a[3] = (*(unsigned char *)((char *)&buf_a + 3));
      entry->c[0] = buf_c0;
      entry->c[2] = buf_c2;
      entry->c[3] = buf_c3;
      entry->b[0] = buf_b0;
      entry->b[1] = buf_b1;
      entry->b[2] = buf_b2;
      entry->b[3] = buf_b3;
      if (*list == (request_entry *)0x0) {
        *list = entry;
      }
      else {
        tail->next = entry;
      }
      i = i + 1;
      tail = entry;
    } while (i < n_entries);
  }
  return;
#undef n_entries
#undef buf_a
#undef buf_c0
#undef buf_c2
#undef buf_c3
#undef buf_b0
#undef buf_b1
#undef buf_b2
#undef buf_b3
}



