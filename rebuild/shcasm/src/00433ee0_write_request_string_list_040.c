#include "decls.h"
#include "imports.h"

// entry: 00433ee0
// name : write_request_string_list_040
// size : 158
// sig  : void __cdecl write_request_string_list_040(request_string **list,FILE *out)


int __cdecl write_request_string_list_040(request_string **list,FILE *out)

{
  unsigned char _frec_4[4];
#define item_count (*(short *)(_frec_4 + 0))
#define str_len (*(ushort *)(_frec_4 + 2))
  uint result;
  int scan_count;
  char *scan;
  char ch;
  request_string *item;
  
  item_count = 0;
  for (item = *list; item != (request_string *)0x0; item = item->next) {
    item_count = item_count + 1;
  }
  result = write_file_bytes(out,(char *)&item_count,2);
  check_request_write_result(result);
  if (item_count != 0) {
    for (item = *list; item != (request_string *)0x0; item = item->next) {
      scan_count = -1;
      scan = item->str;
      do {
        if (scan_count == 0) break;
        scan_count = scan_count + -1;
        ch = *scan;
        scan = scan + 1;
      } while (ch != '\0');
      str_len = ~(ushort)scan_count;
      result = write_file_bytes(out,(char *)&str_len,2);
      check_request_write_result(result);
      result = write_file_bytes(out,item->str,(int)(short)str_len);
      check_request_write_result(result);
    }
  }
  return;
#undef item_count
#undef str_len
}
