/* Induction-variable rules (only with SHC_REBUILD_UPDATED=1).

   MDL_IV=<bits> (unset: 3, the arcade rule; 0: Release 26).
     1  scan_derived_induction_expr: a cast that narrows an induction variable keeps the variable's number, so
        (char)(i * 6) derives from i like i * 6 does (Release 26 drops the number at any narrowing cast).
        With 2 only a cast to char, with 4 only a cast to short (both: both). */
#include "decls.h"
#include <stdlib.h>

int mdl_iv_rules(void)
{
    static int k = -1;
    if (k < 0) {
        const char *v = getenv("MDL_IV");
        k = v ? atoi(v) : 3;
    }
    return k;
}
