#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00423800
// name : select_matrix_column
// size : 4768
// sig  : uchar select_matrix_column(gen_node * operand, uchar * rules, char first)


/* WARNING: Type propagation algorithm not settling */

uchar __cdecl select_matrix_column(gen_node *operand,uchar *rules,char first)

{
  label_ref *plVar1;
  char short_shift;
  short sVar2;
  undefined3 extraout_var = 0;
  undefined3 extraout_var_00 = 0;
  int iVar3;
  uint uVar4;
  byte bVar5;
  byte bVar6;
  ea *peVar7;
  uint sign;
  int const_value;
  ea *value_ea;
  node_desc *desc;
  gen_node *inner;
  bool matched;
  gen_node *parent;
  
  bVar6 = 0;
  desc = operand->desc;
  matched = false;
  parent = operand->parent;
  value_ea = desc->mem_ea;
  if (value_ea != (ea *)0x0) {
    bVar6 = value_ea->type & 0x1f;
  }
  if ((bVar6 == 0) && (value_ea = &desc->dest, (value_ea->type & 0x1f) == 0)) {
    if ((desc->flags2 & 8) == 0) {
      value_ea = &desc->value;
    }
    else {
      value_ea = &g_ea_pop;
    }
  }
  if (operand->op == IL_CONST) {
    const_value = operand->val;
  }
  else {
    const_value = (int)value_ea;
    if (desc->opnd_class == '\x02') {
      const_value = value_ea->disp;
    }
  }
  do {
    plVar1 = (label_ref *)const_value;
    switch(rules[first * 2]) {
    case '\x01':
      bVar6 = (parent->desc->dest).type & 0x1f;
joined_r0x004246ec:
      if (bVar6 != 0) goto switchD_0042388f_caseD_ff;
      break;
    case '\x02':
      if (operand->op == IL_B_QUALIFY) goto switchD_0042388f_caseD_ff;
      break;
    case '\x03':
      bVar6 = operand->type & 0xe0;
      if ((((bVar6 != 0x20) && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST))))
          && ((bVar6 != 0x40 || (operand->val2 == 0)))) && (const_value < 0x80))
      goto switchD_0042388f_caseD_ff;
      if ((((parent != (gen_node *)0x0) && ('7' < (char)parent->op)) && ((char)parent->op < '>')) &&
         ((parent->type & 0xe0) == 0x40)) {
        iVar3 = parent->val;
        goto joined_r0x0042406a;
      }
      break;
    case '\x04':
      bVar6 = operand->type & 0xe0;
      if (((((bVar6 != 0x20) && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST)))
            ) && ((bVar6 != 0x40 || (operand->val2 == 0)))) && (const_value < 0x81)) ||
         ((((parent != (gen_node *)0x0 && ('7' < (char)parent->op)) && ((char)parent->op < '>')) &&
          (((parent->type & 0xe0) == 0x40 && (parent->val < 0x81))))))
      goto switchD_0042388f_caseD_ff;
      break;
    case '\x05':
      bVar6 = operand->type & 0xe0;
      if (((bVar6 != 0x20) && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST))))
         && ((bVar6 != 0x40 || (operand->val2 == 0)))) {
joined_r0x00423ddb:
        if ((const_value < 0x80) && (-0x81 < const_value)) goto switchD_0042388f_caseD_ff;
      }
      break;
    case '\x06':
      bVar6 = operand->type & 0xe0;
      if (((bVar6 != 0x20) && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST))))
         && (((bVar6 != 0x40 || (operand->val2 == 0)) &&
             ((const_value < 0x80 && (-0x80 < const_value)))))) goto switchD_0042388f_caseD_ff;
      break;
    case '\a':
      bVar6 = operand->type & 0xe0;
      if (((bVar6 != 0x20) && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST))))
         && ((bVar6 != 0x40 || (operand->val2 == 0)))) {
        sVar2 = single_bit_position(const_value);
joined_r0x004245a9:
        if (sVar2 != -1) goto switchD_0042388f_caseD_ff;
      }
      break;
    case '\b':
      bVar6 = operand->type & 0xe0;
      if (((bVar6 != 0x20) && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST))))
         && ((bVar6 != 0x40 || (operand->val2 == 0)))) {
        sVar2 = single_bit_position(const_value - 1);
        goto joined_r0x004245a9;
      }
      break;
    case '\t':
      bVar6 = operand->type & 0xe0;
      if (((bVar6 != 0x20) && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST))))
         && ((bVar6 != 0x40 || (operand->val2 == 0)))) {
        sVar2 = single_bit_position(const_value + 1);
        goto joined_r0x004245a9;
      }
      break;
    case '\n':
      bVar6 = operand->type & 0xe0;
      if (((bVar6 != 0x20) && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST))))
         && ((bVar6 != 0x40 || (operand->val2 == 0)))) {
        sVar2 = two_bit_mask_bit_position(const_value,1);
        goto joined_r0x004245a9;
      }
      break;
    case '\v':
      bVar6 = operand->type & 0xe0;
      if ((((bVar6 != 0x20) && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST))))
          && ((bVar6 != 0x40 || (operand->val2 == 0)))) &&
         ((const_value < 0x1e && (-1 < const_value)))) {
        short_shift = is_short_constant_shift(const_value);
        sVar2 = (short)CONCAT31(extraout_var,short_shift);
joined_r0x0042433d:
        if (sVar2 != 0) goto switchD_0042388f_caseD_ff;
      }
      break;
    case '\f':
      bVar6 = operand->type & 0xe0;
      if ((bVar6 != 0x20) && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST)))) {
        if (bVar6 == 0x40) {
          iVar3 = operand->val2;
joined_r0x00423e8c:
          if (iVar3 != 0) break;
        }
joined_r0x00423e95:
        if (const_value == 0x1e) goto switchD_0042388f_caseD_ff;
      }
      break;
    case '\r':
      bVar6 = operand->type & 0xe0;
      if (((bVar6 != 0x20) && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST))))
         && ((bVar6 != 0x40 || (operand->val2 == 0)))) {
joined_r0x004242f3:
        if (const_value == 0x1f) goto switchD_0042388f_caseD_ff;
      }
      break;
    case '\x0e':
      if (operand->op == IL_B_QUALIFY) {
        desc = operand->desc;
        bVar6 = 0;
        if (desc->saved_ea != (ea *)0x0) {
          bVar6 = desc->saved_ea->type & 0x1f;
        }
        if (bVar6 != 0) {
          peVar7 = desc->saved_reg_ea;
          bVar6 = 0;
          if (peVar7 != (ea *)0x0) {
            bVar6 = peVar7->type & 0x1f;
          }
          if ((bVar6 == 0) && (peVar7 = &g_ea_pop, (desc->flags3 & 0x10) == 0)) {
            peVar7 = desc->saved_ea;
          }
          if ((peVar7->type & 0x1f) == 1) goto switchD_0042388f_caseD_ff;
        }
      }
      break;
    case '\x0f':
      bVar6 = operand->type & 0xe0;
      if ((((((bVar6 != 0x20) && ((parent->type & 4) == 0)) &&
            (bVar5 = parent->type & 0xe0, bVar5 != 0x80)) && (bVar5 != 0x40)) &&
          (((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST)) &&
           ((bVar6 != 0x40 || (operand->val2 == 0)))))) && (const_value < 5)) {
joined_r0x0042463d:
        if (-1 < const_value) goto switchD_0042388f_caseD_ff;
      }
      break;
    case '\x10':
      bVar6 = operand->type & 0xe0;
      if ((bVar6 != 0x20) &&
         ((((((parent->type & 4) != 0 || (bVar5 = parent->type & 0xe0, bVar5 == 0x80)) ||
            (bVar5 == 0x40)) ||
           ((((parent->child->op == IL_CAST &&
              (inner = parent->child->child, inner != (gen_node *)0x0)) &&
             ((bVar5 = inner->type, (bVar5 & 4) != 0 ||
              (((bVar5 & 0xe0) == 0x80 || ((bVar5 & 0xe0) == 0x40)))))) &&
            (((bVar5 & 0xf8) == 0 || ((bVar5 & 0xf8) == 8)))))) &&
          (((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST)) &&
           (((bVar6 != 0x40 || (operand->val2 == 0)) && ((const_value < 0x1e && (-1 < const_value)))
            ))))))) {
        short_shift = is_short_constant_shift(const_value);
        sVar2 = (short)CONCAT31(extraout_var_00,short_shift);
        goto joined_r0x0042433d;
      }
      break;
    case '\x11':
      if ((value_ea != (ea *)0x0) && ((value_ea->type & 0x1f) == 1)) {
        bVar6 = value_ea->base;
joined_r0x004246a3:
        if (bVar6 == 0) goto switchD_0042388f_caseD_ff;
      }
      break;
    case '\x12':
      bVar6 = operand->type & 0xe0;
      if (((bVar6 != 0x20) && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST))))
         && ((bVar6 != 0x40 || (operand->val2 == 0)))) {
        if ((const_value < 0x100) && (-1 < const_value)) goto switchD_0042388f_caseD_ff;
        if (((parent->type & 0xfc) == 0) &&
           ((bVar6 = parent->type & 0xe0, bVar6 != 0x80 && (bVar6 != 0x40))))
        goto joined_r0x00423ddb;
      }
      break;
    case '\x13':
      if (value_ea != (ea *)0x0) {
        uVar4 = ea_register_mask(value_ea);
        plVar1 = (label_ref *)(uVar4 & 1);
joined_r0x004240de:
        if (plVar1 == (label_ref *)0x0) goto switchD_0042388f_caseD_ff;
      }
      break;
    case '\x14':
      bVar6 = operand->type & 0xe0;
      if (((bVar6 != 0x20) &&
          (((((parent->type & 4) != 0 || (bVar5 = parent->type & 0xe0, bVar5 == 0x80)) ||
            (bVar5 == 0x40)) ||
           ((((parent->child->op == IL_CAST &&
              (inner = parent->child->child, inner != (gen_node *)0x0)) &&
             ((bVar5 = inner->type, (bVar5 & 4) != 0 ||
              (((bVar5 & 0xe0) == 0x80 || ((bVar5 & 0xe0) == 0x40)))))) &&
            (((bVar5 & 0xf8) == 0 || ((bVar5 & 0xf8) == 8)))))))) &&
         ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST)))) {
        if (bVar6 == 0x40) {
          iVar3 = operand->val2;
          goto joined_r0x00423e8c;
        }
        goto joined_r0x00423e95;
      }
      break;
    case '\x15':
      bVar6 = operand->type & 0xe0;
      if (((bVar6 != 0x20) &&
          (((((parent->type & 4) != 0 || (bVar5 = parent->type & 0xe0, bVar5 == 0x80)) ||
            (bVar5 == 0x40)) ||
           ((((parent->child->op == IL_CAST &&
              (inner = parent->child->child, inner != (gen_node *)0x0)) &&
             ((bVar5 = inner->type, (bVar5 & 4) != 0 ||
              (((bVar5 & 0xe0) == 0x80 || ((bVar5 & 0xe0) == 0x40)))))) &&
            (((bVar5 & 0xf8) == 0 || ((bVar5 & 0xf8) == 8)))))))) &&
         ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST)))) {
        if (bVar6 == 0x40) {
          iVar3 = operand->val2;
joined_r0x004242ea:
          if (iVar3 != 0) break;
        }
        goto joined_r0x004242f3;
      }
      break;
    case '\x16':
      bVar6 = operand->type & 0xe0;
      if ((bVar6 != 0x20) && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST)))) {
        if (bVar6 == 0x40) {
          iVar3 = operand->val2;
joined_r0x004240d6:
          if (iVar3 != 0) break;
        }
        goto joined_r0x004240de;
      }
      break;
    case '\x17':
      if ((value_ea != (ea *)0x0) && ((value_ea->type & 0x1f) == 0xd))
      goto switchD_0042388f_caseD_ff;
      break;
    case '\x18':
      if ((value_ea != (ea *)0x0) &&
         (((bVar6 = value_ea->type & 0x1f, bVar6 == 2 && (value_ea->base == 'l')) ||
          ((bVar6 == 8 && (value_ea->base == 'l')))))) goto switchD_0042388f_caseD_ff;
      break;
    case '\x19':
      if (value_ea != (ea *)0x0) {
        bVar6 = value_ea->type & 0x1f;
        if (bVar6 == 2) goto switchD_0042388f_caseD_ff;
        if ((bVar6 == 8) && (value_ea->disp == 0)) {
          plVar1 = value_ea->labels;
          goto joined_r0x004240de;
        }
      }
      break;
    case '\x1a':
      if ((((value_ea != (ea *)0x0) && (uVar4 = value_ea->disp, 0 < (int)uVar4)) &&
          ((int)uVar4 < 0x39)) &&
         (sign = (int)uVar4 >> 0x1f, ((uVar4 ^ sign) - sign & 3 ^ sign) == sign)) {
        plVar1 = value_ea->labels;
        goto joined_r0x004240de;
      }
      break;
    case '\x1b':
      if (((value_ea != (ea *)0x0) && (value_ea->labels == (label_ref *)0x0)) &&
         (iVar3 = value_ea->disp, -0x80 < iVar3)) {
joined_r0x0042406a:
        if (iVar3 < 0x80) goto switchD_0042388f_caseD_ff;
      }
      break;
    case '\x1c':
      if ((operand->type & 0xf8) == 0x30) {
        bVar6 = operand->desc->flags2 & 8;
        goto joined_r0x004246ec;
      }
      break;
    case '\x1d':
      bVar6 = operand->type & 0xe0;
      if (((((bVar6 != 0x20) && ((operand->type & 4) == 0)) && (bVar6 != 0x80)) && (bVar6 != 0x40))
         && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST)))) {
        if (bVar6 == 0x40) {
          iVar3 = operand->val2;
          goto joined_r0x004240d6;
        }
        goto joined_r0x004240de;
      }
      break;
    case '\x1e':
      bVar6 = operand->type & 0xe0;
      if ((((bVar6 != 0x20) && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST))))
          && ((bVar6 != 0x40 || (operand->val2 == 0)))) && (const_value < 0x20))
      goto joined_r0x0042463d;
      break;
    case '\x1f':
      bVar6 = operand->type & 0xe0;
      if ((bVar6 != 0x20) && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST)))) {
        if (bVar6 == 0x40) {
          iVar3 = operand->val2;
joined_r0x0042462c:
          if (iVar3 != 0) break;
        }
joined_r0x00424635:
        if (const_value < 0x1d) goto joined_r0x0042463d;
      }
      break;
    case ' ':
      bVar6 = operand->type & 0xe0;
      if (((bVar6 != 0x20) && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST))))
         && (((bVar6 != 0x40 || (operand->val2 == 0)) && (const_value == 0x1d))))
      goto switchD_0042388f_caseD_ff;
      break;
    case '!':
      bVar6 = operand->type & 0xe0;
      if (((bVar6 != 0x20) &&
          (((((parent->type & 4) != 0 || (bVar5 = parent->type & 0xe0, bVar5 == 0x80)) ||
            (bVar5 == 0x40)) ||
           ((((parent->child->op == IL_CAST &&
              (inner = parent->child->child, inner != (gen_node *)0x0)) &&
             ((bVar5 = inner->type, (bVar5 & 4) != 0 ||
              (((bVar5 & 0xe0) == 0x80 || ((bVar5 & 0xe0) == 0x40)))))) &&
            (((bVar5 & 0xf8) == 0 || ((bVar5 & 0xf8) == 8)))))))) &&
         (((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST)) &&
          (((bVar6 != 0x40 || (operand->val2 == 0)) && (const_value < 0x20)))))) {
joined_r0x00424298:
        if (0x1c < const_value) goto switchD_0042388f_caseD_ff;
      }
      break;
    case '\"':
      bVar6 = operand->type & 0xe0;
      if ((((((bVar6 != 0x20) && ((parent->type & 4) == 0)) &&
            ((bVar5 = parent->type & 0xe0, bVar5 != 0x80 && (bVar5 != 0x40)))) &&
           ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST)))) &&
          ((bVar6 != 0x40 || (operand->val2 == 0)))) && (const_value < 0x1f))
      goto joined_r0x00424298;
      break;
    case '#':
      bVar6 = operand->type & 0xe0;
      if ((((bVar6 != 0x20) && ((parent->type & 4) == 0)) &&
          (bVar5 = parent->type & 0xe0, bVar5 != 0x80)) &&
         ((bVar5 != 0x40 && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST))))))
      {
        if (bVar6 == 0x40) {
          iVar3 = operand->val2;
          goto joined_r0x004242ea;
        }
        goto joined_r0x004242f3;
      }
      break;
    case '$':
      bVar6 = operand->type & 0xe0;
      if (((bVar6 != 0x20) && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST))))
         && ((bVar6 != 0x40 || (operand->val2 == 0)))) {
        iVar3 = expand_multiply_by_constant(const_value,(ea *)0x0,(ea **)0x0,0);
        sVar2 = (short)iVar3;
        goto joined_r0x0042433d;
      }
      break;
    case '%':
      bVar6 = operand->type & 0xe0;
      if ((((((bVar6 != 0x20) && ((operand->type & 4) == 0)) && (bVar6 != 0x80)) && (bVar6 != 0x40))
          && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST)))) &&
         (((bVar6 != 0x40 || (operand->val2 == 0)) && (const_value == 2))))
      goto switchD_0042388f_caseD_ff;
      break;
    case '&':
      bVar6 = operand->type & 0xe0;
      if ((((bVar6 != 0x20) && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST))))
          && ((bVar6 != 0x40 || (operand->val2 == 0)))) &&
         ((((-1 < const_value && (const_value < 7)) || ((7 < const_value && (const_value < 0xd))))
          || (((0xf < const_value && (const_value < 0x15)) ||
              ((0x17 < const_value && (const_value < 0x1b)))))))) goto switchD_0042388f_caseD_ff;
      break;
    case '\'':
      bVar6 = operand->type & 0xe0;
      if (((bVar6 != 0x20) &&
          (((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST)) &&
           ((bVar6 != 0x40 || (operand->val2 == 0)))))) &&
         (((((((parent->type & 4) != 0 || (bVar6 = parent->type & 0xe0, bVar6 == 0x80)) ||
             (bVar6 == 0x40)) ||
            ((((parent->child->op == IL_CAST &&
               (inner = parent->child->child, inner != (gen_node *)0x0)) &&
              ((bVar6 = inner->type, (bVar6 & 4) != 0 ||
               (((bVar6 & 0xe0) == 0x80 || ((bVar6 & 0xe0) == 0x40)))))) &&
             (((bVar6 & 0xf8) == 0 || ((bVar6 & 0xf8) == 8)))))) &&
           ((((-1 < const_value && (const_value < 7)) || ((7 < const_value && (const_value < 0xd))))
            || (((0xf < const_value && (const_value < 0x15)) ||
                ((0x17 < const_value && (const_value < 0x1b)))))))) ||
          ((((-1 < const_value && (const_value < 4)) || (const_value == 0x10)) ||
           ((const_value == 0x11 || (const_value == 0x18)))))))) goto switchD_0042388f_caseD_ff;
      break;
    case '(':
      bVar6 = operand->type & 0xe0;
      if ((((((bVar6 != 0x20) && ((parent->type & 4) == 0)) &&
            (bVar5 = parent->type & 0xe0, bVar5 != 0x80)) &&
           ((bVar5 != 0x40 && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST)))))
           ) && ((bVar6 != 0x40 || (operand->val2 == 0)))) &&
         ((((const_value < 7 && (-1 < const_value)) || ((const_value < 0x15 && (0xf < const_value)))
           ) || ((const_value < 0x1c && (0x17 < const_value)))))) goto switchD_0042388f_caseD_ff;
      break;
    case ')':
      bVar6 = operand->type & 0xe0;
      if (((bVar6 != 0x20) && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST))))
         && (((bVar6 != 0x40 || (operand->val2 == 0)) &&
             ((const_value != 0 && ((const_value & 0xfffefef9U) == 0)))))) {
        sVar2 = two_bit_mask_bit_position(const_value,1);
        goto joined_r0x004245a9;
      }
      break;
    case '*':
      bVar6 = operand->type & 0xe0;
      if ((bVar6 != 0x20) &&
         ((((((parent->type & 4) != 0 || (bVar5 = parent->type & 0xe0, bVar5 == 0x80)) ||
            (bVar5 == 0x40)) ||
           ((((parent->child->op == IL_CAST &&
              (inner = parent->child->child, inner != (gen_node *)0x0)) &&
             ((bVar5 = inner->type, (bVar5 & 4) != 0 ||
              (((bVar5 & 0xe0) == 0x80 || ((bVar5 & 0xe0) == 0x40)))))) &&
            (((bVar5 & 0xf8) == 0 || ((bVar5 & 0xf8) == 8)))))) &&
          ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST)))))) {
        if (bVar6 == 0x40) {
          iVar3 = operand->val2;
          goto joined_r0x0042462c;
        }
        goto joined_r0x00424635;
      }
      break;
    case '+':
      if ((((parent != (gen_node *)0x0) && (parent->op == IL_B_AND)) &&
          (parent->desc->usage == '\x01')) && (value_ea != (ea *)0x0)) {
        if (value_ea->labels == (label_ref *)0x0) {
          uVar4 = 0;
        }
        else {
          uVar4 = (uint)value_ea->labels->labno1;
        }
        if ((g_symbol_table[(uVar4 ^ (int)uVar4 >> 0x1f) - ((int)uVar4 >> 0x1f)].attr & 3) != 0) {
          bVar6 = operand->type & 0xf8;
          goto joined_r0x004246a3;
        }
      }
      break;
    case ',':
      if (((operand->type & 0xf8) == 0) && (value_ea != (ea *)0x0)) {
        if (value_ea->labels == (label_ref *)0x0) {
          uVar4 = 0;
        }
        else {
          uVar4 = (uint)value_ea->labels->labno1;
        }
        bVar6 = g_symbol_table[(uVar4 ^ (int)uVar4 >> 0x1f) - ((int)uVar4 >> 0x1f)].attr & 3;
        goto joined_r0x004246ec;
      }
      break;
    case '-':
      bVar6 = operand->type & 0xe0;
      if (((bVar6 != 0x20) &&
          (((((parent->type & 4) != 0 || (bVar5 = parent->type & 0xe0, bVar5 == 0x80)) ||
            (bVar5 == 0x40)) ||
           ((((parent->child->op == IL_CAST &&
              (inner = parent->child->child, inner != (gen_node *)0x0)) &&
             ((bVar5 = inner->type, (bVar5 & 4) != 0 ||
              (((bVar5 & 0xe0) == 0x80 || ((bVar5 & 0xe0) == 0x40)))))) &&
            (((bVar5 & 0xf8) == 0 || ((bVar5 & 0xf8) == 8)))))))) &&
         ((((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST)) &&
           ((bVar6 != 0x40 || (operand->val2 == 0)))) &&
          ((const_value < 0x20 && (0x1d < const_value)))))) goto switchD_0042388f_caseD_ff;
      break;
    case '.':
      bVar6 = operand->type & 0xe0;
      if (((((((bVar6 != 0x20) && ((operand->type & 4) == 0)) && (bVar6 != 0x80)) &&
            ((bVar6 != 0x40 && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST))))
            )) && ((bVar6 != 0x40 || (operand->val2 == 0)))) &&
          (sVar2 = single_bit_position(const_value), sVar2 != -1)) &&
         ((((sVar2 = single_bit_position(const_value), 1 < sVar2 && (sVar2 < 4)) ||
           ((0xf < sVar2 && (sVar2 < 0x12)))) || (sVar2 == 0x18)))) goto switchD_0042388f_caseD_ff;
      break;
    case '/':
      bVar6 = operand->type & 0xe0;
      if (((((((bVar6 != 0x20) && ((operand->type & 4) == 0)) && (bVar6 != 0x80)) &&
            ((bVar6 != 0x40 && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST))))
            )) && ((bVar6 != 0x40 || (operand->val2 == 0)))) &&
          ((sVar2 = single_bit_position(const_value), sVar2 != -1 &&
           (sVar2 = single_bit_position(const_value), sVar2 != 0x1f)))) && (3 < sVar2))
      goto switchD_0042388f_caseD_ff;
      break;
    case '0':
      bVar6 = operand->type & 0xe0;
      if (((((((bVar6 != 0x20) && ((operand->type & 4) == 0)) && (bVar6 != 0x80)) && (bVar6 != 0x40)
            ) && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST)))) &&
          (((bVar6 != 0x40 || (operand->val2 == 0)) &&
           ((sVar2 = single_bit_position(const_value), sVar2 != -1 &&
            (sVar2 = single_bit_position(const_value), 1 < sVar2)))))) && (sVar2 < 0x1d))
      goto switchD_0042388f_caseD_ff;
      break;
    case '1':
      bVar6 = operand->type & 0xe0;
      if (((((bVar6 != 0x20) && ((operand->type & 4) == 0)) && (bVar6 != 0x80)) &&
          ((bVar6 != 0x40 && ((operand->desc->opnd_class == '\x02' || (operand->op == IL_CONST))))))
         && (((bVar6 != 0x40 || (operand->val2 == 0)) &&
             (((sVar2 = single_bit_position(const_value), sVar2 != -1 &&
               (sVar2 = single_bit_position(const_value), 0x1c < sVar2)) && (sVar2 < 0x1f))))))
      goto switchD_0042388f_caseD_ff;
      break;
    case '2':
      bVar6 = operand->type;
      if (((((bVar6 & 4) != 0) || (((bVar6 & 0xe0) == 0x80 || ((bVar6 & 0xe0) == 0x40)))) &&
          (((bVar6 & 0xf8) == 0x10 || ((bVar6 & 0xf8) == 0x18)))) || ((bVar6 & 0xe0) == 0x40))
      goto switchD_0042388f_caseD_ff;
      break;
    case '3':
      if (((parent != (gen_node *)0x0) && (parent->op == IL_CAST)) &&
         ((operand->type & 0xf8) == 0x28)) {
        bVar6 = parent->type;
        bVar5 = bVar6 & 0xe0;
        if (bVar5 == 0x40) goto switchD_0042388f_caseD_ff;
joined_r0x00424a62:
        if (((((bVar6 & 4) != 0) || (bVar5 == 0x80)) || (bVar5 == 0x40)) &&
           (((bVar6 & 0xf8) == 0x10 || ((bVar6 & 0xf8) == 0x18)))) goto switchD_0042388f_caseD_ff;
      }
      break;
    case '4':
      if (operand->op == IL_B_QUALIFY) {
        bVar6 = operand->type;
joined_r0x00424a5e:
        bVar5 = bVar6 & 0xe0;
        if (bVar5 != 0x40) goto joined_r0x00424a62;
        goto switchD_0042388f_caseD_ff;
      }
      break;
    case '5':
      if (((parent != (gen_node *)0x0) && (parent->op == IL_CAST)) &&
         ((operand->type & 0xf8) == 0x30)) {
        bVar6 = parent->type;
        goto joined_r0x00424a5e;
      }
      break;
    case 0xff:
switchD_0042388f_caseD_ff:
      matched = true;
    }
    first = first + '\x01';
    if (matched) {
      return rules[first * 2 + -1];
    }
  } while( true );
}



