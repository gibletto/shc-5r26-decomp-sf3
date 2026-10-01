#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0040daf0
// name : add_scope_to_enclosing_block
// size : 467
// sig  : void add_scope_to_enclosing_block(il_node * block)


int __cdecl add_scope_to_enclosing_block(il_node *block)

{
  short *info;
  void *array;
  short sVar1;
  int ofs;
  short *member;
  il_node *encl;
  int j;
  short kept;
  short *block_info;
  int i;
  
  encl = block->parent;
  if (encl != (il_node *)0x0) {
    do {
      if (encl->op == IL_BLOCK) break;
      encl = encl->parent;
    } while (encl != (il_node *)0x0);
    if (encl != (il_node *)0x0) {
      info = g_symtab[encl->symx].new_info;
      if (info == (short *)0x0) {
        info = copy_symbol_info(encl->symx);
        g_symtab[encl->symx].new_info = info;
      }
      g_inline_scopes_changed = '\x01';
      sVar1 = *info + 1;
      *info = sVar1;
      if (sVar1 == 1) {
        array = stock_calloc(1,2);
        *(void **)(info + 2) = array;
        if (array == (void *)0x0) {
          abort_function_optimization();
        }
        **(short **)(info + 2) = block->symx;
        return;
      }
      block_info = g_symtab[block->symx].new_info;
      if (block_info == (short *)0x0) {
        block_info = g_symtab[block->symx].info;
      }
      array = stock_calloc(1,sVar1 * 2);
      if (array == (void *)0x0) {
        abort_function_optimization();
      }
      ofs = 0;
      kept = 0;
      i = 0;
      if (*info != 1 && -1 < *info + -1) {
        do {
          j = 0;
          sVar1 = *block_info;
          if (0 < sVar1) {
            member = *(short **)(block_info + 2);
            do {
              if (*member == *(short *)(*(int *)(info + 2) + ofs)) break;
              member = member + 1;
              j = j + 1;
            } while (j < sVar1);
          }
          if (sVar1 <= j) {
            *(undefined2 *)((int)array + kept * 2) = *(undefined2 *)(*(int *)(info + 2) + ofs);
            kept = kept + 1;
          }
          ofs = ofs + 2;
          i = i + 1;
        } while (i < *info + -1);
      }
      *(short *)((int)array + kept * 2) = block->symx;
      kept = kept + 1;
      stock_free(*(void **)(info + 2));
      *(void **)(info + 2) = array;
      if (*info == kept) {
        return;
      }
      *info = kept;
      array = stock_realloc(*(void **)(info + 2),kept * 2);
      *(void **)(info + 2) = array;
      if (array != (void *)0x0) {
        return;
      }
      abort_function_optimization();
      return;
    }
  }
  fatal_error(0x109b);
  return;
}



