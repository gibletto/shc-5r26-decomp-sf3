/* GEN_MEM_INDEX (src/_memindexrules.c), compiled in with SHC_REBUILD_UPDATED=1; otherwise Release 26's. */
#ifndef MEMINDEXRULES_H
#define MEMINDEXRULES_H
#if SHC_REBUILD_UPDATED
extern int gen_mem_index_plain(gen_node *node, gen_node *left, gen_node *right, int other);
/* fold_address_add, a memory operand beside an operand of class `other` (7 a register other than r0, 6 r0, 1 an
   address constant, 8 memory too) under a dereference: 1 leaves the sum to the add template, 0 keeps Release 26's
   indexed access */
#define MEM_INDEX_PLAIN(node, left, right, other) gen_mem_index_plain(node, left, right, other)
#else
#define MEM_INDEX_PLAIN(node, left, right, other) 0
#endif
#endif
