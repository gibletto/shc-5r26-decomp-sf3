#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x267c4))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 00404240
// name : write_symbol_file
// size : 474
// sig  : void write_symbol_file(void)


int __cdecl write_symbol_file(void)

{
  unsigned char _frec_2[2];
#define sym_index (*(short *)(_frec_2 + 0))
  int rc;
  symbol *sym;
  short nsymbols;
  
  nsymbols = (short)g_options->symbol_count;
  if ((g_symbol_count < nsymbols) || (g_symbol_table_modified != '\0')) {
    g_sym_file = stock_fopen(g_options->sym_file,&g_mode_wb);
    if (g_sym_file == (FILE *)0x0) {
      fatal_error(0xce4);
    }
    sym_index = 1;
    if (0 < nsymbols) {
      do {
        sym = g_symtab + sym_index;
        if (sym->sclass != '\0') {
          write_symbol_bytes(g_sym_file,(char *)&sym_index,2);
          write_symbol_class(sym->sclass);
          write_symbol_class_short(sym->sclass,sym->unknown_04);
          write_symbol_name_length(sym->name_len);
          write_symbol_name(sym->name_len,sym->name);
          write_symbol_type(sym->type);
          write_symbol_aggregate_size(sym->type,sym->size);
          write_symbol_byte_06(sym->unknown_06);
          write_symbol_bytes(g_sym_file,(char *)&sym->flags,1);
          write_symbol_bytes(g_sym_file,(char *)&sym->attr,1);
          write_symbol_bytes(g_sym_file,(char *)&sym->unknown_16,2);
          write_symbol_bytes(g_sym_file,&sym->unknown_38,1);
          if (((sym->sclass == '\x01') || (sym->sclass == '\x03')) && (sym->type == 'H')) {
            write_symbol_function_info(sym);
          }
          if ((sym->flags & 0x10) != 0) {
            write_symbol_init_info(sym);
          }
          if (sym->sclass == '\n') {
            write_symbol_class10_lists(sym);
          }
          if (sym->sclass == '\t') {
            write_symbol_bytes(g_sym_file,(char *)&sym->unknown_18,4);
          }
        }
        sym_index = sym_index + 1;
      } while (sym_index <= nsymbols);
    }
    rc = _fclose(g_sym_file);
    if (rc != 0) {
      fatal_error(0xce5);
    }
  }
  return;
#undef sym_index
}



