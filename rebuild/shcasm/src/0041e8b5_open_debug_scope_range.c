#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_scope_saved_sibling
#define g_scope_saved_sibling (*(debug_scope * *)(g_sd + 0x9320))


// entry: 0041e8b5
// name : open_debug_scope_range
// size : 207
// sig  : void __cdecl open_debug_scope_range(int at_previous_insn)


int __cdecl open_debug_scope_range(int at_previous_insn)

{
  debug_scope *new_scope;
  debug_scope **link_slot;
  int old_top;
  
  old_top = g_scope_top;
  if (g_scope_stack[g_scope_top]->child == (debug_scope *)0x0) {
    g_scope_saved_sibling = (debug_scope *)0x0;
    link_slot = &g_scope_stack[g_scope_top]->child;
  }
  else {
    g_scope_saved_sibling = g_scope_stack[g_scope_top + 1];
    g_scope_top = g_scope_top + 1;
    link_slot = &g_scope_stack[g_scope_top]->next;
  }
  g_scope_top = old_top + 1;
  new_scope = pool_alloc(0x10);
  *link_slot = new_scope;
  g_scope_stack[g_scope_top] = *link_slot;
  if (at_previous_insn == 0) {
    g_scope_stack[g_scope_top]->start = g_location_counter;
  }
  else {
    g_scope_stack[g_scope_top]->start = g_location_counter + -2;
  }
  return;
}
