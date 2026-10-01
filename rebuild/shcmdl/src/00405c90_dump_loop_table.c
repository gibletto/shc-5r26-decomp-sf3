#include "decls.h"
#include "imports.h"

// entry: 00405c90
// name : dump_loop_table
// size : 401
// sig  : void dump_loop_table(loop * lp)


int __cdecl dump_loop_table(loop *lp)

{
  char *kind_name;
  char bit;
  int i;
  
  for (; lp != (loop *)0x0; lp = lp->next) {
    FID_conflict__wprintf(s_LP_d__004337b0,(int)lp->lpnumber);
    FID_conflict__wprintf(s_BRC_No__d_004337a4,(int)lp->brc);
    kind_name = s_ENTER_0043379c;
    if ((lp->flag & 1) == 0) {
      kind_name = &g_str_exit;
    }
    FID_conflict__wprintf(s____type____s_00433780,kind_name);
    if (lp->start != (bblock *)0x0) {
      FID_conflict__wprintf(s____start___B_d_0043376c,(int)lp->start->number);
    }
    if (lp->exit != (bblock *)0x0) {
      FID_conflict__wprintf(s____exit___B_d_00433758,(int)lp->exit->number);
    }
    if (lp->pre != (bblock *)0x0) {
      FID_conflict__wprintf(s____pre___B_d_00433744,(int)lp->pre->number);
    }
    if (lp->child != (loop *)0x0) {
      FID_conflict__wprintf(s____child___LP_d_0043372c,(int)lp->child->lpnumber);
    }
    if (lp->fath != (loop *)0x0) {
      FID_conflict__wprintf(s____fath___LP_d_00433714,(int)lp->fath->lpnumber);
    }
    if (lp->next != (loop *)0x0) {
      FID_conflict__wprintf(s____next___LP_d_004336fc,(int)lp->next->lpnumber);
    }
    if (lp->front != (loop *)0x0) {
      FID_conflict__wprintf(s____front___LP_d_004336e4,(int)lp->front->lpnumber);
    }
    if (lp->lstep != 0) {
      FID_conflict__wprintf(s____lstep____d_004336d0,lp->lstep);
    }
    if (lp->repet != 0) {
      FID_conflict__wprintf(s____repet____d_004336bc,lp->repet);
    }
    i = 0;
    FID_conflict__wprintf(s____nestcnt___d_004336a8,(int)lp->nestcnt);
    FID_conflict__wprintf(s____flag___00433698);
    do {
      bit = (char)i;
      i = i + 1;
      FID_conflict__wprintf(&g_str_percent_1d,(uint)((1 << (0x1fU - bit & 0x1f) & lp->flag) != 0));
    } while (i < 0x20);
    FID_conflict__wprintf(&g_str_newline);
    dump_loop_table(lp->child);
  }
  return;
}



