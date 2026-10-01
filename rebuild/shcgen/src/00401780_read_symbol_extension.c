#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x1f99c))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00401780
// name : read_symbol_extension
// size : 199
// sig  : uchar * read_symbol_extension(sym_entry * sym)


uchar * __cdecl read_symbol_extension(sym_entry *sym)

{
  uint *buf;
  short index;
  uint *dst;
  
  dst = (uint *)0x0;
  if ((sym->sym_flags & 0x10) != 0) {
    dst = stock_malloc(0xc);
    if (dst == (uint *)0x0) {
      report_codegen_message(0xbcd,1,0,0,(char *)0x0);
      return (uchar *)0x0;
    }
    zero_words(dst,3);
    read_bytes_or_fail((char *)dst,1,g_sym_file);
    if ((*dst & 2) != 0) {
      if ((*dst & 4) == 0) {
        read_bytes_or_fail((char *)(dst + 1),4,g_sym_file);
      }
      else {
        buf = dst + 1;
        read_bytes_or_fail((char *)buf,2,g_sym_file);
        index = (short)*buf + 0xb6;
        *(short *)buf = index;
        g_symbol_table[index].flags = g_symbol_table[index].flags | 8;
      }
    }
    if ((*dst & 1) != 0) {
      read_bytes_or_fail((char *)(dst + 2),4,g_sym_file);
    }
  }
  return (uchar *)dst;
}



