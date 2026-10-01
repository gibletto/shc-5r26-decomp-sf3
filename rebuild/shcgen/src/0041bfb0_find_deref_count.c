#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_deref_count_cursor
#define g_deref_count_cursor (*(deref_count * *)(g_sd + 0x1fa18))


// entry: 0041bfb0
// name : find_deref_count
// size : 70
// sig  : deref_count * find_deref_count(short symx, ushort lreg)


deref_count * __cdecl find_deref_count(short symx,ushort lreg)

{
  deref_count *entry;
  bool found;
  
  found = false;
  entry = (deref_count *)&g_deref_counts;
  do {
    if (g_deref_count_cursor <= entry) {
LAB_0041bfec:
      if (!found) {
        entry = (deref_count *)0x0;
      }
      return entry;
    }
    if ((entry->symx == symx) &&
       (entry->lreg == (ushort)((lreg ^ (short)lreg >> 0xf) - ((short)lreg >> 0xf)))) {
      found = true;
      goto LAB_0041bfec;
    }
    entry = entry + 1;
  } while( true );
}



