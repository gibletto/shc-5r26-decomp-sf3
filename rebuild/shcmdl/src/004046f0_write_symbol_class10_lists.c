#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x267c4))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 004046f0
// name : write_symbol_class10_lists
// size : 262
// sig  : void write_symbol_class10_lists(symbol * sym)


int __cdecl write_symbol_class10_lists(symbol *sym)

{
  unsigned char _frec_7[7];
#define impvol_flag (*(uchar *)(_frec_7 + 0))
#define sym_index (*(short *)(_frec_7 + 1))
#define scope_count (*(short *)(_frec_7 + 3))
#define member_count (*(short *)(_frec_7 + 5))
  bool more;
  short *sinfo;
  
  sinfo = sym->info;
  scope_count = *sinfo;
  write_symbol_bytes(g_sym_file,(char *)&scope_count,2);
  while (more = scope_count != 0, scope_count = scope_count + -1, more) {
    sym_index = *(short *)(*(int *)(sinfo + 2) + scope_count * 2);
    write_symbol_bytes(g_sym_file,(char *)&sym_index,2);
  }
  member_count = sinfo[1];
  write_symbol_bytes(g_sym_file,(char *)&member_count,2);
  while (member_count != 0) {
    member_count = member_count + -1;
    sym_index = *(short *)(*(int *)(sinfo + 4) + member_count * 2);
    impvol_flag = g_symtab[sym_index].impvol;
    write_symbol_bytes(g_sym_file,(char *)&sym_index,2);
    write_symbol_bytes(g_sym_file,(char *)&impvol_flag,1);
  }
  return;
#undef impvol_flag
#undef sym_index
#undef scope_count
#undef member_count
}



