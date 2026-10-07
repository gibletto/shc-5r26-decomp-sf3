/* GEN_RELOAD (src/_reloadrules.c), compiled in with SHC_REBUILD_UPDATED=1; otherwise Release 26's. */
#ifndef RELOADRULES_H
#define RELOADRULES_H
#if SHC_REBUILD_UPDATED
extern int gen_reload_last_use(gen_node *node);
/* find_register_holding_variable: the reference ends its logical register's life, so no register copy is looked up */
#define RELOAD_LAST_USE(node) gen_reload_last_use(node)
#else
#define RELOAD_LAST_USE(node) 0
#endif
#endif
