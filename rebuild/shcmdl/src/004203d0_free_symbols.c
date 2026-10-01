#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 004203d0
// name : free_symbols
// size : 175
// sig  : void free_symbols(short first, short last)


int __cdecl free_symbols(short first,short last)

{
  int ofs;
  int symx;
  int next_symx;
  void *info;
  
  symx = (int)first;
  if (symx <= last) {
    ofs = symx * 0x3c;
    do {
      if (g_symtab->unknown_39[ofs + -0x39] == '\n') {
        info = *(void **)(g_symtab->unknown_39 + ofs + -0x39 + 0x10);
        if (info != (void *)0x0) {
          if (*(void **)((int)info + 4) != (void *)0x0) {
            stock_free(*(void **)((int)info + 4));
          }
          if (*(void **)((int)info + 8) != (void *)0x0) {
            stock_free(*(void **)((int)info + 8));
          }
          stock_free(info);
        }
        info = *(void **)(g_symtab->unknown_39 + ofs + -0x19);
        if (info != (void *)0x0) {
          if (*(void **)((int)info + 4) != (void *)0x0) {
            stock_free(*(void **)((int)info + 4));
          }
          if (*(void **)((int)info + 8) != (void *)0x0) {
            stock_free(*(void **)((int)info + 8));
          }
          stock_free(info);
        }
      }
      ofs = ofs + 0x3c;
      next_symx = symx + 1;
      clear_symbol((short)symx);
      symx = next_symx;
    } while (next_symx <= last);
  }
  return;
}



