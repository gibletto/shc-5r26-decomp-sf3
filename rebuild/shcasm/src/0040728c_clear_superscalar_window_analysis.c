#include "decls.h"
#include "imports.h"

// entry: 0040728c
// name : clear_superscalar_window_analysis
// size : 652
// sig  : void clear_superscalar_window_analysis(void)


int __cdecl clear_superscalar_window_analysis(void)

{
  char byte_no;
  char entry_no;
  
  for (entry_no = '\0'; entry_no <= g_pipeline_window_last_index; entry_no = entry_no + '\x01') {
    g_superscalar_window[entry_no].order = 0xff;
    g_superscalar_window[entry_no].scheduled = '\0';
    g_superscalar_window[entry_no].read_count = '\0';
    g_superscalar_window[entry_no].write_count = '\0';
    for (byte_no = '\0'; byte_no < '\x18'; byte_no = byte_no + '\x01') {
      *(undefined1 *)(entry_no * 0xe0 + SD(0x0044bcd0) + (int)byte_no) = 0;
      *(undefined1 *)(entry_no * 0xe0 + SD(0x0044bce8) + (int)byte_no) = 0;
    }
    g_superscalar_window[entry_no].latency = '\0';
    g_superscalar_window[entry_no].issue_group = '\0';
    g_superscalar_window[entry_no].expr_rewritten = '\0';
    g_superscalar_window[entry_no].path_length = 0;
    for (byte_no = '\0'; byte_no < '@'; byte_no = byte_no + '\x01') {
      *(undefined1 *)(entry_no * 0xe0 + SD(0x0044bd08) + (int)byte_no) = 0;
      *(undefined1 *)(entry_no * 0xe0 + SD(0x0044bd48) + (int)byte_no) = 0;
    }
    g_superscalar_window[entry_no].flow_child_count = '\0';
    g_superscalar_window[entry_no].flow_parent_count = '\0';
    g_superscalar_window[entry_no].flow_children = 0;
    g_superscalar_window[entry_no].flow_parents = 0;
    g_superscalar_window[entry_no].anti_child_count = '\0';
    g_superscalar_window[entry_no].anti_parent_count = '\0';
    g_superscalar_window[entry_no].anti_children = 0;
    g_superscalar_window[entry_no].anti_parents = 0;
    g_superscalar_window[entry_no].ambi_child_count = '\0';
    g_superscalar_window[entry_no].ambi_parent_count = '\0';
    g_superscalar_window[entry_no].ambi_children = 0;
    g_superscalar_window[entry_no].ambi_parents = 0;
  }
  return;
}
