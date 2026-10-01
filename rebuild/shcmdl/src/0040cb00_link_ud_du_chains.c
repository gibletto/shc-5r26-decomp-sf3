#include "decls.h"
#include "imports.h"

// entry: 0040cb00
// name : link_ud_du_chains
// size : 439
// sig  : void link_ud_du_chains(bblock * block, il_node * node)


int __cdecl link_ud_du_chains(bblock *block,il_node *node)

{
  unsigned char _frec_2c[44];
#define word_p (*(uint * *)(_frec_2c + 0))
#define reach (*(uint (*)[8])(_frec_2c + 12))
  byte kind;
  node_list *link;
  uint *in_p;
  uint *dst;
  uint *dst_next;
  uint *gen_p;
  int bit;
  il_node **def;
  uint bits;
  short def_count;
  il_node *sub;
  byte ty;
  
  for (sub = node->child; sub != (il_node *)0x0; sub = sub->next) {
    link_ud_du_chains(block,sub);
  }
  if (node->op == IL_ID) {
    ty = node->type;
    kind = ty & 0xf0;
    if ((((((kind != 0x80) && (kind != 0x90)) && ((ty & 0xf8) != 0x48)) &&
         (((ty & 2) == 0 && (kind != 0x60)))) &&
        ((kind != 0x70 && ((node == node->cmnexp && (node->cmnexp->duptr != (dutbl *)0x0)))))) &&
       (gen_p = g_leaf_table[node->nleaf].gen, gen_p != (uint *)0x0)) {
      in_p = block->d_in;
      dst = reach;
      do {
        bits = *gen_p;
        gen_p = gen_p + 1;
        dst_next = dst + 1;
        *dst = bits & *in_p;
        in_p = in_p + 1;
        dst = dst_next;
      } while (dst_next < (void *)(_frec_2c + 0x2c));
      word_p = reach;
      def = g_def_nodes;
      def_count = 1;
      do {
        bit = 0;
        bits = *word_p;
        do {
          if ((bits & 1 << (0x1fU - (char)bit & 0x1f)) != 0) {
            link = pool_alloc(8);
            if (link == (node_list *)0x0) {
              abort_function_optimization();
            }
            link->next = node->cmnexp->duptr->links;
            node->cmnexp->duptr->links = link;
            node->cmnexp->duptr->links->node = *def;
            node->cmnexp->duptr->kind = 1;
            node->cmnexp->duptr->count = def_count;
            link = pool_alloc(8);
            if (link == (node_list *)0x0) {
              abort_function_optimization();
            }
            link->next = (*def)->cmnexp->duptr->links;
            (*def)->cmnexp->duptr->links = link;
            (*def)->cmnexp->duptr->links->node = node;
            (*def)->cmnexp->duptr->kind = 2;
            def_count = def_count + 1;
          }
          def = def + 1;
          bit = bit + 1;
        } while (bit < 0x20);
        word_p = word_p + 1;
      } while (word_p < (void *)(_frec_2c + 0x2c));
    }
  }
  return;
#undef word_p
#undef reach
}



