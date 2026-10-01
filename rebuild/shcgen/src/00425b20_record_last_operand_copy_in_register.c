#include "decls.h"
#include "imports.h"

// entry: 00425b20
// name : record_last_operand_copy_in_register
// size : 312
// sig  : void record_last_operand_copy_in_register(gen_node * node, tmpl_header * tmpl, short left_reg, short right_reg, gen_node * operand)


int __cdecl
record_last_operand_copy_in_register
          (gen_node *node,tmpl_header *tmpl,short left_reg,short right_reg,gen_node *operand)

{
  short reg;
  tmpl_entry *entry;
  ushort opnd_code;
  tmpl_entry *first;
  ushort op;
  
  reg = -1;
  if ((left_reg != -1) || (right_reg != -1)) {
    first = tmpl->entries;
    op = first->op;
    entry = first;
    while (op != 0xff00) {
      entry = entry + 1;
      op = entry->op;
    }
    do {
      entry = entry + -1;
      if (entry < first) goto LAB_00425c2f;
      op = entry->op;
      if ((((((op == 0xc00) && (entry->opnd[0] == 0xa9)) ||
            ((op == 0xf00 && (entry->opnd[1] == 0xa9)))) ||
           ((op == 0x2700 && (entry->opnd[0] == 0xa9)))) ||
          ((op == 0x2800 && (entry->opnd[1] == 0xa9)))) ||
         (((op == 0x2b00 && (entry->opnd[0] == 0xa9)) ||
          ((op == 0x1c00 && (entry->opnd[1] == 0xa9)))))) {
        opnd_code = 0xa9;
        reg = left_reg;
        goto LAB_00425c2f;
      }
    } while (((((op != 0xc00) || (entry->opnd[0] != 0xaa)) &&
              ((op != 0xf00 || (entry->opnd[1] != 0xaa)))) &&
             ((op != 0x2700 || (entry->opnd[0] != 0xaa)))) &&
            (((op != 0x2800 || (entry->opnd[1] != 0xaa)) &&
             (((op != 0x2b00 || (entry->opnd[0] != 0xaa)) &&
              ((op != 0x1c00 || (entry->opnd[1] != 0xaa))))))));
    opnd_code = 0xaa;
    reg = right_reg;
LAB_00425c2f:
    if (reg != -1) {
      record_operand_copy_in_register(node,tmpl,reg,opnd_code,operand);
    }
  }
  return;
}



