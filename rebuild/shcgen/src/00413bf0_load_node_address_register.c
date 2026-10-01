#include "decls.h"
#include "imports.h"

// entry: 00413bf0
// name : load_node_address_register
// size : 261
// sig  : void load_node_address_register(gen_node * node)


int __cdecl load_node_address_register(gen_node *node)

{
  unsigned char _frec_1c[28];
#define opnd0 (*(ea * *)(_frec_1c + 0))
#define opnd1 (*(ea * *)(_frec_1c + 4))
#define opnd2 (*(ea * *)(_frec_1c + 8))
  tmpl_header *tmpl;
  byte ea_kind;
  node_desc *desc;
  uchar saved_type;
  
  ea_kind = 0;
  desc = node->desc;
  if (desc->addr_reg_ea != (ea *)0x0) {
    ea_kind = desc->addr_reg_ea->type & 0x1f;
  }
  if (ea_kind != 0) {
    if ((desc->flags2 & 8) == 0) {
      opnd0 = &desc->dest;
      opnd1 = desc->addr_reg_ea;
      load_slot_register_operands(4,node,&opnd0);
      desc = node->desc;
      saved_type = node->type;
      if ((desc->usage == '\x03') || ((desc->flags3 & 0x20) != 0)) {
        node->type = '@';
      }
      tmpl = select_transfer_template(0,0,opnd0,opnd1,opnd2,node->type,desc->usage,node);
      if (tmpl != (tmpl_header *)0x0) {
        emit_template_record_sequence_for_node(node,tmpl->entries,&opnd0);
      }
      node->type = saved_type;
      free_slot_register_operands(4,&opnd0);
      return;
    }
    opnd0 = new_ea_operand_with_flags('\x04','\x0f',-1,0,'\0',(label_ref *)0x0);
    opnd1 = copy_ea(node->desc->addr_reg_ea);
    emit_psd_for_node(0x40,-1,'\0','\x02',opnd0,opnd1,(gen_node *)0x0);
  }
  return;
#undef opnd0
#undef opnd1
#undef opnd2
}



