#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 00402200
// name : prepare_unary_plus_node
// size : 851
// sig  : void prepare_unary_plus_node(gen_node * node)


int __cdecl prepare_unary_plus_node(gen_node *node)

{
  byte ea_kind;
  short reg;
  ea *operand;
  gen_node *child;
  node_desc *desc;
  uchar *flags_p;
  bool handled;
  
  handled = false;
  child = node->child;
  desc = node->desc;
  if ((desc->flags2 & 8) == 0) {
    if ((desc->flags3 & 0x20) == 0) {
      operand = &desc->dest;
      ea_kind = operand->type & 0x1f;
      if (ea_kind == 0) {
LAB_00402340:
        if (desc->target_regs != 0) {
          reg = mask_to_register((int)(short)desc->target_regs);
          handled = true;
          fill_ea(&child->desc->dest,'\x01',(char)reg,-1,'\0',0,(label_ref *)0x0);
          fill_ea(&node->desc->value,'\x01',(char)reg,-1,'\0',0,(label_ref *)0x0);
          node->desc->opnd_class = '\x01';
          goto LAB_00402438;
        }
        if (desc->ftarget_regs != 0) {
          reg = float_mask_to_register(desc->ftarget_regs);
          handled = true;
          fill_ea(&child->desc->dest,'\x01',(char)reg,-1,'\0',0,(label_ref *)0x0);
          fill_ea(&node->desc->value,'\x01',(char)reg,-1,'\0',0,(label_ref *)0x0);
          node->desc->opnd_class = '\x01';
          goto LAB_00402438;
        }
        if (ea_kind == 0) {
          if (desc->usage != '\0') goto LAB_00402438;
        }
        else {
          operand->type = operand->type & 0xf0;
          if ((g_request->cpu == 4) || ((node->type & 0xf8) != 0x30)) goto LAB_00402438;
          flags_p = &child->desc->flags2;
          *flags_p = *flags_p | 8;
          flags_p = &node->desc->flags2;
          *flags_p = *flags_p | 8;
          node->desc->opnd_class = '\x03';
        }
      }
      else {
        if ((ea_kind == 2) || (ea_kind == 8)) {
          if ((desc->dest).base < '\x0f') {
            if ((1 << ((desc->dest).base & 0x1fU) & (int)(short)~g_var_gpr_mask) != 0)
            goto LAB_00402340;
          }
          if (((desc->dest).base < ' ') && ('\x0f' < (desc->dest).base)) {
            if ((1 << ((desc->dest).base - 0x10U & 0x1f) & (int)(short)~g_var_fpr_mask) != 0)
            goto LAB_00402340;
          }
          if (((desc->dest).base < '/') && ('\x1f' < (desc->dest).base)) {
            if (((int)(short)g_var_fpr_mask &
                (1 << ((desc->dest).base - 0x1fU & 0x1f) | 1 << ((desc->dest).base - 0x20U & 0x1f)))
                == 0) goto LAB_00402340;
          }
        }
        copy_ea_into(&child->desc->dest,operand);
      }
    }
    else {
      flags_p = &child->desc->flags3;
      *flags_p = *flags_p | 0x20;
      copy_ea_into(&child->desc->dest,&node->desc->dest);
      flags_p = &node->desc->flags3;
      *flags_p = *flags_p & 0xdf;
      operand = &node->desc->dest;
      operand->type = operand->type & 0xf0;
    }
  }
  else {
    flags_p = &child->desc->flags2;
    *flags_p = *flags_p | 8;
    node->desc->opnd_class = '\x03';
  }
  handled = true;
LAB_00402438:
  child->desc->busy_regs = node->desc->busy_regs;
  child->desc->fbusy_regs = node->desc->fbusy_regs;
  child->desc->frame_top = node->desc->frame_top;
  flags_p = &child->desc->flags7;
  *flags_p = *flags_p | node->desc->flags7 & 0x40;
  desc = child->desc;
  if ((desc->pref_regs == 0) && (desc->fpref_regs == 0)) {
    desc->pref_regs = node->desc->pref_regs;
    child->desc->fpref_regs = node->desc->fpref_regs;
  }
  dispatch_and_finalize_code_node(child);
  if (!handled) {
    if (child->desc->opnd_class == '\x02') {
      flags_p = &node->desc->flags3;
      *flags_p = *flags_p | 8;
      if (node->desc->tmpl == (tmpl_header *)0x0) {
        flags_p = &node->desc->flags3;
        *flags_p = *flags_p | 0x80;
      }
    }
    node->desc->busy_regs = child->desc->busy_regs;
    node->desc->fbusy_regs = child->desc->fbusy_regs;
    node->desc->frame_top = child->desc->frame_top;
    ea_kind = 0;
    desc = child->desc;
    operand = desc->mem_ea;
    if (operand != (ea *)0x0) {
      ea_kind = operand->type & 0x1f;
    }
    if (((ea_kind == 0) && (operand = &desc->dest, (operand->type & 0x1f) == 0)) &&
       (operand = &g_ea_pop, (desc->flags2 & 8) == 0)) {
      operand = &desc->value;
    }
    copy_ea_into(&node->desc->value,operand);
    node->desc->opnd_class = child->desc->opnd_class;
  }
  flags_p = &node->desc->flags3;
  *flags_p = *flags_p | 0x80;
  flags_p = &node->desc->flags3;
  *flags_p = *flags_p | 8;
  return;
}



