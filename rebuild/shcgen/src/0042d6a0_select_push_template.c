#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 0042d6a0
// name : select_push_template
// size : 1830
// sig  : tmpl_header * select_push_template(uchar type, ea * src, char usage, gen_node * node)


tmpl_header * __cdecl select_push_template(uchar type,ea *src,char usage,gen_node *node)

{
  byte src_kind;
  int iVar1;
  int variant;
  uint uVar2;
  byte type_class;
  int max_disp;
  uint sign;
  byte bVar3;
  tmpl_header *tmpl;
  tmpl_header *local_8;
  short cpu;
  label_ref *sym_ref;
  
  bVar3 = type & 0xe0;
  if ((((bVar3 == 0) || (bVar3 == 0x40)) || (bVar3 == 0x80)) ||
     (type_class = type & 0xf8, type_class == 0x28)) {
    cpu = g_request->cpu;
    if ((src->type & 0x1f) == 1) {
      if ((cpu == 2) && (g_request->fpu_mode == '\x03')) {
        bVar3 = 1;
      }
      else {
        bVar3 = -(cpu == 4) & 2;
      }
      if ((bVar3 != 0) && ((type & 0xf8) == 0x28)) {
        return (tmpl_header *)&g_tmpl_apush020;
      }
      return (tmpl_header *)&g_tmpl_apush001;
    }
    if ((cpu == 2) && (g_request->fpu_mode == '\x03')) {
      bVar3 = 1;
    }
    else {
      bVar3 = -(cpu == 4) & 2;
    }
    if ((bVar3 != 0) && ((type & 0xf8) == 0x28)) {
      return (tmpl_header *)&g_tmpl_apush021;
    }
    return (tmpl_header *)&g_tmpl_apush002;
  }
  if ((type_class == 0x30) || (type_class == 0x38)) {
    if (g_request->cpu == 4) {
      if ((src->type & 0x1f) != 1) {
        if (g_request->unknown_028[2] == '\0') {
          return (tmpl_header *)&g_tmpl_apush023;
        }
        return (tmpl_header *)&g_tmpl_apush025;
      }
      if (g_request->unknown_028[2] == '\0') {
        return (tmpl_header *)&g_tmpl_apush022;
      }
      return (tmpl_header *)&g_tmpl_apush024;
    }
    bVar3 = src->type & 0x1f;
    if (bVar3 == 0xd) {
      if (src->labels == (label_ref *)0x0) {
        uVar2 = 0;
      }
      else {
        uVar2 = (uint)src->labels->labno1;
      }
      if ((g_symbol_table[(uVar2 ^ (int)uVar2 >> 0x1f) - ((int)uVar2 >> 0x1f)].attr & 3) != 0) {
        return (tmpl_header *)&g_tmpl_apush018;
      }
      return (tmpl_header *)&g_tmpl_apush003;
    }
    if (((bVar3 == 2) && (src->base == 'l')) || ((bVar3 == 8 && (src->base == 'l')))) {
      return (tmpl_header *)&g_tmpl_apush004;
    }
    if (bVar3 == 0xe) {
      if (g_request->unknown_028[2] == '\0') {
        return (tmpl_header *)&g_tmpl_apush005;
      }
      return (tmpl_header *)&g_tmpl_apush019;
    }
    if ((bVar3 != 2) && (bVar3 != 8)) {
      report_codegen_message(0x11ff,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
      return local_8;
    }
    if (src->labels == (label_ref *)0x0) {
      if (src->disp == 0) {
        return (tmpl_header *)&g_tmpl_apush006;
      }
      uVar2 = src->disp;
      if (((0 < (int)uVar2) && ((int)uVar2 < 0x39)) &&
         (sign = (int)uVar2 >> 0x1f, ((uVar2 ^ sign) - sign & 3 ^ sign) == sign)) {
        return (tmpl_header *)&g_tmpl_apush007;
      }
    }
    if (((src->labels != (label_ref *)0x0) || (src->disp < -0x80)) || (0x7f < src->disp)) {
      bVar3 = src->base;
      if ((((((char)bVar3 < '\x0f') && ((1 << (bVar3 & 0x1f) & (int)(short)~g_var_gpr_mask) != 0))
           || (((char)bVar3 < ' ' &&
               (('\x0f' < (char)bVar3 &&
                (((int)(short)~g_var_fpr_mask & 1 << (bVar3 - 0x10 & 0x1f)) != 0)))))) ||
          (((char)bVar3 < '/' &&
           (('\x1f' < (char)bVar3 &&
            (((int)(short)g_var_fpr_mask & (1 << (bVar3 - 0x1f & 0x1f) | 1 << (bVar3 - 0x20 & 0x1f))
             ) == 0)))))) && (usage != '\x03')) {
        return (tmpl_header *)&g_tmpl_apush010;
      }
      return (tmpl_header *)&g_tmpl_apush011;
    }
    bVar3 = src->base;
    if ((((((char)bVar3 < '\x0f') && ((1 << (bVar3 & 0x1f) & (int)(short)~g_var_gpr_mask) != 0)) ||
         (((char)bVar3 < ' ' &&
          (('\x0f' < (char)bVar3 &&
           (((int)(short)~g_var_fpr_mask & 1 << (bVar3 - 0x10 & 0x1f)) != 0)))))) ||
        (((char)bVar3 < '/' &&
         (('\x1f' < (char)bVar3 &&
          (((int)(short)g_var_fpr_mask & (1 << (bVar3 - 0x1f & 0x1f) | 1 << (bVar3 - 0x20 & 0x1f)))
           == 0)))))) && (usage != '\x03')) {
      return (tmpl_header *)&g_tmpl_apush008;
    }
    return (tmpl_header *)&g_tmpl_apush009;
  }
  tmpl = (tmpl_header *)0x0;
  uVar2 = node->val;
  if (((((((bVar3 == 0x60) || (bVar3 == 0x80)) && ((type & 0x18) == 0)) || (type_class == 0)) &&
       (uVar2 == 1)) ||
      (((((bVar3 == 0x60 || (bVar3 == 0x80)) && ((type & 0x18) == 8)) || (type_class == 8)) &&
       (uVar2 == 2)))) ||
     (((((bVar3 == 0x60 || (bVar3 == 0x80)) && ((type & 0x18) == 0x10)) ||
       ((((type_class == 0x10 || (type_class == 0x18)) || (bVar3 == 0x20)) || (bVar3 == 0x40)))) &&
      (uVar2 == 4)))) {
    tmpl = (tmpl_header *)&g_tmpl_apush017;
    goto LAB_0042da40;
  }
  if (g_request->switch_density_rule == 0) goto LAB_0042da40;
  if (((((bVar3 == 0x60) || (bVar3 == 0x80)) && ((type & 0x18) == 0x10)) ||
      (((type_class == 0x10 || (type_class == 0x18)) || ((bVar3 == 0x20 || (bVar3 == 0x40)))))) &&
     ((int)uVar2 < 0x41)) {
LAB_0042d9fd:
    if (((src == (ea *)0x0) || ((bVar3 = src->type & 0x1f, bVar3 != 2 && (bVar3 != 8)))) ||
       ((src->labels != (label_ref *)0x0 ||
        ((src->base == 'l' || (iVar1 = 0, 0x3c < (int)(src->disp + uVar2 + -4))))))) {
      iVar1 = 1;
    }
    tmpl = (tmpl_header *)(&g_push_long_copy_templates)[iVar1];
    goto LAB_0042da40;
  }
  if ((((((bVar3 == 0x60) || (bVar3 == 0x80)) && ((type & 0x18) == 0)) || (type_class == 0)) ||
      ((((bVar3 == 0x60 || (bVar3 == 0x80)) && ((type & 0x18) == 8)) || (type_class == 8)))) &&
     (((int)uVar2 < 0x41 && (sign = (int)uVar2 >> 0x1f, ((uVar2 ^ sign) - sign & 3 ^ sign) == sign))
     )) {
    src_kind = src->type & 0x1f;
    if ((((src_kind == 2) && (src->base == 'l')) || ((src_kind == 8 && (src->base == 'l')))) &&
       (sign = src->disp >> 0x1f, ((src->disp ^ sign) - sign & 3 ^ sign) == sign))
    goto LAB_0042d9fd;
    if (src_kind == 0xd) {
      if ((src->labels == (label_ref *)0x0) &&
         (sign = src->disp >> 0x1f, ((src->disp ^ sign) - sign & 3 ^ sign) == sign))
      goto LAB_0042d9fd;
      sym_ref = src->labels;
      if ((sym_ref != (label_ref *)0x0) && (sym_ref->labno2 == 0)) {
        iVar1 = 0;
        if (sym_ref != (label_ref *)0x0) {
          iVar1 = (int)sym_ref->labno1;
        }
        if (g_symbol_table[iVar1].sclass != '\x03') {
          iVar1 = 0;
          if (sym_ref != (label_ref *)0x0) {
            iVar1 = (int)sym_ref->labno1;
          }
          if (g_symbol_table[iVar1].sclass != '\x01') {
            iVar1 = 0;
            if (sym_ref != (label_ref *)0x0) {
              iVar1 = (int)sym_ref->labno1;
            }
            if (g_symbol_table[iVar1].sclass != '\t') {
              iVar1 = 0;
              if (sym_ref != (label_ref *)0x0) {
                iVar1 = (int)sym_ref->labno1;
              }
              if (g_symbol_table[iVar1].sclass != '\x04') goto LAB_0042d936;
            }
          }
        }
        iVar1 = 0;
        if (sym_ref != (label_ref *)0x0) {
          iVar1 = (int)sym_ref->labno1;
        }
        if ((g_symbol_table[iVar1].frame_offset + src->disp & 3U) == 0) goto LAB_0042d9fd;
      }
    }
  }
LAB_0042d936:
  if ((((((bVar3 != 0x60) && (bVar3 != 0x80)) || ((type & 0x18) != 0)) && (type_class != 0)) ||
      (0x10 < (int)uVar2)) &&
     (((((bVar3 != 0x60 && (bVar3 != 0x80)) || ((type & 0x18) != 8)) && (type_class != 8)) ||
      (0x20 < (int)uVar2)))) goto LAB_0042da40;
  if (((src == (ea *)0x0) || ((src_kind = src->type & 0x1f, src_kind != 2 && (src_kind != 8)))) ||
     ((src->base == '\0' || ((src->labels != (label_ref *)0x0 || (src->base == 'l')))))) {
LAB_0042d9eb:
    variant = 1;
  }
  else {
    if ((((bVar3 == 0x60) || (bVar3 == 0x80)) && ((type & 0x18) == 0)) ||
       (iVar1 = 2, type_class == 0)) {
      iVar1 = 1;
    }
    if ((((bVar3 == 0x60) || (bVar3 == 0x80)) && ((type & 0x18) == 0)) ||
       (max_disp = 0x1e, type_class == 0)) {
      max_disp = 0xf;
    }
    variant = 0;
    if (max_disp < (int)((src->disp - iVar1) + uVar2)) goto LAB_0042d9eb;
  }
  tmpl = (tmpl_header *)(&g_push_short_copy_templates)[variant];
LAB_0042da40:
  if (tmpl != (tmpl_header *)0x0) {
    return tmpl;
  }
  return (tmpl_header *)&g_tmpl_apush012;
}



