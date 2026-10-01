#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_inline_node_free_list
#define g_inline_node_free_list (*(il_node * *)(g_sd + 0x1e784))


// entry: 00404f60
// name : allocate_il_node_block
// size : 109
// sig  : void allocate_il_node_block(int count)


int __cdecl allocate_il_node_block(int count)

{
  il_node *piVar1;
  il_node *cur;
  int n;
  longlong smaller;
  
  do {
    piVar1 = pool_alloc(count * 0x68);
    if (piVar1 != (il_node *)0x0) {
LAB_00404faa:
      n = count + -1;
      cur = piVar1;
      g_inline_node_free_list = piVar1;
      if (0 < n) {
        do {
          piVar1 = cur + 1;
          n = n + -1;
          cur->next = piVar1;
          cur = piVar1;
        } while (n != 0);
      }
      piVar1->next = (il_node *)0x0;
      return;
    }
    if (count < 0xb) {
      fatal_error(0xbcd);
      goto LAB_00404faa;
    }
    smaller = (longlong)(int)((double)count * *(double *)SD(0x00432000));
    count = (int)smaller;
  } while( true );
}



