/* Unit-profile rules of the older compiler that built New Generation's sound driver (only with
   SHC_REBUILD_UPDATED=1; unset: Release 26).
   MDL_SAVED_PRIO=<n> (unset or 0: 3, Release 26): the least priority a variable web needs for a callee-saved register
     (r8-r14) in assign_physical_registers; the older compiler gives one to a web of priority 2.
   MDL_CONST_ENTRY=1: a constant or address that becomes a register candidate is loaded once at the function's
     entry, not at the block that dominates its uses (choose_const_dominator keeps the entry block). */
#if SHC_REBUILD_UPDATED
#include <stdlib.h>
#include "decls.h"
#include "oldunit.h"
static int env_int(const char *name, int dflt, int *cache)
{
    if (*cache == -99) {
        const char *v = getenv(name);
        *cache = (v && *v) ? (int)strtol(v, 0, 0) : dflt;
    }
    return *cache;
}
int mdl_saved_prio(void)
{
    static int k = -99;
    int v = env_int("MDL_SAVED_PRIO", 3, &k);
    return v > 0 ? v : 3;
}
int mdl_const_entry(void)
{
    static int k = -99;
    return env_int("MDL_CONST_ENTRY", 0, &k) & 1;
}
#endif
