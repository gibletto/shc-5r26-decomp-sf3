#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0040de10
// name : add_member_to_scope
// size : 173
// sig  : void add_member_to_scope(short scope_symx, short member_symx)


int __cdecl add_member_to_scope(short scope_symx,short member_symx)

{
  short *info;
  undefined2 *members;
  int i;
  int ofs;
  undefined2 *dst;
  short old_count;
  
  info = g_symtab[scope_symx].new_info;
  if (info == (short *)0x0) {
    info = copy_symbol_info(scope_symx);
    g_symtab[scope_symx].new_info = info;
  }
  g_inline_scopes_changed = '\x01';
  old_count = info[1];
  info[1] = old_count + 1;
  members = stock_calloc(1,(short)(old_count + 1) * 2);
  if (members == (undefined2 *)0x0) {
    abort_function_optimization();
  }
  ofs = 0;
  i = 0;
  dst = members;
  if (info[1] != 1 && -1 < info[1] + -1) {
    do {
      ofs = ofs + 2;
      *dst = *(undefined2 *)(*(int *)(info + 4) + -2 + ofs);
      i = i + 1;
      dst = dst + 1;
    } while (i < info[1] + -1);
  }
  members[i] = member_symx;
  if (*(void **)(info + 4) != (void *)0x0) {
    stock_free(*(void **)(info + 4));
  }
  *(undefined2 **)(info + 4) = members;
  return;
}



