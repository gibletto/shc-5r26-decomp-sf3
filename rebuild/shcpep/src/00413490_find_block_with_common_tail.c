#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_common_tail_a
#define g_common_tail_a (*(psd * *)(g_sd + 0x5bb0))
#undef g_common_tail_b
#define g_common_tail_b (*(psd * *)(g_sd + 0x5ba8))
#undef g_current_block
#define g_current_block (*(code_node * *)(g_sd + 0x5c38))
#undef g_current_node_list
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))
#undef g_current_symbol
#define g_current_symbol (*(symbol * *)(g_sd + 0x6d4c))
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00413490
// name : find_block_with_common_tail
// size : 953
// sig  : short find_block_with_common_tail(code_node * * block_a, code_node * * block_b, code_node * * label_block, psd * rec)


short __cdecl
find_block_with_common_tail
          (code_node **block_a,code_node **block_b,code_node **label_block,psd *rec)

{
  code_node *pcVar1;
  code_node *pcVar2;
  int *label_node;
  label_block_ref *ref;
  label_block_ref *last_ref;
  code_node *cur_block;
  psd *label_rec;
  short labno;
  psd_op op;
  label_block_ref *refs;
  short sym_number;
  
  cur_block = g_current_block;
  ref = (label_block_ref *)0x0;
  op = rec->op;
  if ((op == OP_JUMP) || (op == OP_RETURN)) {
    labno = rec->ea1->labels->labno1;
    g_current_symbol = g_symbol_hash[labno % 0x3fd];
    sym_number = g_current_symbol->number;
    while (sym_number != labno) {
      g_current_symbol = g_current_symbol->hash_next;
      sym_number = g_current_symbol->number;
    }
    if (g_current_symbol != (symbol *)0x0) {
      label_rec = g_current_symbol->label_psd;
      if (label_rec != (psd *)0x0) {
        label_node = &label_rec[-1].expno;
        pcVar1 = (code_node *)0x0;
        for (pcVar2 = g_current_node_list;
            (pcVar2 != (code_node *)0x0 && (pcVar2 != (code_node *)label_node));
            pcVar2 = pcVar2->next_block) {
          pcVar1 = pcVar2;
        }
        if (((((pcVar1 != (code_node *)0x0) && (g_current_block != (code_node *)0x0)) &&
             (label_rec[-1].filno != 0)) &&
            ((g_current_block != (code_node *)label_node && (g_current_block != pcVar1)))) &&
           ((g_current_block->target_labno == label_rec[-1].filno &&
            ((pcVar1->target_labno == 0 &&
             (g_common_tail_count =
                   count_common_tail_records
                             (g_current_block,pcVar1,&g_common_tail_a,&g_common_tail_b,1),
             g_common_tail_count != 0)))))) {
          *block_b = pcVar1;
          *label_block = (code_node *)label_node;
          *block_a = cur_block;
          if (((byte)g_stage_flags & 0x10) != 0) {
            _printf(s_dc_lbchk_end__rc___d_00427788,1);
          }
          return 1;
        }
      }
      if (g_current_symbol != (symbol *)0x0) {
        refs = g_current_symbol->ref_blocks;
        if (refs != (label_block_ref *)0x0) {
          ref = refs->next;
          last_ref = refs;
        }
        if ((cur_block->target_labno == 0) || (ref == (label_block_ref *)0x0)) {
          ref = (label_block_ref *)alloc_zeroed_flushing_blocks(8);
          ref->next = (label_block_ref *)0x0;
          ref->block = cur_block;
          if (((byte)g_stage_flags & 0x40) != 0) {
            _printf(s_make_LISTTBL_blkptr___08lx_0042776c,cur_block);
          }
          if (g_current_symbol->ref_blocks == (label_block_ref *)0x0) {
            last_ref = (label_block_ref *)alloc_zeroed_flushing_blocks(8);
            last_ref->block = (code_node *)0x0;
            g_current_symbol->ref_blocks = last_ref;
          }
        }
        else {
          do {
            last_ref = ref;
            pcVar1 = last_ref->block;
            if (pcVar1->target_labno == cur_block->target_labno) {
              if (pcVar1 == cur_block) {
LAB_0041377d:
                if (((byte)g_stage_flags & 0x10) != 0) {
                  _printf(s_dc_lbchk_end__rc___d_00427788,0);
                }
                return 0;
              }
              g_common_tail_count =
                   count_common_tail_records(cur_block,pcVar1,&g_common_tail_a,&g_common_tail_b,2);
              if (g_common_tail_count != 0) {
                *block_b = pcVar1;
                *block_a = cur_block;
                if (((byte)g_stage_flags & 0x10) != 0) {
                  _printf(s_dc_lbchk_end__rc___d_00427788,2);
                }
                return 2;
              }
            }
            else if (pcVar1 == cur_block) goto LAB_0041377d;
            ref = last_ref->next;
          } while (last_ref->next != (label_block_ref *)0x0);
          ref = (label_block_ref *)alloc_zeroed_flushing_blocks(8);
          ref->next = (label_block_ref *)0x0;
          ref->block = cur_block;
          if (((byte)g_stage_flags & 0x40) != 0) {
            _printf(s_make_LISTTBL_blkptr___08lx_0042776c,cur_block);
          }
          if (last_ref == (label_block_ref *)0x0) goto LAB_00413826;
        }
        last_ref->next = ref;
      }
    }
  }
  else if (op == OP_LABEL) {
    g_current_symbol = g_symbol_hash[*(short *)&rec->ea1 % 0x3fd];
    labno = g_current_symbol->number;
    while (labno != *(short *)&rec->ea1) {
      g_current_symbol = g_current_symbol->hash_next;
      labno = g_current_symbol->number;
    }
    g_current_symbol->label_psd = rec;
    label_rec = g_current_symbol->label_psd;
    label_node = &label_rec[-1].expno;
    cur_block = (code_node *)0x0;
    for (pcVar1 = g_current_node_list;
        (pcVar1 != (code_node *)0x0 && (pcVar1 != (code_node *)label_node));
        pcVar1 = pcVar1->next_block) {
      cur_block = pcVar1;
    }
    if (g_current_symbol->ref_blocks != (label_block_ref *)0x0) {
      ref = g_current_symbol->ref_blocks->next;
    }
    for (; ref != (label_block_ref *)0x0; ref = ref->next) {
      pcVar1 = ref->block;
      if (((((label_node != (int *)0x0) && (pcVar1 != (code_node *)0x0)) &&
           (cur_block != (code_node *)0x0)) &&
          (((labno = label_rec[-1].filno, labno != 0 && (pcVar1 != (code_node *)label_node)) &&
           ((pcVar1 != cur_block &&
            ((pcVar1->target_labno == labno && (cur_block->target_labno == 0)))))))) &&
         (g_common_tail_count =
               count_common_tail_records(pcVar1,cur_block,&g_common_tail_a,&g_common_tail_b,1),
         g_common_tail_count != 0)) {
        *block_a = pcVar1;
        *block_b = cur_block;
        *label_block = (code_node *)label_node;
        if (((byte)g_stage_flags & 0x10) != 0) {
          _printf(s_dc_lbchk_end__rc___d_00427788,1);
        }
        return 1;
      }
    }
  }
LAB_00413826:
  if (((byte)g_stage_flags & 0x10) != 0) {
    _printf(s_dc_lbchk_end__rc__d_00427754,0);
  }
  return 0;
}



