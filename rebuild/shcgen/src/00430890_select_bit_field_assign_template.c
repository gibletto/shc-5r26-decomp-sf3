#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00430890
// name : select_bit_field_assign_template
// size : 1256
// sig  : tmpl_header * select_bit_field_assign_template(gen_node * node, char before_operands)


tmpl_header * __cdecl select_bit_field_assign_template(gen_node *node,char before_operands)

{
  unsigned char _frec_18[24];
#define chosen (*(tmpl_header * *)(_frec_18 + 0))
#define assigned (*(uint *)(_frec_18 + 8))
  char cVar1;
  byte bVar2;
  char offset_in_byte;
  gen_node *source;
  uint uVar3;
  int byte_offset;
  int word_disp;
  int iVar4;
  int word_bit;
  int long_bit;
  ea *dest_ea;
  gen_node *child;
  node_desc *child_desc;
  bool found;
  char offset;
  
  bVar2 = 0;
  found = false;
  child = node->child;
  child_desc = child->desc;
  dest_ea = child_desc->mem_ea;
  if (dest_ea != (ea *)0x0) {
    bVar2 = dest_ea->type & 0x1f;
  }
  if (((bVar2 == 0) && (dest_ea = &child_desc->dest, (dest_ea->type & 0x1f) == 0)) &&
     (dest_ea = &g_ea_pop, (child_desc->flags2 & 8) == 0)) {
    dest_ea = &child_desc->value;
  }
  source = (gen_node *)0x0;
  if (child != (gen_node *)0x0) {
    source = child->next;
  }
  if (source->op != IL_CONST) {
    source = (gen_node *)0x0;
    if (child != (gen_node *)0x0) {
      source = child->next;
    }
    if (source->desc->opnd_class != '\x02') goto LAB_00430d66;
  }
  source = (gen_node *)0x0;
  if (child != (gen_node *)0x0) {
    source = child->next;
  }
  if (source->desc->opnd_class == '\x02') {
    source = (gen_node *)0x0;
    if (child != (gen_node *)0x0) {
      source = child->next;
    }
    assigned = (source->desc->value).disp;
  }
  else {
    source = (gen_node *)0x0;
    if (child != (gen_node *)0x0) {
      source = child->next;
    }
    assigned = source->val;
  }
  if (((dest_ea != (ea *)0x0) && ((dest_ea->type & 0x1f) == 0xd)) &&
     ((node->desc->bit_width == '\x01' && (((node->type & 2) == 0 || ((node->type & 0xf8) == 0))))))
  {
    if (dest_ea->labels == (label_ref *)0x0) {
      uVar3 = 0;
    }
    else {
      uVar3 = (uint)dest_ea->labels->labno1;
    }
    if ((g_symbol_table[(uVar3 ^ (int)uVar3 >> 0x1f) - ((int)uVar3 >> 0x1f)].attr & 3) != 0) {
      uVar3 = (int)assigned >> 0x1f;
      if (((assigned ^ uVar3) - uVar3 & 1 ^ uVar3) == uVar3) {
        found = true;
        chosen = (tmpl_header *)&g_tmpl_aassgn040;
      }
      else {
        found = true;
        chosen = (tmpl_header *)&g_tmpl_aassgn039;
      }
      goto LAB_00430d66;
    }
  }
  cVar1 = node->desc->bit_width;
  if ((cVar1 == '\x01') && (before_operands == '\x01')) {
    found = true;
    chosen = (tmpl_header *)&g_tmpl_aassgn044;
    goto LAB_00430d66;
  }
  if ((cVar1 != '\x01') || (before_operands != '\0')) {
    offset = node->desc->bit_offset;
    offset_in_byte = offset % '\b';
    if (((offset_in_byte == '\0') && (cVar1 == '\b')) &&
       (((node->type & 2) == 0 || ((node->type & 0xf8) == 0)))) {
      if ((dest_ea == (ea *)0x0) ||
         ((iVar4 = bit_field_byte_offset(child), 0xf < dest_ea->disp + iVar4 ||
          ((((bVar2 = dest_ea->type & 0x1f, bVar2 != 2 && (bVar2 != 8)) ||
            (dest_ea->labels != (label_ref *)0x0)) ||
           ((dest_ea->base == '\0' || (dest_ea->base == 'l')))))))) {
        found = true;
        chosen = (tmpl_header *)&g_tmpl_aassgn023;
      }
      else {
        found = true;
        chosen = (tmpl_header *)&g_tmpl_aassgn026;
      }
    }
    else if (((int)offset_in_byte + (int)cVar1 < 9) &&
            (((node->type & 2) == 0 || ((node->type & 0xf8) == 0)))) {
      found = true;
      chosen = (tmpl_header *)&g_tmpl_aassgn016;
    }
    else {
      chosen = (tmpl_header *)CONCAT31((*(unsigned int *)((char *)&chosen + 1) & 0xffffff),0x10);
      if (((offset % '\x10' == '\0') && (cVar1 == '\x10')) &&
         (((node->type & 2) == 0 || ((node->type & 0xf8) == 8)))) {
        if ((((dest_ea == (ea *)0x0) ||
             (iVar4 = bit_field_byte_offset(child), 0x1e < dest_ea->disp + iVar4)) ||
            ((bVar2 = dest_ea->type & 0x1f, bVar2 != 2 && (bVar2 != 8)))) ||
           (((dest_ea->labels != (label_ref *)0x0 || (dest_ea->base == '\0')) ||
            (dest_ea->base == 'l')))) {
          found = true;
          chosen = (tmpl_header *)&g_tmpl_aassgn024;
        }
        else {
          found = true;
          chosen = (tmpl_header *)&g_tmpl_aassgn027;
        }
      }
      else {
        uVar3 = bit_field_byte_offset(node);
        if ((((uVar3 & 1) == 0) &&
            ((int)(node->desc->bit_offset % '\x10') + (int)node->desc->bit_width < 0x11)) &&
           (((node->type & 2) == 0 || ((node->type & 0xf8) == 8)))) {
          found = true;
          chosen = (tmpl_header *)&g_tmpl_aassgn017;
        }
        else {
          bVar2 = node->child->type & 0xf8;
          if (((bVar2 == 0x18) || (bVar2 == 0x10)) && (node->desc->bit_width == ' ')) {
            if ((((dest_ea == (ea *)0x0) ||
                 (iVar4 = bit_field_byte_offset(node->child), 0x3c < dest_ea->disp + iVar4)) ||
                ((bVar2 = dest_ea->type & 0x1f, bVar2 != 2 && (bVar2 != 8)))) ||
               ((dest_ea->labels != (label_ref *)0x0 || (dest_ea->base == 'l')))) {
              found = true;
              chosen = (tmpl_header *)&g_tmpl_aassgn025;
            }
            else {
              found = true;
              chosen = (tmpl_header *)&g_tmpl_aassgn028;
            }
          }
          else if ((bVar2 == 0x18) || (bVar2 == 0x10)) {
            found = true;
            chosen = (tmpl_header *)&g_tmpl_aassgn018;
          }
        }
      }
    }
    goto LAB_00430d66;
  }
  byte_offset = bit_field_byte_offset(child);
  iVar4 = dest_ea->disp;
  word_disp = bit_field_word_offset(node->child);
  word_disp = dest_ea->disp + word_disp;
  cVar1 = node->desc->bit_offset;
  chosen = (tmpl_header *)CONCAT31((*(unsigned int *)((char *)&chosen + 1) & 0xffffff),0x20);
  word_bit = 1 << (0xfU - cVar1 % '\x10' & 0x1f);
  long_bit = 1 << (0x1fU - cVar1 % ' ' & 0x1f);
  if (dest_ea == (ea *)0x0) {
LAB_00430b07:
    if ((((dest_ea != (ea *)0x0) && (dest_ea->labels == (label_ref *)0x0)) &&
        (((0x1f < dest_ea->disp && (dest_ea->disp < 0x3d)) &&
         (((bVar2 = node->type & 0xf8, bVar2 == 0x18 || (bVar2 == 0x10)) &&
          ((bVar2 = dest_ea->type & 0x1f, bVar2 == 2 || (bVar2 == 8)))))))) &&
       (dest_ea->base != 'l')) {
      if (((((assigned & 1) == 0) || (long_bit < 0)) || (0xff < long_bit)) ||
         (((node->desc->busy_regs & 1) != 0 || ((node->child->desc->value).base == '\0')))) {
        found = true;
        chosen = (tmpl_header *)&g_tmpl_aassgn043;
      }
      else {
        found = true;
        chosen = (tmpl_header *)&g_tmpl_aassgn046;
      }
      goto LAB_00430d66;
    }
  }
  else {
    if ((((dest_ea->labels == (label_ref *)0x0) && (byte_offset + iVar4 < 0x10)) &&
        (((node->type & 2) == 0 || ((node->type & 0xf8) == 0)))) &&
       (((bVar2 = dest_ea->type & 0x1f, bVar2 == 2 || (bVar2 == 8)) && (dest_ea->base != 'l')))) {
      found = true;
      chosen = (tmpl_header *)&g_tmpl_aassgn041;
      goto LAB_00430d66;
    }
    if (dest_ea != (ea *)0x0) {
      if (((dest_ea->labels == (label_ref *)0x0) && (0xf < word_disp)) && (word_disp < 0x1f)) {
        bVar2 = node->type & 0xf8;
        if (((((bVar2 == 8) || (bVar2 == 0x18)) || (bVar2 == 0x10)) &&
            (((node->type & 2) == 0 || (bVar2 == 8)))) &&
           (((bVar2 = dest_ea->type & 0x1f, bVar2 == 2 || (bVar2 == 8)) && (dest_ea->base != 'l'))))
        {
          if ((((assigned & 1) == 0) || (word_bit < 0)) || (0xff < word_bit)) {
            found = true;
            chosen = (tmpl_header *)&g_tmpl_aassgn042;
          }
          else {
            found = true;
            chosen = (tmpl_header *)&g_tmpl_aassgn045;
          }
          goto LAB_00430d66;
        }
      }
      goto LAB_00430b07;
    }
  }
  if (((node->type & 2) == 0) || ((node->type & 0xf8) == 0)) {
    found = true;
    chosen = (tmpl_header *)&g_tmpl_aassgn044;
  }
LAB_00430d66:
  if (!found) {
    chosen = (tmpl_header *)&g_tmpl_aassgn019;
  }
  return chosen;
#undef chosen
#undef assigned
}



