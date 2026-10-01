/* MDL_ARG_CONST (src/_argconst.c), compiled in with SHC_REBUILD_UPDATED=1; otherwise is_immediate_operand (does
   the operator take this constant as an immediate?) is called as Release 26 calls it. */
#ifndef ARGCONST_H
#define ARGCONST_H
#if SHC_REBUILD_UPDATED
extern int mdl_argconst_fit(int group, il_node *parent, int pos, unsigned int value, const_use *occ);
#define ARGCONST_FIT(group, parent, pos, value, occ) mdl_argconst_fit(group, parent, pos, value, (const_use *)(occ))
#else
#define ARGCONST_FIT(group, parent, pos, value, occ) is_immediate_operand(parent, pos, value)
#endif
#endif
