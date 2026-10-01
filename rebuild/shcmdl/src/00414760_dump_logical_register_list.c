#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_lreg_list
#define g_lreg_list (*(lreg * *)(g_sd + 0x16264))


// entry: 00414760
// name : dump_logical_register_list
// size : 188
// sig  : void dump_logical_register_list(char * title)


int __cdecl dump_logical_register_list(char *title)

{
  lreg *lr;
  int lregno;
  lreg **next_p;
  
  FID_conflict__wprintf(s_____LOGICAL_REGISTER_LIST________00435744,title);
  if ((g_lreg_table[1] == (lreg *)0x0) && (lr = g_lreg_list, g_lreg_list != (lreg *)0x0)) {
    do {
      FID_conflict__wprintf(s_______0043573c);
      FID_conflict__wprintf(s__________________________________004356f0);
      dump_lreg(0,lr,(char *)0x0);
      next_p = &lr->next;
      lr = *next_p;
    } while (*next_p != (lreg *)0x0);
  }
  else {
    lregno = 1;
    if (0 < g_lreg_count) {
      do {
        lr = g_lreg_table[lregno];
        FID_conflict__wprintf(s_______0043573c);
        FID_conflict__wprintf(s__________________________________004356f0);
        dump_lreg(lregno,lr,(char *)0x0);
        lregno = lregno + 1;
      } while (lregno <= g_lreg_count);
    }
  }
  FID_conflict__wprintf(s_______0043573c);
  FID_conflict__wprintf(s__________________________________004356f0);
  return;
}



