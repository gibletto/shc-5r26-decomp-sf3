#include "decls.h"
#include "imports.h"

// entry: 00401a14
// name : emit_runtime_routine_imports
// size : 278
// sig  : void emit_runtime_routine_imports(void)


int __cdecl emit_runtime_routine_imports(void)

{
  short id;
  symbol *sym;
  byte *used_ptr;
  byte bit;
  short bit_no;
  short byte_no;
  byte *imported_ptr;
  undefined4 import_index;
  byte used_bits;
  
  used_ptr = &g_runtime_routines_used;
  imported_ptr = &g_runtime_routine_imported;
  for (byte_no = 0; byte_no < 0x20; byte_no = byte_no + 1) {
    used_bits = *used_ptr;
    bit = 0x80;
    for (bit_no = 0; bit_no < 8; bit_no = bit_no + 1) {
      if ((bit & used_bits) != 0) {
        id = bit_no + byte_no * 8 + 1;
        sym = create_symbol_entry('\v',0x80,id);
        sym->value = 0;
        sym->name = *(char **)(&g_runtime_routine_names + id * 4);
        sym->aux_index = 0;
        sym->layout_records = (layout_record *)0x0;
        if ((bit & *imported_ptr) == 0) {
          emit_import_symbol(id);
        }
        else {
          import_index = *(undefined4 *)(&g_runtime_routine_import_index + id * 4);
          sym->external_index = (short)import_index;
          sym->unknown_2a[0] = (char)((uint)import_index >> 0x10);
          sym->unknown_2a[1] = (char)((uint)import_index >> 0x18);
        }
      }
      bit = (byte)((uint)(int)(char)bit >> 1) & 0x7f;
    }
    used_ptr = used_ptr + 1;
    imported_ptr = imported_ptr + 1;
  }
  return;
}
