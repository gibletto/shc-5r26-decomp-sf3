#include "decls.h"
#include "imports.h"

// entry: 004146a0
// name : emit_mac_builtin_records
// size : 335
// sig  : void emit_mac_builtin_records(int builtin, int count, ea * left, ea * right, ea * mask)


int __cdecl emit_mac_builtin_records(int builtin,int count,ea *left,ea *right,ea *mask)

{
  ea *opnd2;
  ea *opnd1;
  uchar mac_size;
  ea *right_saved;
  gen_node *no_node;
  
  if ((builtin == 0x18) || (builtin == 0x19)) {
    mac_size = '\x01';
  }
  else {
    mac_size = '\x02';
  }
  if ((builtin == 0x19) || (builtin == 0x1b)) {
    right_saved = copy_ea(right);
  }
  left->type = left->type & 0xf4 | 4;
  right->type = right->type & 0xf4 | 4;
  if ((builtin == 0x18) || (builtin == 0x1a)) {
    if (0 < count) {
      do {
        no_node = (gen_node *)0x0;
        opnd2 = copy_ea(right);
        opnd1 = copy_ea(left);
        emit_psd_for_node(0x72,-1,'\0',mac_size,opnd1,opnd2,no_node);
        count = count + -1;
      } while (count != 0);
    }
  }
  else if (0 < count) {
    do {
      no_node = (gen_node *)0x0;
      opnd2 = copy_ea(right);
      opnd1 = copy_ea(left);
      emit_psd_for_node(0x72,-1,'\0',mac_size,opnd1,opnd2,no_node);
      no_node = (gen_node *)0x0;
      opnd2 = copy_ea(right_saved);
      opnd1 = copy_ea(mask);
      emit_psd_for_node(0x80,-1,'\0','\x02',opnd1,opnd2,no_node);
      count = count + -1;
    } while (count != 0);
  }
  if ((builtin == 0x19) || (builtin == 0x1b)) {
    free_ea(mask);
    free_ea(right_saved);
  }
  free_ea(left);
  free_ea(right);
  return;
}



