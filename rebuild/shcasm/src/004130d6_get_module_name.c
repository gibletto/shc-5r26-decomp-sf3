#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 004130d6
// name : get_module_name
// size : 193
// sig  : void __cdecl get_module_name(char *out)


int __cdecl get_module_name(char *out)

{
  unsigned char _frec_110[272];
#define file_name (*(char (*)[256])(_frec_110 + 0))
#define obj_path (*(char * *)(_frec_110 + 256))
#define p (*(char * *)(_frec_110 + 264))
  ushort copy_status;
  char *name_end;
  
  obj_path = g_current_request->object_path;
  copy_status = copy_path_file_name(file_name,obj_path);
  if (copy_status == 0xffff) {
    report_message_at_source_line(0,0,0x132e,(char *)0x0);
  }
  for (p = file_name; (name_end = p, *p != '\0' && (*p != '.')); p = p + 1) {
  }
  *out = (char)p - (char)file_name;
  for (p = file_name; out = out + 1, p < name_end; p = p + 1) {
    *out = *p;
  }
  return;
#undef file_name
#undef obj_path
#undef p
}
