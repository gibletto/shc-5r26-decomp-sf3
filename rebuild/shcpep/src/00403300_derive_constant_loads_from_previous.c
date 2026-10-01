#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0x5bf0))
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00403300
// name : derive_constant_loads_from_previous
// size : 1509
// sig  : void derive_constant_loads_from_previous(code_node * node)


int __cdecl derive_constant_loads_from_previous(code_node *node)

{
  byte reg;
  byte flg;
  char hit;
  uchar changes;
  short labno;
  psd *rec;
  symbol *sym;
  int iVar1;
  psd *ppVar2;
  ea *peVar3;
  code_node *rec_node;
  psd *scan;
  code_node *new_node;
  psd *ppVar4;
  psd *movi;
  psd *ppVar5;
  uint mask;
  int i;
  psd *local_10;
  int movi_labno;
  label_ref *lab;
  ea *movi_src;
  psd_op op;
  
  if (((*(unsigned char *)((char *)&g_stage_flags + 1)) & 0x20) != 0) {
    _printf(s_labld_start__nodeptr___08lx_004250cc,node);
    dump_node_list_debug(node);
  }
  movi = node->psd;
  i = movi_labno;
  if (((byte)g_stage_flags & 2) != 0) {
    _printf(s_labld_start__cp___08lx_004250b4,movi);
  }
  do {
    if (movi == (psd *)0x0) {
      if (((*(unsigned char *)((char *)&g_stage_flags + 1)) & 0x20) != 0) {
        dump_node_list_debug(node);
        _printf(s_labld_end__00425098);
      }
      return;
    }
    if ((((movi->op == OP_MOVI) && ((movi->ea1->type & 0x1f) == 7)) &&
        ((lab = movi->ea1->labels, lab == (label_ref *)0x0 ||
         (((lab->labno1 != 0 && (lab->labno2 == 0)) || (lab == (label_ref *)0x0)))))) &&
       ((movi->ea2->type & 0x1f) == 1)) {
      reg = movi->ea2->base;
      if (lab != (label_ref *)0x0) {
        movi_labno = (int)lab->labno1;
      }
      rec = find_next_psd_record(node,movi);
      if (((byte)g_stage_flags & 2) != 0) {
        _printf(s_ncp___08lx_00425048,rec);
      }
      if (rec != (psd *)0x0) {
        while (op = rec->op, op != OP_CASEJMP) {
          if (((op == OP_CALL) || (op == OP_JSR)) ||
             ((op == OP_BSR || ((op == OP_TRAPA || (op == OP_BSRF)))))) {
            if (((((-1 < (char)reg) && ((char)reg < '\x04')) ||
                 (((('\x0f' < (char)reg && ((char)reg < '\x14')) || (reg == 0x20)) ||
                  ((reg == 0x22 || (('\x03' < (char)reg && ((char)reg < '\b')))))))) ||
                (('\x13' < (char)reg &&
                 ((int)(char)reg <= g_current_request->scratch_bank_reg_count + 0x13)))) ||
               (('#' < (char)reg &&
                ((int)(char)reg <= g_current_request->scratch_bank_reg_count + 0x23)))) break;
            if (((char)reg < '\b') || ('\x0e' < (char)reg)) {
              if ((((int)(char)reg < g_current_request->scratch_bank_reg_count + 0x14) ||
                  ('\x1f' < (char)reg)) &&
                 (((int)(char)reg < g_current_request->scratch_bank_reg_count + 0x24 ||
                  ('.' < (char)reg)))) goto LAB_00403550;
            }
            if (((rec->ea1 == (ea *)0x0) || (lab = rec->ea1->labels, lab == (label_ref *)0x0)) ||
               (labno = lab->labno1, labno == 0)) {
              labno = 0;
            }
            sym = find_label_symbol(labno);
            if (((sym != (symbol *)0x0) && ((sym->attr & 0x10) == 0)) && ((sym->attr & 0xc) != 0))
            break;
            if ((char)reg < ' ') {
              mask = g_current_request->reg_mask_150 & 1 << (reg & 0x1f);
            }
            else if ((char)reg < '/') {
              mask = (1 << (reg - 0xf & 0x1f) | 1 << (reg - 0x10 & 0x1f)) &
                     g_current_request->reg_mask_150;
            }
            else {
              mask = 0;
            }
            if (mask != 0) break;
          }
LAB_00403550:
          if (((rec->op == OP_MOVI) && (iVar1 = is_movi_feeding_stack_add(node,rec), iVar1 == 0)) &&
             (((rec->op != OP_MOVI ||
               ((rec->ea1->labels != (label_ref *)0x0 ||
                (ppVar2 = find_next_psd_record(node,rec), ppVar2 != (psd *)0x0)))) &&
              (peVar3 = rec->ea1, (peVar3->type & 0x1f) == 7)))) {
            movi_src = movi->ea1;
            if (movi_src->labels == (label_ref *)0x0) {
LAB_004035d1:
              if ((peVar3->labels != (label_ref *)0x0) ||
                 ((-0x81 < peVar3->disp && (peVar3->disp < 0x80)))) goto LAB_00403822;
            }
            else {
              lab = peVar3->labels;
              if (((lab == (label_ref *)0x0) || (lab->labno1 != movi_labno)) || (lab->labno2 != 0))
              {
                if (movi_src->labels != (label_ref *)0x0) goto LAB_00403822;
                goto LAB_004035d1;
              }
            }
            if ((rec->ea2->type & 0x1f) == 1) {
              iVar1 = peVar3->disp - movi_src->disp;
              if ((iVar1 < -0x80) || (0x7f < iVar1)) break;
              if (rec->ea2->base == reg) {
                rec->op = OP_ADD;
                rec->flg = '\x02';
                rec->ea1->disp = iVar1;
                release_label_refs_of_record(rec,0);
                lab = rec->ea1->labels;
                if (lab != (label_ref *)0x0) {
                  pool_free(lab,8);
                }
                rec->ea1->labels = (label_ref *)0x0;
              }
              else {
                ppVar2 = (psd *)0x0;
                rec->op = OP_MOV;
                rec->flg = '\x02';
                release_label_refs_of_record(rec,0);
                peVar3 = copy_ea(movi->ea2);
                rec->ea1 = peVar3;
                rec_node = find_node_containing_record(node,rec);
                if (rec_node != (code_node *)0x0) {
                  scan = rec_node->psd;
                  i = 0;
                  do {
                    if ((scan == (psd *)0x0) || (scan == rec)) break;
                    i = i + 1;
                    scan = scan + 1;
                  } while (i < 0xf);
                }
                if (i < 0xe) {
                  ppVar2 = rec + 1;
                }
                if (((byte)g_stage_flags & 2) != 0) {
                  _printf(s_nncp___08lx_004250a4,ppVar2);
                }
                if ((ppVar2 == (psd *)0x0) || (ppVar2->op != OP_DUMMY)) {
                  new_node = (code_node *)alloc_zeroed_flushing_blocks(0x178);
                  new_node->next = rec_node->next;
                  rec_node->next = new_node;
                  if ((ppVar2 == (psd *)0x0) || (ppVar2->op == OP_DUMMY)) {
                    ppVar2 = new_node->psd;
                  }
                  else {
                    i = 0;
                    scan = rec_node->psd;
                    do {
                      ppVar5 = scan;
                      if (ppVar5 == (psd *)0x0) break;
                      i = i + 1;
                      scan = ppVar5 + 1;
                      local_10 = ppVar5;
                    } while (i < 0xf);
                    copy_psd_record(local_10,new_node->psd);
                    scan = local_10;
                    while (local_10 = scan, ppVar2 != scan) {
                      i = 0;
                      ppVar5 = rec;
                      do {
                        ppVar4 = ppVar5;
                        if (scan == ppVar4) break;
                        i = i + 1;
                        ppVar5 = ppVar4 + 1;
                        local_10 = ppVar4;
                      } while (i < 0xf);
                      copy_psd_record(local_10,scan);
                      scan = local_10;
                    }
                    clear_psd_record(ppVar2);
                  }
                  if (((byte)g_stage_flags & 2) != 0) {
                    _printf(s_nncp___08lx_004250a4,ppVar2);
                  }
                  ppVar2->op = OP_ADD;
                  flg = ppVar2->flg & 0xfc;
                  ppVar2->flg = flg;
                  ppVar2->flg = flg | 2;
                  ppVar2->expno = rec->expno;
                  ppVar2->filno = rec->filno;
                  ppVar2->linno = rec->linno;
                  peVar3 = (ea *)alloc_zeroed_flushing_blocks(0xc);
                  ppVar2->ea1 = peVar3;
                  peVar3->type = '\a';
                  ppVar2->ea1->disp = iVar1;
                  peVar3 = rec->ea2;
                }
                else {
                  ppVar2->op = OP_ADD;
                  flg = ppVar2->flg & 0xfc;
                  ppVar2->flg = flg;
                  ppVar2->flg = flg | 2;
                  ppVar2->expno = rec->expno;
                  ppVar2->filno = rec->filno;
                  ppVar2->linno = rec->linno;
                  peVar3 = (ea *)alloc_zeroed_flushing_blocks(0xc);
                  ppVar2->ea1 = peVar3;
                  peVar3->type = '\a';
                  ppVar2->ea1->disp = iVar1;
                  peVar3 = (ea *)alloc_zeroed_flushing_blocks(0xc);
                  ppVar2->ea2 = peVar3;
                  peVar3 = rec->ea2;
                }
                peVar3 = copy_ea(peVar3);
                ppVar2->ea2 = peVar3;
              }
            }
          }
LAB_00403822:
          hit = operand_uses_register(rec,reg,'\x01');
          if (((hit != '\0') || (hit = operand_uses_register(rec,reg,'\x02'), hit != '\0')) ||
             (changes = record_changes_register(rec,reg), changes != '\0')) break;
          rec = find_next_psd_record(node,rec);
          if (((byte)g_stage_flags & 2) != 0) {
            _printf(s_ncp___08lx_00425048,rec);
          }
          if (rec == (psd *)0x0) break;
        }
      }
    }
    movi = find_next_psd_record(node,movi);
    if (((byte)g_stage_flags & 2) != 0) {
      _printf(s_cp___08lx_0042503c,movi);
    }
  } while( true );
}



