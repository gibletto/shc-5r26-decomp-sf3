#include "decls.h"
#include "imports.h"

// entry: 004273a8
// name : get_source_file_basename
// size : 176
// sig  : void __cdecl get_source_file_basename(char *out,request_source_file *file)


int __cdecl get_source_file_basename(char *out,request_source_file *file)

{
  unsigned char _frec_110[272];
#define file_name (*(char (*)[256])(_frec_110 + 0))
#define full_name (*(char * *)(_frec_110 + 256))
#define name_cursor (*(char * *)(_frec_110 + 264))
  ushort copy_result;
  char *name_end;
  
  full_name = file->name;
  copy_result = copy_path_file_name(file_name,full_name);
  if (copy_result == 0xffff) {
    report_message_at_source_line(0,0,0x132e,(char *)0x0);
  }
  for (name_cursor = file_name; name_end = name_cursor, *name_cursor != '\0';
      name_cursor = name_cursor + 1) {
  }
  *out = (char)name_cursor - (char)file_name;
  for (name_cursor = file_name; out = out + 1, name_cursor < name_end; name_cursor = name_cursor + 1
      ) {
    *out = *name_cursor;
  }
  return;
#undef file_name
#undef full_name
#undef name_cursor
}
