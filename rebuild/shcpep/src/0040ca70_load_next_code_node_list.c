#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_block_being_loaded
#define g_block_being_loaded (*(code_node * *)(g_sd + 0x5bb4))
#undef g_current_block
#define g_current_block (*(code_node * *)(g_sd + 0x5c38))
#undef g_current_input_record
#define g_current_input_record (*(unsigned char * *)(g_sd + 0x5bbc))


// entry: 0040ca70
// name : load_next_code_node_list
// size : 228
// sig  : code_node * load_next_code_node_list(void)


code_node * load_next_code_node_list(void)

{
  code_node *node;
  code_node *tail;
  code_node *head;
  short labno;
  byte next_op;
  symbol *sym;
  short sym_number;
  
  head = (code_node *)0x0;
  g_block_complete = 0;
  g_block_code_count = 0;
  g_block_being_loaded = (code_node *)0x0;
  tail = (code_node *)0x0;
  do {
    node = tail;
    if (g_input_finished != 0) break;
    node = load_next_code_node();
    if (head == (code_node *)0x0) {
      head = node;
    }
    if (tail != (code_node *)0x0) {
      tail->next = node;
    }
    tail = node;
  } while (g_block_complete == 0);
  if (((((head->target_labno == 0) && ((head->flags & 1) == 0)) && (g_block_code_count < 0xf0)) &&
      (((((next_op = *g_current_input_record, 0x23 < next_op && (next_op < 0x27)) ||
         ((next_op == 0x21 || (next_op == 0x22)))) || ((0x8f < next_op && (next_op < 0x93)))) ||
       ((next_op == 0x94 ||
        ((((0x95 < next_op && (next_op < 0x99)) || (next_op == 0x9a)) ||
         ((next_op == 0x8e || (next_op == 0x10)))))))))) && (g_block_complete == 1)) {
    tail = load_next_code_node();
    node->next = tail;
  }
  labno = head->labno;
  if (labno != 0) {
    sym = g_symbol_hash[labno % 0x3fd];
    sym_number = sym->number;
    while (sym_number != labno) {
      sym = sym->hash_next;
      sym_number = sym->number;
    }
  }
  if (g_current_block != head) {
    head = g_current_block;
  }
  return head;
}



