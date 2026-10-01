#include "decls.h"
#include "imports.h"
#include "pep_rules.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_common_tail_a
#define g_common_tail_a (*(psd * *)(g_sd + 0x5bb0))
#undef g_common_tail_b
#define g_common_tail_b (*(psd * *)(g_sd + 0x5ba8))
#undef g_cur_sptravel
#define g_cur_sptravel (*(code_node * *)(g_sd + 0x5c34))
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


// entry: 004131d0
// name : merge_common_block_tails
// size : 689
// sig  : void merge_common_block_tails(psd * rec)


int __cdecl merge_common_block_tails(psd *rec)

{
  unsigned char _frec_14[20];
#define local_14 (*(code_node * *)(_frec_14 + 0))
#define blk_a (*(code_node * *)(_frec_14 + 4))
#define blk_b (*(code_node * *)(_frec_14 + 8))
#define prev_link (*(code_node * *)(_frec_14 + 12))
#define lab_blk (*(code_node * *)(_frec_14 + 16))
  short mode;
  code_node *block;
  int iVar1;
  int *new_ref;
  code_node *pcVar2;
  short labno;
  code_node *ptr;
  code_node *pcVar3;
  psd_op op;
  short sym_number;
  
  ptr = (code_node *)0x0;
  blk_a = (code_node *)0x0;
  blk_b = (code_node *)0x0;
  lab_blk = (code_node *)0x0;
  prev_link = (code_node *)0x0;
  if (((*(unsigned char *)((char *)&g_stage_flags + 1)) & 0x20) != 0) {
    _printf(s_d_comcd_start__00427744);
    dump_node_list_debug(g_current_node_list);
  }
  op = rec->op;
  if ((((op == OP_LABEL) || (op == OP_JUMP)) || (op == OP_RETURN)) &&
     ((mode = find_block_with_common_tail(&blk_a,&blk_b,&lab_blk,rec), XJUMP_FILTER(mode, rec->op), mode != 0 &&
      (block = make_common_code_block(blk_a,blk_b,g_common_tail_a,g_common_tail_b,mode),
      block != (code_node *)0x0)))) {
    if (mode == 1) {
      op = rec->op;
      if (op == OP_LABEL) {
        g_last_block = block;
        block->next_block = blk_b->next_block;
        blk_b->next_block = block;
        pcVar2 = g_last_block->next_block;
        while (pcVar2 != (code_node *)0x0) {
          g_last_block = g_last_block->next_block;
          pcVar2 = g_last_block->next_block;
        }
      }
      else if ((op == OP_JUMP) || (op == OP_RETURN)) {
        block->next_block = lab_blk;
        blk_b->next_block = block;
      }
      labno = lab_blk->labno;
      local_14 = blk_a;
      pcVar2 = (code_node *)lab_blk->psd[0].sptravel;
    }
    else if (mode == 2) {
      g_last_block->next_block = blk_a;
      g_last_block = blk_a;
      g_current_block = block;
      block->next_block = blk_a->next_block;
      if (g_tail_merge_in_list == 1) {
        blk_a->next_block = block;
      }
      labno = block->target_labno;
      local_14 = blk_b;
      pcVar2 = g_cur_sptravel;
    }
    else {
      pcVar2 = local_14;
      labno = (short)local_14;
    }
    iVar1 = compute_block_sptravel_delta(block,(int)pcVar2);
    block->psd[0].sptravel = iVar1;
    g_current_symbol = g_symbol_hash[labno % 0x3fd];
    sym_number = g_current_symbol->number;
    while (sym_number != labno) {
      g_current_symbol = g_current_symbol->hash_next;
      sym_number = g_current_symbol->number;
    }
    pcVar2 = (code_node *)0x0;
    if ((g_current_symbol != (symbol *)0x0) &&
       (pcVar3 = (code_node *)g_current_symbol->ref_blocks, pcVar3 != (code_node *)0x0)) {
      ptr = *(code_node **)pcVar3;
      pcVar2 = pcVar3;
    }
    if (((pcVar2 != (code_node *)0x0) && (*(code_node **)&pcVar2->labno != (code_node *)0x0)) &&
       (local_14 == *(code_node **)&pcVar2->labno)) {
      pcVar2->labno = 0;
      pcVar2->target_labno = 0;
    }
    if (ptr != (code_node *)0x0) {
      pcVar3 = ptr;
      if (ptr == (code_node *)0x0) goto LAB_00413328;
      do {
        pcVar3 = ptr;
        if ((*(code_node **)&ptr->labno != (code_node *)0x0) &&
           (local_14 == *(code_node **)&ptr->labno)) {
          *(code_node **)&ptr->labno = (code_node *)0x0;
          if (prev_link == (code_node *)0x0) {
            prev_link = pcVar2;
          }
          local_14 = *(code_node **)ptr;
          if (local_14 == (code_node *)0x0) {
            prev_link->flags = '\0';
            prev_link->psd_count = '\0';
            prev_link->unknown_02[0] = '\0';
            prev_link->unknown_02[1] = '\0';
            local_14 = prev_link;
          }
          else {
            *(code_node **)prev_link = local_14;
          }
          pool_free(ptr,8);
          break;
        }
LAB_00413328:
        ptr = *(code_node **)pcVar3;
        prev_link = pcVar3;
      } while (ptr != (code_node *)0x0);
    }
    if (mode == 2) {
      (*(unsigned char *)((char *)&iVar1 + 0)) = local_14->flags;
      (*(unsigned char *)((char *)&iVar1 + 1)) = local_14->psd_count;
      (*(unsigned char *)((char *)&iVar1 + 2)) = local_14->unknown_02[0];
      (*(unsigned char *)((char *)&iVar1 + 3)) = local_14->unknown_02[1];
      while (iVar1 != 0) {
        local_14 = *(code_node **)local_14;
        (*(unsigned char *)((char *)&iVar1 + 0)) = local_14->flags;
        (*(unsigned char *)((char *)&iVar1 + 1)) = local_14->psd_count;
        (*(unsigned char *)((char *)&iVar1 + 2)) = local_14->unknown_02[0];
        (*(unsigned char *)((char *)&iVar1 + 3)) = local_14->unknown_02[1];
      }
      new_ref = alloc_zeroed_flushing_blocks(8);
      *new_ref = 0;
      new_ref[1] = (int)block;
      *(int **)local_14 = new_ref;
    }
    if (((*(unsigned char *)((char *)&g_stage_flags + 1)) & 0x20) != 0) {
      _printf(s_d_comcd_end__00427734);
      dump_node_list_debug(g_current_node_list);
    }
  }
  return;
#undef local_14
#undef blk_a
#undef blk_b
#undef prev_link
#undef lab_blk
}



