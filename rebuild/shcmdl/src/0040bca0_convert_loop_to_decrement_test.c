#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))
#undef g_dt_loop
#define g_dt_loop (*(loop * *)(g_sd + 0x26844))
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))
#undef g_loop_tree
#define g_loop_tree (*(loop * *)(g_sd + 0x267f0))


// entry: 0040bca0
// name : convert_loop_to_decrement_test
// size : 629
// sig  : void convert_loop_to_decrement_test(il_node * cond)


int __cdecl convert_loop_to_decrement_test(il_node *cond)

{
  unsigned char _frec_8[8];
#define local_8 (*(il_node * *)(_frec_8 + 0))
  il_node *var;
  int opno;
  node_list *link;
  il_node *def1;
  bblock *block;
  short blkno;
  il_node *def;
  dutbl *du;
  bool have_init;
  bool have_step;
  il_node *init;
  il_op op;
  
  if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 0x20) != 0) {
    FID_conflict__wprintf(s_dt_opt_start_00434fe4);
    dump_loop_table(g_loop_tree);
    dump_loop_tree_titled(g_dt_loop,s_dt_opt_start_00434fd4);
    dump_block_table(g_f_chain,s_dt_opt_start_00434fd4);
  }
  have_step = false;
  have_init = false;
  var = cond->child;
  if ((((var != (il_node *)0x0) && (var->cmnexp != (il_node *)0x0)) &&
      (du = var->cmnexp->duptr, du != (dutbl *)0x0)) && ((1 < du->count && (du->count < 3)))) {
    def1 = local_8;
    init = local_8;
    for (link = du->links; link != (node_list *)0x0; link = link->next) {
      def = link->node;
      blkno = def->duptr->block->number;
      if (blkno < g_dt_loop->start->number) {
        if (blkno < g_dt_loop->pre->number) {
          return;
        }
        if (have_init) {
          g_dt_loop->flag = g_dt_loop->flag | 0x100;
          break;
        }
        have_init = true;
        local_8 = def;
      }
      else {
        local_8 = init;
        if ((blkno <= g_dt_loop->exit->number) && ((def->flag & 0x1000) == 0)) {
          if (have_step) {
            g_dt_loop->flag = g_dt_loop->flag | 0x100;
            break;
          }
          have_step = true;
          op = def->parent->op;
          init = def;
          while ((op == IL_COMMA && (opno = operand_index(init), opno == 2))) {
            init = init->parent;
            op = init->parent->op;
          }
          def1 = def;
          if (init->parent->op == IL_BLOCK) {
            *(byte *)&def->flag2 = (byte)def->flag2 | 2;
          }
        }
      }
      init = local_8;
    }
    block = g_dt_loop->pre;
    if (g_dt_loop->exit->number < block->number) {
      (*(unsigned char *)((char *)&local_8 + 0)) = (char)init;
    }
    else {
      do {
        (*(unsigned char *)((char *)&local_8 + 0)) = block_has_no_other_var_ref(block,def1,init,var);
        if ((char)local_8 == '\0') {
          return;
        }
        block = block->f_next;
      } while (block->number <= g_dt_loop->exit->number);
    }
    if ((def1->flag2 & 2) == 0) {
      return;
    }
    link = def1->cmnexp->duptr->links;
    if (link != (node_list *)0x0) {
      do {
        blkno = link->node->duptr->block->number;
        if ((g_dt_loop->exit->number < blkno) || (blkno < g_dt_loop->start->number)) {
          if ((g_dt_loop->flag & 0x10) != 0) {
            (*(unsigned char *)((char *)&local_8 + 0)) = '\0';
            break;
          }
          (*(unsigned char *)((char *)&local_8 + 0)) = '\x02';
        }
        link = link->next;
      } while (link != (node_list *)0x0);
    }
    if (def1->op == IL_ASSIGN) {
      (*(unsigned char *)((char *)&local_8 + 0)) = '\0';
    }
    if ((char)local_8 != '\0') {
      rewrite_loop_count_down(cond,def1,init,(char)local_8);
    }
  }
  if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 0x20) != 0) {
    FID_conflict__wprintf(s_dt_opt_end_00434fc8);
    dump_loop_table(g_loop_tree);
    dump_loop_tree_titled(g_dt_loop,s_dt_opt_end_00434fbc);
    dump_block_table(g_f_chain,s_dt_opt_end_00434fbc);
  }
  return;
#undef local_8
}



