#include "decls.h"
#include "imports.h"

// entry: 00415110
// name : record_common_tail
// size : 329
// sig  : void record_common_tail(il_node * stmt_a, il_node * stmt_b, bblock * block_a, bblock * block_b, char whole)


int __cdecl record_common_tail(il_node *stmt_a,il_node *stmt_b,bblock *block_a,bblock *block_b,char whole)

{
  ushort uVar1;
  undefined4 *rec_a;
  void *rec_b;
  ushort uVar2;
  bblock *into;
  bblock *block;
  
  if ((g_merge_whole_blocks != '\0') ||
     (((block_a->suclst == (block_list *)0x0 || (block_a->suclst->next == (block_list *)0x0)) &&
      ((block_b->suclst == (block_list *)0x0 || (block_b->suclst->next == (block_list *)0x0)))))) {
    uVar1 = block_a->number;
    uVar2 = block_b->number;
    if (whole != '\0') {
      into = block_b;
      block = block_a;
      if ((short)uVar2 <= (short)uVar1) {
        into = block_a;
        block = block_b;
      }
      link_merged_block(into,block);
    }
    rec_a = pool_alloc(0x18);
    if (rec_a == (undefined4 *)0x0) {
      free_merge_tables_and_abort();
    }
    rec_b = pool_alloc(0x18);
    if (rec_b == (void *)0x0) {
      free_merge_tables_and_abort();
    }
    *(byte *)((int)rec_a + 0x16) = *(byte *)((int)rec_a + 0x16) | 1;
    *(byte *)((int)rec_b + 0x16) = *(byte *)((int)rec_b + 0x16) | 2;
    g_merge_id = g_merge_id + 1;
    rec_a[4] = (int)g_merge_id;
    *(int *)((int)rec_b + 0x10) = (int)g_merge_id;
    if (stmt_a->parent->op == IL_RETURN) {
      stmt_a = stmt_a->parent;
    }
    if (stmt_b->parent->op == IL_RETURN) {
      stmt_b = stmt_b->parent;
    }
    if ((short)uVar1 < (short)uVar2) {
      rec_a[2] = block_b;
      *(short *)(rec_a + 5) = block_b->number;
      rec_a[3] = stmt_b;
      *(bblock **)((int)rec_b + 8) = block_a;
      *(short *)((int)rec_b + 0x14) = block_a->number;
      *(il_node **)((int)rec_b + 0xc) = stmt_a;
    }
    else {
      rec_a[2] = block_a;
      *(short *)(rec_a + 5) = block_a->number;
      rec_a[3] = stmt_a;
      *(bblock **)((int)rec_b + 8) = block_b;
      *(short *)((int)rec_b + 0x14) = block_b->number;
      *(il_node **)((int)rec_b + 0xc) = stmt_b;
      uVar2 = uVar1;
    }
    uVar1 = (short)uVar2 >> 0xf;
    *rec_a = (&g_common_tail_buckets)[(short)(((uVar2 ^ uVar1) - uVar1 & 0xf ^ uVar1) - uVar1)];
    rec_a[1] = rec_b;
    (&g_common_tail_buckets)[(short)(((uVar2 ^ uVar1) - uVar1 & 0xf ^ uVar1) - uVar1)] = rec_a;
  }
  return;
}



