#include "decls.h"
#include "imports.h"

// entry: 004340c0
// name : write_request_source_file_list
// size : 167
// sig  : void __cdecl write_request_source_file_list(request_source_file **list,FILE *out)


int __cdecl write_request_source_file_list(request_source_file **list,FILE *out)

{
  unsigned char _frec_6[6];
#define item_count (*(short *)(_frec_6 + 0))
#define file_filno (*(short *)(_frec_6 + 2))
#define file_name_len (*(ushort *)(_frec_6 + 4))
  uint result;
  int scan_count;
  char *scan;
  char ch;
  request_source_file *item;
  
  item_count = 0;
  for (item = *list; item != (request_source_file *)0x0; item = item->next) {
    item_count = item_count + 1;
  }
  result = write_file_bytes(out,(char *)&item_count,2);
  check_request_write_result(result);
  if (item_count != 0) {
    for (item = *list; item != (request_source_file *)0x0; item = item->next) {
      file_filno = item->filno;
      scan_count = -1;
      scan = item->name;
      do {
        if (scan_count == 0) break;
        scan_count = scan_count + -1;
        ch = *scan;
        scan = scan + 1;
      } while (ch != '\0');
      file_name_len = ~(ushort)scan_count;
      result = write_file_bytes(out,(char *)&file_filno,4);
      check_request_write_result(result);
      result = write_file_bytes(out,item->name,(int)(short)file_name_len);
      check_request_write_result(result);
    }
  }
  return;
#undef item_count
#undef file_filno
#undef file_name_len
}
