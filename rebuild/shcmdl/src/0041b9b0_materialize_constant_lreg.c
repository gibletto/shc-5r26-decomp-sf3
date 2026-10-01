#include "decls.h"
#include "imports.h"
#include "argconst.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))
#undef g_func_node
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))


// entry: 0041b9b0
// name : materialize_constant_lreg
// size : 1028
// sig  : void materialize_constant_lreg(int index, short lregno)


int __cdecl materialize_constant_lreg(int index,short lregno)

{
  lreg *lr;
  int iVar1;
  byte kind;
  char not_cond;
  int leafno;
  il_node *piVar2;
  il_node *piVar3;
  il_node *node;
  node_list *item;
  int iVar4;
  undefined3 extraout_var = 0;
  il_node *zero_const;
  undefined4 *puVar5;
  char *src_node;
  uint value;
  void *chain;
  ushort flag;
  byte *flag_byte;
  int *link;
  il_op op;
  
  lr = g_lreg_table[index];
  leafno = new_temporary_leaf();
  piVar2 = alloc_node();
  piVar3 = alloc_node();
  piVar2->op = IL_ID;
  piVar2->type = '\x10';
  piVar2->nleaf = (short)leafno;
  piVar2->symx = g_temp_symx;
  piVar2->lreg = lregno;
  if ((*(short *)lr->chain == 4) || (*(short *)lr->chain == 1)) {
    piVar3->op = IL_ID;
    src_node = *(char **)(*(int *)((int)lr->chain + 8) + 8);
    if (*src_node != 'p') {
      src_node = *(char **)(src_node + 0x14);
    }
    piVar3->type = src_node[3];
    piVar3->nleaf = *(short *)(src_node + 0x58);
    piVar3->symx = *(short *)(src_node + 4);
    node = make_node(IL_ASSIGN,'\x18',piVar2,piVar3,(il_node *)0x0);
    if (*(short *)lr->chain == 4) {
      piVar2 = alloc_node();
      piVar2->op = IL_AMPER;
      piVar2->type = '@';
      insert_parent(piVar3,piVar2);
    }
    if ((*(short *)lr->chain == 1) && ((kind = piVar3->type & 0xf0, kind == 0x60 || (kind == 0x70)))
       ) {
      piVar2 = alloc_node();
      piVar2->op = IL_AMPER;
      piVar2->type = '@';
      insert_parent(piVar3,piVar2);
    }
  }
  else {
    piVar3->op = IL_CONST;
    piVar3->type = '\x10';
    piVar3->val = *(int *)((int)lr->chain + 4);
    node = make_node(IL_ASSIGN,'\x10',piVar2,piVar3,(il_node *)0x0);
    if ((*(byte *)(*(int *)(*(int *)((int)lr->chain + 8) + 8) + 3) & 0xf8) == 0x28) {
      node->type = '(';
      piVar3->type = '(';
      piVar2->type = '(';
    }
    if ((*(byte *)(*(int *)(*(int *)((int)lr->chain + 8) + 8) + 3) & 0xf8) == 0x30) {
      node->type = '0';
      piVar3->type = '0';
      piVar2->type = '0';
    }
  }
  chain = lr->chain;
  if (*(short *)((int)chain + 2) == 0) {
    item = regalloc_alloc(8);
    item->node = node;
    item->next = g_f_chain->ilnode;
    g_f_chain->ilnode = item;
    if (item->next == (node_list *)0x0) {
      insert_operands(g_func_node->child,node,1);
    }
    else {
      iVar4 = operand_index(item->next->node);
      insert_operands(item->next->node->parent,node,iVar4);
    }
  }
  else {
    piVar2 = *(il_node **)((int)chain + 0x18);
    if (piVar2 == (il_node *)0x0) {
      puVar5 = *(undefined4 **)(*(int *)((int)chain + 0x14) + 4);
      if (puVar5 == (undefined4 *)0x0) {
        puVar5 = regalloc_alloc(8);
        *puVar5 = node;
        puVar5[1] = *(undefined4 *)(*(int *)((int)lr->chain + 0x14) + 4);
        *(undefined4 **)(*(int *)((int)lr->chain + 0x14) + 4) = puVar5;
        if ((undefined4 *)puVar5[1] == (undefined4 *)0x0) {
          iVar4 = **(int **)(*(int *)((int)lr->chain + 0x14) + 0xc);
          iVar1 = *(int *)(iVar4 + 0x30);
          if (iVar1 == 0) {
            piVar2 = (il_node *)**(int **)(iVar4 + 4);
            op = piVar2->op;
            while (((op != IL_FOR && (piVar2->op != IL_WHILE)) && (piVar2->op != IL_DO))) {
              piVar2 = piVar2->parent;
              op = piVar2->op;
            }
          }
          else {
            piVar2 = *(il_node **)(iVar1 + 8);
          }
          if (piVar2->parent->op != IL_BLOCK) {
            wrap_in_block_pair(piVar2);
          }
          insert_before(piVar2,node);
        }
        else {
          iVar4 = operand_index(*(il_node **)puVar5[1]);
          insert_operands(*(il_node **)(*(int *)puVar5[1] + 0x10),node,iVar4);
        }
        flag_byte = (byte *)((int)&node->flag + 1);
        *flag_byte = *flag_byte | 2;
      }
      else {
        piVar2 = (il_node *)*puVar5;
        piVar3 = copy_tree(1,piVar2);
        piVar3->op = IL_COMMA;
        insert_parent(piVar2,piVar3);
        insert_before(piVar2,node);
        *puVar5 = piVar3;
        flag_byte = (byte *)((int)&piVar3->flag + 1);
        *flag_byte = *flag_byte | 2;
        flag_byte = (byte *)((int)&piVar2->flag + 1);
        *flag_byte = *flag_byte & 0xfd;
      }
    }
    else {
      flag = piVar2->flag;
      while ((flag & 0x200) == 0) {
        piVar2 = piVar2->parent;
        flag = piVar2->flag;
      }
      link = *(int **)(*(int *)((int)chain + 0x14) + 4);
      piVar3 = (il_node *)*link;
      while (piVar3 != piVar2) {
        link = (int *)link[1];
        piVar3 = (il_node *)*link;
      }
      piVar3 = copy_tree(1,piVar2);
      piVar3->op = IL_COMMA;
      not_cond = is_not_control_condition(piVar2);
      if ((CONCAT31(extraout_var,not_cond) == 0) && (piVar2->op == IL_NULL)) {
        piVar2->op = IL_NOT;
        piVar2->type = '\x10';
        piVar3->type = '\x10';
        zero_const = new_const_node('\x10',0);
        insert_operands(piVar2,zero_const,1);
      }
      insert_parent(piVar2,piVar3);
      insert_before(piVar2,node);
      *link = (int)piVar3;
      flag_byte = (byte *)((int)&piVar3->flag + 1);
      *flag_byte = *flag_byte | 2;
      flag_byte = (byte *)((int)&piVar2->flag + 1);
      *flag_byte = *flag_byte & 0xfd;
    }
  }
  puVar5 = *(undefined4 **)((int)lr->chain + 8);
  do {
    if (puVar5 == (undefined4 *)0x0) {
      return;
    }
    for (piVar2 = (il_node *)puVar5[2]; piVar2 != (il_node *)0x0; piVar2 = piVar2->refchn) {
      if (piVar2->op == IL_CONST) {
        value = piVar2->val;
        iVar4 = operand_index(piVar2);
        iVar4 = ARGCONST_FIT(2,piVar2->parent,iVar4,value,puVar5);
        if ((iVar4 == 0) &&
           ((piVar2->op != IL_CONST ||
            ((((piVar2->parent == (il_node *)0x0 || (iVar4 = operand_index(piVar2), iVar4 != 2)) ||
              ((op = piVar2->parent->op, op != IL_SL &&
               (((op != IL_SR && (op != IL_A_SL)) && (op != IL_A_SR)))))) &&
             (((piVar2->op != IL_CONST || (piVar2->parent == (il_node *)0x0)) ||
              ((iVar4 = operand_index(piVar2), iVar4 != 2 ||
               ((piVar2->parent->op != IL_ASSIGN || (piVar2->parent->child->op != IL_B_QUALIFY))))))
             )))))) goto LAB_0041bd87;
      }
      else {
LAB_0041bd87:
        replace_with_register_temp(piVar2,(short)leafno,lr);
      }
    }
    puVar5 = (undefined4 *)*puVar5;
  } while( true );
}



