#include "decls.h"
#include "imports.h"

// entry: 00415330
// name : match_predecessor_lists
// size : 499
// sig  : uint match_predecessor_lists(block_list * list_a, block_list * list_b, bblock * succ_a, bblock * succ_b)


uint __cdecl match_predecessor_lists(block_list *list_a,block_list *list_b,bblock *succ_a,bblock *succ_b)

{
  bblock *a;
  bblock *b;
  block_list *pbVar1;
  block_list *pbVar2;
  bblock *pbVar3;
  ushort merged_flag;
  bblock *member;
  il_node *stmt_a;
  il_node *stmt_b;
  int nsucc_a;
  int nsucc_b;
  uint res;
  byte *flagp;
  
  a = list_a->block;
  b = list_b->block;
  if (((int)b->number - (int)a->number) + (int)succ_a->number != (int)succ_b->number) {
    return 1;
  }
  if (b == a) {
    return 0;
  }
  merged_flag = a->flag & 0x100;
  if ((merged_flag != 0) || ((b->flag & 0x100) != 0)) {
    if ((merged_flag != 0) && ((b->flag & 0x100) != 0)) {
      return 0;
    }
    return 1;
  }
  res = compare_blocks(a,b);
  if (res != 1) {
    nsucc_a = 0;
    pbVar1 = a->suclst;
    for (pbVar2 = pbVar1; pbVar2 != (block_list *)0x0; pbVar2 = pbVar2->next) {
      nsucc_a = nsucc_a + 1;
    }
    nsucc_b = 0;
    for (pbVar2 = b->suclst; pbVar2 != (block_list *)0x0; pbVar2 = pbVar2->next) {
      nsucc_b = nsucc_b + 1;
    }
    if ((nsucc_b == nsucc_a) && (nsucc_a < 3)) {
      for (; pbVar1 != (block_list *)0x0; pbVar1 = pbVar1->next) {
        if (pbVar1->block != succ_a) {
          for (pbVar2 = b->suclst; pbVar2 != (block_list *)0x0; pbVar2 = pbVar2->next) {
            pbVar3 = pbVar2->block;
            if (pbVar3 != succ_b) {
              member = pbVar1->block->merge_next;
              if (member != (bblock *)0x0) {
                do {
                  if (member == pbVar3) break;
                  member = member->merge_next;
                } while (member != (bblock *)0x0);
                if (member != (bblock *)0x0) goto LAB_00415440;
              }
              if (pbVar3->number != pbVar1->block->number) {
                pbVar3 = a;
                for (member = a->merge_next; member != (bblock *)0x0; member = member->merge_next) {
                  if (member == b) {
                    pbVar3->merge_next = member->merge_next;
                    break;
                  }
                  pbVar3 = member;
                }
                flagp = (byte *)((int)&a->flag + 1);
                *flagp = *flagp & 0xfe;
                flagp = (byte *)((int)&b->flag + 1);
                *flagp = *flagp & 0xfe;
                res = 1;
              }
            }
LAB_00415440: ;
          }
        }
      }
    }
    else {
      res = 1;
    }
  }
  if (res == 0) {
    record_identical_blocks(a,b);
  }
  else if (res == 2) {
    stmt_a = last_statement_of_list(a->ilnode);
    stmt_b = last_statement_of_list(b->ilnode);
    match_statement_tails(stmt_a,stmt_b,a,b);
  }
  if ((((res == 0) && (pbVar2 = a->prelst, pbVar2 != (block_list *)0x0)) &&
      (pbVar1 = b->prelst, pbVar1 != (block_list *)0x0)) && (pbVar2->block != pbVar1->block)) {
    match_predecessor_lists(pbVar2,pbVar1,a,b);
  }
  pbVar2 = list_a->next;
  for (pbVar1 = list_b->next; (pbVar2 != (block_list *)0x0 && (pbVar1 != (block_list *)0x0));
      pbVar1 = pbVar1->next) {
    if (pbVar1->block != pbVar2->block) {
      match_predecessor_lists(pbVar2,pbVar1,succ_a,succ_b);
    }
    pbVar2 = pbVar2->next;
  }
  return res;
}



