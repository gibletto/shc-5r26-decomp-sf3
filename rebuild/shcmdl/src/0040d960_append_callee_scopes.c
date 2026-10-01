#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0040d960
// name : append_callee_scopes
// size : 253
// sig  : void append_callee_scopes(short func_symx, short callee_symx)


int __cdecl append_callee_scopes(short func_symx,short callee_symx)

{
  short new_count;
  short *info;
  undefined2 *scopes;
  int iVar1;
  undefined2 *dst;
  int ofs;
  int old_n;
  void *callee_info;
  short old_count;
  undefined2 *src;
  
  callee_info = g_symtab[callee_symx].info;
  if (0 < *(short *)((int)callee_info + 8)) {
    info = g_symtab[func_symx].new_info;
    if (info == (short *)0x0) {
      info = copy_symbol_info(func_symx);
      g_symtab[func_symx].new_info = info;
    }
    g_inline_scopes_changed = '\x01';
    old_count = info[4];
    new_count = *(short *)((int)callee_info + 8) + old_count;
    info[4] = new_count;
    scopes = stock_calloc(1,new_count * 2);
    if (scopes == (undefined2 *)0x0) {
      abort_function_optimization();
    }
    ofs = 0;
    old_n = 0;
    if (0 < old_count) {
      old_n = (int)old_count;
      iVar1 = old_n;
      dst = scopes;
      do {
        ofs = ofs + 2;
        *dst = *(undefined2 *)(*(int *)(info + 8) + -2 + ofs);
        iVar1 = iVar1 + -1;
        dst = dst + 1;
      } while (iVar1 != 0);
    }
    ofs = 0;
    iVar1 = 0;
    if (0 < *(short *)((int)callee_info + 8)) {
      dst = scopes + old_n;
      do {
        src = (undefined2 *)(*(int *)((int)callee_info + 0x10) + ofs);
        ofs = ofs + 2;
        *dst = *src;
        iVar1 = iVar1 + 1;
        dst = dst + 1;
      } while (iVar1 < *(short *)((int)callee_info + 8));
    }
    if (*(void **)(info + 8) != (void *)0x0) {
      stock_free(*(void **)(info + 8));
    }
    *(undefined2 **)(info + 8) = scopes;
  }
  return;
}



