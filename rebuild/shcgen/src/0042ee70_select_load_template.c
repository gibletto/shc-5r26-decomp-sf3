#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 0042ee70
// name : select_load_template
// size : 1678
// sig  : tmpl_header * select_load_template(ea * src, ea * dst, ea * temp, uchar type)


tmpl_header * __cdecl select_load_template(ea *src,ea *dst,ea *temp,uchar type)

{
  uint labno;
  label_ref *src_labels;
  byte bVar1;
  tmpl_header *chosen_tmpl;
  short cpu;
  
  bVar1 = src->type & 0x1f;
  if (bVar1 == 0xd) {
    cpu = g_request->cpu;
    if ((cpu != 2) || (bVar1 = 1, g_request->fpu_mode != '\x03')) {
      bVar1 = -(cpu == 4) & 2;
    }
    if ((bVar1 != 0) && ((type & 0xf8) == 0x28)) {
      return (tmpl_header *)&g_tmpl_ald021;
    }
    if ((cpu != 4) || ((type & 0xf8) != 0x30)) {
      src_labels = src->labels;
      labno = 0;
      if (src_labels != (label_ref *)0x0) {
        labno = (uint)src_labels->labno1;
      }
      if ((g_symbol_table[(labno ^ (int)labno >> 0x1f) - ((int)labno >> 0x1f)].attr & 3) == 0) {
        return (tmpl_header *)&g_tmpl_ald001;
      }
      if (((dst->type & 0x1f) == 1) && (dst->base == '\0')) {
        src_labels = combine_label_ref_lists(src_labels,(label_ref *)&g_gbr_base_label_ref,1);
        free_label_ref_list(src->labels);
        src->labels = src_labels;
        src->base = 'b';
        src->type = src->type & 0xfb | 0xb;
        return (tmpl_header *)&g_tmpl_ald000;
      }
      if (((temp->type & 0x1f) == 1) && (temp->base == '\0')) {
        src_labels = combine_label_ref_lists(src_labels,(label_ref *)&g_gbr_base_label_ref,1);
        free_label_ref_list(src->labels);
        src->labels = src_labels;
        src->base = 'b';
        src->type = src->type & 0xfb | 0xb;
        return (tmpl_header *)&g_tmpl_ald009;
      }
      return (tmpl_header *)&g_tmpl_ald001;
    }
    chosen_tmpl = (tmpl_header *)&g_tmpl_ald030;
    if (g_request->unknown_028[2] != '\0') {
      return (tmpl_header *)&g_tmpl_ald037;
    }
  }
  else if (((bVar1 == 2) && (src->base == 'l')) || ((bVar1 == 8 && (src->base == 'l')))) {
    if ((g_request->cpu != 4) || ((type & 0xf8) != 0x30)) {
      return (tmpl_header *)&g_tmpl_ald003;
    }
    chosen_tmpl = (tmpl_header *)&g_tmpl_ald031;
    if (g_request->unknown_028[2] != '\0') {
      return (tmpl_header *)&g_tmpl_ald044;
    }
  }
  else if (((((bVar1 == 1) || (bVar1 == 4)) || (bVar1 == 2)) ||
           (((bVar1 == 8 && (src->disp == 0)) && (src->labels == (label_ref *)0x0)))) ||
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
        return (tmpl_header *)&g_tmpl_ald023;
      }
      return (tmpl_header *)&g_tmpl_ald000;
    }
    if (bVar1 == 1) {
      return (tmpl_header *)&g_tmpl_ald032;
    }
    if (bVar1 == 9) {
      chosen_tmpl = (tmpl_header *)&g_tmpl_ald030;
      if (g_request->unknown_028[2] != '\0') {
        return (tmpl_header *)&g_tmpl_ald037;
      }
    }
    else if ((bVar1 == 2) ||
            (((bVar1 == 8 && (src->disp == 0)) && (src->labels == (label_ref *)0x0)))) {
      chosen_tmpl = (tmpl_header *)&g_tmpl_ald038;
      if (g_request->unknown_028[2] != '\0') {
        return (tmpl_header *)&g_tmpl_ald039;
      }
    }
    else if ((bVar1 == 4) &&
            (chosen_tmpl = (tmpl_header *)&g_tmpl_ald045, g_request->unknown_028[2] != '\0')) {
      return (tmpl_header *)&g_tmpl_ald046;
    }
  }
  else if ((bVar1 == 7) || (bVar1 == 0xe)) {
    cpu = g_request->cpu;
    if ((cpu != 2) || (bVar1 = 1, g_request->fpu_mode != '\x03')) {
      bVar1 = -(cpu == 4) & 2;
    }
    if ((bVar1 == 0) || ((type & 0xf8) != 0x28)) {
      if ((cpu != 4) || ((type & 0xf8) != 0x30)) {
        return (tmpl_header *)&g_tmpl_ald014;
      }
      chosen_tmpl = (tmpl_header *)&g_tmpl_ald033;
      if (g_request->unknown_028[2] != '\0') {
        return (tmpl_header *)&g_tmpl_ald043;
      }
    }
    else {
      if (g_float_one_bits == src->disp) {
        return (tmpl_header *)&g_tmpl_ald028;
      }
      chosen_tmpl = (tmpl_header *)&g_tmpl_ald029;
      if (g_float_zero_bits != src->disp) {
        return (tmpl_header *)&g_tmpl_ald024;
      }
    }
  }
  else {
    if ((bVar1 != 2) && (bVar1 != 8)) {
      report_codegen_message(0x122d,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
      return chosen_tmpl;
    }
    cpu = g_request->cpu;
    if ((cpu != 2) || (bVar1 = 1, g_request->fpu_mode != '\x03')) {
      bVar1 = -(cpu == 4) & 2;
    }
    if ((bVar1 == 0) || ((type & 0xf8) != 0x28)) {
      if ((cpu == 4) && ((type & 0xf8) == 0x30)) {
        if (temp->base == '\0') {
          chosen_tmpl = (tmpl_header *)&g_tmpl_ald034;
          if (g_request->unknown_028[2] != '\0') {
            return (tmpl_header *)&g_tmpl_ald040;
          }
        }
        else if (src->base == '\0') {
          chosen_tmpl = (tmpl_header *)&g_tmpl_ald036;
          if (g_request->unknown_028[2] != '\0') {
            return (tmpl_header *)&g_tmpl_ald042;
          }
        }
        else {
          chosen_tmpl = (tmpl_header *)&g_tmpl_ald035;
          if (g_request->unknown_028[2] != '\0') {
            return (tmpl_header *)&g_tmpl_ald041;
          }
        }
      }
      else {
        if ((temp == (ea *)0x0) || (temp->base == -1)) {
          if ((src->labels == (label_ref *)0x0) &&
             (((((((bVar1 = type & 0xe0, bVar1 == 0x60 || (bVar1 == 0x80)) &&
                  ((type & 0x18) == 0x10)) || (((type & 0xf8) == 0x10 || ((type & 0xf8) == 0x18))))
                || ((bVar1 == 0x20 || (bVar1 == 0x40)))) && ((0 < src->disp && (src->disp < 0x3d))))
              || (((((((bVar1 == 0x60 || (bVar1 == 0x80)) && ((type & 0x18) == 0)) ||
                     ((type & 0xf8) == 0)) && ((0 < src->disp && (src->disp < 0x10)))) ||
                   (((((bVar1 == 0x60 || (bVar1 == 0x80)) && ((type & 0x18) == 8)) ||
                     ((type & 0xf8) == 8)) && ((0 < src->disp && (src->disp < 0x1f)))))) &&
                  ((src->base == '\0' && (dst->base == '\0')))))))) {
            return (tmpl_header *)&g_tmpl_ald000;
          }
          return (tmpl_header *)&g_tmpl_ald002;
        }
        if (temp->base == '\0') {
          if ((src->labels == (label_ref *)0x0) &&
             ((((((bVar1 = type & 0xe0, bVar1 == 0x60 || (bVar1 == 0x80)) && ((type & 0x18) == 0))
                || ((type & 0xf8) == 0)) && ((0 < src->disp && (src->disp < 0x10)))) ||
              (((((bVar1 == 0x60 || (bVar1 == 0x80)) && ((type & 0x18) == 8)) ||
                ((type & 0xf8) == 8)) && ((0 < src->disp && (src->disp < 0x1f)))))))) {
            return (tmpl_header *)&g_tmpl_ald009;
          }
          return (tmpl_header *)&g_tmpl_ald005;
        }
        chosen_tmpl = (tmpl_header *)&g_tmpl_ald016;
        if (src->base == '\0') {
          return (tmpl_header *)&g_tmpl_ald020;
        }
      }
    }
    else {
      if (temp->base == '\0') {
        return (tmpl_header *)&g_tmpl_ald025;
      }
      chosen_tmpl = (tmpl_header *)&g_tmpl_ald027;
      if (src->base != '\0') {
        return (tmpl_header *)&g_tmpl_ald026;
      }
    }
  }
  return chosen_tmpl;
}



