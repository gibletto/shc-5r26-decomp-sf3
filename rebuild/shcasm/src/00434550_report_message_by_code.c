#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_loaded_request
#define g_loaded_request (*(request * *)(g_sd + 0x13320))


// entry: 00434550
// name : report_message_by_code
// size : 610
// sig  : uint report_message_by_code(char * file_name, int line, int msgno, char * text)


uint __cdecl report_message_by_code(char *file_name,int line,int msgno,char *text)

{
  unsigned char _frec_b[11];
#define text_len (*(byte *)(_frec_b + 0))
#define msg_code (*(undefined2 *)(_frec_b + 1))
#define local_8 (*(undefined2 *)(_frec_b + 3))
#define file_no (*(short *)(_frec_b + 5))
#define msg_line (*(int *)(_frec_b + 7))
  request *in_EAX;
  byte *name_scan;
  int iVar1;
  FILE *out;
  uint uVar2;
  int close_result;
  request *extraout_EAX;
  byte *file_name_scan;
  request_source_file *src_file;
  char *text_scan;
  bool below;
  char ch;
  byte cur_byte;
  request *req;
  
  if (g_loaded_request == (request *)0x0) goto LAB_004347a7;
  src_file = g_loaded_request->source_files;
  if (src_file == (request_source_file *)0x0) {
LAB_004345b3:
    file_no = 0;
  }
  else {
    while (file_name != (char *)0x0) {
      name_scan = (byte *)src_file->name;
      file_name_scan = (byte *)file_name;
      do {
        cur_byte = *name_scan;
        below = cur_byte < *file_name_scan;
        if (cur_byte != *file_name_scan) {
LAB_004345a0:
          iVar1 = (1 - (uint)below) - (uint)(below != 0);
          goto LAB_004345a5;
        }
        if (cur_byte == 0) break;
        cur_byte = name_scan[1];
        below = cur_byte < file_name_scan[1];
        if (cur_byte != file_name_scan[1]) goto LAB_004345a0;
        name_scan = name_scan + 2;
        file_name_scan = file_name_scan + 2;
      } while (cur_byte != 0);
      iVar1 = 0;
LAB_004345a5:
      if ((iVar1 == 0) || (src_file = src_file->next, src_file == (request_source_file *)0x0))
      break;
    }
    if (src_file == (request_source_file *)0x0) goto LAB_004345b3;
    file_no = src_file->filno;
  }
  local_8 = 0;
  msg_code = (undefined2)msgno;
  iVar1 = msgno / 1000;
  msg_line = line;
  if (((0 < iVar1) || ((g_loaded_request->message_flags & 8) != 0)) ||
     (in_EAX = g_loaded_request, g_loaded_request->message_all == '\x01')) {
    out = stock_fopen(g_loaded_request->message_path,&s_ab_00443114);
    if (out == (FILE *)0x0) {
      report_message_file_error_and_exit(0xce4);
    }
    uVar2 = write_file_bytes(out,(char *)&msg_code,2);
    if (uVar2 == 0xffffffff) {
      report_message_file_error_and_exit(0xce7);
    }
    uVar2 = write_file_bytes(out,(char *)&msg_line,4);
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
      text_scan = text;
      do {
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        ch = *text_scan;
        text_scan = text_scan + 1;
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
    in_EAX = (request *)0x0;
    if (close_result != 0) {
      (extraout_EAX = (request *)report_message_file_error_and_exit(0xce5));
      in_EAX = extraout_EAX;
    }
    req = g_loaded_request;
    if ((iVar1 == 2) || (iVar1 == 6)) {
      g_loaded_request->error_count = g_loaded_request->error_count + 1;
      in_EAX = req;
    }
    else {
      if ((iVar1 == 1) || (iVar1 == 5)) {
        g_loaded_request->warning_count = g_loaded_request->warning_count + 1;
        return (uint)req & 0xffff0000;
      }
      if (iVar1 == 0) {
        g_loaded_request->info_count = g_loaded_request->info_count + 1;
        return (uint)req & 0xffff0000;
      }
    }
  }
LAB_004347a7:
  return (uint)in_EAX & 0xffff0000;
#undef text_len
#undef msg_code
#undef local_8
#undef file_no
#undef msg_line
}



