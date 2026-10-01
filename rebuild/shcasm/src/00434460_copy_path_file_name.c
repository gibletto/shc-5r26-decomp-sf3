#include "decls.h"
#include "imports.h"

// entry: 00434460
// name : copy_path_file_name
// size : 70
// sig  : ushort copy_path_file_name(char * dest, char * path)


ushort __cdecl copy_path_file_name(char *dest,char *path)

{
  int name_offset;
  
  if ((path != (char *)0x0) && (dest != (char *)0x0)) {
    name_offset = find_path_file_name_offset(path);
    copy_string(dest,path + (short)name_offset);
    return (ushort)((short)name_offset == 0);
  }
  return 0xffff;
}



