/* the MDL_REGVAR_LOG diagnostic (src/_regvarlog.c), compiled in with SHC_REBUILD_UPDATED=1 */
#ifndef REGVARLOG_H
#define REGVARLOG_H
#if SHC_REBUILD_UPDATED
extern void mdl_regvar_log(void);
#define REGVAR_LOG() mdl_regvar_log()
#else
#define REGVAR_LOG()
#endif
#endif
