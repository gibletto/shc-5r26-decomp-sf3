#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_scope_saved_sibling
#define g_scope_saved_sibling (*(debug_scope * *)(g_sd + 0x9320))


// entry: 0041e984
// name : close_debug_scope_range
// size : 290
// sig  : void __cdecl close_debug_scope_range(int at_previous_insn,int merge_with_previous)


int __cdecl close_debug_scope_range(int at_previous_insn,int merge_with_previous)

{
  symbol *func_sym;
  request_section *func_section;
  
  if ((merge_with_previous != 0) && (g_scope_saved_sibling != (debug_scope *)0x0)) {
    g_scope_stack[g_scope_top] = g_scope_saved_sibling;
    pool_free(g_scope_stack[g_scope_top]->next,0x10);
    g_scope_stack[g_scope_top]->next = (debug_scope *)0x0;
  }
  if (at_previous_insn == 0) {
    if (g_current_request->optimize != 0) {
      func_sym = find_symbol_by_id(g_debug_function_label);
      if ((func_sym->section_number != g_section_numbers[0]) || (g_location_counter == 0)) {
        func_sym = find_symbol_by_id(g_debug_function_label);
        func_section = find_section_by_id(g_current_request,func_sym->section_id);
        g_scope_stack[g_scope_top]->end = func_section->layout->location[0];
        goto LAB_0041ea9b;
      }
    }
    g_scope_stack[g_scope_top]->end = g_location_counter;
  }
  else {
    g_scope_stack[g_scope_top]->end = g_location_counter + -2;
  }
LAB_0041ea9b:
  g_scope_top = g_scope_top + -1;
  return;
}
