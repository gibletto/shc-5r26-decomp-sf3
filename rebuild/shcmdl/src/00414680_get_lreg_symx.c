#include "decls.h"
#include "imports.h"

// entry: 00414680
// name : get_lreg_symx
// size : 139
// sig  : short get_lreg_symx(lreg * lr)


short __cdecl get_lreg_symx(lreg *lr)

{
  short sVar1;
  char *node_p;
  short set;
  
  sVar1 = -1;
  set = lr->set;
  if ((set == 1) || (set == 3)) {
    node_p = *(char **)((int)lr->chain + 0x10);
    if (*node_p == 'p') {
      return *(short *)(node_p + 4);
    }
    node_p = *(char **)(node_p + 0x14);
    if (node_p == (char *)0x0) {
      return -1;
    }
    if (*node_p == 'p') {
      return *(short *)(node_p + 4);
    }
    sVar1 = *(short *)(*(int *)(node_p + 0x14) + 4);
  }
  else if ((set == 2) || ((set == 0 && (*(short *)lr->chain != 8)))) {
    node_p = *(char **)(*(int *)((int)lr->chain + 8) + 8);
    if (*node_p == 'p') {
      return *(short *)(node_p + 4);
    }
    node_p = *(char **)(node_p + 0x14);
    if (node_p == (char *)0x0) {
      return -1;
    }
    if (*node_p == 'p') {
      return *(short *)(node_p + 4);
    }
    return *(short *)(*(int *)(node_p + 0x14) + 4);
  }
  return sVar1;
}



