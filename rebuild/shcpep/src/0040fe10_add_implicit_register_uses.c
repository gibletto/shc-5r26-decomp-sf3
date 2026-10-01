#include "decls.h"
#include "imports.h"

// entry: 0040fe10
// name : add_implicit_register_uses
// size : 648
// sig  : void add_implicit_register_uses(psd * rec, uint * uses)


int __cdecl add_implicit_register_uses(psd *rec,uint *uses)

{
  char cVar1;
  psd_op op;
  ea *opnd;
  
  if ((rec->op == OP_CASEJMP) && (uses != (uint *)0x0)) {
    *uses = *uses | g_reg_mask_table[0];
  }
  op = rec->op;
  if ((((((((op == OP_XTRCT) || (op == OP_SHAD)) || (op == OP_SHLD)) ||
         ((OP_ROTCR < op && (op < OP_NON_66)))) || ((OP_NON_7F < op && (op < OP_NOT)))) ||
       (((OP_NON_B7 < op && (op < OP_NON_BF)) || (op == OP_NON_CC)))) ||
      ((op == OP_NON_D6 || (op == OP_NON_D8)))) &&
     ((opnd = rec->ea2, opnd != (ea *)0x0 && (((opnd->type & 0x1f) == 1 && (uses != (uint *)0x0)))))
     ) {
    cVar1 = opnd->base;
    if ((cVar1 < '\0') || ('_' < cVar1)) {
      if ((uses != (uint *)0x0) && ('_' < opnd->base)) {
        uses[1] = uses[1] | g_reg_mask_table[opnd->base];
      }
    }
    else {
      *uses = *uses | g_reg_mask_table[cVar1];
    }
  }
  op = rec->op;
  if ((((((OP_SHAD < op) && (op < OP_CMP_EQ)) || ((OP_SHLD < op && (op < OP_ADD)))) || (op == OP_DT)
       ) || (((OP_NON_CF < op && (op < OP_NON_D5)) || (op == OP_NON_F1)))) &&
     (((opnd = rec->ea1, opnd != (ea *)0x0 && ((opnd->type & 0x1f) == 1)) && (uses != (uint *)0x0)))
     ) {
    cVar1 = opnd->base;
    if ((cVar1 < '\0') || ('_' < cVar1)) {
      if ((uses != (uint *)0x0) && ('_' < opnd->base)) {
        uses[1] = uses[1] | g_reg_mask_table[opnd->base];
      }
    }
    else {
      *uses = *uses | g_reg_mask_table[cVar1];
    }
  }
  op = rec->op;
  if (((op == OP_TAS) ||
      ((((OP_NON_7F < op && (op < OP_NOT)) && (rec->ea2 != (ea *)0x0)) &&
       ((rec->ea2->type & 0x1f) == 0xc)))) && (uses != (uint *)0x0)) {
    uses[1] = uses[1] | g_reg_mask_table[0x7f];
  }
  op = rec->op;
  if ((((op == OP_ROTCL) || (op == OP_ROTCR)) ||
      ((op == OP_ADDC || ((op == OP_SUBC || (op == OP_NEGC)))))) && (uses != (uint *)0x0)) {
    uses[1] = uses[1] | g_reg_mask_table[0x61];
  }
  op = rec->op;
  if ((((op == OP_CASEJMP) || ((OP_CALL < op && (op < OP_MOV_LOC)))) ||
      ((OP_SETT < op && (((op < OP_CLRMAC && (op != OP_JMP)) && (op != OP_RTS)))))) &&
     (uses != (uint *)0x0)) {
    uses[1] = uses[1] | g_reg_mask_table[0x6b];
  }
  op = rec->op;
  if ((((op == OP_MOV) || (op == OP_SWAP)) ||
      (((OP_NON_77 < op && (op < OP_NON_7D)) || ((op == OP_NOT || (op == OP_NON_B0)))))) &&
     ((opnd = rec->ea2, opnd != (ea *)0x0 &&
      ((((opnd->type & 0x1f) == 1 &&
        (cVar1 = operand_uses_register(rec,opnd->base,'\x01'), cVar1 == '\x01')) &&
       (uses != (uint *)0x0)))))) {
    cVar1 = rec->ea2->base;
    if ((cVar1 < '\0') || ('_' < cVar1)) {
      if ((uses != (uint *)0x0) && (cVar1 = rec->ea2->base, '_' < cVar1)) {
        uses[1] = uses[1] | g_reg_mask_table[cVar1];
      }
    }
    else {
      *uses = *uses | g_reg_mask_table[cVar1];
    }
  }
  if (rec->op != OP_NON_2E) goto LAB_00410044;
  if (uses == (uint *)0x0) {
LAB_00410022:
    if (uses != (uint *)0x0) {
      *uses = *uses | g_reg_mask_table[0x38];
      goto LAB_0041002d;
    }
  }
  else {
    *uses = *uses | g_reg_mask_table[0x30];
    if (uses != (uint *)0x0) {
      *uses = *uses | g_reg_mask_table[0x34];
      goto LAB_00410022;
    }
LAB_0041002d:
    if (uses == (uint *)0x0) goto LAB_00410044;
    *uses = *uses | g_reg_mask_table[0x3c];
  }
  if (uses != (uint *)0x0) {
    uses[1] = uses[1] | g_reg_mask_table[0x68];
  }
LAB_00410044:
  if (((rec->op == OP_NON_31) && (opnd = rec->ea2, opnd != (ea *)0x0)) &&
     (((opnd->type & 0x1f) == 2 && (uses != (uint *)0x0)))) {
    cVar1 = opnd->base;
    if ((-1 < cVar1) && (cVar1 < '`')) {
      *uses = *uses | g_reg_mask_table[cVar1];
      return;
    }
    if ((uses != (uint *)0x0) && ('_' < opnd->base)) {
      uses[1] = uses[1] | g_reg_mask_table[opnd->base];
    }
  }
  return;
}



