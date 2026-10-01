#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_inline_asm_input
#define g_inline_asm_input (*(FILE * *)(g_sd + 0xf8f0))


// entry: 00426e2d
// name : emit_inline_asm_block
// size : 971
// sig  : void __cdecl emit_inline_asm_block(psd *rec)


int __cdecl emit_inline_asm_block(psd *rec)

{
  unsigned char _frec_40[64];
#define line_len (*(int *)(_frec_40 + 0))
#define local_3c (*(char (*)[2])(_frec_40 + 4))
#define local_3a (*(char (*)[2])(_frec_40 + 6))
#define local_38 (*(char (*)[4])(_frec_40 + 8))
#define bytes_left (*(int *)(_frec_40 + 12))
#define at_end (*(undefined4 *)(_frec_40 + 16))
#define line_buf (*(char (*)[32])(_frec_40 + 20))
#define last_char (*(char *)(_frec_40 + 52))
#define text_column (*(undefined4 *)(_frec_40 + 56))
  int iVar1;
  uint uVar2;
  
  if (g_current_request->code == 1) {
    report_message_at_source_line(rec->filno,(uint)rec->linno,0x132f,(char *)0x0);
  }
  iVar1 = stock_fseek(g_inline_asm_input,(int)rec->ea1,0);
  if (iVar1 != 0) {
    report_message_at_source_line(0,0,0x1356,(char *)0x0);
  }
  uVar2 = read_file_bytes(g_inline_asm_input,local_3c,2);
  if (uVar2 == 0xffffffff) {
    report_message_at_source_line(0,0,0xce6,(char *)0x0);
  }
  uVar2 = read_file_bytes(g_inline_asm_input,local_3a,2);
  if (uVar2 == 0xffffffff) {
    report_message_at_source_line(0,0,0xce6,(char *)0x0);
  }
  uVar2 = read_file_bytes(g_inline_asm_input,local_38,2);
  if (uVar2 == 0xffffffff) {
    report_message_at_source_line(0,0,0xce6,(char *)0x0);
  }
  uVar2 = read_file_bytes(g_inline_asm_input,(char *)&bytes_left,4);
  if (uVar2 == 0xffffffff) {
    report_message_at_source_line(0,0,0xce6,(char *)0x0);
  }
  text_column = 0;
  if (bytes_left == 0) {
    at_end = 1;
  }
  else {
    at_end = 0;
    if (g_inline_asm_needs_label == 1) {
      if (g_last_label_number == 0x7fff) {
        report_message_at_source_line(rec->filno,(uint)rec->linno,0xbc8,(char *)0x0);
      }
      g_last_label_number = g_last_label_number + 1;
      put_char_at_column(2,'L',0);
      write_decimal(2,(int)g_last_label_number,0);
      g_new_symbol_count = g_new_symbol_count + 1;
      put_char_at_column(2,':',0);
      flush_output_line(2);
    }
    g_inline_asm_needs_label = 1;
  }
  last_char = '\0';
  do {
    if (at_end != 0) {
      flush_output_line(2);
      put_text_at_column(2,s__ALIGN_00442070,1);
      put_char_at_column(2,'4',2);
      flush_output_line(2);
      if (rec->ea2 == (ea *)0x0) {
        g_location_counter = g_location_counter + 0x1000;
        uVar2 = g_location_counter >> 0x1f;
        if (((g_location_counter ^ uVar2) - uVar2 & 3 ^ uVar2) != uVar2) {
          g_location_counter = ((int)(g_location_counter + (uVar2 & 3)) >> 2) << 2;
        }
      }
      else {
        g_location_counter = (int)(&rec->ea2->type + g_location_counter);
        uVar2 = g_location_counter >> 0x1f;
        if (((g_location_counter ^ uVar2) - uVar2 & 3 ^ uVar2) != uVar2) {
          g_location_counter = ((int)(g_location_counter + (uVar2 & 3)) >> 2) * 4 + 4;
        }
      }
      return;
    }
    if (last_char == '\n') {
      line_len = 1;
      line_buf[0] = '\n';
    }
    else {
      line_len = 0;
    }
    do {
      if (0x1d < line_len) goto LAB_004270e6;
      iVar1 = line_len + 1;
      uVar2 = read_file_bytes(g_inline_asm_input,line_buf + line_len,1);
      if (uVar2 == 0xffffffff) {
        report_message_at_source_line(0,0,0xce6,(char *)0x0);
      }
      bytes_left = bytes_left + -1;
      line_len = iVar1;
    } while (bytes_left != 0);
    at_end = 1;
LAB_004270e6:
    last_char = line_buf[line_len + -1];
    if ((at_end == 0) && (last_char != '\n')) {
      line_buf[line_len] = '\0';
    }
    else {
      line_buf[line_len + -1] = '\0';
    }
    g_line_wrap_disabled = 1;
    put_text_at_column(2,line_buf,(short)text_column);
    g_line_wrap_disabled = 0;
    text_column = 2;
  } while( true );
#undef line_len
#undef local_3c
#undef local_3a
#undef local_38
#undef bytes_left
#undef at_end
#undef line_buf
#undef last_char
#undef text_column
}
