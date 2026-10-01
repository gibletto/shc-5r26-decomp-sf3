#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_rec_def_mask_hi
#define g_rec_def_mask_hi (*(unsigned int *)(g_sd + 0x6d5c))
#undef g_rec_def_mask_lo
#define g_rec_def_mask_lo (*(unsigned int *)(g_sd + 0x6d58))
#undef g_rec_use_mask_hi
#define g_rec_use_mask_hi (*(unsigned int *)(g_sd + 0x5c44))
#undef g_rec_use_mask_lo
#define g_rec_use_mask_lo (*(unsigned int *)(g_sd + 0x5c40))


// entry: 0040fb20
// name : compute_record_register_use_def
// size : 562
// sig  : char compute_record_register_use_def(psd * rec, uint * uses, uint * defs)


char __cdecl compute_record_register_use_def(psd *rec,uint *uses,uint *defs)

{
  char masks_result;
  byte kind;
  uint uses_hi;
  uint uses_lo;
  char result;
  char base;
  psd_op op;
  ea *opnd;
  
  result = '\0';
  if (((rec == (psd *)0x0) || (uses == (uint *)0x0)) || (defs == (uint *)0x0)) {
    return '\0';
  }
  if (uses != (uint *)0x0) {
    uses[1] = 0;
    *uses = 0;
  }
  if (defs != (uint *)0x0) {
    defs[1] = 0;
    *defs = 0;
  }
  switch(rec->op) {
  case OP_NON_10:
  case OP_SLEEP:
    *uses = 0xffffffff;
    uses[1] = 0xffffffff;
    *defs = 0xffffffff;
    defs[1] = 0xffffffff;
    return '\x01';
  default:
    if (((rec->op != OP_ADD) || (opnd = rec->ea1, (opnd->type & 0x1f) != 7)) ||
       ((opnd->labels != (label_ref *)0x0 || (opnd->disp != 0)))) {
      masks_result = compute_record_register_masks(rec);
      if (defs != (uint *)0x0) {
        *defs = g_rec_def_mask_lo;
        defs[1] = g_rec_def_mask_hi;
      }
      uses_lo = ~g_rec_def_mask_lo & g_rec_use_mask_lo;
      *uses = uses_lo;
      uses_hi = ~g_rec_def_mask_hi & g_rec_use_mask_hi;
      uses[1] = uses_hi;
      op = rec->op;
      if (((op != OP_CASEJMP) && ((op < OP_LABEL || (OP_FLABEL < op)))) &&
         ((op != OP_CTBL &&
          ((((((op != OP_CENT && (op != OP_LINE)) && (op != OP_NON_10)) &&
             ((op != OP_PROGRAM && (opnd = rec->ea1, opnd != (ea *)0x0)))) &&
            ((kind = opnd->type & 0x1f, kind == 3 || (kind == 4)))) && (uses != (uint *)0x0)))))) {
        base = opnd->base;
        if ((base < '\0') || ('_' < base)) {
          if ((uses != (uint *)0x0) && ('_' < opnd->base)) {
            uses[1] = g_reg_mask_table[opnd->base] | uses_hi;
          }
        }
        else {
          *uses = g_reg_mask_table[base] | uses_lo;
        }
      }
      op = rec->op;
      if (((((op != OP_CASEJMP) && (((op < OP_LABEL || (OP_FLABEL < op)) && (op != OP_CTBL)))) &&
           (((op != OP_CENT && (op != OP_LINE)) && (op != OP_NON_10)))) &&
          (((op != OP_PROGRAM && (opnd = rec->ea2, opnd != (ea *)0x0)) &&
           ((kind = opnd->type & 0x1f, kind == 3 || (kind == 4)))))) && (uses != (uint *)0x0)) {
        base = opnd->base;
        if ((base < '\0') || ('_' < base)) {
          if ((uses != (uint *)0x0) && ('_' < opnd->base)) {
            uses[1] = uses[1] | g_reg_mask_table[opnd->base];
          }
        }
        else {
          *uses = *uses | g_reg_mask_table[base];
        }
      }
      add_implicit_register_uses(rec,uses);
      return masks_result != '\0';
    }
    break;
  case OP_ENTER:
  case OP_EXIT:
  case OP_RETURN:
    collect_enter_exit_register_masks(rec,uses,defs);
    return '\0';
  case OP_TRAPA:
    result = '\x01';
  case OP_CALL:
  case OP_BSR:
  case OP_JSR:
  case OP_BSRF:
    compute_call_register_use_def(rec,uses,defs);
  }
  return result;
}



