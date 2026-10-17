/* Standard GEN settings; unset selects the arcade rule, explicit0 restores R26. */
#if SHC_REBUILD_UPDATED
#include <stdlib.h>
#include "decls.h"
#include "gen_rules.h"
static int env_int(const char *name,int dflt)
{
    char *value=getenv(name);
    return value ? (int)strtol(value,0,0) : dflt;
}
int gen_narrow_normalize_mode(void)
{
    return env_int("GEN_NARROW_NORMALIZE",1);
}
#endif
