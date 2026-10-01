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


// entry: 00412a10
// name : rewrite_branch_target_chains
// size : 1663
// sig  : void rewrite_branch_target_chains(psd * rec)


int __cdecl rewrite_branch_target_chains(psd *rec)

{
  unsigned char _frec_14[20];
#define label_rec (*(psd * *)(_frec_14 + 0))
#define chain_sym (*(symbol * *)(_frec_14 + 8))
#define pred_block (*(code_node * *)(_frec_14 + 12))
#define prev_block (*(code_node * *)(_frec_14 + 16))
  code_node *block;
  code_node *pcVar1;
  psd *final_rec;
  label_block_ref *prev_ref;
  label_block_ref *bref;
  code_node *cur_block;
  short final_labno;
  short labno;
  label_ref *lref;
  short next_labno;
  label_block_ref **next_link;
  psd_op op;
  code_node *saved_current;
  symbol *sym;
  short *target_labno_ptr;
  
  prev_block = (code_node *)0x0;
  if (((byte)g_stage_flags & 8) != 0) {
    _printf(s_br_brchg_start__004276e4);
  }
  if (((rec != (psd *)0x0) &&
      (((((op = rec->op, op == OP_JUMP || (op == OP_RETURN)) || (op == OP_JUMPT)) ||
        (op == OP_JUMPF)) &&
       ((rec->ea1 != (ea *)0x0 && (lref = rec->ea1->labels, lref != (label_ref *)0x0)))))) &&
     (labno = lref->labno1, labno != 0)) {
    for (g_current_symbol = g_symbol_hash[labno % 0x3fd];
        (g_current_symbol != (symbol *)0x0 && (g_current_symbol->number != labno));
        g_current_symbol = g_current_symbol->hash_next) {
    }
    if ((g_current_symbol != (symbol *)0x0) &&
       (next_labno = g_current_symbol->savelab, next_labno != 0)) {
      if (((byte)g_stage_flags & 8) != 0) {
        _printf(s_br_brchg_cp___08lx__004276cc,rec);
        _printf(s_labelno___d__savelab___d_004276b0,(int)labno,(int)g_current_symbol->savelab);
      }
      while (next_labno != 0) {
        chain_sym = g_symbol_hash[next_labno % 0x3fd];
        labno = chain_sym->number;
        while (labno != next_labno) {
          chain_sym = chain_sym->hash_next;
          labno = chain_sym->number;
        }
        labno = next_labno;
        next_labno = chain_sym->savelab;
      }
      release_label_refs_of_record(rec,2);
      g_current_symbol->savelab = chain_sym->number;
      rec->ea1->labels->labno1 = g_current_symbol->savelab;
      cur_block = g_current_block;
      target_labno_ptr = &g_current_block->target_labno;
      *target_labno_ptr = rec->ea1->labels->labno1;
      if (((byte)g_stage_flags & 8) != 0) {
        _printf(s_br_brchg_end__cp___08lx__00427694,rec);
        _printf(s_labelno___d_00427684,(int)labno);
      }
      prev_ref = (label_block_ref *)0x0;
      for (bref = g_current_symbol->ref_blocks; bref != (label_block_ref *)0x0; bref = bref->next) {
        if ((bref->block == cur_block) &&
           (bref->block = (code_node *)0x0, prev_ref != (label_block_ref *)0x0)) {
          prev_ref->next = bref->next;
          pool_free(bref,8);
          break;
        }
        prev_ref = bref;
      }
      increment_label_ref_count(*target_labno_ptr);
      g_current_symbol = g_symbol_hash[*target_labno_ptr % 0x3fd];
      labno = g_current_symbol->number;
      while (labno != *target_labno_ptr) {
        g_current_symbol = g_current_symbol->hash_next;
        labno = g_current_symbol->number;
      }
      if (g_current_symbol != (symbol *)0x0) {
        final_rec = find_block_final_record(cur_block);
        merge_common_block_tails(final_rec);
      }
    }
    cur_block = g_current_block;
    if ((rec->op == OP_JUMP) || (rec->op == OP_RETURN)) {
      label_rec = find_previous_psd_record(g_current_block,rec);
      pred_block = find_preceding_nonempty_block(cur_block);
      if (label_rec != (psd *)0x0) {
        if (label_rec == (psd *)0x0) goto LAB_00413018;
        do {
          op = label_rec->op;
          if (((op != OP_LABEL) && (op != OP_CLABEL)) && (op != OP_DLABEL)) {
            return;
          }
          if (label_rec != (psd *)0x0) {
            g_current_symbol = g_symbol_hash[*(short *)&label_rec->ea1 % 0x3fd];
            labno = g_current_symbol->number;
            while (labno != *(short *)&label_rec->ea1) {
              g_current_symbol = g_current_symbol->hash_next;
              labno = g_current_symbol->number;
            }
            pcVar1 = g_current_node_list;
            if (g_current_symbol != (symbol *)0x0) {
              if ((g_current_symbol->savelab == 0) &&
                 (labno = rec->ea1->labels->labno1, g_current_symbol->number != labno)) {
                g_current_symbol->savelab = labno;
                pcVar1 = g_current_node_list;
              }
              else if ((g_current_symbol != (symbol *)0x0) && (g_current_symbol->savelab == 0)) {
                return;
              }
            }
            while (block = pcVar1, block != (code_node *)0x0) {
              final_rec = find_block_final_record(block);
              if ((final_rec != (psd *)0x0) &&
                 ((((op = final_rec->op, op == OP_JUMP || (op == OP_JUMPT)) || (op == OP_JUMPF)) &&
                  ((((final_rec->ea1 != (ea *)0x0 &&
                     (lref = final_rec->ea1->labels, lref != (label_ref *)0x0)) &&
                    (labno = lref->labno1, labno != 0)) && (*(short *)&label_rec->ea1 == labno))))))
              {
                for (g_current_symbol = g_symbol_hash[labno % 0x3fd];
                    (g_current_symbol != (symbol *)0x0 && (g_current_symbol->number != labno));
                    g_current_symbol = g_current_symbol->hash_next) {
                }
                if ((g_current_symbol != (symbol *)0x0) &&
                   (next_labno = g_current_symbol->savelab, next_labno != 0)) {
                  final_labno = labno;
                  if (((byte)g_stage_flags & 8) != 0) {
                    _printf(s_br_brchg_wcp___08lx__0042766c,final_rec);
                    _printf(s_labelno___d__savelab___d_004276b0,(int)labno,
                            (int)g_current_symbol->savelab);
                  }
                  while (next_labno != 0) {
                    sym = g_symbol_hash[next_labno % 0x3fd];
                    final_labno = sym->number;
                    while (final_labno != next_labno) {
                      sym = sym->hash_next;
                      final_labno = sym->number;
                    }
                    final_labno = next_labno;
                    next_labno = sym->savelab;
                  }
                  release_label_refs_of_record(final_rec,2);
                  final_rec->ea1->labels->labno1 = g_current_symbol->savelab;
                  block->target_labno = cur_block->target_labno;
                  if ((rec->op == OP_RETURN) && (final_rec->op == OP_JUMP)) {
                    final_rec->op = OP_RETURN;
                    final_rec->tmp = '\x01';
                  }
                  increment_label_ref_count(block->target_labno);
                  if (((byte)g_stage_flags & 8) != 0) {
                    _printf(s_br_brchg_end__0042765c);
                    _printf(s_wcp___08lx__0042764c,final_rec);
                    _printf(s_labelno___d_00427684,(int)final_labno);
                  }
                  if ((block->next_block != (code_node *)0x0) &&
                     (final_rec = block->next_block->psd, final_rec->op == OP_LABEL)) {
                    delete_branch_to_next_label(final_rec);
                  }
                  for (sym = g_symbol_hash[labno % 0x3fd];
                      (sym != (symbol *)0x0 && (sym->number != labno)); sym = sym->hash_next) {
                  }
                  if (sym->ref_blocks != (label_block_ref *)0x0) {
                    prev_ref = (label_block_ref *)0x0;
                    bref = sym->ref_blocks;
                    do {
                      if ((bref->block == block) &&
                         (bref->block = (code_node *)0x0, prev_ref != (label_block_ref *)0x0)) {
                        prev_ref->next = bref->next;
                        pool_free(bref,8);
                        break;
                      }
                      next_link = &bref->next;
                      prev_ref = bref;
                      bref = *next_link;
                    } while (*next_link != (label_block_ref *)0x0);
                  }
                  labno = block->target_labno;
                  if (labno != 0) {
                    g_current_symbol = g_symbol_hash[labno % 0x3fd];
                    next_labno = g_current_symbol->number;
                    while (next_labno != labno) {
                      g_current_symbol = g_current_symbol->hash_next;
                      next_labno = g_current_symbol->number;
                    }
                    if (g_current_symbol != (symbol *)0x0) {
                      final_rec = find_block_final_record(block);
                      saved_current = g_current_block;
                      pcVar1 = g_last_block;
                      g_tail_merge_in_list = 1;
                      g_last_block = prev_block;
                      g_current_block = block;
                      merge_common_block_tails(final_rec);
                      g_tail_merge_in_list = 0;
                      g_last_block = pcVar1;
                      g_current_block = saved_current;
                    }
                  }
                }
              }
              prev_block = block;
              pcVar1 = block->next_block;
            }
          }
LAB_00413018:
          label_rec = (psd *)0x0;
          g_current_symbol = find_label_symbol_of_label_only_block(pred_block);
          if (g_current_symbol != (symbol *)0x0) {
            g_current_symbol->savelab = cur_block->target_labno;
            label_rec = g_current_symbol->label_psd;
            pred_block = find_preceding_nonempty_block(pred_block);
          }
        } while (label_rec != (psd *)0x0);
      }
    }
  }
  if (((byte)g_stage_flags & 8) != 0) {
    _printf(s_br_brchg_end__0042765c);
  }
  return;
#undef label_rec
#undef chain_sym
#undef pred_block
#undef prev_block
}



