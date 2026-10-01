#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x267c4))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0040aad0
// name : read_symbol_table
// size : 1024
// sig  : void read_symbol_table(void)


int __cdecl read_symbol_table(void)

{
  unsigned char _frec_d[13];
#define attr_bits (*(uchar *)(_frec_d + 0))
#define byte_38 (*(char *)(_frec_d + 1))
#define name_length (*(uchar *)(_frec_d + 2))
#define flag_bits (*(byte *)(_frec_d + 3))
#define type_byte (*(uchar *)(_frec_d + 4))
#define word_16 (*(short *)(_frec_d + 5))
#define sym_index (*(short *)(_frec_d + 7))
#define word_18 (*(int *)(_frec_d + 9))
  char kind;
  uchar byte_06;
  short class_short;
  uint nread;
  char *sym_name;
  int size;
  
  g_options->unknown_b4 = g_options->symbol_count;
  g_symbol_count = g_options->unknown_b4;
  g_symbol_limit = (short)g_symbol_count;
  if ((((g_inline_flags & 4) != 0) || (g_options->unknown_35 != '\0')) ||
     (g_options->unknown_20 != 0)) {
    if ((g_options->unknown_44 - g_symbol_count) + -1 < 1000) {
      g_symbol_limit = (short)g_options->unknown_44 + -1;
    }
    else {
      g_symbol_limit = g_symbol_limit + 1000;
    }
  }
  g_symtab = stock_calloc(g_symbol_limit + 1,0x3c);
  if (g_symtab == (symbol *)0x0) {
    fatal_error(0xbcd);
  }
  nread = read_count_or_fail(g_sym_file,(char *)&sym_index,2);
  while (nread != 0) {
    kind = read_symbol_kind();
    class_short = read_symbol_kind_short(kind);
    name_length = read_symbol_name_length();
    sym_name = read_symbol_name(name_length);
    type_byte = read_symbol_type();
    size = read_type_size(type_byte);
    byte_06 = read_symbol_byte_06();
    read_or_fail(g_sym_file,(char *)&flag_bits,1);
    read_or_fail(g_sym_file,(char *)&attr_bits,1);
    read_or_fail(g_sym_file,(char *)&word_16,2);
    read_or_fail(g_sym_file,&byte_38,1);
    if (((kind == '\x01') || (kind == '\x03')) && (type_byte == 'H')) {
      read_function_info(g_symtab + sym_index);
    }
    if ((flag_bits & 0x10) != 0) {
      read_symbol_extension(g_symtab + sym_index);
    }
    if (kind == '\n') {
      read_scope_info(g_symtab + sym_index);
    }
    word_18 = 0;
    if (kind == '\t') {
      read_or_fail(g_sym_file,(char *)&word_18,4);
    }
    g_symtab[sym_index].sclass = kind;
    g_symtab[sym_index].unknown_04 = class_short;
    g_symtab[sym_index].name_len = name_length;
    g_symtab[sym_index].name = sym_name;
    g_symtab[sym_index].type = type_byte;
    g_symtab[sym_index].size = size;
    g_symtab[sym_index].unknown_06 = byte_06;
    g_symtab[sym_index].flags = flag_bits;
    g_symtab[sym_index].attr = attr_bits;
    g_symtab[sym_index].unknown_16 = word_16;
    g_symtab[sym_index].unknown_18 = word_18;
    g_symtab[sym_index].inline_body = (inline_body *)0x0;
    g_symtab[sym_index].new_info = (void *)0x0;
    g_symtab[sym_index].inline_flags = '\0';
    g_symtab[sym_index].inline_symbols = 0;
    g_symtab[sym_index].inline_labels = 0;
    g_symtab[sym_index].no_inline = '\0';
    g_symtab[sym_index].unknown_38 = byte_38;
    nread = read_count_or_fail(g_sym_file,(char *)&sym_index,2);
  }
  return;
#undef attr_bits
#undef byte_38
#undef name_length
#undef flag_bits
#undef type_byte
#undef word_16
#undef sym_index
#undef word_18
}



