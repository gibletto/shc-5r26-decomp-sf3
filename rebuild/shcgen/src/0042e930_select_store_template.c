#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 0042e930
// name : select_store_template
// size : 1330
// sig  : tmpl_header * select_store_template(ea * src, ea * dst, ea * temp, uchar type)


tmpl_header * __cdecl select_store_template(ea *src,ea *dst,ea *temp,uchar type)

{
  uint labno;
  label_ref *dst_labels;
  byte bVar1;
  tmpl_header *chosen_tmpl;
  short cpu;
  
  bVar1 = dst->type & 0x1f;
  if (bVar1 == 0xd) {
    cpu = g_request->cpu;
    if ((cpu != 2) || (bVar1 = 1, g_request->fpu_mode != '\x03')) {
      bVar1 = -(cpu == 4) & 2;
    }
    if ((bVar1 != 0) && ((type & 0xf8) == 0x28)) {
      return (tmpl_header *)&g_tmpl_ast010;
    }
    if ((cpu != 4) || ((type & 0xf8) != 0x30)) {
      dst_labels = dst->labels;
      labno = 0;
      if (dst_labels != (label_ref *)0x0) {
        labno = (uint)dst_labels->labno1;
      }
      if ((g_symbol_table[(labno ^ (int)labno >> 0x1f) - ((int)labno >> 0x1f)].attr & 3) == 0) {
        return (tmpl_header *)&g_tmpl_ast001;
      }
      if (((src->type & 0x1f) == 1) && (src->base == '\0')) {
        dst_labels = combine_label_ref_lists(dst_labels,(label_ref *)&g_gbr_base_label_ref,1);
        free_label_ref_list(dst->labels);
        dst->labels = dst_labels;
        dst->base = 'b';
        dst->type = dst->type & 0xfb | 0xb;
        return (tmpl_header *)&g_tmpl_ast000;
      }
      if (((temp->type & 0x1f) == 1) && (temp->base == '\0')) {
        dst_labels = combine_label_ref_lists(dst_labels,(label_ref *)&g_gbr_base_label_ref,1);
        free_label_ref_list(dst->labels);
        dst->labels = dst_labels;
        dst->base = 'b';
        dst->type = dst->type & 0xfb | 0xb;
        return (tmpl_header *)&g_tmpl_ast005;
      }
      return (tmpl_header *)&g_tmpl_ast001;
    }
    chosen_tmpl = (tmpl_header *)&g_tmpl_ast016;
    if (g_request->unknown_028[2] != '\0') {
      return (tmpl_header *)&g_tmpl_ast022;
    }
  }
  else if (((bVar1 == 2) && (dst->base == 'l')) || ((bVar1 == 8 && (dst->base == 'l')))) {
    cpu = g_request->cpu;
    if ((cpu != 2) || (bVar1 = 1, g_request->fpu_mode != '\x03')) {
      bVar1 = -(cpu == 4) & 2;
    }
    if ((bVar1 != 0) && ((type & 0xf8) == 0x28)) {
      return (tmpl_header *)&g_tmpl_ast011;
    }
    if ((cpu != 4) || ((type & 0xf8) != 0x30)) {
      return (tmpl_header *)&g_tmpl_ast002;
    }
    chosen_tmpl = (tmpl_header *)&g_tmpl_ast017;
    if (g_request->unknown_028[2] != '\0') {
      return (tmpl_header *)&g_tmpl_ast028;
    }
  }
  else if (((((bVar1 == 1) || (bVar1 == 3)) || (bVar1 == 2)) ||
           (((bVar1 == 8 && (dst->disp == 0)) && (dst->labels == (label_ref *)0x0)))) ||
          (bVar1 == 9)) {
    cpu = g_request->cpu;
    if ((cpu != 4) || ((type & 0xf8) != 0x30)) {
      if ((cpu == 2) && (g_request->fpu_mode == '\x03')) {
        bVar1 = 1;
      }
      else {
        bVar1 = -(cpu == 4) & 2;
      }
      if ((bVar1 != 0) && ((type & 0xf8) == 0x28)) {
        return (tmpl_header *)&g_tmpl_ast012;
      }
      return (tmpl_header *)&g_tmpl_ast000;
    }
    if (bVar1 == 1) {
      return (tmpl_header *)&g_tmpl_ast018;
    }
    if (bVar1 == 9) {
      chosen_tmpl = (tmpl_header *)&g_tmpl_ast016;
      if (g_request->unknown_028[2] != '\0') {
        return (tmpl_header *)&g_tmpl_ast022;
      }
    }
    else if ((bVar1 == 2) ||
            (((bVar1 == 8 && (dst->disp == 0)) && (dst->labels == (label_ref *)0x0)))) {
      chosen_tmpl = (tmpl_header *)&g_tmpl_ast023;
      if (g_request->unknown_028[2] != '\0') {
        return (tmpl_header *)&g_tmpl_ast024;
      }
    }
    else if ((bVar1 == 3) &&
            (chosen_tmpl = (tmpl_header *)&g_tmpl_ast029, g_request->unknown_028[2] != '\0')) {
      return (tmpl_header *)&g_tmpl_ast030;
    }
  }
  else {
    if ((bVar1 != 2) && (bVar1 != 8)) {
      report_codegen_message(0x122c,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
      return chosen_tmpl;
    }
    cpu = g_request->cpu;
    if ((cpu != 2) || (bVar1 = 1, g_request->fpu_mode != '\x03')) {
      bVar1 = -(cpu == 4) & 2;
    }
    if ((bVar1 == 0) || ((type & 0xf8) != 0x28)) {
      if ((cpu != 4) || ((type & 0xf8) != 0x30)) {
        if ((temp == (ea *)0x0) || (temp->base == -1)) {
          return (tmpl_header *)&g_tmpl_ast000;
        }
        if (temp->base != '\0') {
          return (tmpl_header *)&g_tmpl_ast009;
        }
        if ((dst->labels == (label_ref *)0x0) &&
           ((((((bVar1 = type & 0xe0, bVar1 == 0x60 || (bVar1 == 0x80)) && ((type & 0x18) == 0)) ||
              ((type & 0xf8) == 0)) && ((0 < dst->disp && (dst->disp < 0x10)))) ||
            (((((bVar1 == 0x60 || (bVar1 == 0x80)) && ((type & 0x18) == 8)) || ((type & 0xf8) == 8))
             && ((0 < dst->disp && (dst->disp < 0x1f)))))))) {
          return (tmpl_header *)&g_tmpl_ast005;
        }
        return (tmpl_header *)&g_tmpl_ast003;
      }
      if (temp->base == '\0') {
        chosen_tmpl = (tmpl_header *)&g_tmpl_ast019;
        if (g_request->unknown_028[2] != '\0') {
          return (tmpl_header *)&g_tmpl_ast025;
        }
      }
      else if (dst->base == '\0') {
        chosen_tmpl = (tmpl_header *)&g_tmpl_ast020;
        if (g_request->unknown_028[2] != '\0') {
          return (tmpl_header *)&g_tmpl_ast026;
        }
      }
      else {
        chosen_tmpl = (tmpl_header *)&g_tmpl_ast021;
        if (g_request->unknown_028[2] != '\0') {
          return (tmpl_header *)&g_tmpl_ast027;
        }
      }
    }
    else {
      if (temp->base == '\0') {
        return (tmpl_header *)&g_tmpl_ast013;
      }
      chosen_tmpl = (tmpl_header *)&g_tmpl_ast014;
      if (dst->base != '\0') {
        return (tmpl_header *)&g_tmpl_ast015;
      }
    }
  }
  return chosen_tmpl;
}



