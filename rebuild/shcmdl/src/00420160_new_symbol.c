#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_func_node
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 00420160
// name : new_symbol
// size : 600
// sig  : uint new_symbol(short from_symx, uchar kind)


uint __cdecl new_symbol(short from_symx,uchar kind)

{
  short symx;
  uint uVar1;
  int iVar2;
  void *info;
  symbol *sym;
  
  iVar2 = new_symbol_number();
  symx = (short)iVar2;
  if (from_symx < 1) {
    clear_symbol(symx);
    g_symtab[symx].sclass = kind;
    g_symtab[symx].unknown_16 = g_symtab[g_func_node->symx].unknown_16;
  }
  else {
    iVar2 = (int)from_symx;
    g_symtab[symx].sclass = g_symtab[iVar2].sclass;
    g_symtab[symx].type = g_symtab[iVar2].type;
    g_symtab[symx].impvol = g_symtab[iVar2].impvol;
    g_symtab[symx].unknown_04 = g_symtab[iVar2].unknown_04;
    g_symtab[symx].unknown_06 = g_symtab[iVar2].unknown_06;
    g_symtab[symx].flags = g_symtab[iVar2].flags;
    g_symtab[symx].size = g_symtab[iVar2].size;
    g_symtab[symx].ms_leaf = g_symtab[iVar2].ms_leaf;
    g_symtab[symx].unknown_16 = g_symtab[g_func_node->symx].unknown_16;
    g_symtab[symx].unknown_18 = g_symtab[iVar2].unknown_18;
    g_symtab[symx].ext_flags = g_symtab[iVar2].ext_flags;
    g_symtab[symx].ext_30 = g_symtab[iVar2].ext_30;
    g_symtab[symx].ext_34 = g_symtab[iVar2].ext_34;
    g_symtab[symx].inline_flags = '\0';
    g_symtab[symx].no_inline = '\0';
    g_symtab[symx].inline_symbols = 0;
    g_symtab[symx].inline_labels = 0;
    g_symtab[symx].name_len = '\0';
    g_symtab[symx].name = (char *)0x0;
    g_symtab[symx].info = (void *)0x0;
    g_symtab[symx].inline_body = (inline_body *)0x0;
    g_symtab[symx].new_info = (void *)0x0;
  }
  sym = g_symtab + symx;
  iVar2 = 0;
  switch(sym->sclass) {
  case '\x05':
  case '\x06':
  case '\a':
  case '\b':
    break;
  default:
    iVar2 = fatal_error(0x109b);
    return CONCAT22((short)((uint)iVar2 >> 0x10),symx);
  case '\n':
    info = stock_calloc(1,0x14);
    if (info == (void *)0x0) {
      abort_function_optimization();
    }
    g_symtab[symx].info = info;
    *(undefined2 *)g_symtab[symx].info = 0;
    *(undefined2 *)((int)g_symtab[symx].info + 2) = 0;
    *(undefined4 *)((int)g_symtab[symx].info + 4) = 0;
    uVar1 = (uint)g_symtab >> 0x10;
    *(undefined4 *)((int)g_symtab[symx].info + 8) = 0;
    return CONCAT22((short)uVar1,symx);
  case '\v':
    iVar2 = new_label_number();
    sym->unknown_04 = (short)iVar2;
  }
  return CONCAT22((short)((uint)iVar2 >> 0x10),symx);
}



