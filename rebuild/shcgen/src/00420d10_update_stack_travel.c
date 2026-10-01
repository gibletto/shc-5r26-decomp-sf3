#include "decls.h"
#include "imports.h"

// entry: 00420d10
// name : update_stack_travel
// size : 244
// sig  : void update_stack_travel(int is_call, int call_adjust, psd * rec)


int __cdecl update_stack_travel(int is_call,int call_adjust,psd *rec)

{
  byte size_code;
  int nbytes;
  int local_4;
  ea *opnd;
  
  if (is_call == 0) {
    if ((((rec->op == OP_ADD) && ((rec->ea1->type & 0x1f) == 7)) && ((rec->ea2->type & 0x1f) == 1))
       && (rec->ea2->base == '\x0f')) {
      g_sptravel = g_sptravel - rec->ea1->disp;
    }
    else {
      size_code = rec->flg & 3;
      if (size_code == 0) {
        nbytes = 1;
      }
      else if (size_code == 1) {
        nbytes = 2;
      }
      else {
        nbytes = 4;
        if (size_code != 2) {
          nbytes = local_4;
        }
      }
      opnd = rec->ea1;
      if (((opnd != (ea *)0x0) && ((opnd->type & 0x1f) == 4)) && (opnd->base == '\x0f')) {
        g_sptravel = g_sptravel - nbytes;
      }
      opnd = rec->ea2;
      if (((opnd != (ea *)0x0) && ((opnd->type & 0x1f) == 3)) && (opnd->base == '\x0f')) {
        g_sptravel = g_sptravel + nbytes;
      }
    }
  }
  else {
    g_sptravel = g_sptravel + call_adjust;
  }
  if (g_max_sptravel < (uint)g_sptravel) {
    g_max_sptravel = g_sptravel;
  }
  if (g_sptravel < 0) {
    report_codegen_message(0xc84,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
  }
  return;
}



