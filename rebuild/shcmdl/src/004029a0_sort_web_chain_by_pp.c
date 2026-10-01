#include "decls.h"
#include "imports.h"

// entry: 004029a0
// name : sort_web_chain_by_pp
// size : 173
// sig  : void sort_web_chain_by_pp(lreg * reg)


int __cdecl sort_web_chain_by_pp(lreg *reg)

{
  int iVar1;
  void *du;
  void *pos;
  void *next_du;
  int pp;
  void *prev_item;
  bool swapped;
  
  du = reg->chain;
  next_du = *(void **)((int)du + 8);
  do {
    prev_item = (void *)0x0;
    swapped = false;
    while (next_du != (void *)0x0) {
      pp = (int)*(short *)(*(int *)((int)du + 0x10) + 0x44);
      pos = du;
      if ((int)(uint)*(ushort *)(*(int *)((int)next_du + 0x10) + 0x44) < pp) {
        iVar1 = *(int *)((int)next_du + 8);
        swapped = true;
        pos = next_du;
        while ((iVar1 != 0 &&
               ((int)(uint)*(ushort *)(*(int *)(*(int *)((int)pos + 8) + 0x10) + 0x44) <= pp))) {
          pos = *(void **)((int)pos + 8);
          iVar1 = *(int *)((int)pos + 8);
        }
        if (prev_item == (void *)0x0) {
          reg->chain = next_du;
        }
        else {
          *(void **)((int)prev_item + 8) = next_du;
        }
        *(undefined4 *)((int)du + 8) = *(undefined4 *)((int)pos + 8);
        *(void **)((int)pos + 8) = du;
        pos = next_du;
      }
      du = *(void **)((int)pos + 8);
      prev_item = pos;
      next_du = *(void **)((int)du + 8);
    }
    du = reg->chain;
    next_du = *(void **)((int)du + 8);
  } while (swapped);
  return;
}



