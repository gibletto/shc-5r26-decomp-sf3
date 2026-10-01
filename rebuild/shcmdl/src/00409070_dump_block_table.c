#include "decls.h"
#include "imports.h"

// entry: 00409070
// name : dump_block_table
// size : 707
// sig  : void dump_block_table(bblock * block, char * title)


int __cdecl dump_block_table(bblock *block,char *title)

{
  node_list *cell;
  int i;
  uint *set;
  
  FID_conflict__wprintf(s___basic_block_table_dump__depth__00434f14,title);
  FID_conflict__wprintf(s__________________________________00434ee8);
  while (block != (bblock *)0x0) {
    FID_conflict__wprintf(s___CUR_number__d__address_0x_08x_00434ec4,(int)block->number,block);
    FID_conflict__wprintf(s___startpp__d__endpp__d_00434eac,(uint)block->startpp,(uint)block->endpp)
    ;
    FID_conflict__wprintf(s___lptbl_0x_08x_00434e9c,block->lptbl);
    FID_conflict__wprintf(&g_str_newline);
    FID_conflict__wprintf
              (s___startexpp__d__endexpp__d_00434e80,(uint)(ushort)block->usepreg,
               (uint)*(ushort *)((int)&block->usepreg + 2));
    FID_conflict__wprintf(s___usepreg_0x_08x_00434e6c,block->usepreg);
    FID_conflict__wprintf(s___usefreg_0x_08x_00434e58,block->usefreg);
    FID_conflict__wprintf(s___suclist__00434e4c);
    if (block->suclst == (block_list *)0x0) {
      FID_conflict__wprintf(s_NULL_00434e44);
    }
    else {
      dump_block_numbers(block->suclst);
    }
    FID_conflict__wprintf(s___prelist__00434e38);
    if (block->prelst == (block_list *)0x0) {
      FID_conflict__wprintf(s_NULL_00434e44);
    }
    else {
      dump_block_numbers(block->prelst);
    }
    FID_conflict__wprintf(s___bn_next__00434e2c);
    if (block->bn_next == (bblock *)0x0) {
      FID_conflict__wprintf(s_NULL_00434e44);
    }
    else {
      FID_conflict__wprintf(s__5d__00434e24,(int)block->bn_next->number);
    }
    FID_conflict__wprintf(s___b_trelst__00434e18);
    if (block->ilnode == (node_list *)0x0) {
      FID_conflict__wprintf(s_NULL_00434e44);
    }
    else {
      dump_tree_node(block->ilnode->node,1);
    }
    if ((g_debug_flags & 0x3000000) == 0x3000000) {
      set = block->d_in;
      FID_conflict__wprintf
                (s___d_in___08x__08x__08x__08x__08x_00434de4,*set,set[1],set[2],set[3],set[4],set[5]
                 ,set[6],set[7]);
      set = block->l_in;
      FID_conflict__wprintf
                (s___l_in___08x__08x__08x__08x__08x_00434db0,*set,set[1],set[2],set[3],set[4],set[5]
                 ,set[6],set[7]);
      set = block->l_in;
      FID_conflict__wprintf
                (s____08x__08x__08x__08x__08x__08x___00434d7c,set[8],set[9],set[10],set[0xb],
                 set[0xc],set[0xd],set[0xe],set[0xf]);
      set = block->out;
      FID_conflict__wprintf
                (s____out___08x__08x__08x__08x__08x_00434d48,*set,set[1],set[2],set[3],set[4],set[5]
                 ,set[6],set[7]);
      set = block->out;
      FID_conflict__wprintf
                (s____08x__08x__08x__08x__08x__08x___00434d7c,set[8],set[9],set[10],set[0xb],
                 set[0xc],set[0xd],set[0xe],set[0xf]);
    }
    if ((g_debug_flags & 0x3000000) != 0) {
      i = 1;
      for (cell = block->statics; cell != (node_list *)0x0; cell = cell->next) {
        FID_conflict__wprintf(s___local_static_datas__d_00434d2c,i);
        dump_tree_node(cell->node,2);
        i = i + 1;
      }
    }
    block = block->bn_next;
    FID_conflict__wprintf(s__________________________________00434ee8);
  }
  return;
}



