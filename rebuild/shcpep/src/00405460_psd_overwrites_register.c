#include "decls.h"
#include "imports.h"

// entry: 00405460
// name : psd_overwrites_register
// size : 403
// sig  : psd * psd_overwrites_register(psd * rec, uchar reg)


psd * __cdecl psd_overwrites_register(psd *rec,uchar reg)

{
  char uses;
  byte src_kind;
  byte dst_kind;
  psd_op op;
  
  dst_kind = 0;
  src_kind = 0;
  if (rec->op == OP_CASEJMP) {
    return (psd *)0x0;
  }
  if ((rec->ea1 != (ea *)0x0) &&
     (((src_kind = rec->ea1->type & 0x1f, src_kind == 3 || (src_kind == 4)) &&
      (uses = operand_uses_register(rec,reg,'\x01'), uses != '\0')))) {
    return (psd *)0x0;
  }
  if (((rec->ea2 != (ea *)0x0) &&
      ((dst_kind = rec->ea2->type & 0x1f, dst_kind == 3 || (dst_kind == 4)))) &&
     (uses = operand_uses_register(rec,reg,'\x02'), uses != '\0')) {
    return (psd *)0x0;
  }
  if (((rec->op == OP_CALL) && (rec->ea1->labels->labno1 < 0xb7)) &&
     ((rec->tmp != reg && (uses = macro_record_references_register(rec,reg), uses != '\0')))) {
    return (psd *)0x0;
  }
  if ((src_kind == 0) || (src_kind != 1)) {
    if (dst_kind == 0) {
      return rec;
    }
    if (dst_kind != 1) {
      if (dst_kind == 0) {
        return rec;
      }
      if (dst_kind != 2) {
        return rec;
      }
      if (rec->op != OP_NON_31) {
        return rec;
      }
      return (psd *)0x0;
    }
  }
  op = rec->op;
  if (*(short *)(&g_op_dest_operand + (uint)op * 2) == 1) {
    if ((op != OP_NON_B3) && (op != OP_NON_B4)) {
      return (psd *)0x0;
    }
  }
  else if (*(short *)(&g_op_dest_operand + (uint)op * 2) == 2) {
    if (((((OP_ROTCR < op) && (op < OP_NON_66)) || ((OP_NON_7F < op && (op < OP_NOT)))) ||
        (((((op == OP_SHAD || (op == OP_SHLD)) || (op == OP_XTRCT)) ||
          ((OP_NON_B7 < op && (op < OP_NON_BF)))) || (op == OP_NON_CC)))) ||
       ((op == OP_NON_D6 || (op == OP_NON_D8)))) {
      return (psd *)0x0;
    }
  }
  else if (((op == OP_MOV_LOC) && (reg == '\0')) || (op == OP_NON_2E)) {
    return (psd *)0x0;
  }
  return rec;
}



