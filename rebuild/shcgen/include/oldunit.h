/* GEN_AND_TEST and GEN_LAST_KEEP (src/_oldunit.c), compiled in with SHC_REBUILD_UPDATED=1; otherwise Release 26's.
   Two behaviours of the older compiler that built New Generation's sound driver, for a unit profile; unset or 0:
   Release 26. */
#ifndef OLDUNIT_H
#define OLDUNIT_H
#if SHC_REBUILD_UPDATED
extern int gen_and_test(void);
extern int gen_last_keep(void);
#define AND_TEST_FUSES() (!gen_and_test())
#define RELEASE_KEEPS_LAST() gen_last_keep()
#else
#define AND_TEST_FUSES() 1
#define RELEASE_KEEPS_LAST() 0
#endif
#endif
