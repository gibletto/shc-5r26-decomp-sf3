#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 00426a8d
// name : emit_line_comment
// size : 656
// sig  : void __cdecl emit_line_comment(psd *rec)


int __cdecl emit_line_comment(psd *rec)

{
  unsigned char _frec_124[292];
#define out_channel (*(short *)(_frec_124 + 0))
#define shown_len (*(short *)(_frec_124 + 4))
#define i (*(short *)(_frec_124 + 12))
#define base_name_len (*(char *)(_frec_124 + 24))
#define base_name (*(char (*)[255])(_frec_124 + 25))
#define block_kind (*(short *)(_frec_124 + 280))
#define src_file (*(request_source_file * *)(_frec_124 + 284))
  short line_filno;
  ushort line_linno;
  
  line_filno = rec->filno;
  line_linno = rec->linno;
  block_kind = (short)*(char *)&rec->ea1;
  if ((((g_current_request->optimize == 0) || ((g_current_request->back_flags & 0x4000) != 0)) &&
      ((g_current_request->code != 1 ||
       (((g_current_request->show & 2) != 0 && ((g_current_request->show & 0x11) == 0)))))) &&
     (line_filno != 0)) {
    if ((g_current_request->show & 2) == 0) {
      out_channel = 2;
    }
    else {
      out_channel = 3;
    }
    put_text_at_column(out_channel,s___File_0044205c,0);
    for (src_file = g_current_request->source_files;
        (src_file != (request_source_file *)0x0 && (src_file->filno != line_filno));
        src_file = src_file->next) {
    }
    get_source_file_basename(&base_name_len,src_file);
    shown_len = (short)base_name_len;
    if (10 < shown_len) {
      shown_len = 10;
    }
    for (i = 0; i < 10; i = i + 1) {
      if (i < shown_len) {
        put_char_at_column(out_channel,base_name[i],0);
      }
      else {
        put_char_at_column(out_channel,' ',0);
      }
    }
    put_text_at_column(out_channel,&s_comma_sp_00442064,0);
    put_text_at_column(out_channel,s_Line_00442068,0);
    write_decimal(out_channel,(uint)line_linno,0);
    if ((g_current_request->optimize == 0) || ((g_current_request->back_flags & 0x4000) != 0)) {
      put_text_at_column(out_channel,(&PTR_s___block_00441f88)[block_kind],3);
    }
    flush_output_line(out_channel);
  }
  return;
#undef out_channel
#undef shown_len
#undef i
#undef base_name_len
#undef base_name
#undef block_kind
#undef src_file
}
