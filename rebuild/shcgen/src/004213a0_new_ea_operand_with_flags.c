#include "decls.h"
#include "imports.h"

// entry: 004213a0
// name : new_ea_operand_with_flags
// size : 110
// sig  : ea * new_ea_operand_with_flags(uchar kind, char base, char index, int disp, uchar type_flags, label_ref * labels)


ea * __cdecl
new_ea_operand_with_flags
          (uchar kind,char base,char index,int disp,uchar type_flags,label_ref *labels)

{
  ea *operand;
  
  operand = alloc_zeroed(0xc);
  if (operand != (ea *)0x0) {
    fill_ea(operand,type_flags | kind,base,index,'\0',disp,labels);
    return operand;
  }
  report_codegen_message(0xbcd,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
  return (ea *)0x0;
}



