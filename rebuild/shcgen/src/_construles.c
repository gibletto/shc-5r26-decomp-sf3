/* GEN_NARROW_CONST (unset: 1, the arcade rule; 0: Release 26).

   prepare_constant_node keeps the right constant of an ADD/SUB immediate when
   the left operand is already a register. For a full-width or address result,
   fold_address_add_sub can then form a displacement and choose indexed reuse.
   That pass excludes byte and short results, independently of signedness.
   Allow its ordinary live-constant reuse path for those narrow integer results.

   The cache still requires the complete value and relocation labels to agree;
   no low-bit comparison, special literal, register or function is involved.
   Template-immediate exclusions and the labelled-left-operand veto stay intact.
   Across all 460 game modules, four narrowed short sums use the live constant
   in the arcade and no narrowed site opposes reuse. A current-source whole-ROM
   blanket-bypass diagnostic enabled 88 additional veto sites: no byte gains,
   13 byte-exact losses, 24 more code bytes and no non-code changes. All 62
   indexed control sites kept their routine words; their later reuse did not
   establish opposition to early reuse. The narrow rule changes only those
   four sums: three become exact,
   the fourth improves, with no losses, growth or non-code changes. Byte and
   unsigned-short policy is unobserved in the arcade; native fixtures cover both.
*/
#if SHC_REBUILD_UPDATED
#include <stdlib.h>

int gen_narrow_const(unsigned char type)
{
    static int enabled = -1;
    unsigned char kind = type & 0xf8;
    if (enabled < 0) {
        const char *v = getenv("GEN_NARROW_CONST");
        enabled = (v && *v) ? (atoi(v) != 0) : 1;
    }
    return enabled && (kind == 0 || kind == 8);
}
#endif
