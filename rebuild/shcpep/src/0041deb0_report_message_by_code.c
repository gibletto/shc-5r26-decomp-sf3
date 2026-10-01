#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_loaded_request
#define g_loaded_request (*(request * *)(g_sd + 0x6e34))


// entry: 0041deb0
// name : report_message_by_code
// size : 610
// sig  : short report_message_by_code(char * file_name, int line, int msgno, char * text)


short __cdecl report_message_by_code(char *file_name,int line,int msgno,char *text)

{
  unsigned char _frec_b[11];
#define text_len (*(byte *)(_frec_b + 0))
#define msg_code (*(undefined2 *)(_frec_b + 1))
#define local_8 (*(undefined2 *)(_frec_b + 3))
#define file_no (*(short *)(_frec_b + 5))
#define line_out (*(int *)(_frec_b + 7))
  byte *s1;
  int iVar1;
  FILE *out;
  uint uVar2;
  int close_result;
  byte *s2;
  request_source_file *src_file;
  char *p;
  bool below;
  byte c;
  char ch;
  
  if (g_loaded_request == (request *)0x0) {
    return 0;
  }
  src_file = g_loaded_request->source_files;
  if (src_file != (request_source_file *)0x0) {
    while (file_name != (char *)0x0) {
      s1 = (byte *)src_file->name;
      s2 = (byte *)file_name;
      do {
        c = *s1;
        below = c < *s2;
        if (c != *s2) {
LAB_0041df00:
          iVar1 = (1 - (uint)below) - (uint)(below != 0);
          goto LAB_0041df05;
        }
        if (c == 0) break;
        c = s1[1];
        below = c < s2[1];
        if (c != s2[1]) goto LAB_0041df00;
        s1 = s1 + 2;
        s2 = s2 + 2;
      } while (c != 0);
      iVar1 = 0;
LAB_0041df05:
      if ((iVar1 == 0) || (src_file = src_file->next, src_file == (request_source_file *)0x0))
      break;
    }
    if (src_file != (request_source_file *)0x0) {
      file_no = src_file->filno;
      goto LAB_0041df25;
    }
  }
  file_no = 0;
LAB_0041df25:
  local_8 = 0;
  msg_code = (undefined2)msgno;
  iVar1 = msgno / 1000;
  line_out = line;
  if (((0 < iVar1) || ((g_loaded_request->message_flags & 8) != 0)) ||
     (g_loaded_request->message_all == '\x01')) {
    out = open_shared_file(g_loaded_request->message_path,s_ab_004283dc);
    if (out == (FILE *)0x0) {
      report_message_file_error_and_exit(0xce4);
    }
    uVar2 = write_file_bytes(out,(char *)&msg_code,2);
    if (uVar2 == 0xffffffff) {
      report_message_file_error_and_exit(0xce7);
    }
    uVar2 = write_file_bytes(out,(char *)&line_out,4);
    if (uVar2 == 0xffffffff) {
      report_message_file_error_and_exit(0xce7);
    }
    uVar2 = write_file_bytes(out,(char *)&local_8,2);
    if (uVar2 == 0xffffffff) {
      report_message_file_error_and_exit(0xce7);
    }
    uVar2 = write_file_bytes(out,(char *)&file_no,2);
    if (uVar2 == 0xffffffff) {
      report_message_file_error_and_exit(0xce7);
    }
    if (text == (char *)0x0) {
      text_len = 0;
      uVar2 = write_file_bytes(out,(char *)&text_len,1);
    }
    else {
      uVar2 = 0xffffffff;
      p = text;
      do {
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        ch = *p;
        p = p + 1;
      } while (ch != '\0');
      text_len = 0xff;
      if ((short)~uVar2 < 0xff) {
        text_len = (byte)~uVar2;
      }
      uVar2 = write_file_bytes(out,(char *)&text_len,1);
      if (uVar2 == 0xffffffff) {
        report_message_file_error_and_exit(0xce7);
      }
      uVar2 = write_file_bytes(out,text,(uint)text_len);
    }
    if (uVar2 == 0xffffffff) {
      report_message_file_error_and_exit(0xce7);
    }
    close_result = _fclose(out);
    if (close_result != 0) {
      report_message_file_error_and_exit(0xce5);
    }
    if ((iVar1 == 2) || (iVar1 == 6)) {
      g_loaded_request->error_count = g_loaded_request->error_count + 1;
    }
    else {
      if ((iVar1 == 1) || (iVar1 == 5)) {
        g_loaded_request->warning_count = g_loaded_request->warning_count + 1;
        return 0;
      }
      if (iVar1 == 0) {
        g_loaded_request->info_count = g_loaded_request->info_count + 1;
        return 0;
      }
    }
  }
  return 0;
#undef text_len
#undef msg_code
#undef local_8
#undef file_no
#undef line_out
}



