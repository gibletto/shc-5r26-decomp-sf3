#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 00426d1d
// name : emit_line_directive
// size : 272
// sig  : void __cdecl emit_line_directive(uint filno,uint linno)


int __cdecl emit_line_directive(uint filno,uint linno)

{
  unsigned char _frec_10c[268];
#define full_path (*(char (*)[260])(_frec_10c + 0))
#define src_file (*(request_source_file * *)(_frec_10c + 260))
  char *pcVar1;
  uint path_len;
  
  put_text_at_column(2,s__LINE_00441e50,1);
  put_char_at_column(2,'\"',2);
  for (src_file = g_current_request->source_files;
      (src_file != (request_source_file *)0x0 && ((int)src_file->filno != (filno & 0xffff)));
      src_file = src_file->next) {
  }
  pcVar1 = get_full_path(src_file->name,full_path);
  if ((pcVar1 == (char *)0x0) || (path_len = stock_strlen(full_path), 0xe0 < path_len)) {
    put_text_at_column(2,src_file->name,2);
  }
  else {
    put_text_at_column(2,full_path,2);
  }
  put_char_at_column(2,'\"',2);
  put_char_at_column(2,',',2);
  write_decimal(2,linno & 0xffff,2);
  flush_output_line(2);
  return;
#undef full_path
#undef src_file
}
