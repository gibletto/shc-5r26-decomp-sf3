#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_object_expr_cursor
#define g_object_expr_cursor (*(char * *)(g_sd + 0x10ca8))


// entry: 00427769
// name : emit_relocation_expression
// size : 473
// sig  : int emit_relocation_expression(label_ref * refs, int offset, int location, int size_bits, int extra_operand, int mode)


int __cdecl
emit_relocation_expression
          (label_ref *refs,int offset,int location,int size_bits,int extra_operand,int mode)

{
  int term_value;
  bool have_term;
  char *length_byte;
  
  append_reloc_entry_header(location,(short)size_bits,mode);
  length_byte = g_object_expr_cursor;
  g_object_expr_cursor = g_object_expr_cursor + 1;
  have_term = false;
  for (; (refs != (label_ref *)0x0 && (refs->labno1 != 0)); refs = refs->next) {
    term_value = emit_relocation_symbol_term(refs->labno1);
    if (refs->labno1 < 1) {
      if (have_term) {
        append_reloc_expression_byte(0x21);
      }
      else {
        append_reloc_expression_byte(0x24);
        have_term = true;
      }
    }
    else if (have_term) {
      append_reloc_expression_byte(0x20);
    }
    else {
      have_term = true;
    }
    offset = offset + term_value;
    if (refs->labno2 == 0) break;
    term_value = emit_relocation_symbol_term(refs->labno2);
    if (refs->labno2 < 1) {
      append_reloc_expression_byte(0x21);
    }
    else {
      append_reloc_expression_byte(0x20);
    }
    offset = offset + term_value;
  }
  if ((size_bits < 0x11) && (offset != 0)) {
    append_reloc_expression_byte(3);
    append_reloc_expression_byte(4);
    append_reloc_expression_long(offset);
    offset = 0;
    append_reloc_expression_byte(0x20);
  }
  if (extra_operand != 0) {
    append_reloc_expression_byte(0x25);
    append_reloc_expression_byte(1);
    append_reloc_expression_byte(extra_operand);
  }
  append_reloc_expression_byte(0xff);
  *length_byte = ((char)g_object_expr_cursor - (char)length_byte) + -1;
  append_reloc_expression_bytes((char *)0x0,0);
  return offset;
}



