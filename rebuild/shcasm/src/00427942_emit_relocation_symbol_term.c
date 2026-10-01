#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 00427942
// name : emit_relocation_symbol_term
// size : 315
// sig  : int emit_relocation_symbol_term(ushort labno)


int __cdecl emit_relocation_symbol_term(ushort labno)

{
  symbol *sym;
  request_section *sym_section;
  int term_value;
  
  if (labno == 0x8000) {
    append_reloc_expression_byte(5);
    append_reloc_expression_word((int)g_current_request->sections->next->layout->section_number[2]);
    term_value = 0;
  }
  else {
    sym = find_symbol_by_id((labno ^ (short)labno >> 0xf) - ((short)labno >> 0xf));
    if ((((sym->kind & 0x1f) == 0) || (5 < (sym->kind & 0x1f))) &&
       (((sym->kind & 0x1f) < 7 || (9 < (sym->kind & 0x1f))))) {
      term_value = sym->value;
      append_reloc_expression_byte(2);
      append_reloc_expression_word((int)sym->external_index);
    }
    else {
      term_value = sym->value;
      append_reloc_expression_byte(0);
      if ((sym->kind & 0x1f) == 2) {
        sym_section = find_section_by_id(g_current_request,sym->section_id);
        sym->section_number = sym_section->layout->section_number[0];
      }
      append_reloc_expression_word((int)sym->section_number);
    }
    if ((short)labno < 0) {
      term_value = -term_value;
    }
  }
  return term_value;
}



