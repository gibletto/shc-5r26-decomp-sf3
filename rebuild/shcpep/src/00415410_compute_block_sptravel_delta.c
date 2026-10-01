#include "decls.h"
#include "imports.h"

// entry: 00415410
// name : compute_block_sptravel_delta
// size : 414
// sig  : int compute_block_sptravel_delta(code_node * block, int sptravel)


int __cdecl compute_block_sptravel_delta(code_node *block,int sptravel)

{
  uchar changes;
  int size;
  psd *prev_rec;
  int iVar1;
  code_node *sp_delta;
  psd *cur_rec;
  short call_no;
  code_node *node;
  psd_op op;
  ea *opnd;
  
  sp_delta = block;
  node = block;
  do {
    if (node == (code_node *)0x0) {
      iVar1 = sptravel - (int)sp_delta;
      if (iVar1 < 0) {
        iVar1 = -iVar1;
      }
      return iVar1;
    }
    iVar1 = 0;
    cur_rec = node->psd;
    do {
      switch(cur_rec->op) {
      case OP_NON_10:
      case OP_CASEJMP:
      case OP_CTBL:
      case OP_CENT:
      case OP_LINE:
        break;
      default:
        opnd = cur_rec->ea1;
        if (((opnd != (ea *)0x0) && ((opnd->type & 0x1f) == 4)) && (opnd->base == '\x0f')) {
          size = psd_operand_size_bytes(cur_rec);
          sp_delta = (code_node *)((int)sp_delta - size);
        }
        opnd = cur_rec->ea2;
        if (opnd != (ea *)0x0) {
          if (((opnd->type & 0x1f) == 3) && (opnd->base == '\x0f')) {
            size = psd_operand_size_bytes(cur_rec);
            sp_delta = (code_node *)(sp_delta->unknown_02 + size + -2);
          }
          if (((cur_rec->ea2->type & 0x1f) == 4) && (cur_rec->ea2->base == '\x0f')) {
            size = psd_operand_size_bytes(cur_rec);
            sp_delta = (code_node *)((int)sp_delta - size);
          }
        }
        break;
      case OP_LABEL:
        sp_delta = (code_node *)0x0;
        break;
      case OP_CALL:
        call_no = cur_rec->ea1->labels->labno1;
        if (call_no < 0xb7) {
          sp_delta = (code_node *)
                     (sp_delta->unknown_02 + *(int *)(&g_runtime_call_sptravel + call_no * 4) + -2);
        }
        break;
      case OP_ADD:
      case OP_SUB:
        if (((cur_rec->ea2->type & 0x1f) == 1) && (cur_rec->ea2->base == '\x0f')) {
          if ((cur_rec->ea1->type & 0x1f) == 7) {
            sp_delta = (code_node *)((int)sp_delta - cur_rec->ea1->disp);
          }
          else {
            prev_rec = find_previous_psd_record(block,cur_rec);
            if ((((prev_rec != (psd *)0x0) && (prev_rec->op == OP_MOVI)) &&
                (changes = record_changes_register(prev_rec,cur_rec->ea1->base), changes == '\x01'))
               && (opnd = prev_rec->ea1, (opnd->type & 0x1f) == 7)) {
              if (cur_rec->op == OP_ADD) {
                sp_delta = (code_node *)((int)sp_delta - opnd->disp);
              }
              if (cur_rec->op == OP_SUB) {
                sp_delta = (code_node *)(sp_delta->unknown_02 + opnd->disp + -2);
              }
            }
          }
        }
      }
      op = cur_rec->op;
      if ((((OP_CALL < op) && (op < OP_MOV_LOC)) || (op == OP_EXIT)) ||
         ((((op == OP_RETURN || ((OP_SETT < op && (op < OP_BSR)))) || (op == OP_JMP)) ||
          (((OP_JSR < op && (op < OP_BSRF)) || ((op == OP_BRAF || (op == OP_RTE)))))))) break;
      iVar1 = iVar1 + 1;
      cur_rec = cur_rec + 1;
    } while (iVar1 < 0xf);
    node = node->next;
  } while( true );
}



