#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0040df70
// name : copy_symbol_info
// size : 480
// sig  : short * copy_symbol_info(short symx)


short * __cdecl copy_symbol_info(short symx)

{
  short *copy;
  void *array;
  int iVar1;
  int iVar2;
  short *old_info;
  undefined2 *src;
  
  copy = stock_calloc(1,0x14);
  if (copy == (short *)0x0) {
    abort_function_optimization();
  }
  old_info = g_symtab[symx].info;
  if (g_symtab[symx].sclass == '\n') {
    *copy = *old_info;
    copy[1] = old_info[1];
    if (0 < *copy) {
      array = stock_calloc(1,*copy * 2);
      *(void **)(copy + 2) = array;
      if (array == (void *)0x0) {
        stock_free(copy);
        abort_function_optimization();
      }
      iVar1 = 0;
      if (0 < *copy) {
        iVar2 = 0;
        do {
          src = (undefined2 *)(*(int *)(old_info + 2) + iVar2);
          iVar2 = iVar2 + 2;
          *(undefined2 *)(*(int *)(copy + 2) + -2 + iVar2) = *src;
          iVar1 = iVar1 + 1;
        } while (iVar1 < *copy);
      }
    }
    if (0 < copy[1]) {
      array = stock_calloc(1,copy[1] * 2);
      *(void **)(copy + 4) = array;
      if (array == (void *)0x0) {
        if (*(void **)(copy + 2) != (void *)0x0) {
          stock_free(*(void **)(copy + 2));
        }
        stock_free(copy);
        abort_function_optimization();
      }
      iVar1 = 0;
      if (0 < copy[1]) {
        iVar2 = 0;
        do {
          src = (undefined2 *)(*(int *)(old_info + 4) + iVar2);
          iVar2 = iVar2 + 2;
          *(undefined2 *)(*(int *)(copy + 4) + -2 + iVar2) = *src;
          iVar1 = iVar1 + 1;
        } while (iVar1 < copy[1]);
        return copy;
      }
    }
  }
  else {
    *(undefined4 *)copy = *(undefined4 *)old_info;
    *(char *)(copy + 2) = (char)old_info[2];
    *(undefined1 *)((int)copy + 5) = *(undefined1 *)((int)old_info + 5);
    *(char *)(copy + 3) = (char)old_info[3];
    copy[4] = old_info[4];
    if ('\0' < (char)copy[3]) {
      array = stock_calloc(1,(char)copy[3] * 2);
      *(void **)(copy + 6) = array;
      if (array == (void *)0x0) {
        stock_free(copy);
        abort_function_optimization();
      }
      iVar1 = 0;
      iVar2 = 0;
      if ('\0' < (char)copy[3]) {
        do {
          src = (undefined2 *)(*(int *)(old_info + 6) + iVar1);
          iVar1 = iVar1 + 2;
          *(undefined2 *)(*(int *)(copy + 6) + -2 + iVar1) = *src;
          iVar2 = iVar2 + 1;
        } while (iVar2 < (char)copy[3]);
      }
    }
    if (0 < copy[4]) {
      array = stock_calloc(1,copy[4] * 2);
      *(void **)(copy + 8) = array;
      if (array == (void *)0x0) {
        if (*(void **)(copy + 6) != (void *)0x0) {
          stock_free(*(void **)(copy + 6));
        }
        stock_free(copy);
        abort_function_optimization();
      }
      iVar1 = 0;
      iVar2 = 0;
      if (0 < copy[4]) {
        do {
          src = (undefined2 *)(*(int *)(old_info + 8) + iVar1);
          iVar1 = iVar1 + 2;
          *(undefined2 *)(*(int *)(copy + 8) + -2 + iVar1) = *src;
          iVar2 = iVar2 + 1;
        } while (iVar2 < copy[4]);
      }
    }
  }
  return copy;
}



