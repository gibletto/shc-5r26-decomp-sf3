/* MDL_GCSE (src/_gcserules.c), compiled in with SHC_REBUILD_UPDATED=1; otherwise Release 26's global
   common-expression elimination. */
#ifndef GCSERULES_H
#define GCSERULES_H
#if SHC_REBUILD_UPDATED
extern int mdl_gcse_block_ok(il_node *node, bblock *block);
extern void mdl_gcse_reinsert(il_node *rest, il_node *head);
#define GCSE_BLOCK_OK(node, block) mdl_gcse_block_ok(node, block)
extern void mdl_gcse_split(il_node *head);
#define GCSE_REINSERT(rest, head) mdl_gcse_reinsert(rest, head)
#define GCSE_SPLIT(head) mdl_gcse_split(head)
#else
#define GCSE_BLOCK_OK(node, block) 1
#define GCSE_REINSERT(rest, head) cse_reinsert_class(rest)
#define GCSE_SPLIT(head) cse_reinsert_class(head)
#endif
#endif
