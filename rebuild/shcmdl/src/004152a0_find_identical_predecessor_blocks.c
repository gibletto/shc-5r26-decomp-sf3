#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_exit_block
#define g_exit_block (*(bblock * *)(g_sd + 0x267cc))


// entry: 004152a0
// name : find_identical_predecessor_blocks
// size : 132
// sig  : void find_identical_predecessor_blocks(void)


int __cdecl find_identical_predecessor_blocks(void)

{
  bblock *succ_a;
  block_list *list_a;
  block_list *list_b;
  bblock *member;
  block_list *other;
  block_list *pred;
  
  g_merge_whole_blocks = '\x01';
  g_merge_pair_count = 0;
  pred = g_exit_block->prelst;
  do {
    if (pred == (block_list *)0x0) {
      return;
    }
    succ_a = pred->block;
    for (member = succ_a; (member != (bblock *)0x0 && (member->merge_next != (bblock *)0x0));
        member = member->merge_next) {
      for (other = g_exit_block->prelst; other != (block_list *)0x0; other = other->next) {
        if (other->block->number == member->merge_next->number) {
          list_a = succ_a->prelst;
          if (((list_a != (block_list *)0x0) &&
              (list_b = other->block->prelst, list_b != (block_list *)0x0)) &&
             (list_b->block != list_a->block)) {
            match_predecessor_lists(list_a,list_b,succ_a,other->block);
          }
          break;
        }
      }
    }
    pred = pred->next;
  } while( true );
}



