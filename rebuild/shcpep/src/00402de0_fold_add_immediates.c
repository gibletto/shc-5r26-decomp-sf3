#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x6d50))
#undef g_current_node_list
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0x5bf0))
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00402de0
// name : fold_add_immediates
// size : 1055
// sig  : void fold_add_immediates(code_node * node)


int __cdecl fold_add_immediates(code_node *node)

{
  byte reg;
  char hit;
  uchar changes;
  short labno;
  uint uVar1;
  psd *rec;
  symbol *sym;
  psd *add_rec;
  int sum;
  int add_disp;
  label_ref *lab;
  psd_op op;
  
  if (((*(unsigned char *)((char *)&g_stage_flags + 1)) & 0x20) != 0) {
    _printf(s_imadd_start__nodeptr___08lx_0042506c,node);
    dump_node_list_debug(node);
  }
  add_rec = node->psd;
  if (((byte)g_stage_flags & 2) != 0) {
    _printf(s_imadd_start__cp___08lx_00425054,add_rec);
  }
  do {
    if (add_rec == (psd *)0x0) {
      if (((*(unsigned char *)((char *)&g_stage_flags + 1)) & 0x20) != 0) {
        dump_node_list_debug(g_current_node_list);
        _printf(s_imadd_end__00425030);
      }
      return;
    }
    if ((((add_rec->op == OP_ADD) && ((add_rec->ea1->type & 0x1f) == 7)) &&
        (add_rec->ea1->labels == (label_ref *)0x0)) &&
       ((uVar1 = is_record_volatile(add_rec), uVar1 == 0 && ((add_rec->ea2->type & 0x1f) == 1)))) {
      reg = add_rec->ea2->base;
      if (reg == 0xf) {
        rec = find_next_stack_adjust(node,add_rec);
      }
      else {
        rec = find_next_psd_record(node,add_rec);
      }
      if (((byte)g_stage_flags & 2) != 0) {
        _printf(s_ncp___08lx_00425048,add_rec);
      }
      if (rec != (psd *)0x0) {
        while ((op = rec->op, op != OP_EXIT || (reg != 0xf))) {
LAB_00402f06:
          if (op == OP_ADD) {
            if (((((rec->ea1->type & 0x1f) == 7) && ((rec->ea2->type & 0x1f) == 1)) &&
                (add_rec->ea1->labels == (label_ref *)0x0)) &&
               ((uVar1 = is_record_volatile(rec), uVar1 == 0 &&
                (hit = operands_equal(add_rec->ea2,rec->ea2), hit == '\x01')))) {
              sum = rec->ea1->disp + add_rec->ea1->disp;
              if ((-0x81 < sum) && (sum < 0x80)) {
                if (reg == 0xf) {
                  merge_sp_add_flags(add_rec,rec);
                }
                rec->ea1->disp = sum;
                goto LAB_0040319e;
              }
              goto LAB_004031a7;
            }
            hit = operand_uses_register(rec,reg,'\x01');
            if ((hit != '\0') || (hit = operand_uses_register(rec,reg,'\x02'), hit != '\0'))
            goto LAB_004031a7;
            changes = record_changes_register(rec,reg);
          }
          else {
            if (op == OP_CASEJMP) goto LAB_004031a7;
            if ((((op == OP_CALL) || (op == OP_JSR)) || (op == OP_BSR)) ||
               ((op == OP_TRAPA || (op == OP_BSRF)))) {
              if ((((-1 < (char)reg) && ((char)reg < '\x04')) ||
                  (((('\x0f' < (char)reg && ((char)reg < '\x14')) || (reg == 0x20)) ||
                   ((reg == 0x22 || (('\x03' < (char)reg && ((char)reg < '\b')))))))) ||
                 ((('\x13' < (char)reg &&
                   ((int)(char)reg <= g_current_request->scratch_bank_reg_count + 0x13)) ||
                  (('#' < (char)reg &&
                   ((int)(char)reg <= g_current_request->scratch_bank_reg_count + 0x23))))))
              goto LAB_004031a7;
              if (((char)reg < '\b') || ('\x0e' < (char)reg)) {
                if ((((int)(char)reg < g_current_request->scratch_bank_reg_count + 0x14) ||
                    ('\x1f' < (char)reg)) &&
                   (((int)(char)reg < g_current_request->scratch_bank_reg_count + 0x24 ||
                    ('.' < (char)reg)))) goto LAB_0040306a;
              }
              if (((rec->ea1 == (ea *)0x0) || (lab = rec->ea1->labels, lab == (label_ref *)0x0)) ||
                 (labno = lab->labno1, labno == 0)) {
                labno = 0;
              }
              sym = find_label_symbol(labno);
              if (((sym != (symbol *)0x0) && ((sym->attr & 0x10) == 0)) && ((sym->attr & 0xc) != 0))
              goto LAB_004031a7;
              if ((char)reg < ' ') {
                uVar1 = g_current_request->reg_mask_150 & 1 << (reg & 0x1f);
              }
              else if ((char)reg < '/') {
                uVar1 = (1 << (reg - 0xf & 0x1f) | 1 << (reg - 0x10 & 0x1f)) &
                        g_current_request->reg_mask_150;
              }
              else {
                uVar1 = 0;
              }
              if (uVar1 != 0) goto LAB_004031a7;
            }
LAB_0040306a:
            hit = operand_uses_register(rec,reg,'\x01');
            if ((hit != '\0') || (hit = operand_uses_register(rec,reg,'\x02'), hit != '\0'))
            goto LAB_004031a7;
            changes = record_changes_register(rec,reg);
          }
          if (changes != '\0') goto LAB_004031a7;
          rec = find_next_psd_record(node,rec);
          if (((byte)g_stage_flags & 2) != 0) {
            _printf(s_ncp___08lx_00425048,add_rec);
          }
          if (rec == (psd *)0x0) goto LAB_004031a7;
        }
        add_disp = add_rec->ea1->disp;
        sum = g_aux_record_table[g_current_aux_index].sp_adjust +
              g_aux_record_table[g_current_aux_index].frame_size;
        if (((-0x81 < sum) && (sum < 0x80)) && ((sum = add_disp + sum, sum < -0x80 || (0x7f < sum)))
           ) goto LAB_00402f06;
        g_aux_record_table[g_current_aux_index].sp_adjust =
             g_aux_record_table[g_current_aux_index].sp_adjust + add_disp;
LAB_0040319e:
        delete_psd_record(add_rec);
      }
    }
LAB_004031a7:
    add_rec = find_next_psd_record(node,add_rec);
    if (((byte)g_stage_flags & 2) != 0) {
      _printf(s_cp___08lx_0042503c,add_rec);
    }
  } while( true );
}



