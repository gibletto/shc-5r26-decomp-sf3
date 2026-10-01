#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 00406ac1
// name : schedule_superscalar_window
// size : 1668
// sig  : void schedule_superscalar_window(void)


int __cdecl schedule_superscalar_window(void)

{
  unsigned char _frec_44[68];
#define first_entry (*(byte *)(_frec_44 + 0))
#define parent (*(char *)(_frec_44 + 4))
#define j (*(char *)(_frec_44 + 8))
#define slot (*(uchar *)(_frec_44 + 12))
#define cycle_no (*(int *)(_frec_44 + 16))
#define issue_order (*(uchar *)(_frec_44 + 20))
#define busy_cycles (*(char (*)[32])(_frec_44 + 32))
  int conflict;
  char acStackY_a4 [64];
  bool blocked;
  byte pair_entry;
  
  issue_order = '\0';
  for (slot = '\0'; (char)slot <= g_pipeline_window_last_index; slot = slot + '\x01') {
    g_superscalar_order[(char)slot].issued = '\0';
    g_superscalar_order[(char)slot].entry = slot;
    g_superscalar_order[(char)slot].path_length = g_superscalar_window[(char)slot].path_length;
    busy_cycles[(char)slot] = -1;
  }
  sort_array(g_superscalar_order,g_pipeline_window_last_index + 1,0xc,
             compare_order_entries_by_height);
  for (cycle_no = 0; cycle_no < 200; cycle_no = cycle_no + 1) {
    for (j = '\0'; j <= g_pipeline_window_last_index; j = j + '\x01') {
      if ((busy_cycles[j] != -1) && (busy_cycles[j] != '\0')) {
        busy_cycles[j] = busy_cycles[j] + -1;
      }
    }
    slot = '\0';
    while (((char)slot <= g_pipeline_window_last_index &&
           (g_superscalar_order[(char)slot].issued != '\0'))) {
      slot = slot + '\x01';
    }
    if (g_pipeline_window_last_index < (char)slot) break;
    for (slot = '\0'; (char)slot <= g_pipeline_window_last_index; slot = slot + '\x01') {
      if (g_superscalar_order[(char)slot].issued == '\0') {
        first_entry = g_superscalar_order[(char)slot].entry;
        blocked = false;
        for (parent = '\0'; parent < ' '; parent = parent + '\x01') {
          if ((((*(uint *)(&g_window_entry_bit_masks + parent * 4) &
                g_superscalar_window[first_entry].flow_parents) != 0) && (busy_cycles[parent] != -1)
              ) && (busy_cycles[parent] != '\0')) {
            blocked = true;
            break;
          }
          if (((*(uint *)(&g_window_entry_bit_masks + parent * 4) &
               g_superscalar_window[first_entry].flow_parents) != 0) &&
             (g_superscalar_window[parent].scheduled == '\0')) {
            blocked = true;
            break;
          }
        }
        if (!blocked) {
          for (parent = '\0'; parent < ' '; parent = parent + '\x01') {
            if (((*(uint *)(&g_window_entry_bit_masks + parent * 4) &
                 g_superscalar_window[first_entry].anti_parents) != 0) &&
               (g_superscalar_window[parent].scheduled == '\0')) {
              blocked = true;
              break;
            }
          }
        }
        if (!blocked) {
          for (parent = '\0'; parent < ' '; parent = parent + '\x01') {
            if (((*(uint *)(&g_window_entry_bit_masks + parent * 4) &
                 g_superscalar_window[first_entry].ambi_parents) != 0) &&
               (g_superscalar_window[parent].scheduled == '\0')) {
              blocked = true;
              break;
            }
          }
        }
        if (!blocked) {
          busy_cycles[first_entry] = g_superscalar_window[first_entry].latency;
          g_superscalar_window[first_entry].order = issue_order;
          g_superscalar_window[first_entry].scheduled = '\x01';
          g_superscalar_order[(char)slot].issued = '\x01';
          g_superscalar_order[(char)slot].cycle = cycle_no;
          issue_order = issue_order + '\x01';
          break;
        }
      }
    }
    for (slot = '\0'; (char)slot <= g_pipeline_window_last_index; slot = slot + '\x01') {
      if (g_superscalar_order[(char)slot].issued == '\0') {
        pair_entry = g_superscalar_order[(char)slot].entry;
        blocked = false;
        for (parent = '\0'; parent < ' '; parent = parent + '\x01') {
          if ((((*(uint *)(&g_window_entry_bit_masks + parent * 4) &
                g_superscalar_window[pair_entry].flow_parents) != 0) && (busy_cycles[parent] != -1))
             && (busy_cycles[parent] != '\0')) {
            blocked = true;
            break;
          }
          if (((*(uint *)(&g_window_entry_bit_masks + parent * 4) &
               g_superscalar_window[pair_entry].flow_parents) != 0) &&
             (g_superscalar_window[parent].scheduled == '\0')) {
            blocked = true;
            break;
          }
        }
        if (!blocked) {
          for (parent = '\0'; parent < ' '; parent = parent + '\x01') {
            if (((*(uint *)(&g_window_entry_bit_masks + parent * 4) &
                 g_superscalar_window[pair_entry].anti_parents) != 0) &&
               (g_superscalar_window[parent].scheduled == '\0')) {
              blocked = true;
              break;
            }
          }
        }
        if (!blocked) {
          for (parent = '\0'; parent < ' '; parent = parent + '\x01') {
            if (((*(uint *)(&g_window_entry_bit_masks + parent * 4) &
                 g_superscalar_window[pair_entry].ambi_parents) != 0) &&
               (g_superscalar_window[parent].scheduled == '\0')) {
              blocked = true;
              break;
            }
          }
        }
        if ((!blocked) &&
           (conflict = issue_groups_conflict((uint)first_entry,(uint)pair_entry), conflict == 0)) {
          busy_cycles[pair_entry] = g_superscalar_window[pair_entry].latency;
          g_superscalar_window[pair_entry].order = issue_order;
          g_superscalar_window[pair_entry].scheduled = '\x01';
          g_superscalar_order[(char)slot].issued = '\x01';
          g_superscalar_order[(char)slot].cycle = cycle_no;
          issue_order = issue_order + '\x01';
          break;
        }
      }
    }
  }
  if ((g_current_request->flags_13c & 8) != 0) {
    dump_superscalar_window('\x02');
  }
  return;
#undef first_entry
#undef parent
#undef j
#undef slot
#undef cycle_no
#undef issue_order
#undef busy_cycles
}
