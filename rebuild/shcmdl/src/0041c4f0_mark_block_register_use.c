#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))


// entry: 0041c4f0
// name : mark_block_register_use
// size : 442
// sig  : void mark_block_register_use(lreg * lr)


int __cdecl mark_block_register_use(lreg *lr)

{
  byte kind;
  byte ty;
  uint fmask;
  undefined4 *area;
  bblock *blk;
  short *chain;
  short cpu;
  ushort endpp;
  
  sort_life_areas(lr);
  area = lr->life;
  blk = g_f_chain;
  do {
    if (area == (undefined4 *)0x0) {
      return;
    }
    endpp = blk->endpp;
    while (endpp < *(ushort *)(area[1] + 8)) {
      blk = blk->f_next;
      endpp = blk->endpp;
    }
    cpu = g_options->cpu;
    if (lr->set == 0) {
      if (((cpu == 2) && (g_options->fpu_mode == '\x03')) || (cpu == 4)) {
        chain = lr->chain;
        ty = *(byte *)(*(int *)(*(int *)(chain + 4) + 8) + 3);
        kind = ty & 0xe0;
        if ((kind == 0x20) && (*chain == 0)) {
          fmask = 1 << ((byte)lr->pregno & 0x1f) | blk->usefreg;
          blk->usefreg = fmask;
          if (((*(byte *)(*(int *)(*(int *)((int)lr->chain + 8) + 8) + 3) & 0xf8) == 0x30) &&
             (g_options->cpu == 4)) {
            blk->usefreg = 2 << ((byte)lr->pregno & 0x1f) | fmask;
          }
        }
        else if ((kind == 0) || (((ty & 0xf8) == 0x40 || (*chain != 0)))) goto LAB_0041c68f;
      }
      else if ((*(byte *)(*(int *)(*(int *)((int)lr->chain + 8) + 8) + 3) & 0xf8) != 0x30) {
LAB_0041c68f:
        blk->usepreg = blk->usepreg | 1 << ((byte)lr->pregno & 0x1f);
      }
    }
    else if (((cpu == 2) && (g_options->fpu_mode == '\x03')) || (cpu == 4)) {
      ty = *(byte *)(*(int *)((int)lr->chain + 0x10) + 3);
      kind = ty & 0xe0;
      if (kind == 0x20) {
        fmask = 1 << ((byte)lr->pregno & 0x1f) | blk->usefreg;
        blk->usefreg = fmask;
        if (((*(byte *)(*(int *)((int)lr->chain + 0x10) + 3) & 0xf8) == 0x30) &&
           (g_options->cpu == 4)) {
          blk->usefreg = 2 << ((byte)lr->pregno & 0x1f) | fmask;
        }
      }
      else if ((kind == 0) || ((ty & 0xf8) == 0x40)) goto LAB_0041c68f;
    }
    else {
      ty = *(byte *)(*(int *)((int)lr->chain + 0x10) + 3);
      if ((((ty & 0xe0) == 0) || (ty = ty & 0xf8, ty == 0x40)) || (ty == 0x28)) goto LAB_0041c68f;
    }
    area = (undefined4 *)*area;
  } while( true );
}



