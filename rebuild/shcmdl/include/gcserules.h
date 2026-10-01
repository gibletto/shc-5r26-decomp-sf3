/* MDL_GCSE (src/_gcserules.c), compiled in with SHC_REBUILD_UPDATED=1; otherwise Release 26's global
   common-expression elimination. */
#ifndef GCSERULES_H
#define GCSERULES_H
#if SHC_REBUILD_UPDATED
extern int mdl_gcse_block_ok(il_node *node, bblock *block);
extern void mdl_gcse_reinsert(il_node *rest);
#define GCSE_BLOCK_OK(node, block) mdl_gcse_block_ok(node, block)
#define GCSE_REINSERT(rest) mdl_gcse_reinsert(rest)
#else
#define GCSE_BLOCK_OK(node, block) 1
#define GCSE_REINSERT(rest) cse_reinsert_class(rest)
#endif
#endif
