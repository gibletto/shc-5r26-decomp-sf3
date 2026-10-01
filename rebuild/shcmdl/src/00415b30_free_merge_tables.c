#include "decls.h"
#include "imports.h"

// entry: 00415b30
// name : free_merge_tables
// size : 194
// sig  : void free_merge_tables(void)


int __cdecl free_merge_tables(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  uchar *group_bucket;
  
  g_merge_whole_blocks = '\0';
  puVar4 = &g_common_tail_buckets;
  do {
    puVar2 = (undefined4 *)*puVar4;
    while (puVar2 != (undefined4 *)0x0) {
      puVar1 = (undefined4 *)*puVar2;
      puVar3 = puVar2;
      while (puVar2 = puVar1, puVar3 != (undefined4 *)0x0) {
        puVar2 = (undefined4 *)puVar3[1];
        pool_free(puVar3,0x18);
        puVar3 = puVar2;
      }
    }
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  } while (puVar4 < &g_spec_sym1);
  group_bucket = (uchar *)&g_successor_groups;
  do {
    puVar4 = *(undefined4 **)group_bucket;
    while (puVar4 != (undefined4 *)0x0) {
      puVar2 = (undefined4 *)*puVar4;
      puVar1 = puVar4;
      while (puVar4 = puVar2, puVar1 != (undefined4 *)0x0) {
        puVar4 = (undefined4 *)puVar1[1];
        pool_free(puVar1,0x10);
        puVar1 = puVar4;
      }
    }
    group_bucket[0] = '\0';
    group_bucket[1] = '\0';
    group_bucket[2] = '\0';
    group_bucket[3] = '\0';
    group_bucket = group_bucket + 4;
  } while (group_bucket < &g_merge_whole_blocks);
  puVar4 = &g_identical_block_buckets;
  do {
    puVar2 = (undefined4 *)*puVar4;
    while (puVar2 != (undefined4 *)0x0) {
      puVar1 = (undefined4 *)*puVar2;
      puVar3 = puVar2;
      while (puVar2 = puVar1, puVar3 != (undefined4 *)0x0) {
        puVar2 = (undefined4 *)puVar3[1];
        pool_free(puVar3,0x14);
        puVar3 = puVar2;
      }
    }
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  } while (puVar4 < &g_successor_groups);
  return;
}



