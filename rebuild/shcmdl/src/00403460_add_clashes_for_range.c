#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))


// entry: 00403460
// name : add_clashes_for_range
// size : 191
// sig  : void add_clashes_for_range(void * lreg_link, lifetbl * range)


int __cdecl add_clashes_for_range(void *lreg_link,lifetbl *range)

{
  bblock *block;
  ushort pp;
  ushort block_end;
  undefined4 *other;
  lifetbl *other_range;
  
  for (other = *(undefined4 **)lreg_link; other != (undefined4 *)0x0; other = (undefined4 *)*other)
  {
    add_lreg_clash(lreg_link,other);
  }
  for (other_range = range->next; other_range != (lifetbl *)0x0; other_range = other_range->next) {
    for (other = other_range->lregs; other != (undefined4 *)0x0; other = (undefined4 *)*other) {
      add_lreg_clash(lreg_link,other);
    }
  }
  pp = range->st + 1;
  if (pp <= range->en) {
    do {
      if ((range->en == pp) && (*(int *)(*(int *)((int)lreg_link + 4) + 0x18) == 0)) {
        block_end = g_f_chain->endpp;
        block = g_f_chain;
        if (block_end < pp) {
          do {
            block = block->f_next;
          } while (block->endpp < pp);
          block_end = block->endpp;
        }
        if (block_end != pp) {
          return;
        }
      }
      for (other_range = g_lifehash_buckets[pp]; other_range != (lifetbl *)0x0;
          other_range = other_range->next) {
        for (other = other_range->lregs; other != (undefined4 *)0x0; other = (undefined4 *)*other) {
          add_lreg_clash(lreg_link,other);
        }
      }
      pp = pp + 1;
    } while (pp <= range->en);
  }
  return;
}



