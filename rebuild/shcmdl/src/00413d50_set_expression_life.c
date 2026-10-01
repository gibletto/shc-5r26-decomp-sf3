#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))


// entry: 00413d50
// name : set_expression_life
// size : 724
// sig  : void set_expression_life(void)


int __cdecl set_expression_life(void)

{
  lreg *lr;
  undefined4 *puVar1;
  undefined4 *area;
  il_node *expr;
  ushort end_side;
  int pp;
  bblock *blk;
  undefined4 *prev_area;
  undefined4 *local_8;
  lreg **slot;
  int *cell;
  node_list *item;
  node_list *next_item;
  il_node *stmt;
  
  local_8 = (undefined4 *)0x0;
  slot = g_lreg_table + 1;
  do {
    lr = *slot;
    if (lr == (lreg *)0x0) {
      return;
    }
    if ((lr->set == 0) && (*(short *)lr->chain == 8)) {
      prev_area = regalloc_alloc(0xc);
      lr->exp_area = prev_area;
      prev_area[1] = (uint)*(ushort *)
                            (**(int **)(*(int *)(*(int *)((int)lr->chain + 8) + 4) + 4) + 0x54);
      cell = *(int **)(*(int *)(*(int *)((int)lr->chain + 8) + 4) + 4);
      pp = cell[1];
      while (pp != 0) {
        cell = (int *)cell[1];
        pp = cell[1];
      }
      prev_area[2] = (uint)*(ushort *)(*cell + 0x54);
    }
    else if ((lr->set != 3) &&
            ((puVar1 = lr->life, puVar1 != (undefined4 *)0x0 && (lr->pregno != 0)))) {
      for (; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
        if (lr->exp_area == (void *)0x0) {
          area = regalloc_alloc(0xc);
          lr->exp_area = area;
        }
        else {
          area = regalloc_alloc(0xc);
          *prev_area = area;
        }
        area[1] = (uint)*(ushort *)(puVar1[1] + 8);
        area[2] = (uint)*(ushort *)(puVar1[1] + 10);
        prev_area = area;
      }
      sort_and_merge_ranges(lr->exp_area,0);
      if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 2) != 0) {
        dump_lreg(-1,lr,s_setexlife_1_00435584);
      }
      prev_area = (undefined4 *)0x0;
      puVar1 = lr->exp_area;
      blk = g_f_chain;
      while (puVar1 != (undefined4 *)0x0) {
        end_side = 0;
        pp = puVar1[1];
        area = puVar1;
LAB_00413eaf:
        for (; end_side < 2; end_side = end_side + 1) {
          puVar1 = local_8;
          if (blk == (bblock *)0x0) goto LAB_00413f81;
          do {
            if (pp < (int)(uint)blk->startpp) {
              blk = blk->b_next;
            }
            else {
              if (pp <= (int)(uint)blk->endpp) {
                next_item = blk->ilnode;
                goto joined_r0x00413eea;
              }
              blk = blk->f_next;
            }
          } while (blk != (bblock *)0x0);
        }
        prev_area = area;
        puVar1 = (undefined4 *)*area;
      }
      if (local_8 != (undefined4 *)0x0) {
        lr->exp_area = (void *)*local_8;
        pool_free(local_8,0xc);
        local_8 = (undefined4 *)0x0;
      }
      if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 2) != 0) {
        dump_lreg(-1,lr,s_setexlife_2_00435578);
      }
      sort_and_merge_ranges(lr->exp_area,1);
      prev_area = (undefined4 *)0x0;
      if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 2) != 0) {
        dump_lreg(-1,lr,s_setexlife_3_0043556c);
      }
    }
    slot = slot + 1;
    if ((lreg **)SD(0x00448260) < slot) {
      return;
    }
  } while( true );
  while (((int)(uint)item->node->pp < pp && (next_item = item->next, item->next != (node_list *)0x0)
         )) {
joined_r0x00413eea:
    item = next_item;
    if (item == (node_list *)0x0) goto LAB_00413f4c;
  }
  stmt = item->node;
  if ((stmt->expp == 0) && ((stmt->op != IL_NULL && (expr = stmt, stmt != (il_node *)0x0)))) {
    do {
      if (expr->expp != 0) break;
      expr = expr->parent;
    } while (expr != (il_node *)0x0);
    if (expr != (il_node *)0x0) goto LAB_00413f30;
  }
  expr = stmt;
LAB_00413f30:
  if (end_side == 0) {
    area[1] = (uint)expr->expp;
    pp = area[2];
  }
  else {
    area[2] = (uint)expr->expp;
  }
LAB_00413f4c:
  if (((blk->ilnode == (node_list *)0x0) && (end_side == 1)) &&
     (puVar1 = area, prev_area != (undefined4 *)0x0)) {
    end_side = 2;
    *prev_area = *area;
    pool_free(area,0xc);
    area = prev_area;
  }
  else {
LAB_00413f81:
    local_8 = puVar1;
    end_side = end_side + 1;
  }
  goto LAB_00413eaf;
}



