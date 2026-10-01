#include "decls.h"
#include "imports.h"

// entry: 00423410
// name : select_node_template
// size : 664
// sig  : short select_node_template(gen_node * node, tmpl_select * select, char operand_count, char by_constness, tmpl_header * * out)


short __cdecl
select_node_template
          (gen_node *node,tmpl_select *select,char operand_count,char by_constness,tmpl_header **out
          )

{
  uchar *rules;
  char left_class;
  uchar column;
  short left_index;
  void *variants;
  undefined3 extraout_var = 0;
  undefined3 extraout_var_00 = 0;
  char right_class;
  short right_index;
  tmpl_choice *choice;
  gen_node *operand;
  short ret;
  int *matrix;
  gen_node *left_opnd;
  il_op op;
  void **targets;
  
  matrix = (int *)0x0;
  targets = select->targets;
  if (operand_count == '\x01') {
    op = node->op;
    if ((op == IL_NOT) || ((left_opnd = node, '_' < (char)op && ((char)op < 'h')))) {
      left_opnd = node->child;
    }
    left_index = operand_type_class(left_opnd);
    choice = select->choice + left_index + -2;
    if (choice[2].how == '\x01') {
      ret = 0;
      *out = targets[choice[2].index];
      goto LAB_0042358e;
    }
    if (choice[2].index == 0xff) {
      report_codegen_message(0x1228,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    }
    if (choice[2].how != '\x03') {
LAB_00423582:
      matrix = targets[choice[2].index];
      goto LAB_0042358e;
    }
    variants = targets[choice[2].index];
  }
  else {
    left_index = operand_type_class(node->child);
    left_opnd = node;
    if (node->op != IL_CAST) {
      if (node->child == (gen_node *)0x0) {
        left_opnd = (gen_node *)0x0;
      }
      else {
        left_opnd = node->child->next;
      }
    }
    right_index = operand_type_class(left_opnd);
    choice = select->choice + left_index * 5 + (int)right_index + -2;
    if (choice[2].how == '\x01') {
      ret = 0;
      *out = targets[choice[2].index];
      goto LAB_0042358e;
    }
    if (choice[2].index == 0xff) {
      report_codegen_message(0x1228,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    }
    if (choice[2].how != '\x03') goto LAB_00423582;
    variants = targets[choice[2].index];
  }
  ret = select_cpu_variant_template(node,variants,out,&matrix,ret);
LAB_0042358e:
  if (matrix != (int *)0x0) {
    left_opnd = node->child;
    operand = (gen_node *)0x0;
    if (left_opnd != (gen_node *)0x0) {
      operand = left_opnd->next;
    }
    rules = (uchar *)matrix[2];
    if (by_constness == '\x01') {
      ret = 1;
      if ((left_opnd == (gen_node *)0x0) || (left_class = '\x02', left_opnd->op != IL_CONST)) {
        left_class = '\x03';
      }
      if ((operand == (gen_node *)0x0) || (operand->op != IL_CONST)) {
        right_class = '\x03';
      }
      else {
        right_class = '\x02';
      }
    }
    else {
      left_class = '\x03';
      ret = 0;
      if (left_opnd != (gen_node *)0x0) {
        left_class = left_opnd->desc->opnd_class;
      }
      right_class = '\x03';
      if (operand != (gen_node *)0x0) {
        right_class = operand->desc->opnd_class;
      }
    }
    left_index = (short)*(char *)((int)matrix + left_class * 2 + 0xc);
    if (left_index == -1) {
      column = select_matrix_column(left_opnd,rules,*(char *)((int)matrix + left_class * 2 + 0xd));
      left_index = (short)CONCAT31(extraout_var,column);
    }
    right_index = (short)*(char *)((int)matrix + right_class * 2 + 0x14);
    if (right_index == -1) {
      column = select_matrix_column(operand,rules,*(char *)((int)matrix + right_class * 2 + 0x15));
      right_index = (short)CONCAT31(extraout_var_00,column);
    }
    if ((left_index < 0) || (right_index < 0)) {
      report_codegen_message(0x1228,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    }
    *out = *(tmpl_header **)(matrix[1] * (int)left_index + right_index * 4 + *matrix);
  }
  return ret;
}



