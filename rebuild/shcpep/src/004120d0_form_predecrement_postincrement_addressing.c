#include "decls.h"
#include "imports.h"
#include "pep_rules.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_node_list
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))
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


// entry: 004120d0
// name : form_predecrement_postincrement_addressing
// size : 902
// sig  : void form_predecrement_postincrement_addressing(code_node * node)


int __cdecl form_predecrement_postincrement_addressing(code_node *node)

{
  unsigned char _frec_4[4];
#define add_rec (*(psd * *)(_frec_4 + 0))
  byte kind;
  char cVar1;
  uint uVar2;
  psd *rec;
  psd *cur_rec;
  uchar reg;
  psd *load_rec;
  bool reg_touched;
  int disp;
  psd_op op;
  ea *opnd;
  
  if (((*(unsigned char *)((char *)&g_stage_flags + 1)) & 0x20) != 0) {
    _printf(s_prdecea_start__nodeptr___08lx_0042694c,node);
    dump_node_list_debug(node);
  }
  cur_rec = node->psd;
  if (((byte)g_stage_flags & 2) != 0) {
    _printf(s_prdecea_start__cp___08lx_00426930,cur_rec);
  }
  load_rec = (psd *)0x0;
  add_rec = (psd *)0x0;
  if (cur_rec != (psd *)0x0) {
    (*(unsigned char *)((char *)&add_rec + 0)) = '\0';
    reg = (uchar)add_rec;
    do {
      if (((((cur_rec->op == OP_ADD) && (opnd = cur_rec->ea1, (opnd->type & 0x1f) == 7)) &&
           ((disp = opnd->disp, disp == -1 || ((disp == -2 || (disp == -4)))))) &&
          (opnd->labels == (label_ref *)0x0)) && (uVar2 = is_record_volatile(cur_rec), uVar2 == 0))
      {
        reg = cur_rec->ea2->base;
        add_rec = cur_rec;
      }
      if ((cur_rec->op == OP_MOV) || (cur_rec->op == OP_NON_B0)) {
        opnd = cur_rec->ea1;
        kind = opnd->type & 0x1f;
        if ((((kind == 2) || ((kind == 8 && (opnd->disp == 0)))) &&
            ((cur_rec->ea2->type & 0x1f) == 1)) &&
           ((reg = opnd->base, cur_rec->ea2->base != reg &&
            (uVar2 = is_record_volatile(cur_rec), uVar2 == 0)))) {
          load_rec = cur_rec;
        }
      }
      if ((add_rec != (psd *)0x0) || (load_rec != (psd *)0x0)) {
        rec = find_next_psd_record(node,cur_rec);
        if (rec != (psd *)0x0) {
          while ((add_rec == (psd *)0x0 ||
                 ((((rec->op != OP_MOV && (rec->op != OP_NON_B0)) ||
                   ((int)(char)(&g_access_size_bytes)[(byte)rec->flg & 3] + add_rec->ea1->disp != 0)
                   ) || ((rec->ea1->type & 0x1f) != 1))))) {
LAB_00412241:
            if ((((load_rec != (psd *)0x0) && !(pep_autoinc() & 1) && (rec->op == OP_ADD)) &&
                (opnd = rec->ea1, (opnd->type & 0x1f) == 7)) &&
               ((((int)(char)(&g_access_size_bytes)[(byte)load_rec->flg & 3] == opnd->disp &&
                 (rec->ea2->base == reg)) &&
                ((opnd->labels == (label_ref *)0x0 && (uVar2 = is_record_volatile(rec), uVar2 == 0))
                )))) {
              load_rec->ea1->type = load_rec->ea1->type & 0xf0;
              load_rec->ea1->type = load_rec->ea1->type | 4;
              add_rec = rec;
              goto LAB_004123ed;
            }
            op = rec->op;
            if ((((op == OP_SLEEP) || (op == OP_NON_10)) || ((op == OP_TRAPA || (op == OP_CASEJMP)))
                ) || ((((((op == OP_CALL || (op == OP_JSR)) || (op == OP_BSR)) || (op == OP_BSRF))
                       && (cVar1 = call_register_effect(rec,reg,0), cVar1 != '\0')) ||
                      (cVar1 = compute_record_register_masks(rec), cVar1 != '\0'))))
            goto LAB_004123f5;
            if (((char)reg < '\0') || ('_' < (char)reg)) {
              if ((char)reg < '`') {
                reg_touched = false;
              }
              else {
                reg_touched = (g_reg_mask_table[(char)reg] & g_rec_use_mask_hi) != 0;
              }
            }
            else {
              reg_touched = (g_reg_mask_table[(char)reg] & g_rec_use_mask_lo) != 0;
            }
            if (reg_touched) goto LAB_004123f5;
            if (((char)reg < '\0') || ('_' < (char)reg)) {
              if ((char)reg < '`') {
                reg_touched = false;
              }
              else {
                reg_touched = (g_reg_mask_table[(char)reg] & g_rec_def_mask_hi) != 0;
              }
            }
            else {
              reg_touched = (g_reg_mask_table[(char)reg] & g_rec_def_mask_lo) != 0;
            }
            if (reg_touched) goto LAB_004123f5;
            rec = find_next_psd_record(node,rec);
            if (((byte)g_stage_flags & 2) != 0) {
              _printf(s_cp___08lx_0042503c,rec);
            }
            if (rec == (psd *)0x0) goto LAB_004123f5;
          }
          opnd = rec->ea2;
          kind = opnd->type & 0x1f;
          if (((kind != 2) && ((kind != 8 || (opnd->disp != 0)))) ||
             ((reg != opnd->base ||
              ((rec->ea1->base == opnd->base || (uVar2 = is_record_volatile(rec), uVar2 != 0))))))
          goto LAB_00412241;
          if (pep_autoinc() & 2) goto LAB_004123f5;
          rec->ea2->type = rec->ea2->type & 0xf0;
          rec->ea2->type = rec->ea2->type | 3;
LAB_004123ed:
          delete_psd_record(add_rec);
        }
LAB_004123f5:
        load_rec = (psd *)0x0;
        add_rec = (psd *)0x0;
      }
      cur_rec = find_next_psd_record(node,cur_rec);
      if (((byte)g_stage_flags & 2) != 0) {
        _printf(s_cp___08lx_0042503c,cur_rec);
      }
    } while (cur_rec != (psd *)0x0);
  }
  if (((*(unsigned char *)((char *)&g_stage_flags + 1)) & 0x20) != 0) {
    dump_node_list_debug(g_current_node_list);
    _printf(s_prdecea_end__00426920);
  }
  return;
#undef add_rec
}



