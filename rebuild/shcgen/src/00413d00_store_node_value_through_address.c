#include "decls.h"
#include "imports.h"

// entry: 00413d00
// name : store_node_value_through_address
// size : 128
// sig  : void store_node_value_through_address(gen_node * node)


int __cdecl store_node_value_through_address(gen_node *node)

{
  unsigned char _frec_1c[28];
#define opnd0 (*(ea * *)(_frec_1c + 0))
#define opnd1 (*(ea * *)(_frec_1c + 4))
#define opnd2 (*(ea * *)(_frec_1c + 8))
  tmpl_header *tmpl;
  
  opnd0 = &node->desc->value;
  opnd1 = node->desc->mem_ea;
  load_slot_register_operands(1,node,&opnd0);
  tmpl = select_transfer_template(0,0,opnd0,opnd1,opnd2,node->type,node->desc->usage,node);
  if (tmpl != (tmpl_header *)0x0) {
    emit_template_record_sequence_for_node(node,tmpl->entries,&opnd0);
  }
  free_slot_register_operands(1,&opnd0);
  return;
#undef opnd0
#undef opnd1
#undef opnd2
}



