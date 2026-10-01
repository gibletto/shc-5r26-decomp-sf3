#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_lreg
#define g_current_lreg (*(lreg * *)(g_sd + 0x1e4c4))


// entry: 00402de0
// name : make_life_area_entry
// size : 136
// sig  : void * make_life_area_entry(ushort start_pp, short end_pp)


int * __cdecl make_life_area_entry(ushort start_pp,short end_pp)

{
  void *area_entry;
  lifetbl *range;
  undefined4 *lreg_cell;
  lifetbl **bucket;
  
  area_entry = regalloc_alloc(8);
  bucket = g_lifehash_buckets + start_pp;
  range = *bucket;
  do {
    if (range == (lifetbl *)0x0) {
LAB_00402e21:
      if (range == (lifetbl *)0x0) {
        range = regalloc_alloc(0xc);
        range->next = *bucket;
        *bucket = range;
        range->st = start_pp;
        range->en = end_pp;
        *(lifetbl **)((int)area_entry + 4) = range;
      }
      lreg_cell = regalloc_alloc(8);
      *lreg_cell = *(undefined4 *)(*(int *)((int)area_entry + 4) + 4);
      *(undefined4 **)(*(int *)((int)area_entry + 4) + 4) = lreg_cell;
      lreg_cell[1] = g_current_lreg;
      return area_entry;
    }
    if ((range->st == start_pp) && (range->en == end_pp)) {
      *(lifetbl **)((int)area_entry + 4) = range;
      goto LAB_00402e21;
    }
    range = range->next;
  } while( true );
}



