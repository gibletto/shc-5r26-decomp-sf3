#include "decls.h"
#include "imports.h"

// entry: 00434230
// name : write_request_12byte_entry_list
// size : 197
// sig  : void __cdecl write_request_12byte_entry_list(request_entry **list,FILE *out)


int __cdecl write_request_12byte_entry_list(request_entry **list,FILE *out)

{
  unsigned char _frec_e[14];
#define item_count (*(short *)(_frec_e + 0))
#define entry_bytes (*(uchar *)(_frec_e + 2))
#define local_b (*(uchar *)(_frec_e + 3))
#define local_a (*(uchar *)(_frec_e + 4))
#define local_9 (*(uchar *)(_frec_e + 5))
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
  
  item_count = 0;
  for (item = *list; item != (request_entry *)0x0; item = item->next) {
    item_count = item_count + 1;
  }
  result = write_file_bytes(out,(char *)&item_count,2);
  check_request_write_result(result);
  if (item_count != 0) {
    for (item = *list; item != (request_entry *)0x0; item = item->next) {
      entry_bytes = item->b[0];
      local_b = item->b[1];
      local_a = item->b[2];
      local_9 = item->b[3];
      local_8 = item->a[0];
      local_7 = item->a[1];
      local_6 = item->a[2];
      local_5 = item->a[3];
      local_4 = item->c[0];
      local_3 = item->c[1];
      local_2 = item->c[2];
      local_1 = item->c[3];
      result = write_file_bytes(out,(char *)&entry_bytes,0xc);
      check_request_write_result(result);
    }
  }
  return;
#undef item_count
#undef entry_bytes
#undef local_b
#undef local_a
#undef local_9
#undef local_8
#undef local_7
#undef local_6
#undef local_5
#undef local_4
#undef local_3
#undef local_2
#undef local_1
}
