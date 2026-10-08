/* GEN_MEM_INDEX (src/_memindexrules.c), compiled in with SHC_REBUILD_UPDATED=1; otherwise Release 26's. */
#ifndef MEMINDEXRULES_H
#define MEMINDEXRULES_H
#if SHC_REBUILD_UPDATED
extern int gen_mem_index_plain(gen_node *node, gen_node *left, gen_node *right);
/* fold_address_add, a memory operand and a register other than r0 under a dereference: 1 leaves the sum to the add
   template, 0 loads the memory operand into r0 for @(r0,Rn) */
#define MEM_INDEX_PLAIN(node, left, right) gen_mem_index_plain(node, left, right)
#else
#define MEM_INDEX_PLAIN(node, left, right) 0
#endif
#endif
