#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_const_data_list
#define g_const_data_list (*(const_data * *)(g_sd + 0x16498))
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))
#undef g_func_node
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0041c6b0
// name : allocate_block_registers
// size : 1571
// sig  : void allocate_block_registers(void)


int __cdecl allocate_block_registers(void)

{
  byte bVar1;
  bblock *block;
  uint used_mask;
  uint reg_bit;
  int iVar2;
  const_data *cdata;
  const_use *use;
  lreg *lr;
  il_node *piVar3;
  il_node *assign_node;
  il_node *wrapper;
  int index;
  ushort call_flag;
  short *web_lr;
  il_node *piVar4;
  int reg_class;
  int regno;
  node_list *item;
  int next_lregno;
  short cpu;
  byte func_attr;
  bool is_arg_reg;
  il_op parent_op;
  byte ty;
  dutbl *web;
  
  func_attr = g_symtab[g_func_node->symx].attr;
  next_lregno = g_next_lregno;
  block = g_f_chain;
  do {
    if (block == (bblock *)0x0) {
      return;
    }
    sort_block_statics_by_refcnt(block);
    reg_class = 0;
    do {
      if ((reg_class == 1) &&
         (((g_options->cpu != 2 || (g_options->fpu_mode != '\x03')) && (g_options->cpu != 4))))
      break;
      if (reg_class == 0) {
        used_mask = block->usepreg;
      }
      else {
        used_mask = block->usefreg;
      }
      regno = 1;
      item = block->statics;
      while( true ) {
        iVar2 = g_float_reg_count;
        if (reg_class == 0) {
          iVar2 = g_int_reg_count;
        }
        if (iVar2 < regno) goto LAB_0041cca9;
        iVar2 = 5;
        if (reg_class != 0) {
          iVar2 = g_float_arg_reg_limit;
        }
        if ((iVar2 <= regno) && ((func_attr & 0x1c) == 0x10)) goto LAB_0041cca9;
        bVar1 = (byte)regno;
        reg_bit = 1 << ((byte)regno & 0x1f);
        if ((used_mask & reg_bit) == 0) break;
LAB_0041cca0:
        regno = regno + 1;
      }
      call_flag = block->flag & 2;
      if (call_flag != 0) {
        if (reg_class == 1) {
          is_arg_reg = true;
          if (g_float_arg_regs < regno) {
LAB_0041c7f5:
            is_arg_reg = false;
          }
        }
        else {
          is_arg_reg = true;
          if (4 < regno) goto LAB_0041c7f5;
        }
        if (is_arg_reg) goto LAB_0041cca0;
      }
      if (call_flag == 0) {
LAB_0041c83b:
        if (item != (node_list *)0x0) {
LAB_0041c848:
          web_lr = (short *)0x0;
          piVar4 = item->node;
          web = piVar4->duptr;
          if ((web != (dutbl *)0x0) && (web->links != (node_list *)0x0)) {
            if (web->kind == 1) {
              web_lr = (short *)web->links->node->val3;
            }
            else {
              web_lr = (short *)piVar4->val3;
            }
            if (((web_lr[1] == 3) && (*(short **)(web_lr + 0xc) != (short *)0x0)) &&
               (*(short **)(web_lr + 0xc) != web_lr)) {
              do {
                web_lr = *(short **)(web_lr + 0xc);
              } while (*(short **)(web_lr + 0xc) != web_lr);
            }
          }
          piVar3 = piVar4;
          if (((piVar4->op != IL_ID) && (piVar4->op != IL_CONST)) &&
             (piVar3 = piVar4->child, piVar3->op == IL_ASTER)) {
            piVar3 = piVar3->child;
          }
          if (((piVar3->lreg != 0) &&
              (((web_lr == (short *)0x0 || (web_lr[1] != 1)) || (-1 < *web_lr)))) ||
             ((piVar4 = piVar4->cmnexp, piVar4 == (il_node *)0x0 || (piVar4->refcnt < 3))))
          goto LAB_0041ca16;
          ty = piVar3->type;
          if (((((ty & 0xf0) == 0x80) || ((ty & 0xf0) == 0x90)) &&
              ((((piVar4->op == IL_ASSIGN && (piVar4->child == piVar3)) &&
                (piVar4->refchn != (il_node *)0x0)) && (piVar4->refchn->lreg != 0)))) ||
             (((piVar3->op == IL_ID &&
               (((((ty & 0xf8) == 0x48 && (-1 < piVar3->symx)) &&
                 (g_symtab[piVar3->symx].sclass != '\x02')) ||
                ((g_leaf_table[piVar3->nleaf].flag & 0x40) != 0)))) || (piVar3->op != IL_ID))))
          goto LAB_0041ca16;
          cpu = g_options->cpu;
          if (((cpu == 2) && (g_options->fpu_mode == '\x03')) || (cpu == 4)) {
            if (((reg_class != 0) || ((ty & 0xe0) == 0)) || ((ty & 0xf8) == 0x40)) {
              if (((ty & 0xf8) == 0x30) && (cpu == 4)) {
                if (reg_class != 1) goto LAB_0041c9f2;
                if ((used_mask & 1 << ((byte)regno + 1 & 0x1f)) != 0) goto LAB_0041ca16;
              }
              if ((reg_class != 1) ||
                 (((((ty & 0xf8) == 0x28 || (cpu != 2)) || (g_options->fpu_mode != '\x03')) &&
                  (((ty & 0xe0) == 0x20 || (cpu != 4)))))) goto LAB_0041c9f2;
            }
            goto LAB_0041ca16;
          }
          if (((ty & 0xe0) != 0) && (((ty & 0xf8) != 0x40 && ((ty & 0xf8) != 0x28))))
          goto LAB_0041ca16;
LAB_0041c9f2:
          piVar4 = piVar4->cmnexp;
          if (piVar4 != (il_node *)0x0) {
            do {
              if ((piVar4->op == IL_NULL) || (iVar2 = in_conditional_operator(piVar4), iVar2 != 0))
              break;
              piVar4 = piVar4->refchn;
            } while (piVar4 != (il_node *)0x0);
            if (piVar4 != (il_node *)0x0) goto LAB_0041ca16;
          }
          cdata = regalloc_alloc(0x1c);
          cdata->next = g_const_data_list;
          g_const_data_list = cdata;
          use = regalloc_alloc(0x14);
          cdata->uses = use;
          use->block = block;
          cdata->uses->node = item->node;
          lr = new_register_candidate(cdata,0);
          g_lreg_count = g_lreg_count + 1;
          g_lreg_table[g_lreg_count] = lr;
          piVar4 = item->node;
          if ((piVar4->op != IL_ID) && (piVar4->op != IL_CONST)) {
            piVar3 = piVar4->refchn;
            while (piVar3 != (il_node *)0x0) {
              piVar4 = piVar4->refchn;
              piVar3 = piVar4->refchn;
            }
          }
          lr->pregno = (short)regno;
          lr->lregno = (short)next_lregno;
          if (((g_options->cpu == 2) && (g_options->fpu_mode == '\x03')) || (g_options->cpu == 4)) {
            if (reg_class == 0) {
              block->usepreg = block->usepreg | reg_bit;
            }
            else {
              reg_bit = block->usefreg | reg_bit;
              block->usefreg = reg_bit;
              if ((g_options->cpu == 4) && ((piVar4->type & 0xf8) == 0x30)) {
                block->usefreg = 1 << (bVar1 + 1 & 0x1f) | reg_bit;
              }
            }
          }
          else {
            block->usepreg = block->usepreg | reg_bit;
          }
          if (piVar4->op == IL_CONST) {
            *(undefined2 *)lr->chain = 0;
          }
          else {
            *(undefined2 *)lr->chain = 8;
          }
          iVar2 = new_temporary_leaf();
          piVar3 = alloc_node();
          assign_node = alloc_node();
          bVar1 = piVar4->type;
          if ((((bVar1 & 0xf0) == 0x80) || ((bVar1 & 0xf0) == 0x90)) || ((bVar1 & 0xf8) == 0x48)) {
            assign_node->type = '@';
          }
          else {
            assign_node->type = bVar1;
          }
          assign_node->op = IL_ASSIGN;
          piVar3->type = assign_node->type;
          piVar3->nleaf = (short)iVar2;
          piVar3->symx = g_temp_symx;
          piVar3->op = IL_ID;
          piVar3->lreg = (short)next_lregno;
          lr->priori = next_lregno;
          insert_parent(piVar4,assign_node);
          insert_operands(assign_node,piVar3,1);
          if (piVar4->op == IL_CONST) {
            assign_node->type = '\x10';
            piVar3->type = '\x10';
            wrapper = alloc_node();
            wrapper->op = IL_CAST;
            wrapper->type = piVar4->type;
            piVar4->type = '\x10';
            insert_parent(assign_node,wrapper);
          }
          if ((((piVar4->op == IL_ID) && ((piVar4->type & 0xf8) == 0x48)) && (-1 < piVar4->symx)) &&
             ((g_symtab[piVar4->symx].sclass == '\x02' && (assign_node->parent->op == IL_CALL)))) {
            wrapper = alloc_node();
            wrapper->type = piVar4->type;
            wrapper->op = IL_ASTER;
            assign_node->type = '@';
            piVar3->type = '@';
            insert_parent(assign_node,wrapper);
          }
          for (piVar3 = piVar4->cmnexp; piVar3 != (il_node *)0x0; piVar3 = piVar3->refchn) {
            if (((piVar3->op == IL_ID) || (piVar3->op == IL_CONST)) &&
               ((piVar3 != piVar4 &&
                ((index = operand_index(piVar3), index != 1 ||
                 ((parent_op = piVar3->parent->op, (parent_op & IL_NON_F0) != IL_A_ADD &&
                  ((parent_op & IL_NON_F8) != IL_PRI)))))))) {
              replace_with_register_temp(piVar3,(short)iVar2,lr);
            }
          }
          next_lregno = next_lregno + 1;
          item->node = assign_node;
LAB_0041cc99:
          if (item == (node_list *)0x0) goto LAB_0041cca9;
          goto LAB_0041cca0;
        }
        goto LAB_0041cca9;
      }
      if (reg_class == 1) {
        is_arg_reg = true;
        if (regno <= g_float_arg_regs) {
LAB_0041c82a:
          is_arg_reg = false;
        }
      }
      else {
        is_arg_reg = true;
        if (regno < 5) goto LAB_0041c82a;
      }
      if ((!is_arg_reg) || ((func_attr & 8) == 0)) goto LAB_0041c83b;
LAB_0041cca9:
      reg_class = reg_class + 1;
    } while (reg_class < 2);
    block = block->f_next;
  } while( true );
LAB_0041ca16:
  item = item->next;
  if (item == (node_list *)0x0) goto LAB_0041cc99;
  goto LAB_0041c848;
}



