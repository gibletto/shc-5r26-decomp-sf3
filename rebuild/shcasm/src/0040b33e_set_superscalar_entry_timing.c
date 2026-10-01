#include "decls.h"
#include "imports.h"

// entry: 0040b33e
// name : set_superscalar_entry_timing
// size : 162
// sig  : void __cdecl set_superscalar_entry_timing(char latency,char issue_group,int stage_pattern,void *effect_text1,void *effect_text2)


int __cdecl
set_superscalar_entry_timing
          (char latency,char issue_group,int stage_pattern,void *effect_text1,void *effect_text2)

{
  g_superscalar_window[g_superscalar_current_entry].latency = latency;
  g_superscalar_window[g_superscalar_current_entry].issue_group = issue_group;
  stock_memcpy(g_superscalar_window[g_superscalar_current_entry].defs_text,effect_text1,0x40);
  stock_memcpy(g_superscalar_window[g_superscalar_current_entry].expr_text,effect_text2,0x40);
  *(int *)(&g_superscalar_entry_stage_pattern + g_superscalar_current_entry * 4) = stage_pattern;
  return;
}
