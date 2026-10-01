#include "decls.h"
#include "imports.h"
#include "pep_rules.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_branch_defs_hi
#define g_branch_defs_hi (*(unsigned int *)(g_sd + 0x5ba4))
#undef g_branch_defs_lo
#define g_branch_defs_lo (*(unsigned int *)(g_sd + 0x5ba0))
#undef g_branch_uses_hi
#define g_branch_uses_hi (*(unsigned int *)(g_sd + 0x5b9c))
#undef g_branch_uses_lo
#define g_branch_uses_lo (*(unsigned int *)(g_sd + 0x5b98))
#undef g_current_symbol
#define g_current_symbol (*(symbol * *)(g_sd + 0x6d4c))
#undef g_rec_def_mask_hi
#define g_rec_def_mask_hi (*(unsigned int *)(g_sd + 0x6d5c))
#undef g_rec_def_mask_lo
#define g_rec_def_mask_lo (*(unsigned int *)(g_sd + 0x6d58))
#undef g_rec_use_mask_hi
#define g_rec_use_mask_hi (*(unsigned int *)(g_sd + 0x5c44))
#undef g_rec_use_mask_lo
#define g_rec_use_mask_lo (*(unsigned int *)(g_sd + 0x5c40))
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00417080
// name : fill_cond_branch_slot_from_target
// size : 1132
// sig  : void fill_cond_branch_slot_from_target(code_node * node, psd * branch)


int __cdecl fill_cond_branch_slot_from_target(code_node *node,psd *branch)

{
  short labno;
  char cVar1;
  char disjoint;
  code_node *fall_block;
  code_node *label_block;
  psd *rec;
  psd *scan_rec;
  code_node *second_block;
  short slot_labno;
  code_node *slot_block;
  short fall_labno;
  label_ref *labels;
  psd_op op;
  
  if (((byte)g_stage_flags & 2) != 0) {
    _printf(s_delaymov_start__00427bc8);
  }
  g_branch_uses_lo = 0;
  g_branch_uses_hi = 0;
  g_branch_defs_lo = 0;
  g_branch_defs_hi = 0;
  if (((branch != (psd *)0x0) &&
      (((branch->op == OP_JUMPT || (branch->op == OP_JUMPF)) && (branch->ea1 != (ea *)0x0)))) &&
     ((labels = branch->ea1->labels, labels != (label_ref *)0x0 && (labels->labno1 != 0)))) {
    g_branch_uses_hi = g_reg_mask_table[0x61] | g_reg_mask_table[0x6b];
    g_branch_defs_hi = g_reg_mask_table[0x6b];
    cVar1 = branch->tmp;
    if ((cVar1 < '\0') || ('_' < cVar1)) {
      if ('_' < branch->tmp) {
        g_branch_uses_hi = g_branch_uses_hi | g_reg_mask_table[branch->tmp];
      }
    }
    else {
      g_branch_uses_lo = g_reg_mask_table[cVar1];
    }
    cVar1 = branch->tmp;
    if ((cVar1 < '\0') || ('_' < cVar1)) {
      if ('_' < branch->tmp) {
        g_branch_defs_hi = g_reg_mask_table[0x6b] | g_reg_mask_table[branch->tmp];
      }
    }
    else {
      g_branch_defs_lo = g_reg_mask_table[cVar1];
    }
    labno = branch->ea1->labels->labno1;
    fall_block = find_next_nonempty_block(node);
    if ((((fall_block != (code_node *)0x0) && (fall_block->labno == 0)) &&
        (label_block = find_next_nonempty_block(fall_block), label_block != (code_node *)0x0)) &&
       (label_block->labno == labno)) {
      g_current_symbol = find_label_symbol(labno);
      if ((g_current_symbol != (symbol *)0x0) && (g_current_symbol->ref_count != 1)) {
        return;
      }
      fall_labno = fall_block->target_labno;
      second_block = (code_node *)0x0;
      slot_labno = labno;
      slot_block = label_block;
      if (fall_labno != 0) {
        slot_block = find_next_nonempty_block(label_block);
        if (slot_block == (code_node *)0x0) {
          return;
        }
        if (slot_block->labno != fall_labno) {
          return;
        }
        if (label_block->target_labno != 0) {
          return;
        }
        rec = find_block_final_record(fall_block);
        g_current_symbol = find_label_symbol(fall_labno);
        op = rec->op;
        if (((op != OP_JUMP) && (op != OP_JUMPT)) ||
           ((g_current_symbol == (symbol *)0x0 ||
            (second_block = label_block, slot_labno = fall_labno, g_current_symbol->ref_count != 1))
           )) {
          if ((OP_CALL < op) && (op < OP_MOV_LOC)) {
            return;
          }
          if (op == OP_EXIT) {
            return;
          }
          if (op == OP_RETURN) {
            return;
          }
          if ((OP_SETT < op) && (op < OP_BSR)) {
            return;
          }
          if (op == OP_JMP) {
            return;
          }
          if ((OP_JSR < op) && (op < OP_BSRF)) {
            return;
          }
          if (op == OP_BRAF) {
            return;
          }
          second_block = (code_node *)0x0;
          slot_labno = labno;
          slot_block = label_block;
          if (op == OP_RTE) {
            return;
          }
        }
      }
      g_current_symbol = find_label_symbol(slot_labno);
      if ((((g_current_symbol != (symbol *)0x0) && (g_current_symbol->ref_count == 1)) &&
          (g_current_symbol->label_psd != (psd *)0x0)) &&
         (rec = find_slot_candidate_after_label(slot_block,g_current_symbol->label_psd),
         rec != (psd *)0x0)) {
        disjoint = '\0';
        cVar1 = compute_record_register_masks(rec);
        if (cVar1 == '\0') {
          disjoint = delay_slot_masks_disjoint();
        }
#if SHC_REBUILD_UPDATED
        if (slot_no_stack() != 0 && slot_record_is_frame_access((unsigned char *)rec)) {
          disjoint = 0;
        }
#endif
        if (disjoint == '\x01') {
          g_branch_uses_lo = g_rec_use_mask_lo;
          g_branch_uses_hi = g_rec_use_mask_hi;
          g_branch_defs_lo = g_rec_def_mask_lo;
          g_branch_defs_hi = g_rec_def_mask_hi;
          for (scan_rec = fall_block->psd; scan_rec != (psd *)0x0;
              scan_rec = find_next_psd_record(fall_block,scan_rec)) {
            op = scan_rec->op;
            if (op == OP_CASEJMP) {
              return;
            }
            if (op == OP_CALL) {
              return;
            }
            if (op == OP_JSR) {
              return;
            }
            if (op == OP_BSR) {
              return;
            }
            if (op == OP_BSRF) {
              return;
            }
            disjoint = '\0';
            cVar1 = compute_record_register_masks(scan_rec);
            if (cVar1 == '\0') {
              disjoint = delay_slot_masks_disjoint();
            }
            if (disjoint != '\x01') {
              return;
            }
          }
          if (second_block != (code_node *)0x0) {
            for (scan_rec = second_block->psd; scan_rec != (psd *)0x0;
                scan_rec = find_next_psd_record(second_block,scan_rec)) {
              op = scan_rec->op;
              if (op == OP_CASEJMP) {
                return;
              }
              if (op == OP_CALL) {
                return;
              }
              if (op == OP_JSR) {
                return;
              }
              if (op == OP_BSR) {
                return;
              }
              if (op == OP_BSRF) {
                return;
              }
              disjoint = '\0';
              cVar1 = compute_record_register_masks(scan_rec);
              if (cVar1 == '\0') {
                disjoint = delay_slot_masks_disjoint();
              }
              if (disjoint != '\x01') {
                return;
              }
            }
          }
          move_record_into_branch_slot(rec,node,branch);
          adjust_label_sptravel_for_moved_record(branch,slot_block,second_block);
        }
      }
    }
  }
  if (((byte)g_stage_flags & 2) != 0) {
    _printf(s_delaymov_end__00427bb8);
  }
  return;
}



