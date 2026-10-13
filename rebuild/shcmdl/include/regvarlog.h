/* the MDL_REGVAR_LOG diagnostic (src/_regvarlog.c), compiled in with SHC_REBUILD_UPDATED=1 */
#ifndef REGVARLOG_H
#define REGVARLOG_H
#if SHC_REBUILD_UPDATED
extern void mdl_regvar_log(void);
#define REGVAR_LOG() mdl_regvar_log()
extern void mdl_regvar_presort(void);
#define REGVAR_PRESORT() mdl_regvar_presort()
#else
#define REGVAR_LOG()
#define REGVAR_PRESORT()
#endif
#endif
