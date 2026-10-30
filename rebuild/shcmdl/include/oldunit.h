/* MDL_SAVED_PRIO and MDL_CONST_ENTRY (src/_oldunit.c), compiled in with SHC_REBUILD_UPDATED=1; otherwise Release
   26's. Two behaviours of the older compiler that built New Generation's sound driver, for a unit profile; unset:
   Release 26. */
#ifndef OLDUNIT_H
#define OLDUNIT_H
#if SHC_REBUILD_UPDATED
extern int mdl_saved_prio(void);
extern int mdl_const_entry(void);
#define SAVED_PRIORITY_MIN() mdl_saved_prio()
#define CONST_AT_ENTRY() mdl_const_entry()
#else
#define SAVED_PRIORITY_MIN() 3
#define CONST_AT_ENTRY() 0
#endif
#endif
