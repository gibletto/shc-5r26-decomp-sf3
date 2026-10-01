#include "decls.h"
#include "imports.h"

// entry: 00404b20
// name : new_label_operand
// size : 108
// sig  : ea * new_label_operand(short labno)


ea * __cdecl new_label_operand(short labno)

{
  label_ref *ref;
  ea *operand;
  undefined4 local_4;
  
  ref = alloc_zeroed(8);
  if (ref != (label_ref *)0x0) {
    fill_label_ref(ref,labno,0);
    operand = new_ea_operand_with_flags('\a',-1,-1,0,'\0',ref);
    return operand;
  }
  report_codegen_message(0xbcd,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
  return local_4;
}



