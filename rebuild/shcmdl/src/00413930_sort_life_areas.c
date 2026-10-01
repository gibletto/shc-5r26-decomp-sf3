#include "decls.h"
#include "imports.h"

// entry: 00413930
// name : sort_life_areas
// size : 206
// sig  : void sort_life_areas(lreg * lr)


int __cdecl sort_life_areas(lreg *lr)

{
  int *pred2;
  int *prev2;
  int *cur2;
  int *group_pred;
  int *after;
  undefined4 *cur;
  int *group;
  undefined4 *next;
  undefined4 *pred;
  undefined4 *prev;
  bool swapped;
  
  do {
    swapped = false;
    pred = (undefined4 *)0x0;
    next = lr->life;
    prev = lr->life;
    while (cur = next, cur != (undefined4 *)0x0) {
      if (*(ushort *)(cur[1] + 8) < *(ushort *)(prev[1] + 8)) {
        swapped = true;
        if (lr->life == prev) {
          lr->life = cur;
        }
        else {
          *pred = cur;
        }
        *prev = *cur;
        *cur = prev;
      }
      pred = prev;
      prev = cur;
      next = (undefined4 *)*cur;
    }
  } while (swapped);
  group_pred = (int *)0x0;
  group = lr->life;
  do {
    if (group == (int *)0x0) {
      return;
    }
    do {
      cur2 = (int *)*group;
      swapped = false;
      pred2 = group_pred;
      prev2 = group;
      if (cur2 == (int *)0x0) break;
      do {
        if (*(short *)(group[1] + 8) != *(short *)(cur2[1] + 8)) break;
        if (*(ushort *)(cur2[1] + 10) < *(ushort *)(prev2[1] + 10)) {
          swapped = true;
          if (lr->life == prev2) {
            lr->life = cur2;
          }
          else {
            *pred2 = (int)cur2;
          }
          *prev2 = *cur2;
          *cur2 = (int)prev2;
        }
        after = (int *)*cur2;
        pred2 = prev2;
        prev2 = cur2;
        cur2 = after;
      } while (after != (int *)0x0);
    } while (swapped);
    group = (int *)*prev2;
    group_pred = prev2;
  } while( true );
}



