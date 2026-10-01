#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_inline_groups
#define g_inline_groups (*(inline_group * *)(g_sd + 0xdec8))
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 00420520
// name : reset_inline_state
// size : 341
// sig  : void reset_inline_state(void)


int __cdecl reset_inline_state(void)

{
  int i;
  int ofs;
  undefined4 *slot;
  void *extra;
  inline_group *group;
  void *info;
  inline_group *next_group;
  
  if ((g_inline_flags & 7) == 7) {
    clear_inline_maps();
    group = g_inline_groups;
    while (group != (inline_group *)0x0) {
      next_group = group->next;
      free_inline_calls(group->calls);
      pool_free(group,0xc);
      group = next_group;
    }
    g_inline_groups = (inline_group *)0x0;
    g_inline_flags = g_inline_flags & 0xfe;
  }
  if (g_inline_scopes_changed == '\x01') {
    i = 1;
    if (0 < g_symbol_count) {
      ofs = 0x3c;
      do {
        info = *(void **)(g_symtab->unknown_39 + ofs + -0x39 + 0x20);
        if (info != (void *)0x0) {
          if (g_symtab->unknown_39[ofs + -0x39] == '\n') {
            if (*(void **)((int)info + 4) != (void *)0x0) {
              stock_free(*(void **)((int)info + 4));
            }
            extra = *(void **)((int)info + 8);
          }
          else {
            if (*(void **)((int)info + 0xc) != (void *)0x0) {
              stock_free(*(void **)((int)info + 0xc));
            }
            extra = *(void **)((int)info + 0x10);
          }
          if (extra != (void *)0x0) {
            stock_free(extra);
          }
          stock_free(info);
          *(undefined4 *)(g_symtab->unknown_39 + ofs + -0x19) = 0;
        }
        ofs = ofs + 0x3c;
        i = i + 1;
      } while (i <= g_symbol_count);
    }
    g_inline_scopes_changed = '\0';
  }
  free_switch_tables();
  slot = &g_switch_number_stack;
  for (i = 8; i != 0; i = i + -1) {
    *slot = 0;
    slot = slot + 1;
  }
  g_switch_depth = 0;
  free_symbols(g_saved_symbol_count + 1,(short)g_options->symbol_count);
  g_options->symbol_count = (int)g_saved_symbol_count;
  g_options->label_count = (int)g_saved_label_count;
  g_options->next_switch_table = g_saved_switch_count;
  return;
}



