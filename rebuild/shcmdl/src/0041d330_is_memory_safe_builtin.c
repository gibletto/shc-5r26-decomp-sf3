#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_memory_safe_builtins
#define g_memory_safe_builtins (*(unsigned char * *)(g_sd + 0x3bb0))


// entry: 0041d330
// name : is_memory_safe_builtin
// size : 86
// sig  : int is_memory_safe_builtin(char * name)


int __cdecl is_memory_safe_builtin(char *name)

{
  byte *p;
  int cmp;
  byte *q;
  undefined **slot;
  bool less;
  byte c;
  
  if (g_memory_safe_builtins != (undefined *)0x0) {
    slot = &g_memory_safe_builtins;
    do {
      p = *slot;
      q = (byte *)name;
      do {
        c = *p;
        less = c < *q;
        if (c != *q) {
LAB_0041d368:
          cmp = (1 - (uint)less) - (uint)(less != 0);
          goto LAB_0041d36d;
        }
        if (c == 0) break;
        c = p[1];
        less = c < q[1];
        if (c != q[1]) goto LAB_0041d368;
        p = p + 2;
        q = q + 2;
      } while (c != 0);
      cmp = 0;
LAB_0041d36d:
      if (cmp == 0) {
        return 1;
      }
      slot = slot + 1;
    } while (*slot != (undefined *)0x0);
  }
  return 0;
}



