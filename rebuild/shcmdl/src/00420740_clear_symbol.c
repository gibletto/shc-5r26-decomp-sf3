#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 00420740
// name : clear_symbol
// size : 217
// sig  : void clear_symbol(short symx)


int __cdecl clear_symbol(short symx)

{
  int idx;
  
  idx = (int)symx;
  g_symtab[idx].sclass = '\0';
  g_symtab[idx].type = '\0';
  g_symtab[idx].name_len = '\0';
  g_symtab[idx].impvol = '\0';
  g_symtab[idx].unknown_04 = 0;
  g_symtab[idx].unknown_06 = '\0';
  g_symtab[idx].flags = '\0';
  g_symtab[idx].size = 0;
  g_symtab[idx].name = (char *)0x0;
  g_symtab[idx].info = (void *)0x0;
  g_symtab[idx].ms_leaf = 0;
  g_symtab[idx].unknown_16 = 0;
  g_symtab[idx].unknown_18 = 0;
  g_symtab[idx].inline_symbols = 0;
  g_symtab[idx].inline_labels = 0;
  g_symtab[idx].inline_flags = '\0';
  g_symtab[idx].ext_flags = '\0';
  g_symtab[idx].no_inline = '\0';
  g_symtab[idx].ext_30 = 0;
  g_symtab[idx].ext_34 = 0;
  g_symtab[idx].inline_body = (inline_body *)0x0;
  g_symtab[idx].new_info = (void *)0x0;
  return;
}



