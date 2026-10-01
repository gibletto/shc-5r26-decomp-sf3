#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x267c4))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0040b130
// name : read_function_info
// size : 492
// sig  : void read_function_info(symbol * sym)


int __cdecl read_function_info(symbol *sym)

{
  unsigned char _frec_9[9];
#define local_9 (*(char *)(_frec_9 + 0))
#define impvol_flag (*(uchar *)(_frec_9 + 1))
#define param_count (*(char *)(_frec_9 + 2))
#define entry (*(undefined2 *)(_frec_9 + 3))
#define sym_index (*(short *)(_frec_9 + 5))
#define cnt (*(short *)(_frec_9 + 7))
  uchar type;
  void *info;
  int size;
  void *array;
  bool more;
  
  info = stock_calloc(1,0x14);
  sym->info = info;
  if (info == (void *)0x0) {
    fatal_error(0xbcd);
  }
  type = read_symbol_type();
  size = read_type_size(type);
  read_or_fail(g_sym_file,&local_9,1);
  read_or_fail(g_sym_file,&param_count,1);
  *(uchar *)((int)sym->info + 4) = type;
  *(int *)sym->info = size;
  *(char *)((int)sym->info + 5) = local_9;
  *(char *)((int)sym->info + 6) = param_count;
  *(undefined4 *)((int)sym->info + 0xc) = 0;
  if (param_count != '\0') {
    info = sym->info;
    array = stock_calloc(1,*(char *)((int)info + 6) * 2);
    *(void **)((int)info + 0xc) = array;
    if (*(int *)((int)sym->info + 0xc) == 0) {
      fatal_error(0xbcd);
    }
  }
  while (more = param_count != '\0', param_count = param_count + -1, more) {
    read_or_fail(g_sym_file,(char *)&sym_index,2);
    read_or_fail(g_sym_file,(char *)&impvol_flag,1);
    g_symtab[sym_index].impvol = impvol_flag;
    *(short *)(*(int *)((int)sym->info + 0xc) + param_count * 2) = sym_index;
  }
  read_or_fail(g_sym_file,(char *)&cnt,2);
  *(short *)((int)sym->info + 8) = cnt;
  *(undefined4 *)((int)sym->info + 0x10) = 0;
  if (cnt != 0) {
    info = sym->info;
    array = stock_calloc(1,*(short *)((int)info + 8) * 2);
    *(void **)((int)info + 0x10) = array;
    if (*(int *)((int)sym->info + 0x10) == 0) {
      fatal_error(0xbcd);
    }
  }
  while (cnt != 0) {
    cnt = cnt + -1;
    read_or_fail(g_sym_file,(char *)&entry,2);
    *(undefined2 *)(*(int *)((int)sym->info + 0x10) + cnt * 2) = entry;
  }
  return;
#undef local_9
#undef impvol_flag
#undef param_count
#undef entry
#undef sym_index
#undef cnt
}



