#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x1f99c))


// entry: 00401470
// name : read_function_info
// size : 129
// sig  : void read_function_info(sym_entry * sym)


int __cdecl read_function_info(sym_entry *sym)

{
  unsigned char _frec_4[4];
#define skipped (*(char (*)[4])(_frec_4 + 0))
  void *list;
  sym_extension *ext;
  
  sym->func_index = g_function_count;
  g_function_count = g_function_count + 1;
  read_bytes_or_fail((char *)&sym->ret_type,1,g_sym_file);
  if ((sym->ret_type & 0xe0) == 0x60) {
    read_bytes_or_fail(skipped,4,g_sym_file);
  }
  read_bytes_or_fail((char *)&sym->ret_19,1,g_sym_file);
  list = read_parameter_list();
  sym->size = (int)list;
  list = read_function_scope_list();
  sym->list_10 = list;
  ext = (sym_extension *)read_symbol_extension(sym);
  sym->ext = ext;
  return;
#undef skipped
}



