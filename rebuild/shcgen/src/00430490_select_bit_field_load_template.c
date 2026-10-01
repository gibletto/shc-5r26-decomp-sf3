#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00430490
// name : select_bit_field_load_template
// size : 1023
// sig  : tmpl_header * select_bit_field_load_template(gen_node * node)


tmpl_header * __cdecl select_bit_field_load_template(gen_node *node)

{
  uint uVar1;
  tmpl_header *tmpl;
  byte bVar2;
  uint sign;
  ea *operand;
  node_desc *desc;
  byte type;
  
  bVar2 = 0;
  desc = node->child->desc;
  operand = desc->mem_ea;
  if (operand != (ea *)0x0) {
    bVar2 = operand->type & 0x1f;
  }
  if (((bVar2 == 0) && (operand = &desc->dest, (operand->type & 0x1f) == 0)) &&
     (operand = &g_ea_pop, (desc->flags2 & 8) == 0)) {
    operand = &desc->value;
  }
  bVar2 = operand->type & 0x1f;
  if (((bVar2 == 0xd) && (node->desc->bit_width == '\x01')) &&
     (((node->type & 2) == 0 || ((node->type & 0xf8) == 0)))) {
    if (operand->labels == (label_ref *)0x0) {
      uVar1 = 0;
    }
    else {
      uVar1 = (uint)operand->labels->labno1;
    }
    if ((g_symbol_table[(uVar1 ^ (int)uVar1 >> 0x1f) - ((int)uVar1 >> 0x1f)].attr & 3) != 0) {
      return (tmpl_header *)&g_tmpl_abqual008;
    }
  }
  desc = node->desc;
  if ((((desc->bit_width < '\t') &&
       (uVar1 = (int)desc->bit_width + (int)desc->bit_offset, sign = (int)uVar1 >> 0x1f,
       ((uVar1 ^ sign) - sign & 7 ^ sign) == sign)) &&
      ((type = node->type, (type & 2) == 0 || ((type & 0xf8) == 0)))) &&
     ((((type & 4) != 0 || ((type & 0xe0) == 0x80)) || ((type & 0xe0) == 0x40)))) {
    if (((desc->usage == '\x03') && ((bVar2 == 2 || (bVar2 == 8)))) &&
       (((bVar2 = operand->base, (char)bVar2 < '\x0f' &&
         ((1 << (bVar2 & 0x1f) & (int)(short)~g_var_gpr_mask) != 0)) ||
        (((((char)bVar2 < ' ' && ('\x0f' < (char)bVar2)) &&
          (((int)(short)~g_var_fpr_mask & 1 << (bVar2 - 0x10 & 0x1f)) != 0)) ||
         ((((char)bVar2 < '/' && ('\x1f' < (char)bVar2)) &&
          (((int)(short)g_var_fpr_mask & (1 << (bVar2 - 0x1f & 0x1f) | 1 << (bVar2 - 0x20 & 0x1f)))
           == 0)))))))) {
      return (tmpl_header *)&g_tmpl_abqual005;
    }
    return (tmpl_header *)&g_tmpl_abqual001;
  }
  uVar1 = bit_field_byte_offset(node);
  if ((uVar1 & 1) == 0) {
    desc = node->desc;
    if ((((desc->bit_width < '\x11') &&
         (uVar1 = (int)desc->bit_width + (int)desc->bit_offset, sign = (int)uVar1 >> 0x1f,
         ((uVar1 ^ sign) - sign & 0xf ^ sign) == sign)) &&
        ((bVar2 = node->type, (bVar2 & 2) == 0 || ((bVar2 & 0xf8) == 8)))) &&
       ((((bVar2 & 4) != 0 || ((bVar2 & 0xe0) == 0x80)) || ((bVar2 & 0xe0) == 0x40)))) {
      if (((desc->usage == '\x03') && ((bVar2 = operand->type & 0x1f, bVar2 == 2 || (bVar2 == 8))))
         && (((bVar2 = operand->base, (char)bVar2 < '\x0f' &&
              ((1 << (bVar2 & 0x1f) & (int)(short)~g_var_gpr_mask) != 0)) ||
             (((((char)bVar2 < ' ' && ('\x0f' < (char)bVar2)) &&
               (((int)(short)~g_var_fpr_mask & 1 << (bVar2 - 0x10 & 0x1f)) != 0)) ||
              ((((char)bVar2 < '/' && ('\x1f' < (char)bVar2)) &&
               (((int)(short)g_var_fpr_mask &
                (1 << (bVar2 - 0x1f & 0x1f) | 1 << (bVar2 - 0x20 & 0x1f))) == 0)))))))) {
        return (tmpl_header *)&g_tmpl_abqual003;
      }
      return (tmpl_header *)&g_tmpl_abqual002;
    }
  }
  desc = node->desc;
  if ((((' ' < desc->bit_width) ||
       (uVar1 = (int)desc->bit_offset + (int)desc->bit_width, sign = (int)uVar1 >> 0x1f,
       ((uVar1 ^ sign) - sign & 0x1f ^ sign) != sign)) ||
      ((bVar2 = node->type, (bVar2 & 2) != 0 &&
       (((bVar2 & 0xf8) != 0x10 && ((bVar2 & 0xf8) != 0x18)))))) ||
     (((bVar2 & 4) == 0 && (((bVar2 & 0xe0) != 0x80 && ((bVar2 & 0xe0) != 0x40)))))) {
    if (((desc->bit_width == '\x01') && (((node->type & 2) == 0 || ((node->type & 0xf8) == 0)))) &&
       ((desc->usage != '\x03' ||
        (((bVar2 = operand->type & 0x1f, bVar2 != 2 && (bVar2 != 8)) ||
         (((bVar2 = operand->base, '\x0e' < (char)bVar2 ||
           ((1 << (bVar2 & 0x1f) & (int)(short)~g_var_gpr_mask) == 0)) &&
          (((('\x1f' < (char)bVar2 || ((char)bVar2 < '\x10')) ||
            (((int)(short)~g_var_fpr_mask & 1 << (bVar2 - 0x10 & 0x1f)) == 0)) &&
           ((('.' < (char)bVar2 || ((char)bVar2 < ' ')) ||
            (((int)(short)g_var_fpr_mask & (1 << (bVar2 - 0x1f & 0x1f) | 1 << (bVar2 - 0x20 & 0x1f))
             ) != 0)))))))))))) {
      tmpl = (tmpl_header *)&g_tmpl_abqual004;
      if (desc->usage == '\x01') {
        desc->flags2 = desc->flags2 | 0x20;
        return tmpl;
      }
    }
    else {
      tmpl = (tmpl_header *)&g_tmpl_abqual005;
    }
    return tmpl;
  }
  if (((desc->usage == '\x03') && ((bVar2 = operand->type & 0x1f, bVar2 == 2 || (bVar2 == 8)))) &&
     ((((bVar2 = operand->base, (char)bVar2 < '\x0f' &&
        ((1 << (bVar2 & 0x1f) & (int)(short)~g_var_gpr_mask) != 0)) ||
       ((((char)bVar2 < ' ' && ('\x0f' < (char)bVar2)) &&
        (((int)(short)~g_var_fpr_mask & 1 << (bVar2 - 0x10 & 0x1f)) != 0)))) ||
      ((((char)bVar2 < '/' && ('\x1f' < (char)bVar2)) &&
       (((int)(short)g_var_fpr_mask & (1 << (bVar2 - 0x1f & 0x1f) | 1 << (bVar2 - 0x20 & 0x1f))) ==
        0)))))) {
    return (tmpl_header *)&g_tmpl_abqual007;
  }
  return (tmpl_header *)&g_tmpl_abqual006;
}



