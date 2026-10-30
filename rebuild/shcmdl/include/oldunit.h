/* MDL_SAVED_PRIO, MDL_CONST_ENTRY and MDL_PARAM_HOME (src/_oldunit.c), compiled in with SHC_REBUILD_UPDATED=1;
   otherwise Release 26's. Three behaviours of the older compiler that built New Generation's sound driver, for a unit
   profile; unset: Release 26. */
#ifndef OLDUNIT_H
#define OLDUNIT_H
#if SHC_REBUILD_UPDATED
extern int mdl_saved_prio(void);
extern int mdl_const_entry(void);
extern int mdl_param_home(void);
#define SAVED_PRIORITY_MIN() mdl_saved_prio()
#define CONST_AT_ENTRY() mdl_const_entry()
#define UNUSED_PARAM_IN_ARG_REG() (!mdl_param_home())
#else
#define SAVED_PRIORITY_MIN() 3
#define CONST_AT_ENTRY() 0
#define UNUSED_PARAM_IN_ARG_REG() 1
#endif
#endif
