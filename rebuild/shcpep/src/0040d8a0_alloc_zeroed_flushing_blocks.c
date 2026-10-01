#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_node_list
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))
#undef g_current_symbol
#define g_current_symbol (*(symbol * *)(g_sd + 0x6d4c))
#undef g_last_allocation
#define g_last_allocation (*(int * *)(g_sd + 0x6d44))


// entry: 0040d8a0
// name : alloc_zeroed_flushing_blocks
// size : 273
// sig  : int * alloc_zeroed_flushing_blocks(uint size)


int * __cdecl alloc_zeroed_flushing_blocks(uint size)

{
  code_node *block;
  label_block_ref *ptr;
  short i;
  int *mem;
  label_block_ref *prev_ref;
  label_block_ref *first_ref;
  label_block_ref *next_ref;
  
  prev_ref = (label_block_ref *)0x0;
  mem = try_alloc_zeroed(size);
  block = g_current_node_list;
  do {
    g_last_allocation = mem;
    g_current_node_list = block;
    if (mem != (int *)0x0) {
      i = 0;
      if (0 < (int)size) {
        do {
          i = i + 1;
          *(undefined1 *)mem = 0;
          mem = (int *)((int)mem + 1);
        } while ((int)i < (int)size);
      }
      return g_last_allocation;
    }
    flush_block_to_output(block);
    g_current_node_list = g_current_node_list->next_block;
    if (block->target_labno != 0) {
      g_current_symbol = g_symbol_hash[block->target_labno % 0x3fd];
      if (g_current_symbol->number != block->target_labno) {
        do {
          g_current_symbol = g_current_symbol->hash_next;
        } while (g_current_symbol->number != block->target_labno);
      }
      first_ref = g_current_symbol->ref_blocks;
      if (first_ref != (label_block_ref *)0x0) {
        if (first_ref->block == block) {
          first_ref->block = (code_node *)0x0;
        }
        next_ref = first_ref->next;
        while (ptr = next_ref, ptr != (label_block_ref *)0x0) {
          if ((ptr->block != (code_node *)0x0) && (block == ptr->block)) {
            ptr->block = (code_node *)0x0;
            if (prev_ref == (label_block_ref *)0x0) {
              prev_ref = first_ref;
            }
            prev_ref->next = ptr->next;
            pool_free(ptr,8);
            break;
          }
          prev_ref = ptr;
          next_ref = ptr->next;
        }
      }
    }
    free_node_list(block);
    mem = try_alloc_zeroed(size);
    block = g_current_node_list;
  } while( true );
}



