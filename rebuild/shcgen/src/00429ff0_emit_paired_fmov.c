#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 00429ff0
// name : emit_paired_fmov
// size : 189
// sig  : void emit_paired_fmov(gen_node * node, ea * src, ea * dst)


int __cdecl emit_paired_fmov(gen_node *node,ea *src,ea *dst)

{
  ea *peVar1;
  ea *peVar2;
  ea *peVar3;
  gen_node *pgVar4;
  
  peVar1 = copy_ea(src);
  peVar2 = copy_ea(src);
  peVar1->base = peVar1->base + -0x10;
  peVar2->base = peVar2->base + -0xf;
  if (g_request->unknown_028[2] == '\0') {
    pgVar4 = node;
    peVar3 = copy_ea(dst);
    emit_psd_for_node(0xb0,-1,'\0','\x02',peVar1,peVar3,pgVar4);
    peVar1 = copy_ea(dst);
    emit_psd_for_node(0xb0,-1,'\0','\x02',peVar2,peVar1,node);
    return;
  }
  pgVar4 = node;
  peVar3 = copy_ea(dst);
  emit_psd_for_node(0xb0,-1,'\0','\x02',peVar2,peVar3,pgVar4);
  peVar2 = copy_ea(dst);
  emit_psd_for_node(0xb0,-1,'\0','\x02',peVar1,peVar2,node);
  return;
}



