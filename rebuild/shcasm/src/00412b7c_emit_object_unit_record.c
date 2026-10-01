#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_object_language_tag_c
#define g_object_language_tag_c (*(unsigned char * *)(g_sd + 0x8030))
#undef g_object_language_tag_cpp
#define g_object_language_tag_cpp (*(unsigned char * *)(g_sd + 0x8060))


// entry: 00412b7c
// name : emit_object_unit_record
// size : 350
// sig  : void emit_object_unit_record(void)


/* WARNING: Removing unreachable block (ram,0x00412c12) */

int __cdecl emit_object_unit_record(void)

{
  unsigned char _frec_104[260];
#define counted_name (*(uchar (*)[256])(_frec_104 + 0))
  
  if (g_current_request->code == 1) {
    g_unit_record[0] = '@';
    store_u16_big_endian((ushort *)&g_section_count,(ushort *)(g_unit_record + 1));
    store_u16_big_endian((ushort *)&g_import_symbol_count,(ushort *)(g_unit_record + 3));
    store_u16_big_endian((ushort *)&g_export_symbol_count,(ushort *)(g_unit_record + 5));
    append_object_record_bytes(g_unit_record,7,6);
    get_module_name((char *)counted_name);
    append_object_record_bytes(counted_name,(char)counted_name[0] + 1,6);
    if (g_current_request->cpp_block == (request_cpp_block *)0x0) {
      copy_to_counted_string((char *)counted_name,g_object_language_tag_c);
    }
    else {
      copy_to_counted_string((char *)counted_name,g_object_language_tag_cpp);
    }
    append_object_record_bytes(counted_name,(char)counted_name[0] + 1,6);
    append_object_record_bytes(g_module_header_record + 1,0xc,6);
  }
  return;
#undef counted_name
}
