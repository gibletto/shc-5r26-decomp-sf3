#include "decls.h"
#include "imports.h"

// entry: 0041d820
// name : read_request_12byte_entry_list
// size : 257
// sig  : void read_request_12byte_entry_list(request_entry * * list, FILE * in)


int __cdecl read_request_12byte_entry_list(request_entry **list,FILE *in)

{
  unsigned char _frec_e[14];
#define n_entries (*(short *)(_frec_e + 0))
#define buf_b (*(undefined4 *)(_frec_e + 2))
#define buf_a0 (*(uchar *)(_frec_e + 6))
#define buf_a1 (*(uchar *)(_frec_e + 7))
#define buf_a2 (*(uchar *)(_frec_e + 8))
#define buf_a3 (*(uchar *)(_frec_e + 9))
#define buf_c0 (*(uchar *)(_frec_e + 10))
#define buf_c1 (*(uchar *)(_frec_e + 11))
#define buf_c2 (*(uchar *)(_frec_e + 12))
#define buf_c3 (*(uchar *)(_frec_e + 13))
  uint result;
  request_entry *entry;
  int i;
  request_entry *tail;
  
  i = 0;
  result = read_file_bytes(in,(char *)&n_entries,2);
  check_request_read_result(result);
  tail = buf_b;
  if (0 < n_entries) {
    do {
      result = read_file_bytes(in,(char *)&buf_b,0xc);
      check_request_read_result(result);
      entry = stock_malloc(0x10);
      if (entry == (request_entry *)0x0) {
        report_message_by_code((char *)0x0,0,0xbcd,(char *)0x0);
        stock_exit(9);
      }
      entry->next = (request_entry *)0x0;
      entry->b[0] = (uchar)buf_b;
      entry->b[1] = (*(unsigned char *)((char *)&buf_b + 1));
      entry->b[2] = (*(unsigned char *)((char *)&buf_b + 2));
      entry->b[3] = (*(unsigned char *)((char *)&buf_b + 3));
      entry->a[0] = buf_a0;
      entry->a[1] = buf_a1;
      entry->a[2] = buf_a2;
      entry->a[3] = buf_a3;
      entry->c[0] = buf_c0;
      entry->c[1] = buf_c1;
      entry->c[2] = buf_c2;
      entry->c[3] = buf_c3;
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
#undef buf_b
#undef buf_a0
#undef buf_a1
#undef buf_a2
#undef buf_a3
#undef buf_c0
#undef buf_c1
#undef buf_c2
#undef buf_c3
}



