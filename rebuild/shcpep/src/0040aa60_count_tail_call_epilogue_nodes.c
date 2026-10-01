#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x6d50))


// entry: 0040aa60
// name : count_tail_call_epilogue_nodes
// size : 150
// sig  : int count_tail_call_epilogue_nodes(void)


int __cdecl count_tail_call_epilogue_nodes(void)

{
  int iVar1;
  int count;
  aux_record *aux;
  uint bit;
  
  count = 1;
  aux = g_aux_record_table + g_current_aux_index;
  iVar1 = aux->sp_adjust + aux->frame_size;
  if ((iVar1 != 0) && (count = 2, 0x7f < iVar1)) {
    count = 3;
  }
  if ((aux->saved_sys & 2) != 0) {
    count = count + 1;
  }
  if ((aux->saved_sys & 1) != 0) {
    count = count + 1;
  }
  if ((aux->saved_mac & 1) != 0) {
    count = count + 1;
  }
  if ((aux->saved_mac & 2) != 0) {
    count = count + 1;
  }
  if ((aux->flags & 0x8000) == 0) {
    count = count + 1;
  }
  iVar1 = 0;
  do {
    bit = 1 << ((byte)iVar1 & 0x1f);
    if ((bit & (int)aux->saved_regs) != 0) {
      count = count + 1;
    }
    if ((bit & (int)aux->saved_regs2) != 0) {
      count = count + 1;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x10);
  return count / 0xf + (uint)(count % 0xf != 0);
}



