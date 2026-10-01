#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options_for_errors
#define g_options_for_errors (*(option_record * *)(g_sd + 0x27330))


// entry: 004286d0
// name : write_error_record
// size : 610
// sig  : int write_error_record(char * file_name, int line, int errcode, char * text)


int __cdecl write_error_record(char *file_name,int line,int errcode,char *text)

{
  unsigned char _frec_b[11];
#define text_len (*(byte *)(_frec_b + 0))
#define err_code (*(undefined2 *)(_frec_b + 1))
#define local_8 (*(undefined2 *)(_frec_b + 3))
#define file_index (*(undefined2 *)(_frec_b + 5))
#define rec_line (*(int *)(_frec_b + 7))
  option_record *poVar1;
  option_record *in_EAX;
  byte *s1;
  int iVar2;
  FILE *fp;
  uint uVar3;
  int status;
  byte *s2;
  int *entry;
  char *pcVar4;
  bool below;
  byte c1;
  char ch;
  
  if (g_options_for_errors == (option_record *)0x0) goto LAB_00428927;
  entry = g_options_for_errors->file_list;
  if (entry == (int *)0x0) {
LAB_00428733:
    file_index = 0;
  }
  else {
    while (file_name != (char *)0x0) {
      s1 = (byte *)entry[2];
      s2 = (byte *)file_name;
      do {
        c1 = *s1;
        below = c1 < *s2;
        if (c1 != *s2) {
LAB_00428720:
          iVar2 = (1 - (uint)below) - (uint)(below != 0);
          goto LAB_00428725;
        }
        if (c1 == 0) break;
        c1 = s1[1];
        below = c1 < s2[1];
        if (c1 != s2[1]) goto LAB_00428720;
        s1 = s1 + 2;
        s2 = s2 + 2;
      } while (c1 != 0);
      iVar2 = 0;
LAB_00428725:
      if ((iVar2 == 0) || (entry = (int *)*entry, entry == (int *)0x0)) break;
    }
    if (entry == (int *)0x0) goto LAB_00428733;
    file_index = (undefined2)entry[1];
  }
  local_8 = 0;
  err_code = (undefined2)errcode;
  iVar2 = errcode / 1000;
  rec_line = line;
  if (((0 < iVar2) || ((g_options_for_errors->unknown_124 & 8) != 0)) ||
     (in_EAX = g_options_for_errors, g_options_for_errors->warnings == '\x01')) {
    fp = stock_fopen(g_options_for_errors->error_file,&g_str_mode_ab);
    if (fp == (FILE *)0x0) {
      fatal_error_exit(0xce4);
    }
    uVar3 = write_bytes(fp,(char *)&err_code,2);
    if (uVar3 == 0xffffffff) {
      fatal_error_exit(0xce7);
    }
    uVar3 = write_bytes(fp,(char *)&rec_line,4);
    if (uVar3 == 0xffffffff) {
      fatal_error_exit(0xce7);
    }
    uVar3 = write_bytes(fp,(char *)&local_8,2);
    if (uVar3 == 0xffffffff) {
      fatal_error_exit(0xce7);
    }
    uVar3 = write_bytes(fp,(char *)&file_index,2);
    if (uVar3 == 0xffffffff) {
      fatal_error_exit(0xce7);
    }
    if (text == (char *)0x0) {
      text_len = 0;
      uVar3 = write_bytes(fp,(char *)&text_len,1);
    }
    else {
      uVar3 = 0xffffffff;
      pcVar4 = text;
      do {
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        ch = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (ch != '\0');
      text_len = 0xff;
      if ((short)~uVar3 < 0xff) {
        text_len = (byte)~uVar3;
      }
      uVar3 = write_bytes(fp,(char *)&text_len,1);
      if (uVar3 == 0xffffffff) {
        fatal_error_exit(0xce7);
      }
      uVar3 = write_bytes(fp,text,(uint)text_len);
    }
    if (uVar3 == 0xffffffff) {
      fatal_error_exit(0xce7);
    }
    status = _fclose(fp);
    in_EAX = (option_record *)0x0;
    if (status != 0) {
      in_EAX = (option_record *)fatal_error_exit(0xce5);
    }
    poVar1 = g_options_for_errors;
    if ((iVar2 == 2) || (iVar2 == 6)) {
      g_options_for_errors->message_count_cc = g_options_for_errors->message_count_cc + 1;
      in_EAX = poVar1;
    }
    else {
      if ((iVar2 == 1) || (iVar2 == 5)) {
        g_options_for_errors->message_count_c8 = g_options_for_errors->message_count_c8 + 1;
        return (uint)poVar1 & 0xffff0000;
      }
      if (iVar2 == 0) {
        g_options_for_errors->message_count_160 = g_options_for_errors->message_count_160 + 1;
        return (uint)poVar1 & 0xffff0000;
      }
    }
  }
LAB_00428927:
  return (uint)in_EAX & 0xffff0000;
#undef text_len
#undef err_code
#undef local_8
#undef file_index
#undef rec_line
}



