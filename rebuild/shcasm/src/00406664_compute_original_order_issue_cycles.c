#include "decls.h"
#include "imports.h"

// entry: 00406664
// name : compute_original_order_issue_cycles
// size : 1117
// sig  : void compute_original_order_issue_cycles(void)


int __cdecl compute_original_order_issue_cycles(void)

{
  unsigned char _frec_38[56];
#define parent (*(char *)(_frec_38 + 0))
#define j (*(char *)(_frec_38 + 4))
#define entry_no (*(byte *)(_frec_38 + 8))
#define cycle_no (*(int *)(_frec_38 + 12))
#define busy_cycles (*(char (*)[32])(_frec_38 + 20))
  int conflict;
  char acStackY_a4 [80];
  bool blocked;
  byte next_entry;
  
  for (entry_no = '\0'; (char)entry_no <= g_pipeline_window_last_index; entry_no = entry_no + '\x01'
      ) {
    busy_cycles[(char)entry_no] = '\0';
  }
  cycle_no = 0;
  entry_no = 0;
  while ((char)entry_no <= g_pipeline_window_last_index) {
    for (j = '\0'; j <= g_pipeline_window_last_index; j = j + '\x01') {
      if ((busy_cycles[j] != -1) && (busy_cycles[j] != '\0')) {
        busy_cycles[j] = busy_cycles[j] + -1;
      }
    }
    blocked = false;
    for (parent = '\0'; parent < ' '; parent = parent + '\x01') {
      if ((((*(uint *)(&g_window_entry_bit_masks + parent * 4) &
            g_superscalar_window[(char)entry_no].flow_parents) != 0) && (busy_cycles[parent] != -1))
         && (busy_cycles[parent] != '\0')) {
        blocked = true;
        break;
      }
    }
    if (!blocked) {
      for (parent = '\0'; parent < ' '; parent = parent + '\x01') {
        if ((((*(uint *)(&g_window_entry_bit_masks + parent * 4) &
              g_superscalar_window[(char)entry_no].anti_parents) != 0) &&
            (busy_cycles[parent] != -1)) && (busy_cycles[parent] != '\0')) {
          blocked = true;
          break;
        }
      }
    }
    if (!blocked) {
      for (parent = '\0'; parent < ' '; parent = parent + '\x01') {
        if ((((*(uint *)(&g_window_entry_bit_masks + parent * 4) &
              g_superscalar_window[(char)entry_no].ambi_parents) != 0) &&
            (busy_cycles[parent] != -1)) && (busy_cycles[parent] != '\0')) {
          blocked = true;
          break;
        }
      }
    }
    next_entry = entry_no;
    if (!blocked) {
      busy_cycles[entry_no] = g_superscalar_window[entry_no].latency;
      g_superscalar_order[entry_no].cycle = cycle_no;
      next_entry = entry_no + 1;
      if (g_pipeline_window_last_index < (char)next_entry) break;
      for (parent = '\0'; blocked = false, parent < ' '; parent = parent + '\x01') {
        if ((((*(uint *)(&g_window_entry_bit_masks + parent * 4) &
              g_superscalar_window[(char)next_entry].flow_parents) != 0) &&
            (busy_cycles[parent] != -1)) && (busy_cycles[parent] != '\0')) {
          blocked = true;
          break;
        }
      }
      if (!blocked) {
        for (parent = '\0'; parent < ' '; parent = parent + '\x01') {
          if ((((*(uint *)(&g_window_entry_bit_masks + parent * 4) &
                g_superscalar_window[(char)next_entry].anti_parents) != 0) &&
              (busy_cycles[parent] != -1)) && (busy_cycles[parent] != '\0')) {
            blocked = true;
            break;
          }
        }
      }
      if (!blocked) {
        for (parent = '\0'; parent < ' '; parent = parent + '\x01') {
          if ((((*(uint *)(&g_window_entry_bit_masks + parent * 4) &
                g_superscalar_window[(char)next_entry].ambi_parents) != 0) &&
              (busy_cycles[parent] != -1)) && (busy_cycles[parent] != '\0')) {
            blocked = true;
            break;
          }
        }
      }
      if ((!blocked) &&
         (conflict = issue_groups_conflict((uint)entry_no,(uint)next_entry), conflict == 0)) {
        busy_cycles[next_entry] = g_superscalar_window[next_entry].latency;
        g_superscalar_order[next_entry].cycle = cycle_no;
        next_entry = entry_no + 2;
      }
    }
    entry_no = next_entry;
    cycle_no = cycle_no + 1;
  }
  dump_superscalar_window('\x01');
  return;
#undef parent
#undef j
#undef entry_no
#undef cycle_no
#undef busy_cycles
}
