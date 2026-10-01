#include "decls.h"
#include "imports.h"

// entry: 0040faa0
// name : check_builtin_immediate_argument
// size : 512
// sig  : void check_builtin_immediate_argument(gen_node * args)


int __cdecl check_builtin_immediate_argument(gen_node *args)

{
  uchar *puVar1;
  int arg_count;
  gen_node *imm_arg;
  uint uVar2;
  byte info_flags;
  
  info_flags = (&g_builtin_info)[args->parent->desc->builtin * 8];
  if ((info_flags & 7) == 7) {
    arg_count = count_operands(args);
    uVar2 = arg_count - 1;
  }
  else {
    uVar2 = (uint)(info_flags & 7);
  }
  imm_arg = nth_operand(args,uVar2);
  if (imm_arg->desc->opnd_class != '\x02') {
    report_codegen_message(0xaf1,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    imm_arg->op = IL_CONST;
    imm_arg->val = 0;
    puVar1 = &imm_arg->desc->flags3;
    *puVar1 = *puVar1 | 0x80;
    imm_arg->desc->opnd_class = '\x02';
    fill_ea(&imm_arg->desc->value,'\a',-1,-1,'\0',imm_arg->val,(label_ref *)0x0);
  }
  uVar2 = (imm_arg->desc->value).disp;
  if ((info_flags & 0x20) == 0) {
    if ((info_flags & 0x10) == 0) {
      if (((int)uVar2 < 0) || (0x3fc < (int)uVar2)) {
        uVar2 = uVar2 & 0x3fc;
        report_codegen_message(0xaf2,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
      }
      else if ((uVar2 & 3) != 0) {
        uVar2 = uVar2 & 0xfffffffc;
        report_codegen_message(0xaf3,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
      }
    }
    else if (((int)uVar2 < 0) || (0x1fe < (int)uVar2)) {
      uVar2 = uVar2 & 0x1fe;
      report_codegen_message(0xaf2,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    }
    else if ((uVar2 & 1) != 0) {
      uVar2 = uVar2 & 0xfffffffe;
      report_codegen_message(0xaf3,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    }
  }
  else if (((int)uVar2 < 0) || (0xff < (int)uVar2)) {
    uVar2 = uVar2 & 0xff;
    report_codegen_message(0xaf2,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
  }
  if ((imm_arg->desc->value).disp != uVar2) {
    fill_ea(&imm_arg->desc->value,'\a',-1,-1,'\0',uVar2,(label_ref *)0x0);
  }
  return;
}



