#include "decls.h"
#include "imports.h"
#include "pep_rules.h"

// entry: 004028f0
// name : propagate_r0_constant_to_successors
// size : 1254
// sig  : void propagate_r0_constant_to_successors(flow_block * origin, flow_block * block, psd * movi)


int __cdecl propagate_r0_constant_to_successors(flow_block *origin,flow_block *block,psd *movi)

{
  unsigned char _frec_4c[76];
#define local_4c (*(flow_edge * *)(_frec_4c + 0))
#define kept_movi (*(psd * *)(_frec_4c + 4))
#define local_44 (*(flow_block ** *)(_frec_4c + 8))
#define pred_count (*(int *)(_frec_4c + 12))
#define kept_node (*(code_node * *)(_frec_4c + 16))
#define block_defs (*(uint (*)[2])(_frec_4c + 20))
#define uses (*(uint (*)[2])(_frec_4c + 28))
#define pred_blocks (*(flow_block * (*)[10])(_frec_4c + 36))
  code_node *pcVar1;
  char equal;
  uint vol;
  int feeds_stack;
  psd *next_rec;
  psd *ppVar2;
  psd *rec;
  int iVar3;
  bool sets_r0;
  bool bVar4;
  bool deleted;
  code_node *node;
  byte old_flags2;
  psd_op op;
  flow_block *pred;
  flow_block *succ;
  
  if (((origin != (flow_block *)0x0) && (block != (flow_block *)0x0)) && (movi != (psd *)0x0)) {
#if SHC_REBUILD_UPDATED
    if (pep_r0_forget() >= 2 || (pep_r0_forget() == 1 && pep_block_is_conditional((int)block))) {
      return;
    }
#endif
    if ((block->flags & 1) == 0) {
      succ = block->next;
    }
    else {
      succ = block->target;
    }
    do {
      if (succ == (flow_block *)0x0) {
        return;
      }
      deleted = false;
      bVar4 = false;
      kept_movi = (psd *)0x0;
      old_flags2 = succ->flags2;
      if ((old_flags2 & 1) == 0) {
        if ((old_flags2 & 4) == 0) {
          local_4c = succ->preds;
          if ((local_4c == (flow_edge *)0x0) || (local_4c->block != (flow_block *)0x0)) {
            if (((local_4c != (flow_edge *)0x0) &&
                ((local_4c->block == block && (local_4c->next == (flow_edge *)0x0)))) &&
               (((succ->prev->flags & 1) != 0 || (block == succ->prev)))) {
              local_4c = (flow_edge *)0x0;
            }
            sets_r0 = false;
            if (succ != (flow_block *)0xffffffe4) {
              sets_r0 = (succ->defs[0] & g_reg_mask_table[0]) != 0;
            }
            if (sets_r0) {
              for (node = succ->code; node != (code_node *)0x0; node = node->next) {
                rec = node->psd;
                iVar3 = 0;
                do {
                  op = rec->op;
                  ppVar2 = kept_movi;
                  pcVar1 = kept_node;
                  if ((((((op != OP_LABEL) && (op != OP_DLABEL)) && (op != OP_CLABEL)) &&
                       ((op != OP_DUMMY && (op != OP_LINE)))) && (op != OP_BBGN)) && (op != OP_BEND)
                     ) {
                    if ((op == OP_MOVI) && (rec->ea2->base == '\0')) {
                      equal = operands_equal(rec->ea1,movi->ea1);
                      if (equal == '\0') break;
                      vol = is_record_volatile(rec);
                      ppVar2 = rec;
                      pcVar1 = node;
                      if ((((vol == 0) &&
                           (feeds_stack = is_movi_feeding_stack_add(node,rec), feeds_stack == 0)) &&
                          ((rec->op != OP_MOVI ||
                           ((rec->ea1->labels != (label_ref *)0x0 ||
                            (next_rec = find_next_psd_record(node,rec), next_rec != (psd *)0x0))))))
                         && ((kept_movi != (psd *)0x0 || (local_4c == (flow_edge *)0x0)))) {
                        delete_psd_record(rec);
                        deleted = true;
                        ppVar2 = kept_movi;
                        pcVar1 = kept_node;
                      }
                    }
                    else {
                      compute_record_register_use_def(rec,uses,block_defs);
                      if ((g_reg_mask_table[0] & block_defs[0]) != 0) break;
                    }
                  }
                  kept_node = pcVar1;
                  kept_movi = ppVar2;
                  iVar3 = iVar3 + 1;
                  rec = rec + 1;
                } while (iVar3 < 0xf);
                if (iVar3 < 0xf) {
                  succ->flags2 = succ->flags2 | 2;
                  break;
                }
              }
            }
            pred_count = 0;
            if ((local_4c != (flow_edge *)0x0) &&
               (pred_count = collect_pred_blocks_back_to_origin(origin,succ,pred_blocks,10),
               0 < pred_count)) {
              local_4c = (flow_edge *)0x0;
              local_44 = pred_blocks;
              do {
                pred = *local_44;
                if ((pred->flags2 & 2) != 0) {
                  bVar4 = true;
                  break;
                }
#if SHC_REBUILD_UPDATED
                if (pep_r0_forget() == 1 && pep_block_is_conditional((int)pred)) {
                  bVar4 = true;
                  break;
                }
#endif
                if ((pred->flags2 & 5) == 0) {
                  sets_r0 = false;
                  if (pred != (flow_block *)0xffffffe4) {
                    sets_r0 = (pred->defs[0] & g_reg_mask_table[0]) != 0;
                  }
                  if (sets_r0) {
                    for (node = pred->code; node != (code_node *)0x0; node = node->next) {
                      rec = node->psd;
                      iVar3 = 0;
                      do {
                        if ((((rec->op != OP_MOVI) || (rec->ea2->base != '\0')) ||
                            (equal = operands_equal(rec->ea1,movi->ea1), equal == '\0')) &&
                           (compute_record_register_use_def(rec,uses,block_defs),
                           (g_reg_mask_table[0] & block_defs[0]) != 0)) break;
                        iVar3 = iVar3 + 1;
                        rec = rec + 1;
                      } while (iVar3 < 0xf);
                      if (iVar3 < 0xf) {
                        bVar4 = true;
                        (*local_44)->flags2 = (*local_44)->flags2 | 2;
                        break;
                      }
                    }
                  }
                }
                local_44 = local_44 + 1;
                local_4c = (flow_edge *)((int)local_4c + 1);
              } while ((int)local_4c < pred_count);
              if (!bVar4) {
                if (0 < pred_count) {
                  local_44 = pred_blocks;
                  local_4c = (flow_edge *)pred_count;
                  do {
                    pred = *local_44;
                    if ((pred->flags2 & 5) == 0) {
                      sets_r0 = false;
                      if (pred != (flow_block *)0xffffffe4) {
                        sets_r0 = (pred->defs[0] & g_reg_mask_table[0]) != 0;
                      }
                      if (sets_r0) {
                        for (node = pred->code; node != (code_node *)0x0; node = node->next) {
                          rec = node->psd;
                          iVar3 = 0xf;
                          do {
                            if (((((rec->op == OP_MOVI) && (rec->ea2->base == '\0')) &&
                                 ((equal = operands_equal(rec->ea1,movi->ea1), equal != '\0' &&
                                  (feeds_stack = is_movi_feeding_stack_add(node,rec),
                                  feeds_stack == 0)))) &&
                                (((rec->op != OP_MOVI || (rec->ea1->labels != (label_ref *)0x0)) ||
                                 (ppVar2 = find_next_psd_record(node,rec), ppVar2 != (psd *)0x0))))
                               && (vol = is_record_volatile(rec), vol == 0)) {
                              delete_psd_record(rec);
                            }
                            rec = rec + 1;
                            iVar3 = iVar3 + -1;
                          } while (iVar3 != 0);
                        }
                        scan_flow_block_records(*local_44,'\x01');
                        (*local_44)->flags2 = (*local_44)->flags2 | 4;
                      }
                    }
                    local_44 = local_44 + 1;
                    local_4c = (flow_edge *)((int)local_4c + -1);
                  } while (local_4c != (flow_edge *)0x0);
                }
                if ((((kept_movi != (psd *)0x0) && (vol = is_record_volatile(kept_movi), vol == 0))
                    && (iVar3 = is_movi_feeding_stack_add(kept_node,kept_movi), iVar3 == 0)) &&
                   (((kept_movi->op != OP_MOVI || (kept_movi->ea1->labels != (label_ref *)0x0)) ||
                    (rec = find_next_psd_record(kept_node,kept_movi), rec != (psd *)0x0)))) {
                  delete_psd_record(kept_movi);
                  deleted = true;
                }
              }
            }
            if (deleted) {
              scan_flow_block_records(succ,'\x01');
            }
            old_flags2 = succ->flags2;
            succ->flags2 = old_flags2 | 1;
            if ((((old_flags2 & 2) == 0) && (pred_count != -1)) && (!bVar4)) goto LAB_00402da6;
          }
        }
        else {
          succ->flags2 = old_flags2 | 1;
LAB_00402da6:
          propagate_r0_constant_to_successors(origin,succ,movi);
        }
      }
      bVar4 = block->target != succ;
      succ = block->target;
    } while (bVar4);
  }
  return;
#undef local_4c
#undef kept_movi
#undef local_44
#undef pred_count
#undef kept_node
#undef block_defs
#undef uses
#undef pred_blocks
}



