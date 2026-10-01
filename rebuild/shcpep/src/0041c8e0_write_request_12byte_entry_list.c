#include "decls.h"
#include "imports.h"

// entry: 0041c8e0
// name : write_request_12byte_entry_list
// size : 197
// sig  : void write_request_12byte_entry_list(request_entry * * list, FILE * out)


int __cdecl write_request_12byte_entry_list(request_entry **list,FILE *out)

{
  unsigned char _frec_e[14];
#define n_entries (*(short *)(_frec_e + 0))
#define buf_b0 (*(uchar *)(_frec_e + 2))
#define buf_b1 (*(uchar *)(_frec_e + 3))
#define buf_b2 (*(uchar *)(_frec_e + 4))
#define buf_b3 (*(uchar *)(_frec_e + 5))
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
  
  n_entries = 0;
  for (entry = *list; entry != (request_entry *)0x0; entry = entry->next) {
    n_entries = n_entries + 1;
  }
  result = write_file_bytes(out,(char *)&n_entries,2);
  check_request_write_result(result);
  if (n_entries != 0) {
    for (entry = *list; entry != (request_entry *)0x0; entry = entry->next) {
      buf_b0 = entry->b[0];
      buf_b1 = entry->b[1];
      buf_b2 = entry->b[2];
      buf_b3 = entry->b[3];
      buf_a0 = entry->a[0];
      buf_a1 = entry->a[1];
      buf_a2 = entry->a[2];
      buf_a3 = entry->a[3];
      buf_c0 = entry->c[0];
      buf_c1 = entry->c[1];
      buf_c2 = entry->c[2];
      buf_c3 = entry->c[3];
      result = write_file_bytes(out,(char *)&buf_b0,0xc);
      check_request_write_result(result);
    }
  }
  return;
#undef n_entries
#undef buf_b0
#undef buf_b1
#undef buf_b2
#undef buf_b3
#undef buf_a0
#undef buf_a1
#undef buf_a2
#undef buf_a3
#undef buf_c0
#undef buf_c1
#undef buf_c2
#undef buf_c3
}



