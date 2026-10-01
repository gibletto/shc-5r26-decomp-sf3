#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 00414820
// name : dump_lreg
// size : 913
// sig  : void dump_lreg(int lregno, lreg * lr, char * title)


int __cdecl dump_lreg(int lregno,lreg *lr,char *title)

{
  short sVar1;
  char *pcVar2;
  char *name;
  int col;
  undefined4 *cell;
  void *chain;
  
  if (title != (char *)0x0) {
    FID_conflict__wprintf(s___s__00435980,title);
  }
  sVar1 = lr->set;
  if (sVar1 == 1) {
    pcVar2 = s_WEB_CHAIN_00435974;
  }
  else if (sVar1 == 3) {
    pcVar2 = s_DELETE_WEB__00435968;
  }
  else {
    pcVar2 = s_MEMORY_ALLOCATED_00435954;
    if (sVar1 != 2) {
      pcVar2 = s_CONST_DATA_00435948;
    }
  }
  FID_conflict__wprintf
            (s____0x_08x_lregno__d__pregno__d__s_0043591c,lr,lregno,(int)lr->pregno,pcVar2);
  FID_conflict__wprintf(&g_str_newline);
  if (lr->set == 1) {
    pcVar2 = *(char **)((int)lr->chain + 0x10);
    if (*pcVar2 != 'p') {
      pcVar2 = *(char **)(pcVar2 + 0x14);
    }
    sVar1 = *(short *)(pcVar2 + 4);
    name = &g_str_empty;
    if (0 < sVar1) {
      name = g_symtab[sVar1].name;
    }
    FID_conflict__wprintf
              (s___symno__d__leafno__d__name___s__004358f8,(int)sVar1,(int)*(short *)(pcVar2 + 0x58)
               ,name);
    FID_conflict__wprintf(&g_str_newline);
  }
  FID_conflict__wprintf(s___priori__d__profit__d_004358dc,lr->priori,lr->profit);
  if ((lr->set == 1) || (lr->set == 3)) {
    col = 0;
    FID_conflict__wprintf(s___chained_nodes___004358c8);
    for (chain = lr->chain; chain != (void *)0x0; chain = *(void **)((int)chain + 8)) {
      col = col + 1;
      if (0xe < col) {
        col = 1;
        FID_conflict__wprintf(s___004358b4);
      }
      FID_conflict__wprintf(&g_fmt_3d,(uint)*(ushort *)(*(int *)((int)chain + 0x10) + 0x44));
    }
    goto LAB_00414a6e;
  }
  pcVar2 = s_ADDRESS_CONST_004358a4;
  if (*(short *)lr->chain != 1) {
    pcVar2 = s_NUMBER_CONST_00435894;
  }
  FID_conflict__wprintf
            (s___contents__s__value__d_00435878,pcVar2,*(undefined4 *)((int)lr->chain + 4));
  col = 0;
  FID_conflict__wprintf(&g_str_newline);
  FID_conflict__wprintf(s___chained_nodes___004358c8);
  for (cell = *(undefined4 **)((int)lr->chain + 8); cell != (undefined4 *)0x0;
      cell = (undefined4 *)*cell) {
    col = col + 1;
    if (0xe < col) {
      col = 1;
      FID_conflict__wprintf(s___004358b4);
    }
    FID_conflict__wprintf(&g_fmt_3d,(uint)*(ushort *)(cell[2] + 0x44));
  }
  FID_conflict__wprintf(&g_str_newline);
  sVar1 = *(short *)((int)lr->chain + 2);
  if (sVar1 == 0) {
    pcVar2 = s___dominator_type___NO_DOM_0043585c;
LAB_004149d1:
    FID_conflict__wprintf(pcVar2);
  }
  else {
    if (sVar1 == 1) {
      pcVar2 = s___dominator_type___EX_DOM_00435824;
      goto LAB_004149d1;
    }
    if (sVar1 == 2) {
      pcVar2 = s___dominator_type___SELF_DOM_00435840;
      goto LAB_004149d1;
    }
  }
  FID_conflict__wprintf(&g_str_newline);
  FID_conflict__wprintf(s___dominator_block_No____00435808);
  if (*(short *)((int)lr->chain + 2) == 0) {
    FID_conflict__wprintf(s_NOT_DOMINATOR_004357f8);
  }
  else {
    FID_conflict__wprintf(&g_str_percent_d,(int)**(short **)((int)lr->chain + 0x14));
  }
LAB_00414a6e:
  col = 0;
  FID_conflict__wprintf(&g_str_newline);
  sort_life_areas(lr);
  FID_conflict__wprintf(s___life_area_____004357e8);
  for (cell = lr->life; cell != (undefined4 *)0x0; cell = (undefined4 *)*cell) {
    col = col + 1;
    if (7 < col) {
      col = 1;
      FID_conflict__wprintf(s___004357d4);
    }
    FID_conflict__wprintf
              (s___3d__3d__004357c8,(uint)*(ushort *)(cell[1] + 8),(uint)*(ushort *)(cell[1] + 10));
  }
  col = 0;
  FID_conflict__wprintf(&g_str_close_brace_newline);
  FID_conflict__wprintf(s___exp_area_____004357b4);
  for (cell = lr->exp_area; cell != (undefined4 *)0x0; cell = (undefined4 *)*cell) {
    col = col + 1;
    if (7 < col) {
      col = 1;
      FID_conflict__wprintf(s___004357d4);
    }
    FID_conflict__wprintf(s___3d__3d__004357c8,cell[1],cell[2]);
  }
  col = 0;
  FID_conflict__wprintf(&g_str_close_brace_newline);
  FID_conflict__wprintf(s___clashed_lregs___004357a0);
  for (cell = lr->clashed; cell != (undefined4 *)0x0; cell = (undefined4 *)*cell) {
    col = col + 1;
    if (6 < col) {
      col = 1;
      FID_conflict__wprintf(s___004358b4);
    }
    FID_conflict__wprintf(s__08x_00435798,cell[1]);
  }
  FID_conflict__wprintf(&g_str_newline);
  FID_conflict__wprintf(s___bind_at_0x_08x_00435784,lr->bind);
  FID_conflict__wprintf(s___bakbind_at_0x_08x_0043576c,lr->bakbind);
  return;
}



