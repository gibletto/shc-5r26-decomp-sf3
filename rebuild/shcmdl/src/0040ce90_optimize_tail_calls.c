#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_bn_chain
#define g_bn_chain (*(bblock * *)(g_sd + 0x26ef8))
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))
#undef g_exit_block
#define g_exit_block (*(bblock * *)(g_sd + 0x267cc))
#undef g_func_node
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0040ce90
// name : optimize_tail_calls
// size : 738
// sig  : void optimize_tail_calls(void)


int __cdecl optimize_tail_calls(void)

{
  bblock *block;
  char cVar1;
  byte ptype;
  undefined3 extraout_var = 0;
  il_node *arg;
  int n;
  char cVar2;
  int i;
  uchar *flagp;
  char *s1;
  node_list **link;
  char *s2;
  bool bVar3;
  node_list *item;
  node_list *last;
  bool leaves_ok;
  node_list *next_item;
  block_list *next_pred;
  bool no_setjmp;
  il_op op;
  bool params_simple;
  block_list *pred;
  ushort symno;
  
  i = 1;
  leaves_ok = true;
  no_setjmp = true;
  if (0 < g_leaf_count) {
    flagp = &g_leaf_table[1].flag;
    do {
      if (((*(ushort *)flagp & 1) == 0) && ((*(ushort *)flagp & 0xc) != 0)) {
        leaves_ok = false;
        break;
      }
      symno = *(ushort *)(flagp + -2);
      if ((-1 < (short)symno) && ((g_symtab[(short)symno].type & 0xf8) == 0x48)) {
        n = 7;
        bVar3 = true;
        s1 = g_symtab[(short)symno].name;
        s2 = &g_str_setjmp;
        do {
          if (n == 0) break;
          n = n + -1;
          bVar3 = *s1 == *s2;
          s1 = s1 + 1;
          s2 = s2 + 1;
        } while (bVar3);
        if (bVar3) {
          no_setjmp = false;
          break;
        }
      }
      flagp = flagp + 0x10;
      i = i + 1;
    } while (i <= g_leaf_count);
  }
  i = 1;
  bVar3 = true;
  if (0 < g_leaf_count) {
    flagp = &g_leaf_table[1].flag;
    do {
      if (((((*flagp & 1) == 0) && (-1 < *(short *)(flagp + -2))) &&
          (g_symtab[*(short *)(flagp + -2)].sclass != '\t')) &&
         (0x5f < (g_symtab[*(short *)(flagp + -2)].type & 0xe0))) {
        bVar3 = false;
        break;
      }
      flagp = flagp + 0x10;
      i = i + 1;
    } while (i <= g_leaf_count);
  }
  params_simple = true;
  cVar1 = *(char *)((int)g_symtab[g_func_node->symx].info + 6);
  do {
    cVar2 = cVar1 + -1;
    if (cVar1 == '\0') goto LAB_0040cfd7;
    ptype = g_symtab[*(short *)(*(int *)((int)g_symtab[g_func_node->symx].info + 0xc) + cVar2 * 2)].
            type;
    cVar1 = cVar2;
  } while ((((ptype & 0xe0) == 0) || (((ptype & 0xe0) == 0x20 && ((ptype & 0x18) == 8)))) ||
          ((ptype & 0xf8) == 0x40));
  params_simple = false;
LAB_0040cfd7:
  pred = g_exit_block->prelst;
  do {
    while( true ) {
      do {
        do {
          do {
            if (pred == (block_list *)0x0) {
              if (((*(unsigned char *)((char *)&g_debug_flags + 2)) & 4) != 0) {
                dump_tree(g_func_node,0,s_after_esp_optimize_00435298);
                dump_cfg_blocks();
              }
              return;
            }
            next_pred = pred->next;
            block = pred->block;
            pred = next_pred;
          } while (block->b_next == (bblock *)0x0);
          link = &block->ilnode;
        } while (*link == (node_list *)0x0);
        for (last = (*link)->next; last != (node_list *)0x0; last = last->next->next) {
          last = *link;
          link = &last->next;
        }
        last = *link;
      } while (((last->node->op != IL_CALL) || (!leaves_ok)) ||
              ((!no_setjmp ||
               (cVar1 = is_not_control_condition(last->node), CONCAT31(extraout_var,cVar1) == 0))));
      if (params_simple) break;
LAB_0040d111:
      if ((bVar3) && ((g_symtab[g_func_node->symx].attr & 0x10) == 0)) {
        flagp = &last->node->call_flags;
        *flagp = *flagp | 4;
      }
    }
    arg = last->node->child;
    if (arg->symx != g_func_node->symx) goto LAB_0040d111;
    arg = arg->next->child;
    cVar1 = *(char *)((int)g_symtab[g_func_node->symx].info + 6);
    op = arg->op;
    while (op != IL_E_ARG) {
      ptype = arg->type & 0xe0;
      if (((ptype != 0) && (ptype != 0x20)) && ((arg->type & 0xf8) != 0x40)) {
        cVar1 = -1;
        break;
      }
      arg = arg->next;
      cVar1 = cVar1 + -1;
      op = arg->op;
    }
    if (cVar1 == '\0') {
      item = g_bn_chain->ilnode;
      if (item == (node_list *)0x0) {
        arg = g_func_node->child->child;
      }
      else {
        next_item = item->next;
        while (next_item != (node_list *)0x0) {
          item = item->next;
          next_item = item->next;
        }
        arg = item->node->next;
      }
      if ((arg->op != IL_GLABEL) || (arg->symx != -1)) {
        insert_entry_label(arg);
      }
      convert_self_tail_call_to_jump(block,last,link);
    }
  } while( true );
}



