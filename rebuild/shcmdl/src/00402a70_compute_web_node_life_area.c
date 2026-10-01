#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_lreg
#define g_current_lreg (*(lreg * *)(g_sd + 0x1e4c4))


// entry: 00402a70
// name : compute_web_node_life_area
// size : 657
// sig  : void compute_web_node_life_area(dutbl * chain_node)


int __cdecl compute_web_node_life_area(dutbl *chain_node)

{
  unsigned char _frec_84[132];
#define leafno (*(int *)(_frec_84 + 0))
#define used_in (*(uint (*)[16])(_frec_84 + 4))
#define used_out (*(uint (*)[16])(_frec_84 + 68))
  uchar any;
  ushort end_pp;
  node_list *link;
  undefined3 extraout_var = 0;
  il_node *latest;
  undefined4 *area_entry;
  undefined3 extraout_var_00 = 0;
  ushort start_pp;
  bool live_across;
  uint *live_out;
  il_node *node;
  block_list *succ;
  
  live_across = false;
  link = chain_node->links;
  if (link == (node_list *)0x0) {
    g_first_chain_node = '\0';
    node = chain_node->node;
    start_pp = node->pp;
    end_pp = node->flag;
    while ((end_pp & 0x200) == 0) {
      node = node->parent;
      end_pp = node->flag;
    }
    end_pp = node->pp;
    goto LAB_00402c58;
  }
  if (chain_node->kind == 2) {
    g_first_chain_node = '\0';
    node = chain_node->node;
    start_pp = node->pp;
    leafno = (int)node->child->nleaf;
    link = chain_node->links;
    if (link != (node_list *)0x0) {
      do {
        if (link->node->duptr->block != chain_node->block) break;
        link = link->next;
      } while (link != (node_list *)0x0);
      if (link != (node_list *)0x0) {
        live_across = true;
        end_pp = chain_node->block->endpp;
        goto LAB_00402c58;
      }
    }
    node = node->cmnexp;
    latest = node->refchn;
joined_r0x00402b91:
    if (latest != (il_node *)0x0) {
LAB_00402c4f:
      node = latest;
    }
  }
  else {
    leafno = (int)chain_node->node->nleaf;
    if (link == (node_list *)0x0) {
LAB_00402b45:
      if (g_first_chain_node != '\x01') {
        node = chain_node->node->cmnexp;
        start_pp = node->pp;
        link = node->duptr->links;
        if (link != (node_list *)0x0) {
          do {
            if (link->node->duptr->block != chain_node->block) break;
            link = link->next;
          } while (link != (node_list *)0x0);
          if (link != (node_list *)0x0) {
            end_pp = chain_node->block->endpp;
            live_across = true;
            goto LAB_00402c58;
          }
        }
        latest = node->refchn;
        goto joined_r0x00402b91;
      }
    }
    else {
      do {
        if (link->node->duptr->block != chain_node->block) break;
        link = link->next;
      } while (link != (node_list *)0x0);
      if (link == (node_list *)0x0) goto LAB_00402b45;
    }
    g_first_chain_node = '\0';
    start_pp = chain_node->block->startpp;
    clear_bytes((char *)used_in,0x40);
    bitset_and(used_in,g_leaf_table[chain_node->node->nleaf].use,chain_node->block->l_in,'\x10');
    clear_bytes((char *)used_out,0x40);
    live_out = chain_node->block->out;
    if (live_out == (uint *)0x0) {
      latest = chain_node->node->refchn;
      if (latest == (il_node *)0x0) {
        latest = chain_node->node;
      }
      goto LAB_00402c4f;
    }
    bitset_and(used_out,used_in,live_out,'\x10');
    any = any_bit_set(used_out,0x10);
    if (CONCAT31(extraout_var,any) != 0) {
      end_pp = chain_node->block->endpp;
      live_across = true;
      goto LAB_00402c58;
    }
    node = chain_node->node->refchn;
    if (node == (il_node *)0x0) {
      node = chain_node->node;
    }
  }
  end_pp = statement_pp(node);
LAB_00402c58:
  area_entry = make_life_area_entry(start_pp,end_pp);
  *area_entry = g_current_lreg->life;
  g_current_lreg->life = area_entry;
  if (live_across) {
    for (succ = chain_node->block->suclst; succ != (block_list *)0x0; succ = succ->next) {
      if (((succ->block->l_in != (uint *)0x0) && (g_leaf_table[leafno].use != (uint *)0x0)) &&
         ((succ->block->flag & 0x10U) == 0)) {
        clear_bytes((char *)used_in,0x40);
        bitset_and(used_in,succ->block->l_in,g_leaf_table[leafno].use,'\x10');
        any = any_bit_set(used_in,0x10);
        if (CONCAT31(extraout_var_00,any) != 0) {
          add_block_to_life_area(succ->block);
        }
      }
    }
  }
  return;
#undef leafno
#undef used_in
#undef used_out
}



