/* Unit-profile rules of the older compiler that built New Generation's sound driver (only with
   SHC_REBUILD_UPDATED=1; unset or 0: Release 26).
   GEN_AND_TEST=1: a bit-and whose value is only tested (if (x & m)) is computed into a register and that register is
     tested (and Rm,Rn / tst Rn,Rn); Release 26 marks the and for the test template, tst Rm,Rn.
   GEN_LAST_KEEP=1: releasing a node's registers leaves the chooser's last-chosen register as it is, so the next
     choice still passes over the register chosen last; Release 26 forgets it there. */
#if SHC_REBUILD_UPDATED
#include <stdlib.h>
#include "decls.h"
#include "oldunit.h"
static int env_int(const char *name, int *cache)
{
    if (*cache < 0) {
        const char *v = getenv(name);
        *cache = (v && *v) ? (int)strtol(v, 0, 0) : 0;
    }
    return *cache;
}
int gen_and_test(void)
{
    static int k = -1;
    return env_int("GEN_AND_TEST", &k) & 1;
}
int gen_last_keep(void)
{
    static int k = -1;
    return env_int("GEN_LAST_KEEP", &k) & 1;
}
#endif
