#include "decls.h"
#include "imports.h"

// entry: 0041c590
// name : write_request_string_list_040
// size : 158
// sig  : void write_request_string_list_040(request_string * * list, FILE * out)


int __cdecl write_request_string_list_040(request_string **list,FILE *out)

{
  unsigned char _frec_4[4];
#define n_entries (*(short *)(_frec_4 + 0))
#define str_len (*(ushort *)(_frec_4 + 2))
  uint result;
  int remaining;
  char *p;
  char ch;
  request_string *entry;
  
  n_entries = 0;
  for (entry = *list; entry != (request_string *)0x0; entry = entry->next) {
    n_entries = n_entries + 1;
  }
  result = write_file_bytes(out,(char *)&n_entries,2);
  check_request_write_result(result);
  if (n_entries != 0) {
    for (entry = *list; entry != (request_string *)0x0; entry = entry->next) {
      remaining = -1;
      p = entry->str;
      do {
        if (remaining == 0) break;
        remaining = remaining + -1;
        ch = *p;
        p = p + 1;
      } while (ch != '\0');
      str_len = ~(ushort)remaining;
      result = write_file_bytes(out,(char *)&str_len,2);
      check_request_write_result(result);
      result = write_file_bytes(out,entry->str,(int)(short)str_len);
      check_request_write_result(result);
    }
  }
  return;
#undef n_entries
#undef str_len
}



