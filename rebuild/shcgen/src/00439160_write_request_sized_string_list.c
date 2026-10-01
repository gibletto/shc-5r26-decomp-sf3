#include "decls.h"
#include "imports.h"

// entry: 00439160
// name : write_request_sized_string_list
// size : 148
// sig  : void write_request_sized_string_list(request_sized_string * * list, FILE * out)


int __cdecl write_request_sized_string_list(request_sized_string **list,FILE *out)

{
  unsigned char _frec_4[4];
#define n_entries (*(short *)(_frec_4 + 0))
#define str_len (*(short *)(_frec_4 + 2))
  uint result;
  request_sized_string *entry;
  
  n_entries = 0;
  for (entry = *list; entry != (request_sized_string *)0x0; entry = entry->next) {
    n_entries = n_entries + 1;
  }
  result = write_file_bytes(out,(char *)&n_entries,2);
  check_request_write_result(result);
  if (n_entries != 0) {
    for (entry = *list; entry != (request_sized_string *)0x0; entry = entry->next) {
      str_len = entry->len + 1;
      result = write_file_bytes(out,(char *)&str_len,2);
      check_request_write_result(result);
      result = write_file_bytes(out,entry->str,(int)str_len);
      check_request_write_result(result);
    }
  }
  return;
#undef n_entries
#undef str_len
}



