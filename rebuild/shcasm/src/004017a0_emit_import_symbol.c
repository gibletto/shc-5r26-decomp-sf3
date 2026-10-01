#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 004017a0
// name : emit_import_symbol
// size : 628
// sig  : void __cdecl emit_import_symbol(short symbol_id)


int __cdecl emit_import_symbol(short symbol_id)

{
  uchar *data;
  byte bVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  short sVar4;
  symbol *sym;
  uint name_len;
  uint sym_name_len;
  int cmp;
  short routine_no;
  
  sym = find_symbol_by_id(symbol_id);
  data = (uchar *)sym->name;
  if (((sym->kind & 0x1f) != 10) || (sym->attr2 == 0xff)) {
    for (routine_no = 1; routine_no < 0xb7; routine_no = routine_no + 1) {
      if (*(int *)(&g_runtime_routine_names + routine_no * 4) != 0) {
        name_len = stock_strlen(*(char **)(&g_runtime_routine_names + routine_no * 4));
        sym_name_len = stock_strlen((char *)data);
        if ((name_len == sym_name_len) &&
           (cmp = _strcmp((char *)data,*(char **)(&g_runtime_routine_names + routine_no * 4)),
           cmp == 0)) {
          sVar4 = (short)((int)(routine_no + -1 + (routine_no + -1 >> 0x1f & 7U)) >> 3);
          bVar1 = (byte)(routine_no + -1 >> 0x1f);
          (&g_runtime_routine_imported)[sVar4] =
               (&g_runtime_routine_imported)[sVar4] |
               (byte)(1 << (7 - ((((byte)(routine_no + -1) ^ bVar1) - bVar1 & 7 ^ bVar1) - bVar1) &
                           0x1f));
          *(int *)(&g_runtime_routine_import_index + routine_no * 4) = g_next_import_index;
          break;
        }
      }
    }
    if ((sym->flags & 0x40) == 0) {
      if (g_current_request->code == 1) {
        name_len = stock_strlen((char *)data);
        sVar4 = (short)name_len;
        if (((sVar4 < 0x20) &&
            ((int)g_output_channels[1].end - (int)g_output_channels[1].cursor <
             (int)(short)(sVar4 + 3))) ||
           ((int)g_output_channels[1].end - (int)g_output_channels[1].cursor < 1)) {
          append_object_record_bytes((uchar *)0x0,0,0x8c);
        }
        append_object_record_byte(0xc0,0xc);
        uVar2 = (*(unsigned char *)((char *)&g_next_import_index + 2));
        uVar3 = (*(unsigned char *)((char *)&g_next_import_index + 3));
        sym->external_index = (undefined2)g_next_import_index;
        sym->unknown_2a[0] = uVar2;
        sym->unknown_2a[1] = uVar3;
        g_next_import_index = g_next_import_index + 1;
        if ((int)g_output_channels[1].end - (int)g_output_channels[1].cursor < sVar4 + 2) {
          append_object_record_bytes((uchar *)0x0,0,0x8c);
        }
        append_object_record_byte((char)name_len + '\x01',0xc);
        append_object_record_byte('_',0xc);
        append_object_record_bytes(data,(int)sVar4,0xc);
      }
      else {
        put_text_at_column(2,s__IMPORT_0043c034,1);
        put_char_at_column(2,'_',2);
        put_text_at_column(2,(char *)data,2);
        flush_output_line(2);
      }
    }
  }
  return;
}
