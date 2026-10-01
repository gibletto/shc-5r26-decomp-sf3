#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_symbol
#define g_current_symbol (*(symbol * *)(g_sd + 0x6d4c))
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00414b40
// name : check_label_movable
// size : 165
// sig  : short check_label_movable(short labno)


short __cdecl check_label_movable(short labno)

{
  short sym_labno;
  
  g_current_symbol = g_symbol_hash[labno % 0x3fd];
  sym_labno = g_current_symbol->number;
  while (sym_labno != labno) {
    g_current_symbol = g_current_symbol->hash_next;
    sym_labno = g_current_symbol->number;
  }
  if (((byte)g_stage_flags & 8) != 0) {
    _printf(s_labchk_start__labno___d__00427acc,(int)labno);
    _printf(s_labtype___d_00427abc,(int)(char)g_current_symbol->type);
  }
  if (((byte)g_stage_flags & 0x10) != 0) {
    _printf(s_labchk_end__rc__d_00427aa8,1);
  }
  return 1;
}



