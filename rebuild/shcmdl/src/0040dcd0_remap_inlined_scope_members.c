#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0040dcd0
// name : remap_inlined_scope_members
// size : 320
// sig  : void remap_inlined_scope_members(short scope_symx)


int __cdecl remap_inlined_scope_members(short scope_symx)

{
  inline_map_entry *entry;
  short *info;
  void *array;
  void *pvVar1;
  int slot;
  int ofs;
  short count;
  int i;
  
  entry = find_inline_map_entry(2,scope_symx);
  if (entry == (inline_map_entry *)0x0) {
    fatal_error(0x109b);
  }
  pvVar1 = g_symtab[entry->new_number].info;
  if (0 < *(short *)((int)pvVar1 + 2)) {
    info = g_symtab[scope_symx].new_info;
    if (info == (short *)0x0) {
      info = copy_symbol_info(scope_symx);
      g_symtab[scope_symx].new_info = info;
    }
    g_inline_scopes_changed = '\x01';
    count = *(short *)((int)pvVar1 + 2);
    info[1] = count;
    array = stock_calloc(1,count * 2);
    *(void **)(info + 4) = array;
    if (array == (void *)0x0) {
      abort_function_optimization();
    }
    count = 0;
    ofs = 0;
    i = 0;
    if (0 < *(short *)((int)pvVar1 + 2)) {
      do {
        entry = find_inline_map_entry(1,*(short *)(*(int *)((int)pvVar1 + 8) + ofs));
        if (entry != (inline_map_entry *)0x0) {
          slot = (int)count;
          count = count + 1;
          *(short *)(*(int *)(info + 4) + slot * 2) = entry->new_number;
        }
        ofs = ofs + 2;
        i = i + 1;
      } while (i < *(short *)((int)pvVar1 + 2));
    }
    if (count == 0) {
      stock_free(*(void **)(info + 4));
      info[4] = 0;
      info[5] = 0;
      info[1] = 0;
      return;
    }
    if (info[1] != count) {
      info[1] = count;
      pvVar1 = stock_realloc(*(void **)(info + 4),count * 2);
      *(void **)(info + 4) = pvVar1;
      if (pvVar1 == (void *)0x0) {
        abort_function_optimization();
      }
    }
  }
  return;
}



