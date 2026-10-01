#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_call_list
#define g_call_list (*(node_cell * *)(g_sd + 0x164b0))
#undef g_const_data_list
#define g_const_data_list (*(const_data * *)(g_sd + 0x16498))
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))
#undef g_lreg_list
#define g_lreg_list (*(lreg * *)(g_sd + 0x16264))
#undef g_mem_freq_list
#define g_mem_freq_list (*(mem_freq * *)(g_sd + 0x164a0))


// entry: 00413440
// name : free_register_allocation_tables
// size : 636
// sig  : void free_register_allocation_tables(void)


int __cdecl free_register_allocation_tables(void)

{
  char *pcVar1;
  lreg **slot;
  lreg *lr;
  lifetbl **bucket;
  int i;
  bblock *blk;
  node_cell *call;
  const_data *cdata;
  undefined4 *cell;
  mem_freq *freq;
  node_list *item;
  lifetbl *life;
  int lr_addr;
  undefined4 *next;
  bblock *next_blk;
  node_list *next_item;
  lifetbl *next_life;
  lreg *next_lreg;
  const_use *next_use;
  const_use *use;
  
  if ((g_debug_flags & 0x2000000) != 0) {
    FID_conflict__wprintf(s_lifehash_________________________004354d0);
  }
  i = 0;
  if (0 < g_pp_count) {
    bucket = g_lifehash_buckets;
    do {
      life = *bucket;
      while (life != (lifetbl *)0x0) {
        if ((g_debug_flags & 0x2000000) != 0) {
          FID_conflict__wprintf(s_lifetbl__d___d__004354b8,(uint)life->st,(uint)life->en);
        }
        next_life = life->next;
        cell = life->lregs;
        while (cell != (undefined4 *)0x0) {
          if ((g_debug_flags & 0x2000000) != 0) {
            lr_addr = cell[1];
            if ((*(short *)(lr_addr + 2) == 1) || (*(short *)(lr_addr + 2) == 3)) {
              pcVar1 = *(char **)(*(int *)(lr_addr + 0x20) + 0x10);
              if (*pcVar1 != 'p') {
                pcVar1 = *(char **)(pcVar1 + 0x14);
              }
            }
            else {
              pcVar1 = *(char **)(*(int *)(*(int *)(lr_addr + 0x20) + 8) + 8);
            }
            FID_conflict__wprintf
                      (s_used_lreg_0x_08x___d___00435498,lr_addr,(int)*(short *)(pcVar1 + 0x30));
          }
          next = (undefined4 *)*cell;
          pool_free(cell,8);
          cell = next;
        }
        pool_free(life,0xc);
        life = next_life;
      }
      i = i + 1;
      *bucket = (lifetbl *)0x0;
      bucket = bucket + 1;
    } while (i < g_pp_count);
  }
  lr = g_lreg_list;
  g_lreg_list = (lreg *)0x0;
  if (lr != (lreg *)0x0) {
    slot = g_lreg_table;
    do {
      slot = slot + 1;
      next_lreg = lr->next;
      cell = lr->life;
      while (cell != (undefined4 *)0x0) {
        next = (undefined4 *)*cell;
        pool_free(cell,8);
        cell = next;
      }
      cell = lr->clashed;
      while (cell != (undefined4 *)0x0) {
        next = (undefined4 *)*cell;
        pool_free(cell,8);
        cell = next;
      }
      cell = lr->exp_area;
      while (cell != (undefined4 *)0x0) {
        next = (undefined4 *)*cell;
        pool_free(cell,0xc);
        cell = next;
      }
      pool_free(lr,0x2c);
      *slot = (lreg *)0x0;
      lr = next_lreg;
    } while (next_lreg != (lreg *)0x0);
  }
  while (cdata = (const_data *)0x0, blk = g_f_chain, g_const_data_list != (const_data *)0x0) {
    use = g_const_data_list->uses;
    while (use != (const_use *)0x0) {
      next_use = use->next;
      pool_free(use,0x14);
      use = next_use;
    }
    cdata = g_const_data_list;
    g_const_data_list = g_const_data_list->next;
    pool_free(cdata,0x1c);
  }
  while (g_const_data_list = cdata, call = g_call_list, blk != (bblock *)0x0) {
    item = blk->statics;
    next_blk = blk->f_next;
    blk->statics = (node_list *)0x0;
    while (cdata = g_const_data_list, blk = next_blk, item != (node_list *)0x0) {
      next_item = item->next;
      pool_free(item,8);
      item = next_item;
    }
  }
  while (call != (node_cell *)0x0) {
    g_call_list = call->next;
    pool_free(call,8);
    call = g_call_list;
  }
  g_call_list = (node_cell *)0x0;
  freq = g_mem_freq_list;
  while (freq != (mem_freq *)0x0) {
    g_mem_freq_list = freq->next;
    pool_free(freq,0x1c);
    freq = g_mem_freq_list;
  }
  g_mem_freq_list = freq;
  return;
}



