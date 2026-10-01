#include "decls.h"
#include "imports.h"

// entry: 00438f80
// name : write_request_section_list
// size : 148
// sig  : void write_request_section_list(request_section * * list, FILE * out)


int __cdecl write_request_section_list(request_section **list,FILE *out)

{
  unsigned char _frec_2[2];
#define n_entries (*(short *)(_frec_2 + 0))
  uint result;
  short len;
  request_section *section;
  
  n_entries = 0;
  for (section = *list; section != (request_section *)0x0; section = section->next) {
    n_entries = n_entries + 1;
  }
  result = write_file_bytes(out,(char *)&n_entries,2);
  check_request_write_result(result);
  if (n_entries != 0) {
    for (section = *list; section != (request_section *)0x0; section = section->next) {
      len = section->name_len;
      result = write_file_bytes(out,(char *)section,0x20);
      check_request_write_result(result);
      if (section->name_len != 0) {
        result = write_file_bytes(out,section->name,(int)(short)(len + 1));
        check_request_write_result(result);
      }
    }
  }
  return;
#undef n_entries
}



