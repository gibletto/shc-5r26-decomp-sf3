#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 00401b2a
// name : emit_export_symbol
// size : 579
// sig  : void __cdecl emit_export_symbol(short symbol_id)


int __cdecl emit_export_symbol(short symbol_id)

{
  unsigned char _frec_18[24];
#define value_be (*(uint *)(_frec_18 + 0))
#define sym_name_len (*(short *)(_frec_18 + 4))
#define sym_name (*(uchar * *)(_frec_18 + 8))
#define section_be (*(ushort (*)[2])(_frec_18 + 12))
#define sym (*(symbol * *)(_frec_18 + 16))
  undefined1 uVar1;
  undefined1 uVar2;
  uint uVar3;
  
  sym = find_symbol_by_id(symbol_id);
  sym_name = (uchar *)sym->name;
  if ((((sym->kind & 0x1f) < 7) || (9 < (sym->kind & 0x1f))) || (sym->attr2 == 0xff)) {
    if (g_current_request->code == 1) {
      uVar3 = stock_strlen((char *)sym_name);
      sym_name_len = (short)uVar3;
      if (((sym_name_len < 0x20) &&
          ((int)g_output_channels[1].end - (int)g_output_channels[1].cursor < sym_name_len + 9)) ||
         ((int)g_output_channels[1].end - (int)g_output_channels[1].cursor < 7)) {
        append_object_record_bytes((uchar *)0x0,0,0x94);
      }
      switch(sym->kind & 0x1f) {
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
        section_be[0] = sym->section_number;
        store_u16_big_endian(section_be,section_be);
        append_object_record_bytes((uchar *)section_be,2,0x14);
        append_object_record_byte('\0',0x14);
        break;
      case 6:
        break;
      case 7:
      case 8:
      case 9:
        section_be[0] = sym->section_number;
        store_u16_big_endian(section_be,section_be);
        append_object_record_bytes((uchar *)section_be,2,0x14);
        append_object_record_byte(' ',0x14);
      }
      store_u32_big_endian((uint *)&sym->value,&value_be);
      append_object_record_bytes((uchar *)&value_be,4,0x14);
      if ((int)g_output_channels[1].end - (int)g_output_channels[1].cursor < sym_name_len + 2) {
        append_object_record_bytes((uchar *)0x0,0,0x94);
      }
      append_object_record_byte((char)sym_name_len + '\x01',0x14);
      append_object_record_byte('_',0x14);
      append_object_record_bytes(sym_name,(int)sym_name_len,0x14);
      uVar1 = (*(unsigned char *)((char *)&g_next_export_index + 2));
      uVar2 = (*(unsigned char *)((char *)&g_next_export_index + 3));
      sym->external_index = (undefined2)g_next_export_index;
      sym->unknown_2a[0] = uVar1;
      sym->unknown_2a[1] = uVar2;
      g_next_export_index = g_next_export_index + 1;
    }
    else {
      put_text_at_column(2,s__EXPORT_0043c03c,1);
      put_char_at_column(2,'_',2);
      put_text_at_column(2,(char *)sym_name,2);
      flush_output_line(2);
    }
  }
  return;
#undef value_be
#undef sym_name_len
#undef sym_name
#undef section_be
#undef sym
}
