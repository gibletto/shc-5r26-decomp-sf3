#include "decls.h"
#include "imports.h"

// entry: 004202b1
// name : emit_line_directive_for_record
// size : 151
// sig  : void __cdecl emit_line_directive_for_record(psd *rec)


int __cdecl emit_line_directive_for_record(psd *rec)

{
  if ((((OP_BEND < rec->op) && (rec->op < OP_DUMMY_1C)) || (g_line_directive_prev_op == 0x90)) ||
     (g_line_directive_prev_op == 0x91)) {
    free_line_directive_list(0);
  }
  emit_line_directive_if_new(rec);
  if ((g_line_directive_prev_op == 0x98) || (g_line_directive_prev_op == 0x97)) {
    g_line_directive_prev_op = 0x91;
  }
  else {
    g_line_directive_prev_op = rec->op;
  }
  return;
}
