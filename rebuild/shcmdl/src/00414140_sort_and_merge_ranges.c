#include "decls.h"
#include "imports.h"

// entry: 00414140
// name : sort_and_merge_ranges
// size : 220
// sig  : void sort_and_merge_ranges(void * ranges, int mode)


int __cdecl sort_and_merge_ranges(void *ranges,int mode)

{
  undefined4 *next_range;
  int *cur;
  int *next;
  bool swapped;
  int tmp;
  
  do {
    swapped = false;
    next = ranges;
    while (cur = next, cur != (int *)0x0) {
      tmp = cur[1];
      if (cur[2] < tmp) {
        cur[1] = cur[2];
        cur[2] = tmp;
      }
      next = (int *)*cur;
      if (next != (int *)0x0) {
        tmp = cur[1];
        if ((next[1] < tmp) || (next[2] < tmp)) {
          swapped = true;
          cur[1] = next[1];
          *(int *)(*cur + 4) = tmp;
          tmp = cur[2];
          cur[2] = *(int *)(*cur + 8);
          *(int *)(*cur + 8) = tmp;
          next = cur;
        }
      }
    }
  } while (swapped);
  next_range = *(undefined4 **)ranges;
  if ((*(int *)((int)ranges + 4) == 0) && (mode == 1)) {
    do {
      *(undefined4 *)((int)ranges + 4) = next_range[1];
      *(undefined4 *)((int)ranges + 8) = next_range[2];
      *(undefined4 *)ranges = *next_range;
      pool_free(next_range,0xc);
      next_range = *(undefined4 **)ranges;
    } while (*(int *)((int)ranges + 4) == 0);
  }
  while (next_range != (undefined4 *)0x0) {
    tmp = *(int *)((int)ranges + 8);
    if ((tmp < (int)next_range[1]) && ((mode != 1 || (tmp - next_range[1] != -1)))) {
      ranges = *(void **)ranges;
    }
    else {
      if (tmp < (int)next_range[2]) {
        *(int *)((int)ranges + 8) = next_range[2];
      }
      *(undefined4 *)ranges = *next_range;
      pool_free(next_range,0xc);
    }
    next_range = *(undefined4 **)ranges;
  }
  return;
}



