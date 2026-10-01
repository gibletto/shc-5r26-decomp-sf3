#include "decls.h"
#include "imports.h"

// entry: 00401ce0
// name : retarget_block_branch
// size : 240
// sig  : char retarget_block_branch(flow_block * block, psd * branch, short labno, flow_block * target)


char __cdecl retarget_block_branch(flow_block *block,psd *branch,short labno,flow_block *target)

{
  char unlinked;
  code_node *node;
  psd_op op;
  
  if (((block == (flow_block *)0x0) || (node = block->code, node == (code_node *)0x0)) ||
     (node->target_labno == 0)) {
    return '\0';
  }
  if (branch == (psd *)0x0) {
    branch = find_block_final_record(node);
  }
  op = branch->op;
  if ((((op != OP_JUMP) && (op != OP_JUMPT)) &&
      ((op != OP_JUMPF && ((op != OP_RETURN && (op != OP_BF)))))) &&
     ((op != OP_BT && ((((op != OP_BRA && (op != OP_BSR)) && (op != OP_BT_S)) && (op != OP_BF_S)))))
     ) {
    return '\0';
  }
  if (target == (flow_block *)0x0) {
    if (labno != 0) {
      return '\0';
    }
  }
  else if (target->code->labno != labno) {
    return '\0';
  }
  unlinked = unlink_from_target_preds(block);
  if (unlinked != '\0') {
    decrement_label_ref_count(branch->ea1->labels->labno1);
  }
  if (labno == 0) {
    delete_psd_record(branch);
    block->flags = block->flags & 0xfe;
  }
  else {
    branch->ea1->labels->labno1 = labno;
  }
  node->target_labno = labno;
  block->target = target;
  return '\x01';
}



