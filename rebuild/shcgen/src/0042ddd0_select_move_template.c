#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_amv_block_templates
#define g_amv_block_templates (*(unsigned char * *)(g_sd + 0x1c160))
#undef g_amv_copy_templates
#define g_amv_copy_templates (*(unsigned char * *)(g_sd + 0x1c170))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 0042ddd0
// name : select_move_template
// size : 2444
// sig  : tmpl_header * select_move_template(uchar type, ea * src, ea * dst, gen_node * node)


tmpl_header * __cdecl select_move_template(uchar type,ea *src,ea *dst,gen_node *node)

{
  byte type_class;
  byte ea_kind;
  byte dst_kind;
  int iVar1;
  uint dst_offset;
  int iVar2;
  int src_variant;
  byte bVar3;
  uint uVar4;
  int dst_variant;
  int sym_index;
  tmpl_header *chosen_tmpl;
  uint block_size;
  short cpu;
  label_ref *sym_ref;
  
  cpu = g_request->cpu;
  if ((cpu != 2) || (bVar3 = 1, g_request->fpu_mode != '\x03')) {
    bVar3 = -(cpu == 4) & 2;
  }
  if ((bVar3 != 0) && ((type & 0xf8) == 0x28)) {
    chosen_tmpl = (tmpl_header *)&g_tmpl_amv025;
    return chosen_tmpl;
  }
  if ((cpu == 4) && ((type & 0xf8) == 0x30)) {
    chosen_tmpl = (tmpl_header *)&g_tmpl_amv026;
    return chosen_tmpl;
  }
  bVar3 = type & 0xe0;
  if (((bVar3 == 0) || (bVar3 == 0x40)) || (type_class = type & 0xf8, type_class == 0x28)) {
    chosen_tmpl = (tmpl_header *)&g_tmpl_amv003;
    return chosen_tmpl;
  }
  if ((type_class == 0x30) || (type_class == 0x38)) {
    if ((src->type & 0x1f) != 0xe) {
      chosen_tmpl = (tmpl_header *)&g_tmpl_amv005;
      return chosen_tmpl;
    }
    if (g_request->unknown_028[2] == '\0') {
      return (tmpl_header *)&g_tmpl_amv006;
    }
    return (tmpl_header *)&g_tmpl_amv007;
  }
  if ((bVar3 != 0x60) && (bVar3 != 0x80)) {
    return chosen_tmpl;
  }
  chosen_tmpl = (tmpl_header *)0x0;
  block_size = node->val;
  if (((((((bVar3 == 0x60) || (bVar3 == 0x80)) && ((type & 0x18) == 0)) || (type_class == 0)) &&
       (block_size == 1)) ||
      (((((bVar3 == 0x60 || (bVar3 == 0x80)) && ((type & 0x18) == 8)) || (type_class == 8)) &&
       (block_size == 2)))) ||
     (((((bVar3 == 0x60 || (bVar3 == 0x80)) && ((type & 0x18) == 0x10)) ||
       ((((type_class == 0x10 || (type_class == 0x18)) || (bVar3 == 0x20)) || (bVar3 == 0x40)))) &&
      (block_size == 4)))) {
    chosen_tmpl = (tmpl_header *)&g_tmpl_amv024;
    goto LAB_0042e6ce;
  }
  if (g_request->switch_density_rule == 0) goto LAB_0042e6ce;
  if (((((bVar3 == 0x60) || (bVar3 == 0x80)) && ((type & 0x18) == 0x10)) ||
      (((type_class == 0x10 || (type_class == 0x18)) || ((bVar3 == 0x20 || (bVar3 == 0x40)))))) &&
     ((int)block_size < 0x41)) goto LAB_0042e644;
  if (((((((bVar3 == 0x60) || (bVar3 == 0x80)) && ((type & 0x18) == 0)) || (type_class == 0)) ||
       (((bVar3 == 0x60 || (bVar3 == 0x80)) && ((type & 0x18) == 8)))) || (type_class == 8)) &&
     (((int)block_size < 0x41 &&
      (uVar4 = (int)block_size >> 0x1f, ((block_size ^ uVar4) - uVar4 & 3 ^ uVar4) == uVar4)))) {
    ea_kind = src->type & 0x1f;
    if ((((ea_kind == 2) && (src->base == 'l')) || ((ea_kind == 8 && (src->base == 'l')))) &&
       (uVar4 = src->disp >> 0x1f, ((src->disp ^ uVar4) - uVar4 & 3 ^ uVar4) == uVar4)) {
LAB_0042e0d7:
      ea_kind = dst->type & 0x1f;
      if ((((ea_kind == 2) && (dst->base == 'l')) || ((ea_kind == 8 && (dst->base == 'l')))) &&
         (uVar4 = dst->disp >> 0x1f, ((dst->disp ^ uVar4) - uVar4 & 3 ^ uVar4) == uVar4)) {
LAB_0042e644:
        if ((dst == (ea *)0x0) ||
           ((((bVar3 = dst->type & 0x1f, bVar3 != 2 && (bVar3 != 8)) ||
             (dst->labels != (label_ref *)0x0)) ||
            ((dst->base == 'l' || (iVar1 = 0, 0x3c < (int)(dst->disp + block_size + -4))))))) {
          iVar1 = 1;
        }
        if ((((src == (ea *)0x0) || ((bVar3 = src->type & 0x1f, bVar3 != 2 && (bVar3 != 8)))) ||
            (src->labels != (label_ref *)0x0)) ||
           ((src->base == 'l' || (iVar2 = 0, 0x3c < (int)(src->disp + block_size + -4))))) {
          iVar2 = 1;
        }
        chosen_tmpl = (tmpl_header *)(&g_amv_block_templates)[iVar2 + iVar1 * 2];
        goto LAB_0042e6ce;
      }
      if (ea_kind == 0xd) {
        if ((dst->labels == (label_ref *)0x0) &&
           (uVar4 = dst->disp >> 0x1f, ((dst->disp ^ uVar4) - uVar4 & 3 ^ uVar4) == uVar4))
        goto LAB_0042e644;
        sym_ref = dst->labels;
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
                if (g_symbol_table[iVar1].sclass != '\x04') goto LAB_0042e20f;
              }
            }
          }
          iVar1 = 0;
          if (sym_ref != (label_ref *)0x0) {
            iVar1 = (int)sym_ref->labno1;
          }
          if ((g_symbol_table[iVar1].frame_offset + dst->disp & 3U) == 0) goto LAB_0042e644;
        }
      }
    }
    else if (ea_kind == 0xd) {
      if ((src->labels == (label_ref *)0x0) &&
         (uVar4 = src->disp >> 0x1f, ((src->disp ^ uVar4) - uVar4 & 3 ^ uVar4) == uVar4))
      goto LAB_0042e0d7;
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
              if (g_symbol_table[iVar1].sclass != '\x04') goto LAB_0042e20f;
            }
          }
        }
        iVar1 = 0;
        if (sym_ref != (label_ref *)0x0) {
          iVar1 = (int)sym_ref->labno1;
        }
        if ((g_symbol_table[iVar1].frame_offset + src->disp & 3U) == 0) goto LAB_0042e0d7;
      }
    }
  }
LAB_0042e20f:
  if (((((bVar3 == 0x60) || (bVar3 == 0x80)) && ((type & 0x18) == 0)) ||
      ((type_class == 0 ||
       ((((bVar3 == 0x60 || (bVar3 == 0x80)) && ((type & 0x18) == 8)) || (type_class == 8)))))) &&
     ((7 < (int)block_size && ((int)block_size < 0x41)))) {
    ea_kind = src->type & 0x1f;
    if (((ea_kind != 2) || (src->base != 'l')) && ((ea_kind != 8 || (src->base != 'l')))) {
      if (ea_kind != 0xd) goto LAB_0042e4e8;
      if (src->labels != (label_ref *)0x0) {
        sym_ref = src->labels;
        if ((sym_ref == (label_ref *)0x0) || (sym_ref->labno2 != 0)) goto LAB_0042e4e8;
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
              if (g_symbol_table[iVar1].sclass != '\x04') goto LAB_0042e4e8;
            }
          }
        }
      }
    }
    dst_kind = dst->type & 0x1f;
    if (((dst_kind != 2) || (dst->base != 'l')) && ((dst_kind != 8 || (dst->base != 'l')))) {
      if (dst_kind != 0xd) goto LAB_0042e4e8;
      if (dst->labels != (label_ref *)0x0) {
        if ((dst->labels == (label_ref *)0x0) || (sym_ref = dst->labels, sym_ref->labno2 != 0))
        goto LAB_0042e4e8;
        if (sym_ref == (label_ref *)0x0) {
          sym_index = 0;
        }
        else {
          sym_index = (int)sym_ref->labno1;
        }
        if (g_symbol_table[sym_index].sclass != '\x03') {
          if (dst->labels == (label_ref *)0x0) {
            sym_index = 0;
          }
          else {
            sym_index = (int)dst->labels->labno1;
          }
          if (g_symbol_table[sym_index].sclass != '\x01') {
            if (dst->labels == (label_ref *)0x0) {
              sym_index = 0;
            }
            else {
              sym_index = (int)dst->labels->labno1;
            }
            if (g_symbol_table[sym_index].sclass != '\t') {
              iVar1 = 0;
              if (dst->labels != (label_ref *)0x0) {
                iVar1 = (int)dst->labels->labno1;
              }
              if (g_symbol_table[iVar1].sclass != '\x04') goto LAB_0042e4e8;
            }
          }
        }
      }
    }
    if ((((ea_kind == 2) && (src->base == 'l')) || ((ea_kind == 8 && (src->base == 'l')))) ||
       ((ea_kind == 0xd && (src->labels == (label_ref *)0x0)))) {
      uVar4 = src->disp;
    }
    else {
      if (src->labels == (label_ref *)0x0) {
        iVar1 = 0;
      }
      else {
        iVar1 = (int)src->labels->labno1;
      }
      uVar4 = g_symbol_table[iVar1].frame_offset + src->disp;
    }
    if ((((dst_kind == 2) && (dst->base == 'l')) || ((dst_kind == 8 && (dst->base == 'l')))) ||
       ((dst_kind == 0xd && (dst->labels == (label_ref *)0x0)))) {
      dst_offset = dst->disp;
    }
    else {
      if (dst->labels == (label_ref *)0x0) {
        iVar1 = 0;
      }
      else {
        iVar1 = (int)dst->labels->labno1;
      }
      dst_offset = g_symbol_table[iVar1].frame_offset + dst->disp;
    }
    if (((uVar4 ^ dst_offset) & 3) == 0) {
      chosen_tmpl = (tmpl_header *)&g_tmpl_amv019;
      goto LAB_0042e6ce;
    }
  }
LAB_0042e4e8:
  if ((((((bVar3 != 0x60) && (bVar3 != 0x80)) || ((type & 0x18) != 0)) && (type_class != 0)) ||
      (0x10 < (int)block_size)) &&
     (((((bVar3 != 0x60 && (bVar3 != 0x80)) || ((type & 0x18) != 8)) && (type_class != 8)) ||
      (0x20 < (int)block_size)))) goto LAB_0042e6ce;
  if (((dst == (ea *)0x0) || ((ea_kind = dst->type & 0x1f, ea_kind != 2 && (ea_kind != 8)))) ||
     ((dst->base == '\0' || ((dst->labels != (label_ref *)0x0 || (dst->base == 'l')))))) {
LAB_0042e5a8:
    dst_variant = 1;
  }
  else {
    if ((((bVar3 == 0x60) || (bVar3 == 0x80)) && ((type & 0x18) == 0)) ||
       (iVar1 = 2, type_class == 0)) {
      iVar1 = 1;
    }
    if ((((bVar3 == 0x60) || (bVar3 == 0x80)) && ((type & 0x18) == 0)) ||
       (iVar2 = 0x1e, type_class == 0)) {
      iVar2 = 0xf;
    }
    dst_variant = 0;
    if (iVar2 < (int)((dst->disp - iVar1) + block_size)) goto LAB_0042e5a8;
  }
  if (((src == (ea *)0x0) || ((ea_kind = src->type & 0x1f, ea_kind != 2 && (ea_kind != 8)))) ||
     ((src->base == '\0' || ((src->labels != (label_ref *)0x0 || (src->base == 'l')))))) {
LAB_0042e624:
    src_variant = 1;
  }
  else {
    if ((((bVar3 == 0x60) || (bVar3 == 0x80)) && ((type & 0x18) == 0)) ||
       (iVar1 = 2, type_class == 0)) {
      iVar1 = 1;
    }
    if ((((bVar3 == 0x60) || (bVar3 == 0x80)) && ((type & 0x18) == 0)) ||
       (iVar2 = 0x1e, type_class == 0)) {
      iVar2 = 0xf;
    }
    src_variant = 0;
    if (iVar2 < (int)((src->disp - iVar1) + block_size)) goto LAB_0042e624;
  }
  chosen_tmpl = (tmpl_header *)(&g_amv_copy_templates)[src_variant + dst_variant * 2];
LAB_0042e6ce:
  if (chosen_tmpl == (tmpl_header *)0x0) {
    bVar3 = src->type & 0x1f;
    if (((bVar3 == 2) || (bVar3 == 8)) && (src->base == '\x01')) {
      bVar3 = dst->type & 0x1f;
      if (((bVar3 == 2) || (bVar3 == 8)) && (dst->base == '\x02')) {
        chosen_tmpl = (tmpl_header *)&g_tmpl_amv014;
      }
      else {
        chosen_tmpl = (tmpl_header *)&g_tmpl_amv012;
      }
    }
    else {
      chosen_tmpl = (tmpl_header *)&g_tmpl_amv008;
    }
  }
  return chosen_tmpl;
}



