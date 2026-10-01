#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))


// entry: 00423810
// name : build_kill_or_def_set
// size : 343
// sig  : void build_kill_or_def_set(short first, short last, uint * set, int words)


int __cdecl build_kill_or_def_set(short first,short last,uint *set,int words)

{
  uint *word_ptr;
  int iVar1;
  int next_offset;
  il_node **def;
  int num;
  
  num = (int)first;
  if (num < last) {
    def = g_def_nodes + num;
    do {
      if (words == 8) {
        word_ptr = set;
        iVar1 = 0;
        do {
          next_offset = iVar1 + 4;
          *word_ptr = *word_ptr | *(uint *)((int)g_leaf_table[(*def)->nleaf].gen + iVar1);
          word_ptr = word_ptr + 1;
          iVar1 = next_offset;
        } while (next_offset < 0x20);
        set[num >> 5] =
             set[num >> 5] |
             g_leaf_table[(*def)->nleaf].gen[num >> 5] & ~(1 << (0x1f - ((byte)num & 0x1f) & 0x1f));
      }
      else if (words == 0x10) {
        iVar1 = 0;
        word_ptr = set;
        do {
          if (g_leaf_table[(*def)->nleaf].use != (uint *)0x0) {
            *word_ptr = *word_ptr | *(uint *)(iVar1 + (int)g_leaf_table[(*def)->nleaf].use);
          }
          iVar1 = iVar1 + 4;
          word_ptr = word_ptr + 1;
        } while (iVar1 < 0x40);
      }
      else if (((*(unsigned char *)((char *)&g_debug_flags + 2)) & 0x10) != 0) {
        FID_conflict__fwprintf((FILE *)&stock_stdout,(wchar_t *)s_Stopper_Error_00435c50);
      }
      def = def + 1;
      num = num + 1;
    } while (num < last);
  }
  iVar1 = words;
  word_ptr = set;
  if (0 < words) {
    do {
      iVar1 = iVar1 + -1;
      *word_ptr = ~*word_ptr;
      word_ptr = word_ptr + 1;
    } while (iVar1 != 0);
  }
  if (((*(unsigned char *)((char *)&g_debug_flags + 2)) & 0x10) != 0) {
    if (words == 8) {
      dump_bitset(set,8,s_mk_kill_00435c48);
      return;
    }
    dump_bitset(set,0x10,s_mk_def_00435c40);
  }
  return;
}



