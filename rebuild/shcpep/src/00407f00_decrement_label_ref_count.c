#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_symbol
#define g_current_symbol (*(symbol * *)(g_sd + 0x6d4c))
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00407f00
// name : decrement_label_ref_count
// size : 224
// sig  : void __cdecl decrement_label_ref_count(short labno)


int __cdecl decrement_label_ref_count(short labno)

{
  byte kind;
  symbol *sym;
  short sym_number;
  
  if (labno < 0) {
    labno = -labno;
  }
  if (labno < 0xb7) {
    sym = (symbol *)0x0;
  }
  else {
    sym = g_symbol_hash[labno % 0x3fd];
    sym_number = sym->number;
    while (sym_number != labno) {
      sym = sym->hash_next;
      sym_number = sym->number;
    }
  }
  if (((byte)g_stage_flags & 8) != 0) {
    _printf(s_labno___d__00425a1c,(int)labno);
    _printf(s_labtype___d__00425a0c,(int)(char)g_current_symbol->type);
    _printf(s_label_reference_count___ld_004259f0,g_current_symbol->ref_count);
  }
  if (((sym != (symbol *)0x0) &&
      ((((kind = sym->type & 0x1f, kind == 2 || ((kind == 3 && ((sym->flags & 0x20) != 0)))) ||
        ((kind == 4 && ((sym->flags & 0x20) != 0)))) || (kind == 5)))) &&
     (sym->ref_count = sym->ref_count + -1, ((byte)g_stage_flags & 8) != 0)) {
    _printf(s_decriment_labno___d__004259d8,(int)labno);
    _printf(s_reference_count___ld_004259c0,g_current_symbol->ref_count);
  }
  return;
}
