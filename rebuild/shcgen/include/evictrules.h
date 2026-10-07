/* GEN_EVICT_ORDER (src/_evictrules.c), compiled in with SHC_REBUILD_UPDATED=1; otherwise Release 26's. */
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
#else
#define EVICT_BEFORE_INVALIDATE(bit) 0
#define EVICT_LOG(kind, contents, reg)
#endif
#endif
