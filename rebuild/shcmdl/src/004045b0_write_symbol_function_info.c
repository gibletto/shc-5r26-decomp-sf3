#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x267c4))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 004045b0
// name : write_symbol_function_info
// size : 305
// sig  : void write_symbol_function_info(symbol * sym)


int __cdecl write_symbol_function_info(symbol *sym)

{
  unsigned char _frec_8[8];
#define impvol_flag (*(uchar *)(_frec_8 + 0))
#define param_count (*(char *)(_frec_8 + 1))
#define scope_symx (*(undefined2 *)(_frec_8 + 2))
#define param_symx (*(short *)(_frec_8 + 4))
#define scope_count (*(short *)(_frec_8 + 6))
  int *finfo;
  bool more;
  
  finfo = sym->info;
  write_symbol_type((char)finfo[1]);
  write_symbol_aggregate_size((uchar)finfo[1],*finfo);
  write_symbol_bytes(g_sym_file,(char *)((int)finfo + 5),1);
  param_count = *(char *)((int)finfo + 6);
  write_symbol_bytes(g_sym_file,&param_count,1);
  while (more = param_count != '\0', param_count = param_count + -1, more) {
    param_symx = *(short *)(finfo[3] + param_count * 2);
    impvol_flag = g_symtab[param_symx].impvol;
    write_symbol_bytes(g_sym_file,(char *)&param_symx,2);
    write_symbol_bytes(g_sym_file,(char *)&impvol_flag,1);
  }
  scope_count = (short)finfo[2];
  write_symbol_bytes(g_sym_file,(char *)&scope_count,2);
  while (scope_count != 0) {
    scope_count = scope_count + -1;
    scope_symx = *(undefined2 *)(finfo[4] + scope_count * 2);
    write_symbol_bytes(g_sym_file,(char *)&scope_symx,2);
  }
  return;
#undef impvol_flag
#undef param_count
#undef scope_symx
#undef param_symx
#undef scope_count
}



