/* The arcade rules and the pass diagnostics of shcpep (src/_pep_rules.c; tools/shcpep-fixes.py puts the calls into
   the generated functions). Without SHC_REBUILD_UPDATED every hook is the plain Release 26 code. */
#ifndef PEP_RULES_H
#define PEP_RULES_H

#if SHC_REBUILD_UPDATED
/* PEP_SKIP / PEP_POST_SKIP=<mask>: leave out pass k of run_node_optimization_passes / optimize_current_node_list */
int pep_skip(int k);
int pep_post_skip(int k);
#define PEPPASS(k, call) do { if (!pep_skip(k)) call; } while (0)
#define PEPPOST(k, call) do { if (!pep_post_skip(k)) call; pep_dump(#call, g_current_node_list); } while (0)

/* SWITCH_ARCADE_BRANCH / SWITCH_ARCADE_JUMP */
int keep_branch_over_jump(int *block);
int keep_jump_to_next(int *block);

/* PEP_R0_FORGET */
int pep_r0_forget(void);
int pep_block_is_conditional(int block);
int pep_keep_target_head(int pred, unsigned char *head);

/* PEP_NO_THREAD */
int pep_no_thread(void);
int pep_no_thread_here(int *blk, int *dest);
void pep_xj_labels_clear(void);
void pep_xj_label_mark(short l);

/* XJUMP_OFF / XJUMP_MIN / XJUMP_LOG */
extern char xjump_tail[];
int xjump_reject(char kind, int mode, int count);
/* in merge_common_block_tails: a rejected match's mode becomes 0 (no merge) */
#define XJUMP_FILTER(mode, kind)   ((mode) != 0 && xjump_reject((char)(kind), (mode), g_common_tail_count) ? ((mode) = 0) : 0)
void xjump_tail_add(unsigned char *rec);
#define XJ_TAIL(rec) xjump_tail_add(rec)
/* the XJUMP_LOG fields jt= (the jump temporaries of the two blocks' final records) and pv= (the record in front
   of the tail in each block) */
extern int xjump_jt_a, xjump_jt_b;
#define XJ_JT(a, b) (xjump_jt_a = (a), xjump_jt_b = (b))
void xjump_prev(void *ba, void *ta, void *bb, void *tb);
#define XJ_PREV(ba, ta, bb, tb) xjump_prev(ba, ta, bb, tb)

/* PEP_RET_R0 */
int pep_ret_r0(void);
#define PEP_RET_TMP(t) ((char)((pep_ret_r0() & 1) ? 0 : (t)))
/* two RETURNs: the shared tail leaves r0 alone whatever temporary the earlier one carries */
#define PEP_RET_PAIR(a, b, t) (((pep_ret_r0() & 1) && (a)->op == OP_RETURN && (b)->op == OP_RETURN) ? ((t) = 0) : 0)

/* the exit block after merged returns (bit 4) */
int pep_exit_kept(void *flow_block);
#define PEP_EXIT_KEPT(b) pep_exit_kept(b)
/* the reference of a deleted unreachable block (bit 8) */
int pep_dead_ref_kept(short labno);
#define PEP_DEAD_REF_KEPT(l) pep_dead_ref_kept(l)

/* diagnostics (src/_pep_dump.c): PEP_DUMP, the function name and the TAIL/NEXT lines of XJUMP_LOG */
void pep_dump(const char *tag, void *list);
const char *pep_current_function(void);
int pep_xj_label_was_made(short l);
void pep_log_tail(int op);
void pep_log_xj_next(int *blk, int op);

/* PEP_AUTOINC */
int pep_autoinc(void);

/* SLOT_NO_STACK */
int slot_no_stack(void);
int slot_record_is_frame_access(unsigned char *rec);
#else
#define PEPPASS(k, call) call
#define PEPPOST(k, call) call
#define pep_post_skip(k) 0
#define keep_branch_over_jump(block) 0
#define keep_jump_to_next(block) 0
#define pep_keep_target_head(pred, head) 0
#define pep_no_thread() 0
#define pep_no_thread_here(blk, dest) 0
#define XJ_TAIL(rec) ((void)0)
#define XJ_JT(a, b) ((void)0)
#define XJ_PREV(ba, ta, bb, tb) ((void)0)
#define PEP_RET_TMP(t) (t)
#define PEP_RET_PAIR(a, b, t) 0
#define PEP_EXIT_KEPT(b) 0
#define PEP_DEAD_REF_KEPT(l) 0
#define XJUMP_FILTER(mode, kind) 0
#define pep_autoinc() 0
#endif

#endif
