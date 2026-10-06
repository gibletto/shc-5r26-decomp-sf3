/* GEN_POOL_MOVLOC (src/_poolrules.c), compiled in with SHC_REBUILD_UPDATED=1; otherwise Release 26's. */
#ifndef POOLRULES_H
#define POOLRULES_H
#if SHC_REBUILD_UPDATED
extern int gen_pool_record_size(psd *rec, int size);
/* decide_literal_pool_placement: the bytes a record adds to the pool window */
#define POOL_RECORD_SIZE(rec, size) gen_pool_record_size(rec, size)
#else
#define POOL_RECORD_SIZE(rec, size) (size)
#endif
#endif
