#include "decls.h"
#include "imports.h"

// entry: 00428a20
// name : copy_file_basename
// size : 70
// sig  : uint copy_file_basename(char * dst, char * path)


uint __cdecl copy_file_basename(char *dst,char *path)

{
  undefined4 in_EAX;
  int offset;
  int iVar1;
  
  if ((path != (char *)0x0) && (dst != (char *)0x0)) {
    offset = find_basename_offset(path);
    iVar1 = copy_string(dst,path + (short)offset);
    return CONCAT22((short)((uint)iVar1 >> 0x10),(ushort)((short)offset == 0));
  }
  return CONCAT22((short)((uint)in_EAX >> 0x10),0xffff);
}



