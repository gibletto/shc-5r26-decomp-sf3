#include "decls.h"
#include "imports.h"

// entry: 0041c770
// name : write_request_source_file_list
// size : 167
// sig  : void write_request_source_file_list(request_source_file * * list, FILE * out)


int __cdecl write_request_source_file_list(request_source_file **list,FILE *out)

{
  unsigned char _frec_6[6];
#define n_entries (*(short *)(_frec_6 + 0))
#define file_no (*(short *)(_frec_6 + 2))
#define name_size (*(ushort *)(_frec_6 + 4))
  uint result;
  int remaining;
  char *p;
  char ch;
  request_source_file *entry;
  
  n_entries = 0;
  for (entry = *list; entry != (request_source_file *)0x0; entry = entry->next) {
    n_entries = n_entries + 1;
  }
  result = write_file_bytes(out,(char *)&n_entries,2);
  check_request_write_result(result);
  if (n_entries != 0) {
    for (entry = *list; entry != (request_source_file *)0x0; entry = entry->next) {
      file_no = entry->filno;
      remaining = -1;
      p = entry->name;
      do {
        if (remaining == 0) break;
        remaining = remaining + -1;
        ch = *p;
        p = p + 1;
      } while (ch != '\0');
      name_size = ~(ushort)remaining;
      result = write_file_bytes(out,(char *)&file_no,4);
      check_request_write_result(result);
      result = write_file_bytes(out,entry->name,(int)(short)name_size);
      check_request_write_result(result);
    }
  }
  return;
#undef n_entries
#undef file_no
#undef name_size
}



