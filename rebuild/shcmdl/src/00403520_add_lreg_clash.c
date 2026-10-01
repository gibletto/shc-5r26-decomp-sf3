#include "decls.h"
#include "imports.h"

// entry: 00403520
// name : add_lreg_clash
// size : 101
// sig  : void add_lreg_clash(void * link_a, void * link_b)


int __cdecl add_lreg_clash(void *link_a,void *link_b)

{
  undefined4 *clash;
  
  if (*(int *)((int)link_b + 4) != *(int *)((int)link_a + 4)) {
    for (clash = *(undefined4 **)(*(int *)((int)link_a + 4) + 0x10); clash != (undefined4 *)0x0;
        clash = (undefined4 *)*clash) {
      if (clash[1] == *(int *)((int)link_b + 4)) {
        return;
      }
    }
    clash = regalloc_alloc(8);
    clash[1] = *(undefined4 *)((int)link_b + 4);
    *clash = *(undefined4 *)(*(int *)((int)link_a + 4) + 0x10);
    *(undefined4 **)(*(int *)((int)link_a + 4) + 0x10) = clash;
    clash = regalloc_alloc(8);
    clash[1] = *(undefined4 *)((int)link_a + 4);
    *clash = *(undefined4 *)(*(int *)((int)link_b + 4) + 0x10);
    *(undefined4 **)(*(int *)((int)link_b + 4) + 0x10) = clash;
  }
  return;
}



