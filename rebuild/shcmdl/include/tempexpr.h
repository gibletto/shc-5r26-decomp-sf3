/* MDL_TEMP_EXPR (src/_tempexprrules.c), compiled in with SHC_REBUILD_UPDATED=1; otherwise Release 26's global
   common-expression elimination. */
#ifndef TEMPEXPR_H
#define TEMPEXPR_H
#if SHC_REBUILD_UPDATED
extern int mdl_temp_expr_skip(il_node *node);
#define TEMP_EXPR_SKIP(node) mdl_temp_expr_skip(node)
extern int mdl_temp_expr_ok(il_node *node, bblock *block);
#define TEMP_EXPR_OK(node, block) mdl_temp_expr_ok(node, block)
#else
#define TEMP_EXPR_SKIP(node) 1
#define TEMP_EXPR_OK(node, block) 1
#endif
#endif
