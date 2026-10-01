#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_branch_defs_hi
#define g_branch_defs_hi (*(unsigned int *)(g_sd + 0x5ba4))
#undef g_branch_defs_lo
#define g_branch_defs_lo (*(unsigned int *)(g_sd + 0x5ba0))
#undef g_branch_uses_hi
#define g_branch_uses_hi (*(unsigned int *)(g_sd + 0x5b9c))
#undef g_branch_uses_lo
#define g_branch_uses_lo (*(unsigned int *)(g_sd + 0x5b98))
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0x5bf0))
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00415860
// name : fill_branch_delay_slots
// size : 1457
// sig  : void fill_branch_delay_slots(code_node * list)


int __cdecl fill_branch_delay_slots(code_node *list)

{
  char cVar1;
  psd *slot_rec;
  uint mask;
  int i;
  psd *rec;
  psd *scan_rec;
  char filled;
  short rewrite_mode;
  code_node *node;
  psd_op op;
  
  filled = '\0';
  do {
    node = list;
    if (list == (code_node *)0x0) {
      return;
    }
joined_r0x0041587e:
    if (node != (code_node *)0x0) {
      i = 1;
      rec = node->psd;
      do {
        op = rec->op;
        scan_rec = rec;
        if ((((((op < OP_EXIT) || (OP_JUMPF < op)) && (op != OP_RTE)) &&
             ((op < OP_BRA || (OP_RTS < op)))) && (op != OP_BSRF)) && (op != OP_BRAF))
        goto LAB_00415c97;
        if ((((op == OP_JUMPT) || (op == OP_JUMPF)) && (g_current_request->cpu == 0)) ||
           (((op == OP_EXIT || (op == OP_RETURN)) &&
            (rewrite_mode = classify_branch_rewrite_mode(rec), rewrite_mode == 0))))
        goto LAB_00415deb;
        slot_rec = find_previous_psd_record(list,rec);
        slot_rec = find_previous_slot_candidate(list,slot_rec);
        if (slot_rec == (psd *)0x0) goto LAB_00415c97;
        if (((byte)g_stage_flags & 0x80) != 0) {
          dump_node_list_debug(node);
        }
        g_branch_uses_lo = 0;
        g_branch_uses_hi = 0;
        g_branch_defs_lo = 0;
        g_branch_defs_hi = 0;
        if (slot_rec != (psd *)0x0) {
          g_branch_defs_hi = g_reg_mask_table[0x6b];
          g_branch_uses_hi = g_reg_mask_table[0x6b];
          switch(rec->op) {
          case OP_EXIT:
            add_epilogue_register_masks();
            break;
          case OP_RETURN:
            if (rewrite_mode < 2) {
              add_epilogue_register_masks();
            }
            else {
              g_branch_defs_lo = g_reg_mask_table[1];
              g_branch_uses_lo = g_reg_mask_table[1];
            }
            break;
          case OP_CALL:
            cVar1 = rec->tmp;
            if ((cVar1 < '\0') || ('_' < cVar1)) {
              if ('_' < rec->tmp) {
                g_branch_defs_hi = g_reg_mask_table[0x6b] | g_reg_mask_table[rec->tmp];
              }
            }
            else {
              g_branch_defs_lo = g_reg_mask_table[cVar1];
            }
            cVar1 = rec->tmp;
            if ((cVar1 < '\0') || ('_' < cVar1)) {
              if ('_' < rec->tmp) {
                g_branch_uses_hi = g_reg_mask_table[0x6b] | g_reg_mask_table[rec->tmp];
              }
            }
            else {
              g_branch_uses_lo = g_reg_mask_table[cVar1];
            }
            goto LAB_00415c01;
          case OP_JUMPT:
          case OP_JUMPF:
            cVar1 = accumulate_compare_test_record_masks(slot_rec);
            if (cVar1 != '\0') {
              slot_rec = find_previous_psd_record(list,slot_rec);
              slot_rec = find_previous_slot_candidate(list,slot_rec);
              if (slot_rec == (psd *)0x0) {
                i = i + 1;
                scan_rec = rec + 1;
                fill_cond_branch_slot_from_target(list,rec);
                goto LAB_00415c97;
              }
            }
            g_branch_uses_hi = g_branch_uses_hi | g_reg_mask_table[0x61];
          case OP_JUMP:
            cVar1 = rec->tmp;
            if ((cVar1 < '\0') || ('_' < cVar1)) {
              if ('_' < rec->tmp) {
                g_branch_defs_hi = g_branch_defs_hi | g_reg_mask_table[rec->tmp];
              }
            }
            else {
              g_branch_defs_lo = g_branch_defs_lo | g_reg_mask_table[cVar1];
            }
            cVar1 = rec->tmp;
            if ((cVar1 < '\0') || ('_' < cVar1)) {
              if ('_' < rec->tmp) {
                g_branch_uses_hi = g_branch_uses_hi | g_reg_mask_table[rec->tmp];
              }
            }
            else {
              g_branch_uses_lo = g_branch_uses_lo | g_reg_mask_table[cVar1];
            }
            break;
          case OP_RTE:
            g_branch_defs_hi = g_reg_mask_table[0x6b] | g_reg_mask_table[0x61];
            mask = g_reg_mask_table[0x61];
            goto LAB_00415c06;
          case OP_JMP:
            cVar1 = rec->ea1->base;
            if ((cVar1 < '\0') || ('_' < cVar1)) {
              cVar1 = rec->ea1->base;
              if ('_' < cVar1) {
                g_branch_uses_hi = g_reg_mask_table[0x6b] | g_reg_mask_table[cVar1];
              }
            }
            else {
              g_branch_uses_lo = g_reg_mask_table[cVar1];
            }
            break;
          case OP_JSR:
            cVar1 = rec->ea1->base;
            if ((cVar1 < '\0') || ('_' < cVar1)) {
              cVar1 = rec->ea1->base;
              if ('_' < cVar1) {
                g_branch_uses_hi = g_reg_mask_table[0x6b] | g_reg_mask_table[cVar1];
              }
            }
            else {
              g_branch_uses_lo = g_reg_mask_table[cVar1];
            }
          case OP_BSR:
          case OP_RTS:
LAB_00415c01:
            g_branch_defs_hi = g_branch_defs_hi | g_reg_mask_table[0x66];
            mask = g_reg_mask_table[0x66];
LAB_00415c06:
            g_branch_uses_hi = g_branch_uses_hi | mask;
            break;
          case OP_BSRF:
          case OP_BRAF:
            cVar1 = rec->ea1->base;
            if ((cVar1 < '\0') || ('_' < cVar1)) {
              cVar1 = rec->ea1->base;
              if ('_' < cVar1) {
                g_branch_uses_hi = g_reg_mask_table[0x6b] | g_reg_mask_table[cVar1];
              }
            }
            else {
              g_branch_uses_lo = g_reg_mask_table[cVar1];
            }
          }
          filled = select_delay_slot_record(list,slot_rec);
        }
        if ((filled == '\0') && ((rec->op == OP_JUMPT || (rec->op == OP_JUMPF)))) goto LAB_00415dc7;
        if (((byte)g_stage_flags & 0x80) != 0) {
          dump_node_list_debug(node);
        }
        op = rec->op;
        if (((((OP_CALL < op) && (op < OP_MOV_LOC)) || (op == OP_EXIT)) ||
            ((op == OP_RETURN || ((OP_SETT < op && (op < OP_BSR)))))) ||
           ((op == OP_JMP ||
            (((OP_JSR < op && (op < OP_BSRF)) || ((op == OP_BRAF || (op == OP_RTE))))))))
        goto LAB_00415deb;
LAB_00415c97:
        rec = scan_rec + 1;
        i = i + 1;
        if (0xf < i) goto LAB_00415deb;
      } while( true );
    }
    list = list->next_block;
  } while( true );
LAB_00415dc7:
  fill_cond_branch_slot_from_target(list,rec);
  if ((rec->op != OP_JUMPT) && ((rec->op != OP_JUMPF && (i == 0xf)))) {
    node = node->next;
  }
LAB_00415deb:
  node = node->next;
  goto joined_r0x0041587e;
}



