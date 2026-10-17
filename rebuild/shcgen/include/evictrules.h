/* GEN_EVICT_ORDER and GEN_RIGHT_FIRST_DROP (src/_evictrules.c), compiled in with SHC_REBUILD_UPDATED=1; otherwise
   Release 26's. */
#ifndef EVICTRULES_H
#define EVICTRULES_H
#if SHC_REBUILD_UPDATED
extern int gen_evict_order(void);
/* record_variable_in_register (bit 1) / record_constant_in_register (bit 2): does the oldest other content go
   before the register's own old content is dropped? */
#define EVICT_BEFORE_INVALIDATE(bit) ((gen_evict_order() & (bit)) != 0)
/* GEN_EVICT_LOG: the records at each place where the two orders can differ */
extern void gen_evict_log(int kind, reg_content *contents, int reg, gen_node *node);
#define EVICT_LOG(kind, contents, reg) gen_evict_log(kind, contents, reg, node)
/* GEN_RIGHT_FIRST_DROP: when an operator's right operand goes first, the notes of the registers the left operand
   will overwrite are forgotten after the operator's template, not when the order is decided */
extern int gen_right_first_drop(void);
extern unsigned short g_right_first_pending;
extern char g_right_first_in_operator;
#define RIGHT_FIRST_IN_OPERATOR(on) (g_right_first_in_operator = (char)(on))
#define RIGHT_FIRST_DEFER() (g_right_first_in_operator && gen_right_first_drop())
#define RIGHT_FIRST_PEND(mask) (g_right_first_pending |= (unsigned short)(mask))
#define RIGHT_FIRST_DROP_PENDING()   do { if (g_right_first_pending) { invalidate_register_contents(g_right_first_pending); g_right_first_pending = 0; } } while (0)
#else
#define EVICT_BEFORE_INVALIDATE(bit) 0
#define RIGHT_FIRST_IN_OPERATOR(on) ((void)0)
#define RIGHT_FIRST_DEFER() 0
#define RIGHT_FIRST_PEND(mask) ((void)0)
#define RIGHT_FIRST_DROP_PENDING() ((void)0)
#define EVICT_LOG(kind, contents, reg)
#endif
#endif
