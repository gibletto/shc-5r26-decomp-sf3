#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 004293c0
// name : select_cpu_variant_template
// size : 283
// sig  : short select_cpu_variant_template(gen_node * node, void * variants, tmpl_header * * tmpl_out, void * * select_out, short found)


short __cdecl
select_cpu_variant_template
          (gen_node *node,void *variants,tmpl_header **tmpl_out,void **select_out,short found)

{
  byte fpu_level;
  int fits_16bit;
  tmpl_header *tmpl;
  undefined4 *variant;
  bool done;
  
  variant = (undefined4 *)((int)variants + 4);
  done = false;
  do {
    switch(*(undefined1 *)(variant + -1)) {
    default:
      report_codegen_message(0x1238,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
      break;
    case 1:
      if ((node->op == IL_MUL) && (fits_16bit = mul_fits_16bit_multiply(node), fits_16bit != 0)) {
        tmpl = (tmpl_header *)*variant;
        if (*(char *)((int)variant + -3) != '\x01') goto LAB_004294bf;
        found = 0;
        *tmpl_out = tmpl;
        goto LAB_004294c1;
      }
      break;
    case 2:
      if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
        fpu_level = 1;
      }
      else {
        fpu_level = -(g_request->cpu == 4) & 2;
      }
      if (fpu_level != 0) {
        tmpl = (tmpl_header *)*variant;
        if (*(char *)((int)variant + -3) != '\x01') goto LAB_004294bf;
        found = 0;
        *tmpl_out = tmpl;
        goto LAB_004294c1;
      }
      break;
    case 3:
      if (g_request->cpu == 4) {
        tmpl = (tmpl_header *)*variant;
        if (*(char *)((int)variant + -3) != '\x01') goto LAB_004294bf;
        found = 0;
        *tmpl_out = tmpl;
        goto LAB_004294c1;
      }
      break;
    case 0xff:
      tmpl = (tmpl_header *)*variant;
      if (*(char *)((int)variant + -3) == '\x01') {
        found = 0;
        *tmpl_out = tmpl;
      }
      else {
LAB_004294bf:
        *select_out = tmpl;
      }
LAB_004294c1:
      done = true;
    }
    variant = variant + 2;
    if (done) {
      return found;
    }
  } while( true );
}



