#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 0041c200
// name : materialize_operand_record_from_descriptor
// size : 3103
// sig  : ea * materialize_operand_record_from_descriptor(gen_node * node, ushort opnd_code, ea * * extra_operands)


ea * __cdecl
materialize_operand_record_from_descriptor(gen_node *node,ushort opnd_code,ea **extra_operands)

{
  byte bVar1;
  short sVar2;
  int iVar3;
  node_desc *desc;
  uint uVar4;
  label_ref *labels;
  char top_bit;
  uint selector;
  char width;
  ea *source;
  ea *result;
  uint uVar5;
  uchar ea_type;
  char ea_base;
  label_ref *ea_labels;
  bool fill_constant;
  uchar *flags_ptr;
  ushort *mask_ptr;
  gen_node *parent;
  
  ea_type = '\a';
  ea_base = -1;
  uVar5 = 0;
  fill_constant = false;
  ea_labels = (label_ref *)0x0;
  uVar4 = g_operand_desc_table[opnd_code];
  if (uVar4 == 0) {
    result = (ea *)0x0;
    goto switchD_0041cae1_caseD_0;
  }
  selector = uVar4 & 0xfc000000;
  if (selector < 0xc000001) {
    if (selector != 0xc000000) {
      if (selector == 0x8000000) {
        result = copy_ea((ea *)(&g_fixed_operands + (uVar4 & 0x3ffffff) * 0xc));
        goto switchD_0041cae1_caseD_0;
      }
LAB_0041c283:
      report_codegen_message(0x11fb,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
      result = (ea *)0x0;
      goto switchD_0041cae1_caseD_0;
    }
LAB_0041c2dd:
    if (selector == 0x10000000) goto LAB_0041c2e5;
    if (selector == 0x14000000) {
      if (node->child == (gen_node *)0x0) {
        node = (gen_node *)0x0;
      }
      else {
        node = node->child->next;
      }
    }
  }
  else {
    if (0x14000000 < selector) {
      if (selector != 0x18000000) {
        if (selector == 0x1c000000) {
          node = nth_operand(node,((uVar4 & 0x3f00000) >> 0x14) + 2);
          bVar1 = 0;
          desc = node->desc;
          result = desc->mem_ea;
          if (result != (ea *)0x0) {
            bVar1 = result->type & 0x1f;
          }
          if (((bVar1 == 0) && (result = &desc->dest, (result->type & 0x1f) == 0)) &&
             (result = &g_ea_pop, (desc->flags2 & 8) == 0)) {
            result = &desc->value;
          }
          result = copy_ea(result);
          goto switchD_0041cae1_caseD_0;
        }
        goto LAB_0041c283;
      }
      goto LAB_0041c2dd;
    }
    if (selector == 0x14000000) goto LAB_0041c2dd;
    if (selector != 0x10000000) goto LAB_0041c283;
LAB_0041c2e5:
    node = node->child;
  }
  if (selector == 0x18000000) {
    selector = uVar4 & 0x3f00000;
    if (0x100000 < selector) {
      if (selector < 0x300001) {
        if (selector == 0x300000) {
          source = extra_operands[3];
          if (source != (ea *)0x0) goto LAB_0041c66b;
          result = (ea *)0x0;
        }
        else {
          if (selector != 0x200000) goto LAB_0041c5dd;
          source = extra_operands[2];
          if (source != (ea *)0x0) goto LAB_0041c66b;
          result = (ea *)0x0;
        }
      }
      else if (selector == 0x400000) {
        source = extra_operands[4];
        if (source != (ea *)0x0) goto LAB_0041c66b;
        result = (ea *)0x0;
      }
      else if (selector == 0x500000) {
        source = extra_operands[5];
        if (source != (ea *)0x0) goto LAB_0041c66b;
        result = (ea *)0x0;
      }
      else {
        if (selector != 0x600000) goto LAB_0041c5dd;
        result = (ea *)0x0;
        source = extra_operands[6];
        if (source != (ea *)0x0) goto LAB_0041c66b;
      }
      goto LAB_0041c675;
    }
    if (selector == 0x100000) {
      source = extra_operands[1];
    }
    else {
      if (selector != 0) {
LAB_0041c5dd:
        report_codegen_message(0x1232,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
        result = (ea *)0x0;
        goto LAB_0041c675;
      }
      source = *extra_operands;
    }
LAB_0041c66b:
    result = copy_ea(source);
  }
  else {
    selector = uVar4 & 0x3f00000;
    if (selector < 0x100001) {
      if (selector != 0x100000) {
        if (selector != 0) goto LAB_0041c378;
        result = alloc_zeroed(0xc);
        if (result == (ea *)0x0) {
          report_codegen_message(0xbcd,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
        }
        else {
          fill_constant = true;
        }
        goto LAB_0041c675;
      }
      desc = node->desc;
      bVar1 = 0;
      source = desc->mem_ea;
      if (source != (ea *)0x0) {
        bVar1 = source->type & 0x1f;
      }
      if (((bVar1 == 0) && (source = &desc->dest, (source->type & 0x1f) == 0)) &&
         (source = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        source = &desc->value;
      }
      goto LAB_0041c66b;
    }
    if (selector < 0x300001) {
      if (selector == 0x300000) {
        desc = node->desc;
        bVar1 = 0;
        source = desc->saved_reg_ea;
        if (source != (ea *)0x0) {
          bVar1 = source->type & 0x1f;
        }
        if ((bVar1 == 0) && (source = &g_ea_pop, (desc->flags3 & 0x10) == 0)) {
          source = desc->saved_ea;
        }
      }
      else {
        if (selector != 0x200000) goto LAB_0041c378;
        source = &node->desc->dest;
      }
      goto LAB_0041c66b;
    }
    if (selector < 0x500001) {
      if (selector == 0x500000) {
        result = alloc_zeroed(0xc);
        if (result == (ea *)0x0) {
          report_codegen_message(0xbcd,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
        }
        else {
          fill_ea(result,'\x01',node->desc->regs_34[(uVar4 & 0xfc000) >> 0xe],-1,'\0',0,
                  (label_ref *)0x0);
        }
      }
      else if (selector == 0x400000) {
        result = alloc_zeroed(0xc);
        if (result == (ea *)0x0) {
          report_codegen_message(0xbcd,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
        }
        else {
          fill_ea(result,'\x01',node->desc->regs_2c[(uVar4 & 0xfc000) >> 0xe],-1,'\0',0,
                  (label_ref *)0x0);
        }
      }
      else {
LAB_0041c378:
        report_codegen_message(0x1231,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
        result = (ea *)0x0;
      }
    }
    else {
      if (selector != 0x600000) {
        if (selector != 0x700000) goto LAB_0041c378;
        source = node->desc->ea_54;
        goto LAB_0041c66b;
      }
      result = alloc_zeroed(0xc);
      if (result == (ea *)0x0) {
        report_codegen_message(0xbcd,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
      }
      else {
        fill_ea(result,'\x01',node->desc->cond_regs[(uVar4 & 0xfc000) >> 0xe],-1,'\0',0,
                (label_ref *)0x0);
      }
    }
  }
LAB_0041c675:
  if (!fill_constant) {
    if (result == (ea *)0x0) {
      return (ea *)0x0;
    }
    uVar5 = uVar4 & 0x3f00;
    if (uVar5 < 0x101) {
      if (uVar5 == 0x100) {
        result->type = result->type & 0xf1 | 1;
        result->disp = 0;
        result->type = result->type & 0xbf;
      }
      else if (uVar5 != 0) {
LAB_0041ca32:
        report_codegen_message(0x11f9,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
      }
    }
    else if (uVar5 < 0x301) {
      if (uVar5 == 0x300) {
        result->type = result->type & 0xf7 | 7;
        result->index = -1;
        result->base = -1;
        result->type = result->type & 0xbf;
      }
      else {
        if (uVar5 != 0x200) goto LAB_0041ca32;
        result->type = result->type & 0xf8 | 8;
        result->disp = 0;
      }
    }
    else if (uVar5 < 0x501) {
      if (uVar5 == 0x500) {
        result->type = result->type & 0xf9 | 9;
        result->index = '\0';
      }
      else {
        if (uVar5 != 0x400) goto LAB_0041ca32;
        bVar1 = result->type & 0xf8 | 8;
LAB_0041cad4:
        result->type = bVar1;
      }
    }
    else if (uVar5 < 0x701) {
      if (uVar5 == 0x700) {
        bVar1 = result->type & 0xf4 | 4;
        goto LAB_0041cad4;
      }
      if (uVar5 != 0x600) goto LAB_0041ca32;
      result->type = result->type & 0xfb | 0xb;
      result->base = 'b';
    }
    else if (uVar5 == 0x800) {
      result->base = result->base + -0x10;
    }
    else {
      if (uVar5 != 0x900) {
        if (uVar5 != 0xa00) goto LAB_0041ca32;
        bVar1 = result->type & 0xf3 | 3;
        goto LAB_0041cad4;
      }
      result->base = result->base + -0xf;
    }
    switch(uVar4 & 0xff) {
    case 0:
      break;
    case 1:
      result->disp = -result->disp;
      break;
    case 2:
      result->disp = result->disp + 4;
      break;
    case 3:
      result->disp = 4;
      break;
    case 4:
      result->disp = result->disp + node->parent->val2;
      break;
    case 5:
      parent = node->parent;
      iVar3 = bit_field_byte_offset(parent);
      result->disp = result->disp + parent->val2 + iVar3;
      break;
    case 6:
      result->disp = result->disp +
                     (int)(node->parent->desc->bit_offset / '\x10') + node->parent->val2;
      break;
    case 7:
      result->disp = (result->disp & 0xfU) << 4;
      break;
    case 8:
      iVar3 = bit_field_byte_offset(node);
      result->disp = result->disp + iVar3;
      break;
    case 9:
      iVar3 = bit_field_word_offset(node);
      result->disp = result->disp + iVar3;
      break;
    case 10:
      desc = node->parent->desc;
      result->disp = ((1 << (desc->bit_width & 0x1fU)) - 1U & result->disp) <<
                     (('\b' - desc->bit_offset % '\b') - desc->bit_width & 0x1fU);
      break;
    case 0xb:
      desc = node->parent->desc;
      result->disp = ((1 << (desc->bit_width & 0x1fU)) - 1U & result->disp) <<
                     (('\x10' - desc->bit_offset % '\x10') - desc->bit_width & 0x1fU);
      break;
    case 0xc:
      desc = node->parent->desc;
      bVar1 = desc->bit_width;
      result->disp = ((1 << (bVar1 & 0x1f)) - 1U & result->disp) <<
                     ((' ' - desc->bit_offset) - bVar1 & 0x1f);
      break;
    case 0xd:
      sVar2 = multiplier_shift_count(result->disp);
      result->disp = (int)sVar2;
      break;
    case 0xe:
      sVar2 = two_bit_mask_bit_position(result->disp,0);
      result->disp = (int)sVar2;
      break;
    case 0xf:
      result->disp = (int)result->labels;
      break;
    default:
      report_codegen_message(0x11fa,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    }
    goto switchD_0041cae1_caseD_0;
  }
  switch(uVar4 & 0x3fff) {
  case 1:
    uVar5 = node->val2;
    break;
  case 2:
    uVar5 = node_value_size(node);
    break;
  case 3:
    iVar3 = node_value_size(node);
    uVar5 = -iVar3;
    break;
  case 4:
    uVar5 = (int)node->desc->bit_offset << 8 | (int)node->desc->bit_width;
    break;
  case 5:
    uVar5 = (1 << (node->desc->bit_width & 0x1fU)) - 1;
    break;
  case 6:
    top_bit = '\a';
    desc = node->desc;
    width = '\b';
    goto LAB_0041c96e;
  case 7:
    bVar1 = node->desc->bit_offset % '\b';
    uVar5 = (1 << (('\b' - node->desc->bit_width) - bVar1 & 0x1f)) - 1U | -0x100 >> (bVar1 & 0x1f);
    break;
  case 8:
    bVar1 = node->desc->bit_offset % '\x10';
    uVar5 = (1 << (('\x10' - node->desc->bit_width) - bVar1 & 0x1f)) - 1U |
            -0x10000 >> (bVar1 & 0x1f);
    break;
  case 9:
    uVar5 = 0;
    top_bit = node->desc->bit_offset;
    if (top_bit != '\0') {
      uVar5 = -0x80000000 >> (top_bit - 1U & 0x1f);
    }
    uVar5 = (1 << ((' ' - node->desc->bit_width) - top_bit & 0x1fU)) - 1U | uVar5;
    break;
  case 10:
    ea_type = '\x05';
    switch(node->desc->builtin) {
    case '\x03':
    case '\x04':
      ea_base = 'a';
      break;
    case '\x05':
    case '\x06':
      ea_base = 'b';
      break;
    default:
      report_codegen_message(0x1233,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
      break;
    case '\x11':
    case '\x12':
      ea_base = 'c';
    }
    break;
  case 0xb:
    uVar5 = node_value_size(node);
    uVar4 = uVar5;
    if ((uVar5 & 3) != 0) {
      uVar4 = (uVar5 & 0xfffffffc) + 4;
    }
    uVar5 = uVar5 - uVar4;
    break;
  case 0xc:
    uVar5 = node->val;
    break;
  case 0xd:
    uVar5 = -node->val;
    break;
  default:
    report_codegen_message(0x11f8,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    break;
  case 0xf:
    iVar3 = count_operands(node);
    node = nth_operand(node,iVar3 + -1);
    bVar1 = 0;
    desc = node->desc;
    source = desc->mem_ea;
    if (source != (ea *)0x0) {
      bVar1 = source->type & 0x1f;
    }
    if (((bVar1 == 0) && (source = &desc->dest, (source->type & 0x1f) == 0)) &&
       (source = &g_ea_pop, (desc->flags2 & 8) == 0)) {
      source = &desc->value;
    }
    ea_type = source->type;
    ea_base = source->base;
    uVar5 = source->disp;
    ea_labels = copy_label_ref_list(source->labels);
    break;
  case 0x10:
    iVar3 = count_operands(node);
    node = nth_operand(node,iVar3 + -2);
    desc = node->desc;
    source = desc->mem_ea;
    bVar1 = 0;
    if (source != (ea *)0x0) {
      bVar1 = source->type & 0x1f;
    }
    if (((bVar1 == 0) && (source = &desc->dest, (source->type & 0x1f) == 0)) &&
       (source = &g_ea_pop, (desc->flags2 & 8) == 0)) {
      source = &desc->value;
    }
    ea_type = source->type;
    ea_base = source->base;
    uVar5 = source->disp;
    ea_labels = copy_label_ref_list(source->labels);
    break;
  case 0x11:
    uVar5 = node_value_size(node);
    if ((uVar5 & 3) != 0) {
      uVar5 = (uVar5 & 0xfffffffc) + 4;
    }
    break;
  case 0x12:
    uVar5 = ~(1 << (7U - node->desc->bit_offset % '\b' & 0x1f));
    break;
  case 0x13:
    top_bit = '\x0f';
    desc = node->desc;
    width = '\x10';
    goto LAB_0041c96e;
  case 0x14:
    top_bit = '\x1f';
    desc = node->desc;
    width = ' ';
LAB_0041c96e:
    uVar5 = 1 << (top_bit - desc->bit_offset % width & 0x1fU);
  }
  fill_ea(result,ea_type,ea_base,-1,'\0',uVar5,ea_labels);
switchD_0041cae1_caseD_0:
  if (result != (ea *)0x0) {
    if ((result->type & 0x1f) == 0xe) {
      result->type = result->type & 0xf7 | 7;
      result->labels = (label_ref *)0x0;
    }
    bVar1 = result->type;
    if (((bVar1 & 0x80) != 0) && (((bVar1 & 0x1f) == 7 || ((bVar1 & 0x1f) == 1)))) {
      result->type = bVar1 ^ 0x80;
    }
    if ((((result->type & 0x1f) == 7) && (labels = result->labels, labels != (label_ref *)0x0)) &&
       ((opnd_code == 0xaf || (((opnd_code == 0xb0 || (opnd_code == 0xb6)) || (opnd_code == 0xba))))
       )) {
      uVar4 = 0;
      if (labels != (label_ref *)0x0) {
        uVar4 = (uint)labels->labno1;
      }
      if ((g_symbol_table[(uVar4 ^ (int)uVar4 >> 0x1f) - ((int)uVar4 >> 0x1f)].attr & 3) != 0) {
        labels = combine_label_ref_lists(labels,(label_ref *)&g_gbr_base_label_ref,1);
        free_label_ref_list(result->labels);
        result->labels = labels;
        iVar3 = g_content_hit;
        if ((node->desc->flags7 & 4) == 0) {
          sVar2 = find_register_holding_constant(result,'@');
          if (sVar2 == 0) {
            g_gpr_contents[0].flags = g_gpr_contents[0].flags | 0x80;
            mask_ptr = &node->desc->reused_regs;
            *mask_ptr = *mask_ptr | 1;
            flags_ptr = &node->desc->flags7;
            *flags_ptr = *flags_ptr | 8;
            iVar3 = g_content_hit;
          }
          flags_ptr = &node->desc->flags7;
          *flags_ptr = *flags_ptr | 4;
          g_content_hit = iVar3;
        }
        if ((node->desc->flags7 & 8) != 0) {
          free_label_ref_list(result->labels);
          fill_ea(result,'\x01','\0',-1,'\0',0,(label_ref *)0x0);
        }
      }
    }
    if (((result->type & 0x1f) == 0xb) && (result->labels != (label_ref *)0x0)) {
      labels = copy_label_ref_list(result->labels);
      result->labels = labels;
    }
  }
  return result;
}



