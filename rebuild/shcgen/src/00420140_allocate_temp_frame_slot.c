#include "decls.h"
#include "imports.h"

// entry: 00420140
// name : allocate_temp_frame_slot
// size : 157
// sig  : void allocate_temp_frame_slot(gen_node * node, uint size, ea * out)


int __cdecl allocate_temp_frame_slot(gen_node *node,uint size,ea *out)

{
  int iVar1;
  int *frame_field;
  uint sign;
  
  sign = (int)size >> 0x1f;
  iVar1 = ((size ^ sign) - sign & 3 ^ sign) - sign;
  if (iVar1 != 0) {
    size = (size - iVar1) + 4;
  }
  iVar1 = node->desc->frame_top - size;
  node->desc->frame_top = iVar1;
  if ((g_max_temp_frame + size & 0x80000000) != 0) {
    report_codegen_message(0xc84,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
  }
  if (g_max_temp_frame < (uint)(g_frame_end - iVar1)) {
    g_max_temp_frame = g_frame_end - iVar1;
  }
  frame_field = &node->desc->frame_low;
  if (iVar1 < *frame_field) {
    *frame_field = iVar1;
  }
  fill_ea(out,'\b','l',-1,'\0',iVar1,(label_ref *)0x0);
  return;
}



