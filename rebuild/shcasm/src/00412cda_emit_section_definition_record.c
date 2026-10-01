#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 00412cda
// name : emit_section_definition_record
// size : 447
// sig  : void __cdecl emit_section_definition_record(short kind,request_section *group)


int __cdecl emit_section_definition_record(short kind,request_section *group)

{
  unsigned char _frec_30[48];
#define local_30 (*(uint *)(_frec_30 + 0))
#define section_name (*(uchar (*)[32])(_frec_30 + 4))
#define attr_word (*(ushort (*)[2])(_frec_30 + 36))
#define name_length (*(uchar *)(_frec_30 + 40))
  int iVar1;
  
  if (g_current_request->code == 1) {
    append_object_record_bytes((uchar *)0x0,0,0xff);
    g_section_record[0] = '@';
    local_30 = 0;
    store_u32_big_endian(&local_30,(uint *)(g_section_record + 1));
    if (((g_current_request->flags_13d & 8) == 0) || (kind != 0)) {
      if ((g_current_request->align16 == '\0') || (kind != 0)) {
        if ((g_current_request->cpu == 4) && (kind != 0)) {
          local_30 = 8;
        }
        else {
          local_30 = 4;
        }
      }
      else {
        local_30 = 0x10;
      }
    }
    else {
      local_30 = 0x20;
    }
    store_u32_big_endian(&local_30,(uint *)(g_section_record + 9));
    store_u32_big_endian((uint *)(group->size + kind),(uint *)(g_section_record + 5));
    if (kind == 0) {
      g_section_record[0xd] = '\0';
    }
    else if ((0 < kind) && (kind < 4)) {
      g_section_record[0xd] = '\x10';
    }
    attr_word[0] = 0xffc0;
    store_u16_big_endian(attr_word,(ushort *)(g_section_record + 0xe));
    append_object_record_bytes(g_section_record,0x10,8);
    iVar1 = build_section_name((char *)section_name,group,kind);
    name_length = (uchar)iVar1;
    append_object_record_byte(name_length,8);
    append_object_record_bytes(section_name,(int)(char)name_length,8);
  }
  return;
#undef local_30
#undef section_name
#undef attr_word
#undef name_length
}
