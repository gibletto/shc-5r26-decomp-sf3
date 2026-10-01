#include "decls.h"
#include "imports.h"

// entry: 00403410
// name : build_lreg_clash_lists
// size : 76
// sig  : void build_lreg_clash_lists(void)


int __cdecl build_lreg_clash_lists(void)

{
  lifetbl *range;
  undefined4 *lreg_link;
  uint pp;
  
  pp = 1;
  if (1 < g_pp_count) {
    do {
      for (range = g_lifehash_buckets[pp]; range != (lifetbl *)0x0; range = range->next) {
        for (lreg_link = range->lregs; lreg_link != (undefined4 *)0x0;
            lreg_link = (undefined4 *)*lreg_link) {
          add_clashes_for_range(lreg_link,range);
        }
      }
      pp = (uint)(ushort)((short)pp + 1);
    } while ((int)pp < g_pp_count);
  }
  return;
}



