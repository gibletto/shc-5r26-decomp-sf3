#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x267c4))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0040b320
// name : read_scope_info
// size : 432
// sig  : void read_scope_info(symbol * sym)


int __cdecl read_scope_info(symbol *sym)

{
  unsigned char _frec_7[7];
#define impvol_flag (*(uchar *)(_frec_7 + 0))
#define sym_index (*(short *)(_frec_7 + 1))
#define cnt (*(short *)(_frec_7 + 3))
#define count2 (*(short *)(_frec_7 + 5))
  void *info;
  void *array;
  short *info_words;
  bool more;
  
  info = stock_calloc(1,0x14);
  sym->info = info;
  if (info == (void *)0x0) {
    fatal_error(0xbcd);
  }
  read_or_fail(g_sym_file,(char *)&cnt,2);
  *(short *)sym->info = cnt;
  *(undefined4 *)((int)sym->info + 4) = 0;
  if (cnt != 0) {
    info_words = sym->info;
    info = stock_calloc(1,*info_words * 2);
    *(void **)(info_words + 2) = info;
    if (*(int *)((int)sym->info + 4) == 0) {
      fatal_error(0xbcd);
    }
  }
  while (more = cnt != 0, cnt = cnt + -1, more) {
    read_or_fail(g_sym_file,(char *)&sym_index,2);
    *(short *)(*(int *)((int)sym->info + 4) + cnt * 2) = sym_index;
  }
  read_or_fail(g_sym_file,(char *)&count2,2);
  *(short *)((int)sym->info + 2) = count2;
  *(undefined4 *)((int)sym->info + 8) = 0;
  if (count2 != 0) {
    info = sym->info;
    array = stock_calloc(1,*(short *)((int)info + 2) * 2);
    *(void **)((int)info + 8) = array;
    if (*(int *)((int)sym->info + 8) == 0) {
      fatal_error(0xbcd);
    }
  }
  while (count2 != 0) {
    count2 = count2 + -1;
    read_or_fail(g_sym_file,(char *)&sym_index,2);
    read_or_fail(g_sym_file,(char *)&impvol_flag,1);
    g_symtab[sym_index].impvol = impvol_flag;
    *(short *)(*(int *)((int)sym->info + 8) + count2 * 2) = sym_index;
  }
  return;
#undef impvol_flag
#undef sym_index
#undef cnt
#undef count2
}



