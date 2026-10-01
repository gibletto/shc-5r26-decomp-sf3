#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00414410
// name : copy_ea
// size : 157
// sig  : ea * copy_ea(ea * src)


ea * __cdecl copy_ea(ea *src)

{
  ea *new_ea;
  label_ref *labels;
  
  if (((byte)g_stage_flags & 4) != 0) {
    _printf(s_cpyea_start__eaptr__08lx_00427940,src);
    dump_memory_hex(&src->type,s_input_eatbl_00427934,0xc);
  }
  if (src == (ea *)0x0) {
    return (ea *)0x0;
  }
  new_ea = (ea *)alloc_zeroed_flushing_blocks(0xc);
  new_ea->type = src->type;
  new_ea->base = src->base;
  new_ea->index = src->index;
  new_ea->misc = src->misc;
  new_ea->disp = src->disp;
  if (src->labels != (label_ref *)0x0) {
    labels = copy_label_ref_list(src->labels);
    new_ea->labels = labels;
  }
  if (((byte)g_stage_flags & 4) != 0) {
    dump_memory_hex((uchar *)new_ea,s_output_eatbl_00427924,0xc);
    _printf(s_cpyea_end__eap__08lx_0042790c,new_ea);
  }
  return new_ea;
}



