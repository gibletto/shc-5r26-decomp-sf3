#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00407f10
// name : write_asa_global_records
// size : 297
// sig  : void write_asa_global_records(short kind, short symx)


int __cdecl write_asa_global_records(short kind,short symx)

{
  uchar *sym_bytes;
  uint uVar1;
  uint sym_index;
  int sym_offset;
  short rec_kind;
  byte sclass;
  
  if (((kind == 7) || (kind == 8)) || (kind == 9)) {
    write_asa_data_symbol_record(kind,symx);
    return;
  }
  sym_index = 0xb7;
  g_asa_external_count = 0;
  g_asa_defined_count = 0;
  if (0xb6 < *(int *)g_request->unknown_0b0 + 0xb6) {
    sym_offset = 0x2250;
    do {
      sym_bytes = g_symbol_table->unknown_1a + sym_offset + -0x1a;
      sclass = sym_bytes[1];
      uVar1 = (int)sym_index >> 0x1f;
      if (sclass == 1) {
        g_asa_defined_count = g_asa_defined_count + 1;
LAB_00407f8c:
        if (((g_symbol_table[(sym_index ^ uVar1) - uVar1].type & 0xf8) == 0x48) &&
           ((sym_bytes[5] & 0x80) == 0)) {
          rec_kind = 0xc;
LAB_00407fb4:
          write_asa_global_symbol_record(rec_kind,(short)sym_index);
        }
      }
      else if (sclass == 2) {
        if (((g_symbol_table[(sym_index ^ uVar1) - uVar1].type & 0xf8) != 0x48) ||
           ((*sym_bytes & 0x10) == 0)) {
          g_asa_external_count = g_asa_external_count + 1;
          if ((g_symbol_table[(sym_index ^ uVar1) - uVar1].type & 0xf8) == 0x48) {
            rec_kind = 0xb;
          }
          else {
            rec_kind = 10;
          }
          goto LAB_00407fb4;
        }
      }
      else if (sclass == 3) goto LAB_00407f8c;
      sym_offset = sym_offset + 0x30;
      sym_index = sym_index + 1;
    } while ((int)sym_index <= *(int *)g_request->unknown_0b0 + 0xb6);
  }
  write_asa_record(0xe,0);
  return;
}



