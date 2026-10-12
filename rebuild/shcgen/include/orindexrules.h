#ifndef ORINDEXRULES_H
#define ORINDEXRULES_H

#if SHC_REBUILD_UPDATED
int gen_or_index_begin(gen_node *node);
int gen_or_index_hold(psd *record, int pool_size);
void gen_or_index_end(int owner);
#define OR_INDEX_BEGIN(node) gen_or_index_begin(node)
#define OR_INDEX_HOLD(record, pool_size) gen_or_index_hold(record, pool_size)
#define OR_INDEX_END(owner) gen_or_index_end(owner)
#else
#define OR_INDEX_BEGIN(node) 0
#define OR_INDEX_HOLD(record, pool_size) 0
#define OR_INDEX_END(owner) ((void)0)
#endif

#endif
