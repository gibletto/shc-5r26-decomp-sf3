#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))


// entry: 00414440
// name : sort_lregs_by_mreg
// size : 303
// sig  : void sort_lregs_by_mreg(void)


int __cdecl sort_lregs_by_mreg(void)

{
  int iVar1;
  lreg **other;
  lreg **slot;
  int i;
  short pregno;
  lreg *tmp;
  
  if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 2) != 0) {
    i = 1;
    FID_conflict__wprintf(s__________mregsort_start__________00435678);
    if (0 < g_lreg_count) {
      slot = g_lreg_table;
      do {
        slot = slot + 1;
        if ((*slot)->pregno < 0) {
          FID_conflict__wprintf(&g_fmt_3d,(int)(*slot)->pregno);
        }
        i = i + 1;
      } while (i <= g_lreg_count);
    }
    FID_conflict__wprintf(&g_str_newline);
  }
  for (; g_mem_lreg_count != 0; g_mem_lreg_count = g_mem_lreg_count + -1) {
    i = 1;
    if (1 < g_lreg_count) {
      slot = g_lreg_table;
      do {
        slot = slot + 1;
        if (((*slot)->pregno < 0) && (iVar1 = i + 1, iVar1 <= g_lreg_count)) {
          other = g_lreg_table + iVar1;
          iVar1 = (g_lreg_count - iVar1) + 1;
          do {
            pregno = (*other)->pregno;
            if ((pregno < 0) && (tmp = *slot, pregno < tmp->pregno)) {
              *slot = *other;
              *other = tmp;
            }
            other = other + 1;
            iVar1 = iVar1 + -1;
          } while (iVar1 != 0);
        }
        i = i + 1;
      } while (i < g_lreg_count);
    }
  }
  if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 2) != 0) {
    i = 1;
    FID_conflict__wprintf(s__________mregsort_end__________00435658);
    if (0 < g_lreg_count) {
      slot = g_lreg_table;
      do {
        slot = slot + 1;
        if ((*slot)->pregno < 0) {
          FID_conflict__wprintf(&g_fmt_3d,(int)(*slot)->pregno);
        }
        i = i + 1;
      } while (i <= g_lreg_count);
    }
    FID_conflict__wprintf(&g_str_newline);
  }
  return;
}



