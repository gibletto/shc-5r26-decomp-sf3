#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_lreg_table
#define g_lreg_table (*(unsigned int * *)(g_sd + 0x1fa10))


// entry: 0040b4f0
// name : merge_and_sort_lreg_entries
// size : 628
// sig  : void * merge_and_sort_lreg_entries(void)


int * __cdecl merge_and_sort_lreg_entries(void)

{
  unsigned char _frec_24[36];
#define swap_buf (*(uint (*)[9])(_frec_24 + 0))
  reg_range *merged_ranges;
  void *merged_uses;
  int overlap;
  uint *extraout_EAX;
  uint *puVar1;
  int *range;
  uint live_length;
  uint *entry;
  uint *src;
  int *end_ptr;
  byte entry_flags;
  short lreg;
  int *start_ptr;
  
  lreg = (short)*g_lreg_table;
  entry = g_lreg_table;
  while (lreg != 0) {
    if ((0 < *(short *)((int)entry + 2)) && (entry[4] != 0)) {
      puVar1 = entry + 9;
      lreg = (short)*puVar1;
      while (lreg != 0) {
        if (((0 < *(short *)((int)puVar1 + 2)) && ((reg_range *)puVar1[4] != (reg_range *)0x0)) &&
           (*(short *)((int)entry + 2) == *(short *)((int)puVar1 + 2))) {
          merged_ranges = merge_live_range_lists((reg_range *)entry[4],(reg_range *)puVar1[4]);
          entry[4] = (uint)merged_ranges;
          puVar1[4] = 0;
          if (((entry[5] != 0) && (puVar1[5] != 0)) &&
             (((*(byte *)((int)entry + 5) & 0x80) == 0 || ((*(byte *)((int)puVar1 + 5) & 0x80) == 0)
              ))) {
            *(byte *)((int)entry + 5) = *(byte *)((int)entry + 5) & 0x7f;
          }
          merged_uses = merge_r0_use_lists((void *)entry[5],(void *)puVar1[5]);
          entry[5] = (uint)merged_uses;
          puVar1[5] = 0;
          if ((*(byte *)((int)puVar1 + 5) & 0x40) != 0) {
            *(byte *)((int)entry + 5) = *(byte *)((int)entry + 5) | 0x40;
          }
        }
        puVar1 = puVar1 + 9;
        lreg = (short)*puVar1;
      }
    }
    entry = entry + 9;
    lreg = (short)*entry;
  }
  lreg = (short)*g_lreg_table;
  entry = g_lreg_table;
  while (lreg != 0) {
    range = (int *)entry[4];
    if (range == (int *)0x0) {
      entry[3] = 0;
    }
    else {
      live_length = 0;
      do {
        end_ptr = range + 2;
        start_ptr = range + 1;
        range = (int *)*range;
        live_length = live_length + (*end_ptr - *start_ptr) + 1;
      } while (range != (int *)0x0);
      entry[3] = live_length;
    }
    entry = entry + 9;
    lreg = (short)*entry;
  }
  lreg = (short)*g_lreg_table;
  entry = g_lreg_table;
  while (lreg != 0) {
    if (entry[3] != 0) {
      puVar1 = entry + 9;
      lreg = (short)*puVar1;
      while (lreg != 0) {
        if (((puVar1[3] != 0) && (entry[5] != 0)) &&
           ((puVar1[5] != 0 &&
            (overlap = live_range_lists_overlap((reg_range *)entry[4],(reg_range *)puVar1[4]),
            overlap != 0)))) {
          if (entry[5] != 0) {
            *(byte *)((int)entry + 5) = *(byte *)((int)entry + 5) & 0x7f;
            cut_r0_ranges_at_serials((serial_block *)entry[5]);
          }
          if (puVar1[4] != 0) {
            *(byte *)((int)puVar1 + 5) = *(byte *)((int)puVar1 + 5) & 0x7f;
            cut_r0_ranges_at_serials((serial_block *)puVar1[5]);
          }
        }
        puVar1 = puVar1 + 9;
        lreg = (short)*puVar1;
      }
    }
    entry = entry + 9;
    lreg = (short)*entry;
  }
  lreg = (short)*g_lreg_table;
  entry = g_lreg_table;
  while (lreg != 0) {
    if ((*(byte *)((int)entry + 5) & 0x80) == 0) {
      if ((serial_block *)entry[5] != (serial_block *)0x0) {
        cut_r0_ranges_at_serials((serial_block *)entry[5]);
      }
      puVar1 = entry + 9;
      if ((short)*puVar1 == 0) break;
      do {
        if ((*(byte *)((int)puVar1 + 5) & 0x80) != 0) {
          copy_words(swap_buf,entry,9);
          copy_words(entry,puVar1,9);
          copy_words(puVar1,swap_buf,9);
          break;
        }
        if ((serial_block *)puVar1[5] != (serial_block *)0x0) {
          cut_r0_ranges_at_serials((serial_block *)puVar1[5]);
        }
        puVar1 = puVar1 + 9;
      } while ((short)*puVar1 != 0);
      if ((short)*puVar1 == 0) break;
    }
    entry = entry + 9;
    lreg = (short)*entry;
  }
  entry_flags = *(byte *)((int)g_lreg_table + 5);
  entry = g_lreg_table;
  while ((entry_flags & 0x80) != 0) {
    entry_flags = *(byte *)((int)entry + 0x29);
    entry = entry + 9;
  }
  lreg = (short)*entry;
  puVar1 = g_lreg_table;
  while (lreg != 0) {
    if (entry[3] != 0) {
      src = entry + 9;
      lreg = (short)*src;
      while (lreg != 0) {
        puVar1 = (uint *)src[3];
        if ((puVar1 != (uint *)0x0) && (puVar1 < (uint *)entry[3])) {
          copy_words(swap_buf,entry,9);
          copy_words(entry,src,9);
          (extraout_EAX = (uint *)copy_words(src,swap_buf,9));
          puVar1 = extraout_EAX;
        }
        src = src + 9;
        lreg = (short)*src;
      }
    }
    entry = entry + 9;
    lreg = (short)*entry;
  }
  return puVar1;
#undef swap_buf
}



