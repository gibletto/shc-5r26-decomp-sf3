#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00414de0
// name : delete_switch_marker_pair
// size : 287
// sig  : void __cdecl delete_switch_marker_pair(psd *rec)


int __cdecl delete_switch_marker_pair(psd *rec)

{
  bool keep_rec;
  char *begin_marker;
  int depth;
  psd_op op;
  
  if (((byte)g_stage_flags & 2) != 0) {
    _printf(s_sw_delete_start__00427b40);
  }
  depth = g_switch_marker_depth;
  op = rec->op;
  if (op != OP_CASEJMP) {
    if (op == OP_SWBGN) {
      if (g_switch_scan_single_block == 0) {
        (&g_switch_marker_pairs)[g_switch_marker_depth * 2] = rec;
        g_switch_marker_depth = g_switch_marker_depth + 1;
      }
      else {
        (&g_switch_marker_pairs)[g_switch_marker_depth * 2] = 0;
        g_switch_marker_depth = g_switch_marker_depth + 1;
      }
    }
    else if (op == OP_SWEND) {
      keep_rec = g_switch_scan_single_block == 0;
      (&g_switch_marker_pairs)[g_switch_marker_depth * 2] = 0;
      (&g_switch_brackets_end)[depth * 2] = 0;
      if (keep_rec) {
        g_switch_marker_depth = g_switch_marker_depth + -1;
        (&g_switch_brackets_end)[g_switch_marker_depth * 2] = rec;
      }
      else {
        g_switch_marker_depth = g_switch_marker_depth + -1;
        (&g_switch_brackets_end)[g_switch_marker_depth * 2] = 0;
      }
    }
    else {
      begin_marker = (char *)(&g_switch_marker_pairs)[g_switch_marker_depth * 2];
      if ((((begin_marker != (char *)0x0) &&
           ((char *)(&g_switch_brackets_end)[g_switch_marker_depth * 2] != (char *)0x0)) &&
          (*begin_marker != '\0')) &&
         (*(char *)(&g_switch_brackets_end)[g_switch_marker_depth * 2] != '\0')) {
        *begin_marker = '\0';
        *(undefined1 *)(&g_switch_brackets_end)[g_switch_marker_depth * 2] = 0;
        if (((byte)g_stage_flags & 2) == 0) {
          return;
        }
        _printf(s_SWBGN___SWEND_delete__00427b28);
      }
    }
  }
  if (((byte)g_stage_flags & 2) != 0) {
    _printf(s_sw_delete_end__00427b18);
  }
  return;
}
