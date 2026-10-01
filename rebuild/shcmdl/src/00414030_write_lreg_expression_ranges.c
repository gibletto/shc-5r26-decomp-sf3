#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_reg_file
#define g_reg_file (*(FILE * *)(g_sd + 0x1e72c))


// entry: 00414030
// name : write_lreg_expression_ranges
// size : 271
// sig  : void write_lreg_expression_ranges(lreg * lr)


int __cdecl write_lreg_expression_ranges(lreg *lr)

{
  unsigned char _frec_2[2];
#define local_2 (*(short *)(_frec_2 + 0))
  uint got;
  uint uVar1;
  undefined4 *range;
  
  uVar1 = 0;  local_2 = 0;
  for (range = lr->exp_area; range != (undefined4 *)0x0; range = (undefined4 *)*range) {
    local_2 = local_2 + 1;  uVar1 = (uint)(ushort)local_2;
  }
  got = write_bytes(g_reg_file,(char *)&local_2,2);
  if (got == 0xffffffff) {
    fatal_error(0xce7);
  }
  if ((g_debug_flags & 0x3000000) != 0) {
    FID_conflict__wprintf(s__num__2d______004355ac,uVar1 & 0xffff);
  }
  if (((lr->set == 0) && (*(short *)lr->chain != 8)) && (*(short *)((int)lr->chain + 2) == 0)) {
    *(undefined4 *)((int)lr->exp_area + 4) = 1;
  }
  for (range = lr->exp_area; range != (undefined4 *)0x0; range = (undefined4 *)*range) {
    uVar1 = write_bytes(g_reg_file,(char *)(range + 1),4);
    if (uVar1 == 0xffffffff) {
      fatal_error(0xce7);
    }
    uVar1 = write_bytes(g_reg_file,(char *)(range + 2),4);
    if (uVar1 == 0xffffffff) {
      fatal_error(0xce7);
    }
    if ((g_debug_flags & 0x3000000) != 0) {
      FID_conflict__wprintf(s_____st__2d_en__3d__00435590,range[1],range[2]);
    }
  }
  return;
#undef local_2
}



