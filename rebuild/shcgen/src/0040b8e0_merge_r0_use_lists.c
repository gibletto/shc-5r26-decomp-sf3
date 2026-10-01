#include "decls.h"
#include "imports.h"

// entry: 0040b8e0
// name : merge_r0_use_lists
// size : 417
// sig  : void * merge_r0_use_lists(void * a, void * b)


int * __cdecl merge_r0_use_lists(void *a,void *b)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *next_a;
  undefined4 *out_block;
  int out_i;
  int a_i;
  int b_i;
  undefined4 *out_head;
  uint serial_a;
  uint serial_b;
  
  out_head = (undefined4 *)0x0;
  if ((a != (void *)0x0) || (b != (void *)0x0)) {
    out_head = alloc_zeroed(0x14);
    *out_head = 0;
  }
  out_i = 0;
  b_i = 0;
  a_i = 0;
  out_block = out_head;
  if (a != (void *)0x0) {
    do {
      serial_a = *(uint *)((int)a + (a_i + 1) * 4);
      puVar2 = b;
      if (((serial_a == 0) || (b == (undefined4 *)0x0)) ||
         (serial_b = *(uint *)((int)b + (b_i + 1) * 4), serial_b == 0)) break;
      if (serial_a < serial_b) {
        out_block[out_i + 1] = serial_a;
        a_i = a_i + 1;
      }
      else {
        out_block[out_i + 1] = serial_b;
        b_i = b_i + 1;
      }
      out_i = out_i + 1;
      puVar1 = out_block;
      if (3 < out_i) {
        out_i = 0;
        puVar1 = alloc_zeroed(0x14);
        *out_block = puVar1;
        *puVar1 = 0;
      }
      next_a = a;
      if (3 < a_i) {
        next_a = *(undefined4 **)a;
        a_i = 0;
        pool_free(a,0x14);
      }
      if (3 < b_i) {
        puVar2 = *(undefined4 **)b;
        b_i = 0;
        pool_free(b,0x14);
      }
      b = puVar2;
      a = next_a;
      out_block = puVar1;
    } while (next_a != (undefined4 *)0x0);
    while ((b = puVar2, a != (undefined4 *)0x0 && (*(int *)((int)a + (a_i + 1) * 4) != 0))) {
      out_block[out_i + 1] = *(int *)((int)a + (a_i + 1) * 4);
      out_i = out_i + 1;
      a_i = a_i + 1;
      puVar1 = out_block;
      if (3 < out_i) {
        out_i = 0;
        puVar1 = alloc_zeroed(0x14);
        *out_block = puVar1;
        *puVar1 = 0;
      }
      out_block = puVar1;
      if (3 < a_i) {
        puVar1 = *(undefined4 **)a;
        a_i = 0;
        pool_free(a,0x14);
        a = puVar1;
      }
    }
  }
  while ((b != (undefined4 *)0x0 && (*(int *)((int)b + (b_i + 1) * 4) != 0))) {
    out_block[out_i + 1] = *(int *)((int)b + (b_i + 1) * 4);
    out_i = out_i + 1;
    b_i = b_i + 1;
    puVar2 = out_block;
    if (3 < out_i) {
      out_i = 0;
      puVar2 = alloc_zeroed(0x14);
      *out_block = puVar2;
      *puVar2 = 0;
    }
    out_block = puVar2;
    if (3 < b_i) {
      puVar2 = *(undefined4 **)b;
      b_i = 0;
      pool_free(b,0x14);
      b = puVar2;
    }
  }
  return out_head;
}



