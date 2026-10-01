#include "decls.h"
#include "imports.h"

// entry: 00439960
// name : stock_alloc_osfhnd
// size : 184
// sig  : int stock_alloc_osfhnd(void)


int __cdecl stock_alloc_osfhnd(void)

{
  undefined4 *ioinfo;
  undefined4 *puVar1;
  int *block_slot;
  int base_fh;
  int fh;
  int block_index;
  
  fh = -1;
  block_index = 0;
  base_fh = 0;
  block_slot = &stock_pioinfo;
  do {
    ioinfo = (undefined4 *)*block_slot;
    if (ioinfo == (undefined4 *)0x0) {
      ioinfo = stock_malloc(0x100);
      if (ioinfo != (undefined4 *)0x0) {
        stock_nhandle = stock_nhandle + 0x20;
        (&stock_pioinfo)[block_index] = ioinfo;
        if (ioinfo < ioinfo + 0x40) {
          do {
            *(undefined1 *)(ioinfo + 1) = 0;
            puVar1 = ioinfo + 2;
            *ioinfo = 0xffffffff;
            *(undefined1 *)((int)ioinfo + 5) = 10;
            ioinfo = puVar1;
          } while (puVar1 < (undefined4 *)((&stock_pioinfo)[block_index] + 0x100));
        }
        fh = block_index << 5;
      }
      return fh;
    }
    puVar1 = ioinfo + 0x40;
    for (; ioinfo < puVar1; ioinfo = ioinfo + 2) {
      if ((*(byte *)(ioinfo + 1) & 1) == 0) {
        *ioinfo = 0xffffffff;
        fh = ((int)ioinfo - *block_slot >> 3) + base_fh;
        break;
      }
    }
    if (fh != -1) {
      return fh;
    }
    base_fh = base_fh + 0x20;
    block_slot = block_slot + 1;
    block_index = block_index + 1;
    if ((int *)SD(0x00450caf) < block_slot) {
      return -1;
    }
  } while( true );
}



