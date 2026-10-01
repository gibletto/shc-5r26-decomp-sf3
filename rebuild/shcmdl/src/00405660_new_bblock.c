#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cfg_cur_block
#define g_cfg_cur_block (*(bblock * *)(g_sd + 0x26868))


// entry: 00405660
// name : new_bblock
// size : 349
// sig  : bblock * new_bblock(void)


bblock * new_bblock(void)

{
  bblock *block;
  bblock_sets *sets;
  uint *kill;
  uint *gen;
  uint *d_in;
  uint *reach_out;
  uint *def;
  uint *live_out;
  uint *use;
  uint *l_in;
  
  if (0xff < g_block_count) {
    cfg_out_of_memory();
  }
  block = pool_alloc(0x68);
  if (block == (bblock *)0x0) {
    cfg_out_of_memory();
  }
  sets = pool_alloc(0x14);
  if (sets == (bblock_sets *)0x0) {
    cfg_out_of_memory();
  }
  kill = pool_alloc(0x20);
  if (kill == (uint *)0x0) {
    cfg_out_of_memory();
  }
  gen = pool_alloc(0x20);
  if (gen == (uint *)0x0) {
    cfg_out_of_memory();
  }
  d_in = pool_alloc(0x20);
  if (d_in == (uint *)0x0) {
    cfg_out_of_memory();
  }
  reach_out = pool_alloc(0x20);
  if (reach_out == (uint *)0x0) {
    cfg_out_of_memory();
  }
  def = pool_alloc(0x40);
  if (def == (uint *)0x0) {
    cfg_out_of_memory();
  }
  live_out = pool_alloc(0x40);
  if (live_out == (uint *)0x0) {
    cfg_out_of_memory();
  }
  use = pool_alloc(0x40);
  if (use == (uint *)0x0) {
    cfg_out_of_memory();
  }
  l_in = pool_alloc(0x40);
  if (l_in == (uint *)0x0) {
    cfg_out_of_memory();
  }
  block->sets = sets;
  sets->kill = kill;
  block->sets->reach_out = reach_out;
  block->sets->gen = gen;
  block->d_in = d_in;
  block->sets->def = def;
  block->sets->use = use;
  block->out = live_out;
  block->l_in = l_in;
  if (g_cfg_cur_block != (bblock *)0x0) {
    g_cfg_cur_block->bn_next = block;
  }
  g_block_count = g_block_count + 1;
  block->number = (short)g_block_count;
  return block;
}



