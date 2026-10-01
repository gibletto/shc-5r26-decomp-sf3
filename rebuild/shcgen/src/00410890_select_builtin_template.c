#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00410890
// name : select_builtin_template
// size : 1481
// sig  : tmpl_header * select_builtin_template(char before_operands, gen_node * args)


tmpl_header * __cdecl select_builtin_template(char before_operands,gen_node *args)

{
  uint uVar1;
  int sym_index;
  int labno;
  gen_node *first_arg;
  gen_node *second_arg;
  ea *operand;
  byte ea_type;
  uint uVar2;
  char builtin_id;
  node_desc *desc;
  char first_class;
  label_ref *lab;
  
  builtin_id = args->desc->builtin;
  switch(builtin_id) {
  case '\x01':
    if (before_operands == '\x01') {
      if (args->child->op == IL_CONST) {
        return *(tmpl_header **)(*(int *)(&DAT_00449e4c + builtin_id * 8) + 4);
      }
      return *(tmpl_header **)(*(int *)(&DAT_00449e4c + builtin_id * 8) + 8);
    }
    first_class = args->child->desc->opnd_class;
    if ((first_class != '\x01') && (first_class != '\0')) {
      if (first_class == '\x02') {
        return *(tmpl_header **)(*(int *)(&DAT_00449e4c + builtin_id * 8) + 4);
      }
      return *(tmpl_header **)(*(int *)(&DAT_00449e4c + builtin_id * 8) + 8);
    }
    return (tmpl_header *)**(undefined4 **)(&DAT_00449e4c + builtin_id * 8);
  default:
    return (tmpl_header *)**(undefined4 **)(&DAT_00449e4c + builtin_id * 8);
  case '\x03':
  case '\x05':
  case '\n':
  case '\v':
  case '\f':
  case '\x11':
  case '\x14':
    if (before_operands == '\x01') {
      return *(tmpl_header **)(*(int *)(&DAT_00449e4c + builtin_id * 8) + 4);
    }
    first_class = args->child->desc->opnd_class;
    if ((first_class != '\x01') && (first_class != '\0')) {
      return *(tmpl_header **)(*(int *)(&DAT_00449e4c + builtin_id * 8) + 4);
    }
    return (tmpl_header *)**(undefined4 **)(&DAT_00449e4c + builtin_id * 8);
  case '\r':
  case '\x0e':
  case '\x0f':
  case '\x10':
    if (before_operands == '\x01') {
      return *(tmpl_header **)(*(int *)(&DAT_00449e4c + builtin_id * 8) + 4);
    }
    first_arg = args->child;
    second_arg = (gen_node *)0x0;
    if (first_arg != (gen_node *)0x0) {
      second_arg = first_arg->next;
    }
    if (second_arg->desc->opnd_class != '\x01') {
      second_arg = (gen_node *)0x0;
      if (first_arg != (gen_node *)0x0) {
        second_arg = first_arg->next;
      }
      if (second_arg->desc->opnd_class != '\0') {
        return *(tmpl_header **)(*(int *)(&DAT_00449e4c + builtin_id * 8) + 4);
      }
    }
    return (tmpl_header *)**(undefined4 **)(&DAT_00449e4c + builtin_id * 8);
  case '\x16':
    break;
  case '\x18':
  case '\x1a':
    if (before_operands == '\x01') {
      if (args->child->op == IL_CONST) {
        return (tmpl_header *)**(undefined4 **)(&DAT_00449e4c + builtin_id * 8);
      }
      return (tmpl_header *)(*(undefined4 **)(&DAT_00449e4c + builtin_id * 8))[1];
    }
    desc = args->child->desc;
    ea_type = 0;
    operand = desc->mem_ea;
    if (operand != (ea *)0x0) {
      ea_type = operand->type & 0x1f;
    }
    if (((ea_type == 0) && (operand = &desc->dest, (operand->type & 0x1f) == 0)) &&
       (operand = &g_ea_pop, (desc->flags2 & 8) == 0)) {
      operand = &desc->value;
    }
    if ((((operand->type & 0x1f) == 7) && (operand->labels == (label_ref *)0x0)) &&
       ((uint)operand->disp < 0x21)) {
      return (tmpl_header *)**(undefined4 **)(&DAT_00449e4c + builtin_id * 8);
    }
    return *(tmpl_header **)(*(int *)(&DAT_00449e4c + builtin_id * 8) + 4);
  case '\x19':
  case '\x1b':
    if (before_operands == '\x01') {
      if (args->child == (gen_node *)0x0) {
        first_arg = (gen_node *)0x0;
      }
      else {
        first_arg = args->child->next;
      }
      if (first_arg->op == IL_CONST) {
        return (tmpl_header *)**(undefined4 **)(&DAT_00449e4c + builtin_id * 8);
      }
      return (tmpl_header *)(*(undefined4 **)(&DAT_00449e4c + builtin_id * 8))[1];
    }
    first_arg = args->child;
    second_arg = (gen_node *)0x0;
    if (first_arg != (gen_node *)0x0) {
      second_arg = first_arg->next;
    }
    if (second_arg->desc->mem_ea == (ea *)0x0) {
      ea_type = 0;
    }
    else {
      second_arg = (gen_node *)0x0;
      if (first_arg != (gen_node *)0x0) {
        second_arg = first_arg->next;
      }
      ea_type = second_arg->desc->mem_ea->type & 0x1f;
    }
    if (ea_type == 0) {
      second_arg = (gen_node *)0x0;
      if (first_arg != (gen_node *)0x0) {
        second_arg = first_arg->next;
      }
      if (((second_arg->desc->dest).type & 0x1f) == 0) {
        second_arg = (gen_node *)0x0;
        if (first_arg != (gen_node *)0x0) {
          second_arg = first_arg->next;
        }
        if ((second_arg->desc->flags2 & 8) == 0) {
          second_arg = (gen_node *)0x0;
          if (first_arg != (gen_node *)0x0) {
            second_arg = first_arg->next;
          }
          operand = &second_arg->desc->value;
        }
        else {
          operand = &g_ea_pop;
        }
      }
      else if (first_arg == (gen_node *)0x0) {
        operand = (ea *)((*(int *)0x00000028) + 0x74);
      }
      else {
        operand = &first_arg->next->desc->dest;
      }
    }
    else if (first_arg == (gen_node *)0x0) {
      operand = *(ea **)((*(int *)0x00000028) + 0x5c);
    }
    else {
      operand = first_arg->next->desc->mem_ea;
    }
    if ((((operand->type & 0x1f) == 7) && (operand->labels == (label_ref *)0x0)) &&
       ((uint)operand->disp < 0x21)) {
      return (tmpl_header *)**(undefined4 **)(&DAT_00449e4c + builtin_id * 8);
    }
    return *(tmpl_header **)(*(int *)(&DAT_00449e4c + builtin_id * 8) + 4);
  }
  if (before_operands == '\x01') {
    if ((((g_request->switch_density_rule != 0) && (args->child->op == IL_ID)) &&
        (uVar1 = (int)args->child->symx + 0xb6, uVar2 = (int)uVar1 >> 0x1f,
        sym_index = (uVar1 ^ uVar2) - uVar2, g_symbol_table[sym_index].sclass == '\t')) &&
       ((int)g_symbol_table[sym_index].list_10 < 0x81)) {
      return *(tmpl_header **)(*(int *)(&DAT_00449e4c + builtin_id * 8) + 4);
    }
    return (tmpl_header *)**(undefined4 **)(&DAT_00449e4c + builtin_id * 8);
  }
  first_arg = args->child;
  second_arg = (gen_node *)0x0;
  if (first_arg != (gen_node *)0x0) {
    second_arg = first_arg->next;
  }
  if (second_arg->desc->mem_ea == (ea *)0x0) {
    ea_type = 0;
  }
  else {
    second_arg = (gen_node *)0x0;
    if (first_arg != (gen_node *)0x0) {
      second_arg = first_arg->next;
    }
    ea_type = second_arg->desc->mem_ea->type & 0x1f;
  }
  if (ea_type == 0) {
    second_arg = (gen_node *)0x0;
    if (first_arg != (gen_node *)0x0) {
      second_arg = first_arg->next;
    }
    if (((second_arg->desc->dest).type & 0x1f) == 0) {
      second_arg = (gen_node *)0x0;
      if (first_arg != (gen_node *)0x0) {
        second_arg = first_arg->next;
      }
      if ((second_arg->desc->flags2 & 8) == 0) {
        second_arg = (gen_node *)0x0;
        if (first_arg != (gen_node *)0x0) {
          second_arg = first_arg->next;
        }
        operand = &second_arg->desc->value;
      }
      else {
        operand = &g_ea_pop;
      }
    }
    else if (first_arg == (gen_node *)0x0) {
      operand = (ea *)((*(int *)0x00000028) + 0x74);
    }
    else {
      operand = &first_arg->next->desc->dest;
    }
  }
  else if (first_arg == (gen_node *)0x0) {
    operand = *(ea **)((*(int *)0x00000028) + 0x5c);
  }
  else {
    operand = first_arg->next->desc->mem_ea;
  }
  if (((g_request->switch_density_rule == 0) || (first_arg->op != IL_ID)) ||
     (uVar1 = (int)first_arg->symx + 0xb6, uVar2 = (int)uVar1 >> 0x1f,
     sym_index = (uVar1 ^ uVar2) - uVar2, g_symbol_table[sym_index].sclass != '\t'))
  goto LAB_00410c9e;
  if (((int)g_symbol_table[sym_index].list_10 < 0x81) &&
     ((ea_type = operand->type, (ea_type & 0x40) != 0 || ((ea_type & 0x1f) == 7)))) {
    ea_type = ea_type & 0x1f;
    if (((((ea_type == 2) && (operand->base == 'l')) || ((ea_type == 8 && (operand->base == 'l'))))
        && (uVar1 = operand->disp >> 0x1f, ((operand->disp ^ uVar1) - uVar1 & 3 ^ uVar1) == uVar1))
       || ((((ea_type == 0xd || (ea_type == 7)) && (operand->labels == (label_ref *)0x0)) &&
           (uVar1 = operand->disp >> 0x1f, ((operand->disp ^ uVar1) - uVar1 & 3 ^ uVar1) == uVar1)))
       ) goto LAB_00410c79;
    if (((ea_type == 0xd) || (ea_type == 7)) &&
       ((lab = operand->labels, lab != (label_ref *)0x0 && (lab->labno2 == 0)))) {
      labno = 0;
      if (lab != (label_ref *)0x0) {
        labno = (int)lab->labno1;
      }
      if (g_symbol_table[labno].sclass != '\x03') {
        labno = 0;
        if (lab != (label_ref *)0x0) {
          labno = (int)lab->labno1;
        }
        if (g_symbol_table[labno].sclass != '\x01') {
          labno = 0;
          if (lab != (label_ref *)0x0) {
            labno = (int)lab->labno1;
          }
          if (g_symbol_table[labno].sclass != '\t') {
            labno = 0;
            if (lab != (label_ref *)0x0) {
              labno = (int)lab->labno1;
            }
            if (g_symbol_table[labno].sclass != '\x04') goto LAB_00410c74;
          }
        }
      }
      labno = 0;
      if (lab != (label_ref *)0x0) {
        labno = (int)lab->labno1;
      }
      if ((g_symbol_table[labno].frame_offset + operand->disp & 3U) == 0) goto LAB_00410c79;
    }
  }
LAB_00410c74:
  if (0x20 < (int)g_symbol_table[sym_index].list_10) {
LAB_00410c9e:
    return (tmpl_header *)**(undefined4 **)(&DAT_00449e4c + builtin_id * 8);
  }
LAB_00410c79:
  if (args->parent->desc->usage == '\0') {
    return *(tmpl_header **)(*(int *)(&DAT_00449e4c + builtin_id * 8) + 4);
  }
  return *(tmpl_header **)(*(int *)(&DAT_00449e4c + builtin_id * 8) + 8);
}



