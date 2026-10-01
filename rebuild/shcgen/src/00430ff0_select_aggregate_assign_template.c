#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_long_copy_templates
#define g_long_copy_templates (*(unsigned char * *)(g_sd + 0x1c180))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_short_copy_templates
#define g_short_copy_templates (*(unsigned char * *)(g_sd + 0x1c190))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00430ff0
// name : select_aggregate_assign_template
// size : 2395
// sig  : tmpl_header * select_aggregate_assign_template(gen_node * node, int after_operands)


tmpl_header * __cdecl select_aggregate_assign_template(gen_node *node,int after_operands)

{
  byte type_class;
  byte src_kind;
  byte bVar1;
  int iVar2;
  uint src_offset;
  int iVar3;
  int src_far;
  uint uVar4;
  byte type_kind;
  gen_node *src;
  uint uVar5;
  int dst_far;
  byte kind;
  ea *src_ea;
  ea *dst_ea;
  tmpl_header *chosen;
  node_desc *desc;
  gen_node *dst;
  label_ref *labels;
  
  dst = node->child;
  src = (gen_node *)0x0;
  chosen = (tmpl_header *)0x0;
  if (dst != (gen_node *)0x0) {
    src = dst->next;
  }
  desc = dst->desc;
  bVar1 = 0;
  dst_ea = desc->mem_ea;
  if (dst_ea != (ea *)0x0) {
    bVar1 = dst_ea->type & 0x1f;
  }
  if (((bVar1 == 0) && (dst_ea = &desc->dest, (dst_ea->type & 0x1f) == 0)) &&
     (dst_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
    dst_ea = &desc->value;
  }
  desc = src->desc;
  bVar1 = 0;
  src_ea = desc->mem_ea;
  if (src_ea != (ea *)0x0) {
    bVar1 = src_ea->type & 0x1f;
  }
  if (((bVar1 == 0) && (src_ea = &desc->dest, (src_ea->type & 0x1f) == 0)) &&
     (src_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
    src_ea = &desc->value;
  }
  bVar1 = src->type;
  uVar4 = src->val;
  type_class = bVar1 & 0xf8;
  type_kind = bVar1 & 0xe0;
  if (((((((type_kind == 0x60) || (type_kind == 0x80)) && ((bVar1 & 0x18) == 0)) ||
        (type_class == 0)) && (uVar4 == 1)) ||
      (((((type_kind == 0x60 || (type_kind == 0x80)) && ((bVar1 & 0x18) == 8)) || (type_class == 8))
       && (uVar4 == 2)))) ||
     (((((type_kind == 0x60 || (type_kind == 0x80)) && ((bVar1 & 0x18) == 0x10)) ||
       (((type_class == 0x10 || (type_class == 0x18)) ||
        ((type_kind == 0x20 || (type_kind == 0x40)))))) && (uVar4 == 4)))) {
    chosen = (tmpl_header *)&g_tmpl_aassgn038;
    goto LAB_004318fd;
  }
  if (g_request->switch_density_rule == 0) goto LAB_004318fd;
  if (after_operands == 0) {
    if ((((((type_kind == 0x60) || (type_kind == 0x80)) && ((bVar1 & 0x18) == 0x10)) ||
         ((type_class == 0x10 || (type_class == 0x18)))) ||
        ((type_kind == 0x20 || (type_kind == 0x40)))) && ((int)uVar4 < 0x41)) {
      chosen = (tmpl_header *)&g_tmpl_aassgn032;
    }
    else if ((((((type_kind == 0x60) || (type_kind == 0x80)) && ((bVar1 & 0x18) == 0)) ||
              (type_class == 0)) && ((int)uVar4 < 0x11)) ||
            (((((type_kind == 0x60 || (type_kind == 0x80)) && ((bVar1 & 0x18) == 8)) ||
              (type_class == 8)) && ((int)uVar4 < 0x21)))) {
      chosen = (tmpl_header *)&g_tmpl_aassgn037;
    }
    goto LAB_004318fd;
  }
  if ((((((type_kind == 0x60) || (type_kind == 0x80)) && ((bVar1 & 0x18) == 0x10)) ||
       ((type_class == 0x10 || (type_class == 0x18)))) ||
      ((type_kind == 0x20 || (type_kind == 0x40)))) && ((int)uVar4 < 0x41)) goto LAB_004317ed;
  if (((((((type_kind == 0x60) || (type_kind == 0x80)) && ((bVar1 & 0x18) == 0)) ||
        (type_class == 0)) ||
       (((type_kind == 0x60 || (type_kind == 0x80)) && ((bVar1 & 0x18) == 8)))) || (type_class == 8)
      ) && (((int)uVar4 < 0x41 &&
            (uVar5 = (int)uVar4 >> 0x1f, ((uVar4 ^ uVar5) - uVar5 & 3 ^ uVar5) == uVar5)))) {
    kind = dst_ea->type & 0x1f;
    if ((((kind == 2) && (dst_ea->base == 'l')) || ((kind == 8 && (dst_ea->base == 'l')))) &&
       (uVar5 = dst_ea->disp >> 0x1f, ((dst_ea->disp ^ uVar5) - uVar5 & 3 ^ uVar5) == uVar5)) {
LAB_004312d4:
      kind = src_ea->type & 0x1f;
      if ((((kind == 2) && (src_ea->base == 'l')) || ((kind == 8 && (src_ea->base == 'l')))) &&
         (uVar5 = src_ea->disp >> 0x1f, ((src_ea->disp ^ uVar5) - uVar5 & 3 ^ uVar5) == uVar5)) {
LAB_004317ed:
        if (((dst_ea == (ea *)0x0) ||
            (((bVar1 = dst_ea->type & 0x1f, bVar1 != 2 && (bVar1 != 8)) ||
             (dst_ea->labels != (label_ref *)0x0)))) ||
           ((dst_ea->base == 'l' || (iVar2 = 0, 0x3c < (int)(dst_ea->disp + uVar4 + -4))))) {
          iVar2 = 1;
        }
        if (((src_ea == (ea *)0x0) || ((bVar1 = src_ea->type & 0x1f, bVar1 != 2 && (bVar1 != 8))))
           || ((src_ea->labels != (label_ref *)0x0 ||
               ((src_ea->base == 'l' || (iVar3 = 0, 0x3c < (int)(src_ea->disp + uVar4 + -4))))))) {
          iVar3 = 1;
        }
        chosen = (tmpl_header *)(&g_long_copy_templates)[iVar3 + iVar2 * 2];
        goto LAB_004318fd;
      }
      if (kind == 0xd) {
        if ((src_ea->labels == (label_ref *)0x0) &&
           (uVar5 = src_ea->disp >> 0x1f, ((src_ea->disp ^ uVar5) - uVar5 & 3 ^ uVar5) == uVar5))
        goto LAB_004317ed;
        labels = src_ea->labels;
        if ((labels != (label_ref *)0x0) && (labels->labno2 == 0)) {
          iVar2 = 0;
          if (labels != (label_ref *)0x0) {
            iVar2 = (int)labels->labno1;
          }
          if (g_symbol_table[iVar2].sclass != '\x03') {
            iVar2 = 0;
            if (labels != (label_ref *)0x0) {
              iVar2 = (int)labels->labno1;
            }
            if (g_symbol_table[iVar2].sclass != '\x01') {
              iVar2 = 0;
              if (labels != (label_ref *)0x0) {
                iVar2 = (int)labels->labno1;
              }
              if (g_symbol_table[iVar2].sclass != '\t') {
                iVar2 = 0;
                if (labels != (label_ref *)0x0) {
                  iVar2 = (int)labels->labno1;
                }
                if (g_symbol_table[iVar2].sclass != '\x04') goto LAB_004313f0;
              }
            }
          }
          iVar2 = 0;
          if (labels != (label_ref *)0x0) {
            iVar2 = (int)labels->labno1;
          }
          if ((g_symbol_table[iVar2].frame_offset + src_ea->disp & 3U) == 0) goto LAB_004317ed;
        }
      }
    }
    else if (kind == 0xd) {
      if ((dst_ea->labels == (label_ref *)0x0) &&
         (uVar5 = dst_ea->disp >> 0x1f, ((dst_ea->disp ^ uVar5) - uVar5 & 3 ^ uVar5) == uVar5))
      goto LAB_004312d4;
      labels = dst_ea->labels;
      if ((labels != (label_ref *)0x0) && (labels->labno2 == 0)) {
        iVar2 = 0;
        if (labels != (label_ref *)0x0) {
          iVar2 = (int)labels->labno1;
        }
        if (g_symbol_table[iVar2].sclass != '\x03') {
          iVar2 = 0;
          if (labels != (label_ref *)0x0) {
            iVar2 = (int)labels->labno1;
          }
          if (g_symbol_table[iVar2].sclass != '\x01') {
            iVar2 = 0;
            if (labels != (label_ref *)0x0) {
              iVar2 = (int)labels->labno1;
            }
            if (g_symbol_table[iVar2].sclass != '\t') {
              iVar2 = 0;
              if (labels != (label_ref *)0x0) {
                iVar2 = (int)labels->labno1;
              }
              if (g_symbol_table[iVar2].sclass != '\x04') goto LAB_004313f0;
            }
          }
        }
        iVar2 = 0;
        if (labels != (label_ref *)0x0) {
          iVar2 = (int)labels->labno1;
        }
        if ((g_symbol_table[iVar2].frame_offset + dst_ea->disp & 3U) == 0) goto LAB_004312d4;
      }
    }
  }
LAB_004313f0:
  if (((((type_kind == 0x60) || (type_kind == 0x80)) && ((bVar1 & 0x18) == 0)) ||
      ((type_class == 0 ||
       ((((type_kind == 0x60 || (type_kind == 0x80)) && ((bVar1 & 0x18) == 8)) || (type_class == 8))
       )))) && ((7 < (int)uVar4 && ((int)uVar4 < 0x41)))) {
    kind = dst_ea->type & 0x1f;
    if (((kind != 2) || (dst_ea->base != 'l')) && ((kind != 8 || (dst_ea->base != 'l')))) {
      if (kind != 0xd) goto LAB_0043169b;
      if (dst_ea->labels != (label_ref *)0x0) {
        labels = dst_ea->labels;
        if ((labels == (label_ref *)0x0) || (labels->labno2 != 0)) goto LAB_0043169b;
        iVar2 = 0;
        if (labels != (label_ref *)0x0) {
          iVar2 = (int)labels->labno1;
        }
        if (g_symbol_table[iVar2].sclass != '\x03') {
          iVar2 = 0;
          if (labels != (label_ref *)0x0) {
            iVar2 = (int)labels->labno1;
          }
          if (g_symbol_table[iVar2].sclass != '\x01') {
            iVar2 = 0;
            if (labels != (label_ref *)0x0) {
              iVar2 = (int)labels->labno1;
            }
            if (g_symbol_table[iVar2].sclass != '\t') {
              iVar2 = 0;
              if (labels != (label_ref *)0x0) {
                iVar2 = (int)labels->labno1;
              }
              if (g_symbol_table[iVar2].sclass != '\x04') goto LAB_0043169b;
            }
          }
        }
      }
    }
    src_kind = src_ea->type & 0x1f;
    if (((src_kind != 2) || (src_ea->base != 'l')) && ((src_kind != 8 || (src_ea->base != 'l')))) {
      if (src_kind != 0xd) goto LAB_0043169b;
      if (src_ea->labels != (label_ref *)0x0) {
        labels = src_ea->labels;
        if ((labels == (label_ref *)0x0) || (labels->labno2 != 0)) goto LAB_0043169b;
        iVar2 = 0;
        if (labels != (label_ref *)0x0) {
          iVar2 = (int)labels->labno1;
        }
        if (g_symbol_table[iVar2].sclass != '\x03') {
          iVar2 = 0;
          if (labels != (label_ref *)0x0) {
            iVar2 = (int)labels->labno1;
          }
          if (g_symbol_table[iVar2].sclass != '\x01') {
            iVar2 = 0;
            if (labels != (label_ref *)0x0) {
              iVar2 = (int)labels->labno1;
            }
            if (g_symbol_table[iVar2].sclass != '\t') {
              iVar2 = 0;
              if (labels != (label_ref *)0x0) {
                iVar2 = (int)labels->labno1;
              }
              if (g_symbol_table[iVar2].sclass != '\x04') goto LAB_0043169b;
            }
          }
        }
      }
    }
    if ((((kind == 2) && (dst_ea->base == 'l')) || ((kind == 8 && (dst_ea->base == 'l')))) ||
       ((kind == 0xd && (dst_ea->labels == (label_ref *)0x0)))) {
      uVar5 = dst_ea->disp;
    }
    else {
      if (dst_ea->labels == (label_ref *)0x0) {
        iVar2 = 0;
      }
      else {
        iVar2 = (int)dst_ea->labels->labno1;
      }
      uVar5 = g_symbol_table[iVar2].frame_offset + dst_ea->disp;
    }
    if ((((src_kind == 2) && (src_ea->base == 'l')) || ((src_kind == 8 && (src_ea->base == 'l'))))
       || ((src_kind == 0xd && (src_ea->labels == (label_ref *)0x0)))) {
      src_offset = src_ea->disp;
    }
    else {
      if (src_ea->labels == (label_ref *)0x0) {
        iVar2 = 0;
      }
      else {
        iVar2 = (int)src_ea->labels->labno1;
      }
      src_offset = g_symbol_table[iVar2].frame_offset + src_ea->disp;
    }
    if (((uVar5 ^ src_offset) & 3) == 0) {
      chosen = (tmpl_header *)&g_tmpl_aassgn033;
      goto LAB_004318fd;
    }
  }
LAB_0043169b:
  if ((((((type_kind != 0x60) && (type_kind != 0x80)) || ((bVar1 & 0x18) != 0)) && (type_class != 0)
       ) || (0x10 < (int)uVar4)) &&
     (((((type_kind != 0x60 && (type_kind != 0x80)) || ((bVar1 & 0x18) != 8)) && (type_class != 8))
      || (0x20 < (int)uVar4)))) goto LAB_004318fd;
  if ((((dst_ea == (ea *)0x0) || ((kind = dst_ea->type & 0x1f, kind != 2 && (kind != 8)))) ||
      (dst_ea->labels != (label_ref *)0x0)) || (dst_ea->base == 'l')) {
LAB_00431759:
    dst_far = 1;
  }
  else {
    if ((((type_kind == 0x60) || (type_kind == 0x80)) && ((bVar1 & 0x18) == 0)) ||
       (iVar2 = 2, type_class == 0)) {
      iVar2 = 1;
    }
    if ((((type_kind == 0x60) || (type_kind == 0x80)) && ((bVar1 & 0x18) == 0)) ||
       (iVar3 = 0x1e, type_class == 0)) {
      iVar3 = 0xf;
    }
    dst_far = 0;
    if (iVar3 < (int)((dst_ea->disp - iVar2) + uVar4)) goto LAB_00431759;
  }
  if (((src_ea == (ea *)0x0) || ((kind = src_ea->type & 0x1f, kind != 2 && (kind != 8)))) ||
     ((src_ea->base == '\0' || ((src_ea->labels != (label_ref *)0x0 || (src_ea->base == 'l')))))) {
LAB_004317d5:
    src_far = 1;
  }
  else {
    if ((((type_kind == 0x60) || (type_kind == 0x80)) && ((bVar1 & 0x18) == 0)) ||
       (iVar2 = 2, type_class == 0)) {
      iVar2 = 1;
    }
    if ((((type_kind == 0x60) || (type_kind == 0x80)) && ((bVar1 & 0x18) == 0)) ||
       (iVar3 = 0x1e, type_class == 0)) {
      iVar3 = 0xf;
    }
    src_far = 0;
    if (iVar3 < (int)((src_ea->disp - iVar2) + uVar4)) goto LAB_004317d5;
  }
  chosen = (tmpl_header *)(&g_short_copy_templates)[src_far + dst_far * 2];
LAB_004318fd:
  if (chosen == (tmpl_header *)0x0) {
    if (((src_ea == (ea *)0x0) || ((src_ea->type & 0x1f) == 0)) ||
       (uVar4 = ea_register_mask(src_ea), (uVar4 & 2) == 0)) {
      chosen = (tmpl_header *)&g_tmpl_aassgn020;
    }
    else {
      uVar4 = ea_register_mask(dst_ea);
      chosen = (tmpl_header *)&g_tmpl_aassgn022;
      if ((uVar4 & 4) == 0) {
        chosen = (tmpl_header *)&g_tmpl_aassgn021;
      }
    }
  }
  return chosen;
}



