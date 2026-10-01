#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_builtin_names
#define g_builtin_names (*(unsigned char * *)(g_sd + 0x22d0))


// entry: 004073f0
// name : is_builtin_name
// size : 86
// sig  : int is_builtin_name(char * name)


int __cdecl is_builtin_name(char *name)

{
  byte *p;
  int cmp;
  byte *q;
  undefined **name_ptr;
  bool below;
  byte c;
  
  if (g_builtin_names != (undefined *)0x0) {
    name_ptr = &g_builtin_names;
    do {
      p = *name_ptr;
      q = (byte *)name;
      do {
        c = *p;
        below = c < *q;
        if (c != *q) {
LAB_00407428:
          cmp = (1 - (uint)below) - (uint)(below != 0);
          goto LAB_0040742d;
        }
        if (c == 0) break;
        c = p[1];
        below = c < q[1];
        if (c != q[1]) goto LAB_00407428;
        p = p + 2;
        q = q + 2;
      } while (c != 0);
      cmp = 0;
LAB_0040742d:
      if (cmp == 0) {
        return 1;
      }
      name_ptr = name_ptr + 1;
    } while (*name_ptr != (undefined *)0x0);
  }
  return 0;
}



