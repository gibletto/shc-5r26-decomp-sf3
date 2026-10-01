#include "decls.h"
#include "imports.h"

// entry: 00433e40
// name : write_request_section_list
// size : 148
// sig  : void __cdecl write_request_section_list(request_section **list,FILE *out)


int __cdecl write_request_section_list(request_section **list,FILE *out)

{
  unsigned char _frec_2[2];
#define section_count (*(short *)(_frec_2 + 0))
  uint result;
  short name_len_saved;
  request_section *sec;
  
  section_count = 0;
  for (sec = *list; sec != (request_section *)0x0; sec = sec->next) {
    section_count = section_count + 1;
  }
  result = write_file_bytes(out,(char *)&section_count,2);
  check_request_write_result(result);
  if (section_count != 0) {
    for (sec = *list; sec != (request_section *)0x0; sec = sec->next) {
      name_len_saved = sec->name_len;
      result = write_file_bytes(out,(char *)sec,0x20);
      check_request_write_result(result);
      if (sec->name_len != 0) {
        result = write_file_bytes(out,sec->name,(int)(short)(name_len_saved + 1));
        check_request_write_result(result);
      }
    }
  }
  return;
#undef section_count
}
