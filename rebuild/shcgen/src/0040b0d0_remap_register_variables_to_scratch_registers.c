#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_lreg_table
#define g_lreg_table (*(short * *)(g_sd + 0x1fa10))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0040b0d0
// name : remap_register_variables_to_scratch_registers
// size : 1049
// sig  : void remap_register_variables_to_scratch_registers(void)


int __cdecl remap_register_variables_to_scratch_registers(void)

{
  short sVar1;
  uint uVar2;
  undefined4 *remap_entry;
  reg_range *prVar3;
  byte var_reg;
  byte scratch;
  undefined4 *tail;
  short *other_entry;
  uint found_scratch;
  int *live_range;
  reg_range *range;
  reg_content *contents;
  bool found;
  reg_range **link;
  uint live_end;
  uint live_start;
  short *lreg;
  undefined4 *next_entry;
  
  merge_and_sort_lreg_entries();
  lreg = g_lreg_table;
  scratch = 0;
  do {
    range = g_gpr_contents[scratch].ranges_tail;
    if ((range != (reg_range *)0x0) && (range->end == 0)) {
      range->end = g_stmt_serial;
    }
    range = g_fpr_contents[scratch].ranges_tail;
    if ((range != (reg_range *)0x0) && (range->end == 0)) {
      range->end = g_stmt_serial;
    }
    scratch = scratch + 1;
  } while (scratch < 4);
  sVar1 = *lreg;
  do {
    if (sVar1 == 0) {
      return;
    }
    sVar1 = lreg[1];
    if ((((7 < sVar1) || ((*(byte *)((int)lreg + 5) & 0x80) != 0)) &&
        ((sVar1 < 0x10 || (g_request->scratch_bank_reg_count + 0x14 <= (int)sVar1)))) &&
       (sVar1 < 0x20)) {
      found = false;
      found_scratch = 0xff;
      scratch = 0;
      var_reg = (byte)sVar1;
      do {
        if (found) break;
        live_range = *(int **)(lreg + 8);
        if (live_range != (int *)0x0) {
          do {
            if ((int)(uint)var_reg < g_request->scratch_bank_reg_count + 0x14) {
              range = g_gpr_contents[scratch].ranges;
            }
            else {
              range = g_fpr_contents[scratch].ranges;
            }
            for (; range != (reg_range *)0x0; range = range->next) {
              if ((range->start <= (uint)live_range[1]) && ((uint)live_range[2] <= range->end)) {
                found = true;
                found_scratch = (uint)scratch;
                break;
              }
              found = false;
            }
          } while ((found) && (live_range = (int *)*live_range, live_range != (int *)0x0));
        }
        scratch = scratch + 1;
      } while (scratch < 4);
      if (found) {
        scratch = (byte)found_scratch;
        found = true;
        if (((*(byte *)((int)lreg + 5) & 0x80) != 0) && (scratch != 0)) {
          if ((1 << (var_reg & 0x1f) & 0xf0U) == 0) {
            *(byte *)((int)lreg + 5) = *(byte *)((int)lreg + 5) & 0x7f;
            cut_r0_ranges_at_serials(*(serial_block **)(lreg + 10));
          }
          else {
            found = false;
          }
        }
        if (found) {
          live_range = *(int **)(lreg + 8);
          if (live_range != (int *)0x0) {
            uVar2 = (uint)var_reg;
            do {
              remap_entry = alloc_zeroed(0x10);
              *(byte *)(remap_entry + 1) = var_reg;
              if ((int)uVar2 < g_request->scratch_bank_reg_count + 0x14) {
                *(byte *)((int)remap_entry + 5) = scratch;
              }
              else {
                *(byte *)((int)remap_entry + 5) = scratch + 0x10;
              }
              remap_entry[2] = live_range[1];
              remap_entry[3] = live_range[2];
              *remap_entry = 0;
              tail = *(undefined4 **)(g_current_aux_record + 0x18);
              if (*(undefined4 **)(g_current_aux_record + 0x18) == (undefined4 *)0x0) {
                *(undefined4 **)(g_current_aux_record + 0x18) = remap_entry;
              }
              else {
                do {
                  next_entry = (undefined4 *)*tail;
                  if (next_entry == (undefined4 *)0x0) break;
                  tail = next_entry;
                } while (next_entry != (undefined4 *)0x0);
                *tail = remap_entry;
              }
              *(short *)(g_current_aux_record + 0x14) = *(short *)(g_current_aux_record + 0x14) + 1;
              if ((((int)uVar2 < g_request->scratch_bank_reg_count + 0x14) && (scratch == 0)) &&
                 ((*(byte *)((int)lreg + 5) & 0x40) != 0)) {
                *(byte *)(g_current_aux_record + 0x28) = var_reg;
              }
              if ((int)uVar2 < g_request->scratch_bank_reg_count + 0x14) {
                range = g_gpr_contents[found_scratch].ranges;
                contents = g_gpr_contents;
              }
              else {
                range = g_fpr_contents[found_scratch].ranges;
                contents = g_fpr_contents;
              }
              if (range != (reg_range *)0x0) {
                live_start = live_range[1];
                prVar3 = (reg_range *)&contents[found_scratch].ranges;
                do {
                  if ((range->start <= live_start) && ((uint)live_range[2] <= range->end)) {
                    live_end = live_range[2];
                    if (range->start == live_start) {
                      if (range->end == live_end) {
                        prVar3->next = range->next;
                        pool_free(range,0xc);
                      }
                      else {
                        range->start = live_end + 1;
                      }
                    }
                    else if (range->end == live_end) {
                      range->end = live_start - 1;
                    }
                    else {
                      prVar3 = alloc_zeroed(0xc);
                      if (prVar3 == (reg_range *)0x0) {
                        report_codegen_message(0x1210,1,0,0,(char *)0x0);
                      }
                      prVar3->start = live_range[2] + 1;
                      prVar3->end = range->end;
                      prVar3->next = range->next;
                      range->end = live_range[1] - 1;
                      range->next = prVar3;
                    }
                    break;
                  }
                  link = &range->next;
                  prVar3 = range;
                  range = *link;
                } while (*link != (reg_range *)0x0);
              }
              live_range = (int *)*live_range;
            } while (live_range != (int *)0x0);
          }
          if ((*(short *)(g_request->unknown_004 + 0x12) != 0) && (*g_lreg_table != 0)) {
            other_entry = g_lreg_table;
            do {
              if ((int)other_entry[1] == (uint)var_reg) {
                sVar1 = (short)found_scratch;
                if (g_request->scratch_bank_reg_count + 0x14 <= (int)(uint)var_reg) {
                  sVar1 = sVar1 + 0x10;
                }
                other_entry[1] = sVar1;
              }
              other_entry = other_entry + 0x12;
            } while (*other_entry != 0);
          }
          if ((int)(uint)var_reg < g_request->scratch_bank_reg_count + 0x14) {
            g_used_gpr_mask = g_used_gpr_mask | 1 << (scratch & 0x1f);
            g_used_gpr_mask = g_used_gpr_mask & ~(1 << (var_reg & 0x1f));
          }
          else {
            g_used_fpr_mask = g_used_fpr_mask | 1 << (scratch & 0x1f);
            g_used_fpr_mask = g_used_fpr_mask & ~(1 << (var_reg - 0x10 & 0x1f));
          }
          goto LAB_0040b4ce;
        }
      }
      if ((*(byte *)((int)lreg + 5) & 0x80) != 0) {
        *(byte *)((int)lreg + 5) = *(byte *)((int)lreg + 5) & 0x7f;
        cut_r0_ranges_at_serials(*(serial_block **)(lreg + 10));
      }
    }
LAB_0040b4ce:
    lreg = lreg + 0x12;
    sVar1 = *lreg;
  } while( true );
}



