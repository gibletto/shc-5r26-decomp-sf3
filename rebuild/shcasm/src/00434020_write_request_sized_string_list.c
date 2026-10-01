#include "decls.h"
#include "imports.h"

// entry: 00434020
// name : write_request_sized_string_list
// size : 148
// sig  : void __cdecl write_request_sized_string_list(request_sized_string **list,FILE *out)


int __cdecl write_request_sized_string_list(request_sized_string **list,FILE *out)

{
  unsigned char _frec_4[4];
#define item_count (*(short *)(_frec_4 + 0))
#define str_len (*(short *)(_frec_4 + 2))
  uint result;
  request_sized_string *item;
  
  item_count = 0;
  for (item = *list; item != (request_sized_string *)0x0; item = item->next) {
    item_count = item_count + 1;
  }
  result = write_file_bytes(out,(char *)&item_count,2);
  check_request_write_result(result);
  if (item_count != 0) {
    for (item = *list; item != (request_sized_string *)0x0; item = item->next) {
      str_len = item->len + 1;
      result = write_file_bytes(out,(char *)&str_len,2);
      check_request_write_result(result);
      result = write_file_bytes(out,item->str,(int)str_len);
      check_request_write_result(result);
    }
  }
  return;
#undef item_count
#undef str_len
}
