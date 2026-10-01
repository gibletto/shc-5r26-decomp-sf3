#include "decls.h"
#include "imports.h"

// entry: 004147f0
// name : emit_operand_moves_to_target_registers
// size : 272
// sig  : void emit_operand_moves_to_target_registers(gen_node * node, int skip)


int __cdecl emit_operand_moves_to_target_registers(gen_node *node,int skip)

{
  unsigned char _frec_1c[28];
#define slot_src (*(ea * *)(_frec_1c + 0))
#define slot_reg (*(ea * *)(_frec_1c + 4))
#define local_14 (*(ea * *)(_frec_1c + 8))
  short reg;
  int i;
  gen_node *operand;
  tmpl_header *tmpl;
  node_desc *desc;
  
  i = count_operands(node);
  i = (i - skip) + -1;
  if (0 < i) {
    do {
      operand = nth_operand(node,i);
      desc = operand->desc;
      if ((desc->target_regs != 0) &&
         ((((desc->dest).type & 0x1f) != 0 || ((desc->flags2 & 8) != 0)))) {
        reg = mask_to_register((int)(short)desc->target_regs);
        if ((operand->desc->flags2 & 8) == 0) {
          slot_src = &operand->desc->dest;
        }
        else {
          slot_src = &g_ea_pop;
        }
        slot_reg = new_ea_operand_with_flags('\x01',(char)reg,-1,0,'\0',(label_ref *)0x0);
        load_slot_register_operands(4,operand,&slot_src);
        tmpl = select_transfer_template
                         (0,0,slot_src,slot_reg,local_14,operand->type,operand->desc->usage,node);
        if (tmpl != (tmpl_header *)0x0) {
          emit_template_record_sequence_for_node(operand,tmpl->entries,&slot_src);
        }
        free_slot_register_operands(4,&slot_src);
        free_ea(slot_reg);
      }
      i = i + -1;
    } while (i != 0);
  }
  return;
#undef slot_src
#undef slot_reg
#undef local_14
}



