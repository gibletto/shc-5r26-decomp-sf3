#ifndef ORLEFTKEEP_H
#define ORLEFTKEEP_H

#if SHC_REBUILD_UPDATED
int gen_or_left_keep(gen_node *node);
#define OR_LEFT_KEEP(node) gen_or_left_keep(node)
#else
#define OR_LEFT_KEEP(node) 0
#endif

#endif
