#include "decls.h"
#include "imports.h"

// entry: 00426c90
// name : r0_result_left_to_chooser
// size : 100
// sig  : int r0_result_left_to_chooser(gen_node * node, tmpl_header * tmpl)


int __cdecl r0_result_left_to_chooser(gen_node *node,tmpl_header *tmpl)

{
  il_op op;
  
  if (node->desc->pref_regs != 1) {
    return 0;
  }
  op = node->op;
  if (op == IL_MUL) {
    if (((tmpl != (tmpl_header *)&g_tmpl_amul005) && (tmpl != (tmpl_header *)&g_tmpl_amul007)) &&
       (tmpl != (tmpl_header *)&g_tmpl_amul008)) {
      return 1;
    }
    return 0;
  }
  if (((('7' < (char)op) && ((char)op < '>')) || (('O' < (char)op && ((char)op < '`')))) &&
     (((node->type & 0xe0) == 0 || ((node->type & 0xf8) == 0x40)))) {
    return 1;
  }
  return 0;
}



