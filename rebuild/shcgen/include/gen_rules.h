/* Normalize an owned narrow compound result in its home before comparison. */
#ifndef GEN_RULES_H
#define GEN_RULES_H
#if SHC_REBUILD_UPDATED
extern int gen_narrow_normalize_mode(void);
extern void gen_narrow_normalize(gen_node *node);
#define NARROW_NORMALIZE(node) gen_narrow_normalize(node)
extern int gen_store_index_late(gen_node *node, gen_node *left, gen_node *right, gen_node *assign);
#define STORE_INDEX_LATE(node, left, right, assign) gen_store_index_late(node, left, right, assign)
extern int gen_store_rhs_index(gen_node *node, gen_node *assign);
#define STORE_RHS_INDEX(node, assign) gen_store_rhs_index(node, assign)
extern void gen_store_index_trace(gen_node *node, gen_node *left, gen_node *right, int lc, int rc, int kind);
#define STORE_INDEX_TRACE(n, l, r, lc, rc, k) gen_store_index_trace(n, l, r, lc, rc, k)
extern int gen_cond_pref_mode(void);
#define COND_TEST_NO_PREF(node) ((gen_cond_pref_mode() & 2) != 0)
extern int gen_assign_no_cond_handover(gen_node *right);
#define ASSIGN_NO_COND_HANDOVER(right) gen_assign_no_cond_handover(right)
#else
#define NARROW_NORMALIZE(node) ((void)0)
#define STORE_INDEX_LATE(node, left, right, assign) 0
#define STORE_RHS_INDEX(node, assign) 0
#define STORE_INDEX_TRACE(n, l, r, lc, rc, k) ((void)0)
#define COND_TEST_NO_PREF(node) 0
#define ASSIGN_NO_COND_HANDOVER(right) 0
#endif
#endif
