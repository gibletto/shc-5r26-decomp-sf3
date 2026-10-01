#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_symbol
#define g_current_symbol (*(symbol * *)(g_sd + 0x6d4c))
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00407fe0
// name : increment_label_ref_count
// size : 232
// sig  : void increment_label_ref_count(short labno)


int __cdecl increment_label_ref_count(short labno)

{
  byte kind;
  short sym_number;
  
  g_current_symbol = g_symbol_hash[labno % 0x3fd];
  sym_number = g_current_symbol->number;
  while (sym_number != labno) {
    g_current_symbol = g_current_symbol->hash_next;
    sym_number = g_current_symbol->number;
  }
  if (((byte)g_stage_flags & 8) != 0) {
    _printf(s_inclad_start__labno___d__00425a40,(int)labno);
    _printf(s_labtype___d__00425a0c,(int)(char)g_current_symbol->type);
    _printf(s_reference_count___ld_004259c0,g_current_symbol->ref_count);
  }
  if ((g_current_symbol != (symbol *)0x0) &&
     ((((kind = g_current_symbol->type & 0x1f, kind == 2 || (kind == 3)) || (kind == 4)) ||
      (kind == 5)))) {
    g_current_symbol->ref_count = g_current_symbol->ref_count + 1;
    g_current_symbol->flags = g_current_symbol->flags | 0x20;
    if (((byte)g_stage_flags & 8) != 0) {
      _printf(s_incriment_labno___d__00425a28,(int)labno);
      _printf(s_label_reference_count___ld_004259f0,g_current_symbol->ref_count);
    }
  }
  return;
}



