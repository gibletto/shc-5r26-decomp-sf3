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

/* MDL_CAST_CSE and MDL_ARG_CAST (src/_castrules.c), with SHC_REBUILD_UPDATED=1 */
#if SHC_REBUILD_UPDATED
extern int mdl_cast_operand_rank(il_node *operand);
extern int mdl_cast_address_leaf(il_node *node);
extern il_node *mdl_arg_as_variable(il_node *arg);
#define CAST_OPERAND_RANK(n) mdl_cast_operand_rank(n)
#define CAST_ADDRESS_LEAF(n) mdl_cast_address_leaf(n)
#define ARG_AS_VARIABLE(a) mdl_arg_as_variable(a)
#else
#define CAST_OPERAND_RANK(n) node_type_rank(n)
#define CAST_ADDRESS_LEAF(n) 0
#define ARG_AS_VARIABLE(a) (a)
#endif

/* MDL_IV, MDL_IV_BASE and MDL_IV_TEMP (src/_ivrules.c), with SHC_REBUILD_UPDATED=1 */
#if SHC_REBUILD_UPDATED
extern int mdl_iv_rules(void);
extern int mdl_iv_licm_pass(int pass, int bit);
#define IV_RULES() mdl_iv_rules()
#define IV_LICM_PASS(bit) mdl_iv_licm_pass(g_licm_pass, bit)
extern int mdl_iv_reuse_temp(il_node *assign);
#define IV_REUSE_TEMP(a) mdl_iv_reuse_temp(a)
extern int mdl_iv_skip_use(il_node *expr);
#define IV_SKIP_USE(e) mdl_iv_skip_use(e)
#else
#define IV_RULES() 0
#define IV_LICM_PASS(bit) g_licm_pass
#define IV_REUSE_TEMP(a) 1
#define IV_SKIP_USE(e) 0
#endif

/* MDL_LOOP_INV and MDL_LOOP_LOG (src/_looprules.c), with SHC_REBUILD_UPDATED=1: does this place of
   select_loops_to_invert see -speed */
#if SHC_REBUILD_UPDATED
extern void mdl_loop_log(loop *lp);
extern int mdl_loop_speed(loop *lp, int speed, int bit);
extern void mdl_loop_inverted(loop *lp);
#define LOOP_LOG(lp) mdl_loop_log(lp)
#define LOOP_SPEED(bit) mdl_loop_speed(lp, g_options->unknown_20 != 0, bit)
#define LOOP_INVERT(lp) (mdl_loop_inverted(lp), invert_loop_to_guarded_do(lp))
#else
#define LOOP_LOG(lp)
#define LOOP_SPEED(bit) (g_options->unknown_20 != 0)
#define LOOP_INVERT(lp) invert_loop_to_guarded_do(lp)
#endif
#endif
