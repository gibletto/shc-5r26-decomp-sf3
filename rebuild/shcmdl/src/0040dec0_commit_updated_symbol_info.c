#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0040dec0
// name : commit_updated_symbol_info
// size : 172
// sig  : void commit_updated_symbol_info(void)


int __cdecl commit_updated_symbol_info(void)

{
  uchar *entry;
  int ofs;
  int i;
  void *array;
  void *info;
  
  i = 1;
  if (0 < g_options->symbol_count) {
    ofs = 0x3c;
    do {
      entry = g_symtab->unknown_39 + ofs + -0x39;
      if (*(int *)(entry + 0x20) != 0) {
        info = *(void **)(entry + 0x10);
        if (info != (void *)0x0) {
          if (*entry == '\n') {
            if (*(void **)((int)info + 4) != (void *)0x0) {
              stock_free(*(void **)((int)info + 4));
            }
            array = *(void **)((int)info + 8);
          }
          else {
            if (*(void **)((int)info + 0xc) != (void *)0x0) {
              stock_free(*(void **)((int)info + 0xc));
            }
            array = *(void **)((int)info + 0x10);
          }
          if (array != (void *)0x0) {
            stock_free(array);
          }
          stock_free(info);
        }
        *(undefined4 *)(g_symtab->unknown_39 + ofs + -0x29) =
             *(undefined4 *)(g_symtab->unknown_39 + ofs + -0x19);
        *(undefined4 *)(g_symtab->unknown_39 + ofs + -0x19) = 0;
      }
      ofs = ofs + 0x3c;
      i = i + 1;
    } while (i <= g_options->symbol_count);
  }
  return;
}



