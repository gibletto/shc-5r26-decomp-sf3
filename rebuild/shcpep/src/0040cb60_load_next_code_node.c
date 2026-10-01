#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_block_being_loaded
#define g_block_being_loaded (*(code_node * *)(g_sd + 0x5bb4))
#undef g_current_block
#define g_current_block (*(code_node * *)(g_sd + 0x5c38))
#undef g_current_input_record
#define g_current_input_record (*(psd * *)(g_sd + 0x5bbc))
#undef g_current_node_list
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0x5bf0))
#undef g_current_section
#define g_current_section (*(request_section * *)(g_sd + 0x5d0c))
#undef g_current_symbol
#define g_current_symbol (*(symbol * *)(g_sd + 0x6d4c))
#undef g_last_block
#define g_last_block (*(code_node * *)(g_sd + 0x5bc4))
#undef g_last_loaded_node
#define g_last_loaded_node (*(code_node * *)(g_sd + 0x5bb8))
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 0040cb60
// name : load_next_code_node
// size : 1240
// sig  : code_node * load_next_code_node(void)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

code_node * load_next_code_node(void)

{
  char has_code;
  short code_size;
  code_node *node;
  code_node *pcVar1;
  symbol *sym;
  int count;
  psd *dst;
  symbol *cand;
  label_ref *lref;
  psd_op op;
  short sym_number;
  
  count = 0;
  g_tail_merge_in_list = 0;
  node = (code_node *)alloc_zeroed_flushing_blocks(0x178);
  if (g_block_being_loaded == (code_node *)0x0) {
    _g_block_end_record_bytes = 0;
    g_last_loaded_node = (code_node *)0x0;
    g_block_being_loaded = node;
    g_current_block = node;
  }
  if (((g_block_complete == 0) ||
      (((pcVar1 = g_last_loaded_node, g_block_complete == 1 && (g_current_block->target_labno == 0))
       && ((g_current_block->flags & 1) == 0)))) &&
     (pcVar1 = node, g_last_loaded_node != (code_node *)0x0)) {
    g_last_loaded_node->next = node;
  }
  g_last_loaded_node = pcVar1;
  if (g_current_node_list == (code_node *)0x0) {
    g_last_block = node;
    g_current_node_list = node;
  }
  node->flags = '\0';
  node->psd_count = '\0';
  node->unknown_02[0] = '\0';
  node->unknown_02[1] = '\0';
  node->labno = 0;
  node->target_labno = 0;
  node->next = (code_node *)0x0;
  node->next_block = (code_node *)0x0;
  if (g_reuse_input_record == 1) {
    g_reuse_input_record = 0;
  }
  dst = node->psd;
  while( true ) {
    if (((node + 1 < (code_node *)(dst + 1)) || (0xef < count)) ||
       ((g_section_end == 1 || (g_input_finished == 1)))) goto LAB_0040cfed;
    if (g_reuse_input_record == 0) {
      if (g_current_input_record->op == OP_PROGRAM) {
        g_current_section = find_section_record(g_current_request,g_current_input_record->filno);
      }
      copy_psd_record(g_current_input_record,dst);
      clear_psd_record(g_current_input_record);
      track_stack_pointer_travel(node,dst);
    }
    op = dst->op;
    if (((op == OP_CALL) || (op == OP_MOVA_PC)) || ((op == OP_MOVI || (op == OP_MOVA_FC)))) {
      count_record_label_references(dst);
    }
    if (g_block_complete == 1) break;
    op = dst->op;
    if (((op == OP_LABEL) || (op == OP_CLABEL)) || ((op == OP_DLABEL || (op == OP_FLABEL)))) {
      code_size = *(short *)&dst->ea1;
      cand = g_symbol_hash[code_size % 0x3fd];
      sym_number = cand->number;
      while ((sym = cand, sym_number != code_size &&
             ((cand != (symbol *)0x0 || (sym = (symbol *)0x0, (*(short *)0x00000006) == code_size))))) {
        cand = cand->hash_next;
        sym_number = cand->number;
      }
      if (op == OP_FLABEL) {
        g_current_aux_index = (int)sym->aux_index;
      }
      if (sym->number == *(short *)&dst->ea1) {
        sym->label_psd = g_block_being_loaded->psd;
      }
      g_block_being_loaded->labno = *(short *)&dst->ea1;
      if (dst->op == OP_LABEL) {
        pcVar1 = find_preceding_nonempty_block(g_block_being_loaded);
        while ((pcVar1 != (code_node *)0x0 &&
               (has_code = block_has_code_records(pcVar1), has_code == '\0'))) {
          g_current_symbol = find_label_symbol_of_label_only_block(pcVar1);
          if (g_current_symbol != (symbol *)0x0) {
            g_current_symbol->savelab = *(short *)&dst->ea1;
          }
          pcVar1 = find_preceding_nonempty_block(pcVar1);
        }
        if (((*(unsigned char *)((char *)&g_stage_flags + 1)) & 8) == 0) {
          invert_cond_branch_over_jump(dst);
          move_target_block_after_jump(dst);
          merge_common_block_tails(dst);
          delete_branch_to_next_label(dst);
        }
      }
    }
    else if ((((OP_CALL < op) && (op < OP_MOV_LOC)) || (op == OP_EXIT)) ||
            ((((op == OP_RETURN || ((OP_SETT < op && (op < OP_BSR)))) || (op == OP_JMP)) ||
             (((OP_JSR < op && (op < OP_BSRF)) ||
              ((op == OP_BRAF || ((op == OP_RTE || (op == OP_NON_10)))))))))) {
      if ((dst->op == OP_NON_10) ||
         ((dst->ea1 == (ea *)0x0 || (lref = dst->ea1->labels, lref == (label_ref *)0x0)))) {
        g_block_being_loaded->flags = g_block_being_loaded->flags | 1;
      }
      else {
        g_block_being_loaded->target_labno = lref->labno1;
        count_record_label_references(dst);
      }
      g_block_complete = 1;
      g_block_being_loaded->psd_count = (char)count + '\x01';
      if (((*(unsigned char *)((char *)&g_stage_flags + 1)) & 8) == 0) {
        op = dst->op;
        if ((((op == OP_JUMP) || (op == OP_RETURN)) || (op == OP_JUMPF)) || (op == OP_JUMPT)) {
          rewrite_branch_target_chains(dst);
        }
        if ((dst->op == OP_JUMP) || (dst->op == OP_RETURN)) {
          move_target_block_after_jump(dst);
          merge_common_block_tails(dst);
          g_cur_sptravel = 0;
        }
      }
      goto LAB_0040cfe8;
    }
    if (*(short *)(&g_op_is_code_record + (uint)dst->op * 2) == 1) {
      dst = dst + 1;
      count = count + 1;
    }
    advance_sua_record_stream();
  }
  defer_post_increments(g_current_block);
  delete_redundant_extensions(g_current_block);
  delete_extensions_before_narrow_stores(g_current_block);
  g_current_block->flags = g_current_block->flags & 0xfd;
  op = dst->op;
  if (((((((OP_CALL < op) && (op < OP_MOV_LOC)) || (op == OP_EXIT)) || (op == OP_RETURN)) ||
       (((OP_SETT < op && (op < OP_BSR)) || ((op == OP_JMP || ((OP_JSR < op && (op < OP_BSRF))))))))
      || (op == OP_BRAF)) || ((op == OP_RTE || (op == OP_NON_10)))) {
    if ((op == OP_NON_10) ||
       ((dst->ea1 == (ea *)0x0 || (lref = dst->ea1->labels, lref == (label_ref *)0x0)))) {
      g_block_being_loaded->flags = g_block_being_loaded->flags | 1;
    }
    else {
      g_block_being_loaded->target_labno = lref->labno1;
      count_record_label_references(dst);
    }
    code_size = compute_record_code_size(dst);
    _g_block_end_record_bytes = _g_block_end_record_bytes + code_size;
    if (((*(unsigned char *)((char *)&g_stage_flags + 1)) & 8) == 0) {
      op = dst->op;
      if ((((op == OP_JUMP) || (op == OP_RETURN)) || (op == OP_JUMPF)) || (op == OP_JUMPT)) {
        rewrite_branch_target_chains(dst);
      }
      if ((dst->op == OP_JUMP) || (dst->op == OP_RETURN)) {
        move_target_block_after_jump(dst);
        merge_common_block_tails(dst);
        g_cur_sptravel = 0;
      }
    }
    g_block_being_loaded->psd_count = (char)count + '\x01';
  }
LAB_0040cfe8:
  advance_sua_record_stream();
LAB_0040cfed:
  if (((((*(unsigned char *)((char *)&g_stage_flags + 1)) & 8) == 0) && (g_current_block != (code_node *)0x0)) &&
     ((g_current_block->flags & 2) != 0)) {
    defer_post_increments(g_current_block);
    delete_redundant_extensions(g_current_block);
    delete_extensions_before_narrow_stores(g_current_block);
  }
  return node;
}



