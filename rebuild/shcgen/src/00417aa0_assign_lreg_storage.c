#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_lreg_table
#define g_lreg_table (*(short * *)(g_sd + 0x1fa10))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 00417aa0
// name : assign_lreg_storage
// size : 427
// sig  : void assign_lreg_storage(void)


int __cdecl assign_lreg_storage(void)

{
  short sVar1;
  byte bVar2;
  byte fpu_mode;
  short *scan;
  int iVar3;
  int ofs;
  int i;
  
  ofs = 0;
  i = 0;
  sVar1 = *g_lreg_table;
  do {
    if (sVar1 == 0) {
      return;
    }
    sVar1 = *(short *)((int)g_lreg_table + ofs + 2);
    if (sVar1 < 0) {
      iVar3 = 0;
      if (0 < ofs) {
        scan = g_lreg_table + 1;
        do {
          if (*scan == sVar1) break;
          scan = scan + 0x12;
          iVar3 = iVar3 + 1;
        } while (iVar3 < i);
      }
      if (iVar3 == i) {
        bVar2 = *(byte *)((int)g_lreg_table + ofs + 4) & 0xf8;
        if ((bVar2 == 0x30) || (bVar2 == 0x38)) {
          g_frame_end = g_frame_end + -8;
        }
        else {
          g_frame_end = g_frame_end + -4;
        }
        iVar3 = g_frame_end;
        if (-1 < g_frame_end) {
          report_codegen_message(0xc84,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
        }
        fill_ea((ea *)((int)g_lreg_table + ofs + 0x18),'\b','l',-1,'\0',iVar3,(label_ref *)0x0);
      }
      else {
        copy_ea_into((ea *)((int)g_lreg_table + ofs + 0x18),
                     (ea *)(g_lreg_table + iVar3 * 0x12 + 0xc));
      }
    }
    else {
      bVar2 = (byte)sVar1;
      fill_ea((ea *)((int)g_lreg_table + ofs + 0x18),'\x01',bVar2,-1,'\0',0,(label_ref *)0x0);
      sVar1 = g_request->cpu;
      if ((sVar1 == 4) && ((*(byte *)((int)g_lreg_table + ofs + 4) & 0xf8) == 0x30)) {
        g_used_fpr_mask = g_used_fpr_mask | 1 << (bVar2 - 0x1f & 0x1f) | 1 << (bVar2 - 0x20 & 0x1f);
      }
      else {
        if ((sVar1 == 2) && (g_request->fpu_mode == '\x03')) {
          fpu_mode = 1;
        }
        else {
          fpu_mode = -(sVar1 == 4) & 2;
        }
        if ((fpu_mode == 0) || ((*(byte *)((int)g_lreg_table + ofs + 4) & 0xf8) != 0x28)) {
          g_used_gpr_mask = g_used_gpr_mask | 1 << (bVar2 & 0x1f);
        }
        else {
          g_used_fpr_mask = g_used_fpr_mask | 1 << (bVar2 - 0x10 & 0x1f);
        }
      }
    }
    ofs = ofs + 0x24;
    i = i + 1;
    sVar1 = *(short *)((int)g_lreg_table + ofs);
  } while( true );
}



