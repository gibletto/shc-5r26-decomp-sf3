/* MDL_CAST_MUL (src/_castmulrules.c), compiled in with SHC_REBUILD_UPDATED=1; otherwise Release 26's global
   common-expression elimination. */
#ifndef CASTMUL_H
#define CASTMUL_H
#if SHC_REBUILD_UPDATED
extern void mdl_castmul_begin(void);
extern void mdl_castmul_visit(il_node *node);
extern int mdl_castmul_ok(il_node *node, bblock *block);
#define CASTMUL_BEGIN() mdl_castmul_begin()
#define CASTMUL_VISIT(node) mdl_castmul_visit(node)
#define CASTMUL_OK(node, block) mdl_castmul_ok(node, block)
#else
#define CASTMUL_BEGIN() ((void)0)
#define CASTMUL_VISIT(node) ((void)0)
#define CASTMUL_OK(node, block) 1
#endif
#endif
