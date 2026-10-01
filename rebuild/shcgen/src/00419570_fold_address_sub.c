#include "decls.h"
#include "imports.h"

// entry: 00419570
// name : fold_address_sub
// size : 597
// sig  : short fold_address_sub(gen_node * node, gen_node * left, gen_node * right)


short __cdecl fold_address_sub(gen_node *node,gen_node *left,gen_node *right)

{
  short left_class;
  short right_class;
  label_ref *merged_labels;
  int iVar1;
  ea *peVar2;
  byte kind;
  ea *src;
  ea *right_ea;
  short fold_result;
  int *disp_ptr;
  node_desc *left_desc;
  int right_disp;
  
  fold_result = 0;
  left_class = classify_address_operand(left);
  right_class = classify_address_operand(right);
  left_desc = left->desc;
  kind = 0;
  peVar2 = left_desc->mem_ea;
  if (peVar2 != (ea *)0x0) {
    kind = peVar2->type & 0x1f;
  }
  src = peVar2;
  if (((kind == 0) && (src = &left_desc->dest, ((left_desc->dest).type & 0x1f) == 0)) &&
     (src = &g_ea_pop, (left_desc->flags2 & 8) == 0)) {
    src = &left_desc->value;
  }
  right_ea = right->desc->mem_ea;
  kind = 0;
  if (right_ea != (ea *)0x0) {
    kind = right_ea->type & 0x1f;
  }
  if (((kind == 0) && (right_ea = &right->desc->dest, (right_ea->type & 0x1f) == 0)) &&
     (right_ea = &g_ea_pop, (right->desc->flags2 & 8) == 0)) {
    right_ea = &right->desc->value;
  }
  switch((&g_sub_fold_kind)[(int)right_class + left_class * 9]) {
  default:
    report_codegen_message(0x1221,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    break;
  case 2:
    if (left_class == 2) {
      iVar1 = src->disp;
      if (iVar1 < 0) {
        if (iVar1 - right_ea->disp < -3) goto LAB_00419681;
        if (iVar1 < 0) {
          return 0;
        }
      }
      if (iVar1 - right_ea->disp < 0) {
        return 0;
      }
    }
LAB_00419681:
    kind = 0;
    if (peVar2 != (ea *)0x0) {
      kind = peVar2->type & 0x1f;
    }
    if (((kind == 0) && (peVar2 = &left_desc->dest, (peVar2->type & 0x1f) == 0)) &&
       (peVar2 = &g_ea_pop, (left_desc->flags2 & 8) == 0)) {
      peVar2 = &left_desc->value;
    }
    copy_ea_into(&node->desc->value,peVar2);
    disp_ptr = &(node->desc->value).disp;
    *disp_ptr = *disp_ptr - right_ea->disp;
    merged_labels = combine_label_ref_lists(src->labels,right_ea->labels,0);
    (node->desc->value).labels = merged_labels;
    goto LAB_004197b1;
  case 3:
    iVar1 = src->disp;
    if (iVar1 < 0) {
LAB_004196fa:
      if (-1 < right_ea->disp) {
        return 0;
      }
    }
    else if (right_ea->disp < 0) {
      if (-1 < iVar1) {
        return 0;
      }
      goto LAB_004196fa;
    }
    merged_labels = (label_ref *)0x0;
    goto LAB_00419792;
  case 4:
    iVar1 = src->disp;
    right_disp = right_ea->disp;
    copy_words((uint *)&node->desc->value,(uint *)src,3);
    (node->desc->value).disp = iVar1 - right_disp;
    if (src->labels != (label_ref *)0x0) {
      merged_labels = copy_label_ref_list(src->labels);
      (node->desc->value).labels = merged_labels;
    }
    peVar2 = &node->desc->value;
    peVar2->type = peVar2->type & 0xf8 | 8;
    fold_result = 1;
    peVar2 = &node->desc->value;
    peVar2->type = peVar2->type | 0x40;
    if ((src->disp != 0) && (right_ea->disp != 0)) {
      fold_result = 5;
    }
    break;
  case 5:
    if (src->base != right_ea->base) {
      return 0;
    }
  case 1:
    merged_labels = combine_label_ref_lists(src->labels,right_ea->labels,0);
    iVar1 = src->disp;
LAB_00419792:
    fill_ea(&node->desc->value,'\a',-1,-1,'\0',iVar1 - right_ea->disp,merged_labels);
LAB_004197b1:
    fold_result = 1;
    break;
  case 0xff:
    break;
  }
  return fold_result;
}



