#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_lreg_table
#define g_lreg_table (*(short * *)(g_sd + 0x1fa10))
#undef g_used_gpr_mask
#define g_used_gpr_mask (*(unsigned char *)(g_sd + 0x1ff60))


// entry: 0041ae20
// name : record_r0_variable_use_serial
// size : 174
// sig  : void record_r0_variable_use_serial(void)


int __cdecl record_r0_variable_use_serial(void)

{
  int *slot_ptr;
  void *new_blk;
  uint i;
  short *entry;
  int *blk;
  int first_link;
  int link;
  bool stored;
  
  if (*g_lreg_table != 0) {
    entry = g_lreg_table;
    do {
      if (*entry == *(short *)(g_r0_variable + 2)) break;
      entry = entry + 0x12;
    } while (*entry != 0);
    if (*entry != 0) {
      blk = (int *)(entry + 10);
      (*(unsigned char *)((char *)&g_used_gpr_mask + 0)) = (byte)g_used_gpr_mask & 0xfe;
      first_link = *blk;
      link = first_link;
      while (link != 0) {
        blk = (int *)*blk;
        link = *blk;
      }
      stored = false;
      if (first_link != 0) {
        i = 0;
        slot_ptr = blk;
        do {
          slot_ptr = slot_ptr + 1;
          if (*slot_ptr == 0) {
            stored = true;
            blk[i + 1] = g_stmt_serial;
            break;
          }
          i = i + 1;
        } while (i < 4);
      }
      if (!stored) {
        new_blk = alloc_zeroed(0x14);
        *blk = (int)new_blk;
        *(uint *)(*blk + 4) = g_stmt_serial;
      }
      if ((int)entry - (int)blk == -0x14) {
        *(byte *)((int)entry + 5) = *(byte *)((int)entry + 5) | 0x80;
      }
      if ((g_r0_used != 0) && ((*(byte *)((int)entry + 5) & 0x80) != 0)) {
        *(byte *)((int)entry + 5) = *(byte *)((int)entry + 5) & 0x7f;
      }
    }
  }
  return;
}



