#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef PTR_DAT_00443040
#define PTR_DAT_00443040 (*(unsigned char * *)(g_sd + 0x8040))
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 00412995
// name : emit_object_module_header_record
// size : 487
// sig  : void emit_object_module_header_record(void)


int __cdecl emit_object_module_header_record(void)

{
  unsigned char _frec_108[264];
#define counted_name (*(uchar (*)[256])(_frec_108 + 0))
#define version_word (*(ushort (*)[2])(_frec_108 + 256))
  
  if (g_current_request->code == 1) {
    if (g_current_request->endian == '\0') {
      g_module_header_record[0] = ' ';
    }
    else {
      g_module_header_record[0] = '(';
    }
    g_module_header_record[1] = g_current_request->compile_date[9];
    g_module_header_record[2] = g_current_request->compile_date[10];
    month_name_to_digits((char *)(g_module_header_record + 3),g_current_request->compile_date + 3);
    g_module_header_record[5] = g_current_request->compile_date[0];
    g_module_header_record[6] = g_current_request->compile_date[1];
    g_module_header_record[7] = g_current_request->compile_date[0xc];
    g_module_header_record[8] = g_current_request->compile_date[0xd];
    g_module_header_record[9] = g_current_request->compile_date[0xf];
    g_module_header_record[10] = g_current_request->compile_date[0x10];
    g_module_header_record[0xb] = g_current_request->compile_date[0x12];
    g_module_header_record[0xc] = g_current_request->compile_date[0x13];
    version_word[0] = 1;
    store_u16_big_endian(version_word,(ushort *)(g_module_header_record + 0xd));
    g_module_header_record[0xf] = '\0';
    g_module_header_record[0x10] = '0';
    g_module_header_record[0x11] = '2';
    g_module_header_record[0x12] = '0';
    g_module_header_record[0x13] = '0';
    g_module_header_record[0x14] = '\b';
    g_module_header_record[0x15] = ' ';
    g_module_header_record[0x16] = ' ';
    g_module_header_record[0x17] = '\0';
    g_module_header_record[0x18] = '\0';
    g_module_header_record[0x19] = '\0';
    g_module_header_record[0x1a] = '\0';
    g_module_header_record[0x1b] = '\0';
    append_object_record_bytes(g_module_header_record,0x1c,4);
    get_module_name((char *)counted_name);
    append_object_record_bytes(counted_name,(char)counted_name[0] + 1,4);
    copy_to_counted_string((char *)counted_name,PTR_DAT_00443040);
    append_object_record_bytes(counted_name,(char)counted_name[0] + 1,4);
  }
  return;
#undef counted_name
#undef version_word
}
