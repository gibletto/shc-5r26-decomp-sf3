#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_block
#define g_current_block (*(code_node * *)(g_sd + 0x5c38))
#undef g_current_node_list
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))
#undef g_current_symbol
#define g_current_symbol (*(symbol * *)(g_sd + 0x6d4c))
#undef g_last_block
#define g_last_block (*(code_node * *)(g_sd + 0x5bc4))
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00414610
// name : move_target_block_after_jump
// size : 1055
// sig  : void move_target_block_after_jump(psd * rec)


int __cdecl move_target_block_after_jump(psd *rec)

{
  code_node *block;
  char has_code;
  short ok;
  label_block_ref *ref_list;
  psd *jump_rec;
  code_node *pcVar1;
  code_node *chain_tail;
  code_node *pcVar2;
  code_node *prev_block;
  label_block_ref *prev_ref;
  code_node *after_target;
  code_node *cur_block;
  label_block_ref *next_ref;
  psd_op op;
  label_block_ref *ref;
  short sym_labno;
  
  prev_ref = (label_block_ref *)0x0;
  if (((*(unsigned char *)((char *)&g_stage_flags + 1)) & 0x20) != 0) {
    _printf(s_str_chg_start__00427a6c);
    dump_node_list_debug(g_current_node_list);
  }
  cur_block = g_current_block;
  op = rec->op;
  if (op == OP_LABEL) {
    g_current_symbol = g_symbol_hash[*(short *)&rec->ea1 % 0x3fd];
    ok = g_current_symbol->number;
    while (ok != *(short *)&rec->ea1) {
      g_current_symbol = g_current_symbol->hash_next;
      ok = g_current_symbol->number;
    }
    g_current_symbol->label_psd = rec;
    return;
  }
  if ((op == OP_JUMP) || (op == OP_RETURN)) {
    ok = rec->ea1->labels->labno1;
    g_current_symbol = g_symbol_hash[ok % 0x3fd];
    sym_labno = g_current_symbol->number;
    while (sym_labno != ok) {
      g_current_symbol = g_current_symbol->hash_next;
      sym_labno = g_current_symbol->number;
    }
    if ((g_current_symbol != (symbol *)0x0) && (g_current_symbol->label_psd == (psd *)0x0)) {
      ref_list = g_current_symbol->ref_blocks;
      if (ref_list == (label_block_ref *)0x0) {
        ref_list = (label_block_ref *)alloc_zeroed_flushing_blocks(8);
        ref_list->next = (label_block_ref *)0x0;
        ref_list->block = cur_block;
        if (((byte)g_stage_flags & 0x40) != 0) {
          _printf(s_make_LISTTBL_node_pointer___08lx_00427a48,cur_block);
        }
        g_current_symbol->ref_blocks = ref_list;
      }
      else if ((ref_list->block == (code_node *)0x0) &&
              (ref_list->block = g_current_block, ((byte)g_stage_flags & 0x40) != 0)) {
        _printf(s_LISTTBL_chained_node_pointer___0_00427a20,cur_block);
      }
    }
    if ((cur_block->labno != 0) && (cur_block->psd[0].op == OP_LABEL)) {
      ok = *(short *)&cur_block->psd[0].ea1;
      g_current_symbol = g_symbol_hash[ok % 0x3fd];
      sym_labno = g_current_symbol->number;
      while (sym_labno != ok) {
        g_current_symbol = g_current_symbol->hash_next;
        sym_labno = g_current_symbol->number;
      }
      ref_list = g_current_symbol->ref_blocks;
      if (ref_list == (label_block_ref *)0x0) {
        return;
      }
      block = ref_list->block;
      if (block == (code_node *)0x0) {
        return;
      }
      after_target = block->next_block;
      chain_tail = block;
      pcVar1 = prev_block;
      while (pcVar2 = chain_tail, pcVar2 != (code_node *)0x0) {
        pcVar1 = pcVar2;
        chain_tail = pcVar2->next_block;
      }
      chain_tail = pcVar1;
      if (pcVar1->target_labno == 0) {
        has_code = block_has_non_marker_records(pcVar1);
        while (pcVar2 = pcVar1, has_code == '\0') {
          pcVar2 = g_current_node_list;
          if (g_current_node_list == chain_tail) {
            return;
          }
          for (; (pcVar2 != (code_node *)0x0 && (pcVar2 != chain_tail)); pcVar2 = pcVar2->next_block
              ) {
            prev_block = pcVar2;
          }
          has_code = block_has_non_marker_records(prev_block);
          chain_tail = prev_block;
        }
      }
      delete_switch_markers_from_cursor();
      jump_rec = find_block_label_jump(block);
      if ((((jump_rec == (psd *)0x0) ||
           (jump_rec = find_block_label_jump(chain_tail), jump_rec == (psd *)0x0)) ||
          (jump_rec = find_block_label_jump(cur_block), jump_rec == (psd *)0x0)) &&
         (ref_list = g_current_symbol->ref_blocks, ref_list->block != (code_node *)0x0)) {
        ref_list->block = (code_node *)0x0;
        if (((byte)g_stage_flags & 0x40) == 0) {
          return;
        }
        _printf(s_clear_node_pointer___08lx_00427a04,cur_block);
        return;
      }
      if (((cur_block == (code_node *)0x0) || (chain_tail == (code_node *)0x0)) ||
         ((block == (code_node *)0x0 ||
          ((ok = check_block_move_branches(cur_block,chain_tail,block), ok == 0 ||
           (ok = check_label_movable(cur_block->labno), ok == 0)))))) {
        if (ref_list->block == block) {
          ref_list->block = (code_node *)0x0;
        }
      }
      else {
        pcVar1 = (code_node *)find_block_label_jump(block);
        release_label_refs_of_record((psd *)pcVar1,1);
        block->target_labno = 0;
        delete_psd_record((psd *)pcVar1);
        if (pcVar2 != (code_node *)0x0) {
          chain_tail = pcVar2;
        }
        chain_tail->next_block = cur_block->next_block;
        cur_block->next_block = after_target;
        block->next_block = cur_block;
        cur_block = g_current_node_list;
        if (after_target != (code_node *)0x0) {
          has_code = block_has_non_marker_records(after_target);
          while (has_code == '\0') {
            after_target = after_target->next_block;
            has_code = block_has_non_marker_records(after_target);
          }
          cur_block = g_current_node_list;
          if (after_target->psd[0].op == OP_LABEL) {
            delete_branch_to_next_label(after_target->psd);
            cur_block = g_current_node_list;
          }
        }
        for (; g_last_block = pcVar1, cur_block != chain_tail; cur_block = cur_block->next_block) {
          pcVar1 = cur_block;
        }
        g_last_block->next_block = (code_node *)0x0;
        g_current_block = chain_tail;
        if (ref_list->block == block) {
          ref_list->block = (code_node *)0x0;
          next_ref = ref_list->next;
          while (ref = next_ref, ref != (label_block_ref *)0x0) {
            if (ref->block == block) {
              ref->block = (code_node *)0x0;
              if (prev_ref == (label_block_ref *)0x0) {
                ref_list->next = ref->next;
              }
              else {
                prev_ref->next = ref->next;
              }
              pool_free(ref,8);
              break;
            }
            prev_ref = ref;
            next_ref = ref->next;
          }
        }
      }
    }
  }
  if (((*(unsigned char *)((char *)&g_stage_flags + 1)) & 0x20) != 0) {
    dump_node_list_debug(g_current_node_list);
    _printf(s_str_chg_end__004279f4);
  }
  return;
}



