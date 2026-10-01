#include "decls.h"
#include "imports.h"

// entry: 0043c880
// name : stock_NMSG_WRITE
// size : 494
// sig  : void stock_NMSG_WRITE(int msg)


int __cdecl stock_NMSG_WRITE(int msg)

{
  unsigned char _frec_1a8[1204];
#define bytes_written (*(DWORD *)(_frec_1a8 + 0))
#define message_text (*(char (*)[100])(_frec_1a8 + 4))
#define acStack_140 (*(char (*)[60])(_frec_1a8 + 104))
#define program_path (*(CHAR (*)[260])(_frec_1a8 + 164))
  int iVar1;
  DWORD path_len;
  HANDLE hFile;
  int *entry;
  int iVar2;
  uint uVar3;
  uint n_words;
  char *pcVar4;
  char *pcVar5;
  CHAR *pCVar6;
  char *pcVar7;
  char ch;
  
  iVar1 = 0;
  entry = &stock_rterrs;
  do {
    if (*entry == msg) break;
    entry = entry + 2;
    iVar1 = iVar1 + 1;
  } while (entry < &stock_adbgmsg);
  if ((&stock_rterrs)[iVar1 * 2] == msg) {
    if ((stock_error_mode == 1) || ((stock_error_mode == 0 && (stock_app_type == 1)))) {
      hFile = *(HANDLE *)(stock_pioinfo + 0x10);
      if (hFile == (HANDLE)0xffffffff) {
        hFile = GetStdHandle(0xfffffff4);
      }
      pcVar4 = *(char **)(iVar1 * 8 + SD(0x0045d27c));
      uVar3 = 0xffffffff;
      pcVar5 = pcVar4;
      do {
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        ch = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (ch != '\0');
      WriteFile(hFile,pcVar4,~uVar3 - 1,&bytes_written,(LPOVERLAPPED)0x0);
    }
    else if (msg != 0xfc) {
      path_len = GetModuleFileNameA((HMODULE)0x0,program_path,0x104);
      if (path_len == 0) {
        pcVar4 = s_str_0045d350;
        pCVar6 = program_path;
        for (iVar2 = 5; iVar2 != 0; iVar2 = iVar2 + -1) {
          *(undefined4 *)pCVar6 = *(undefined4 *)pcVar4;
          pcVar4 = pcVar4 + 4;
          pCVar6 = pCVar6 + 4;
        }
        *(undefined2 *)pCVar6 = *(undefined2 *)pcVar4;
        pCVar6[2] = pcVar4[2];
      }
      pcVar4 = program_path;
      uVar3 = 0xffffffff;
      pcVar5 = program_path;
      do {
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        ch = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (ch != '\0');
      if (0x3c < ~uVar3) {
        uVar3 = 0xffffffff;
        pcVar4 = program_path;
        do {
          if (uVar3 == 0) break;
          uVar3 = uVar3 - 1;
          ch = *pcVar4;
          pcVar4 = pcVar4 + 1;
        } while (ch != '\0');
        pcVar4 = acStack_140 + ~uVar3;
        stock_strncpy(pcVar4,&stock_ellipsis_text,3);
      }
      pcVar5 = s_Runtime_Error__Program__0045d330;
      pcVar7 = message_text;
      for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
        *(undefined4 *)pcVar7 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar7 = pcVar7 + 4;
      }
      *(undefined2 *)pcVar7 = *(undefined2 *)pcVar5;
      uVar3 = 0xffffffff;
      do {
        pcVar5 = pcVar4;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar5 = pcVar4 + 1;
        ch = *pcVar4;
        pcVar4 = pcVar5;
      } while (ch != '\0');
      uVar3 = ~uVar3;
      iVar2 = -1;
      pcVar4 = message_text;
      do {
        pcVar7 = pcVar4;
        if (iVar2 == 0) break;
        iVar2 = iVar2 + -1;
        pcVar7 = pcVar4 + 1;
        ch = *pcVar4;
        pcVar4 = pcVar7;
      } while (ch != '\0');
      pcVar4 = pcVar5 + -uVar3;
      pcVar5 = pcVar7 + -1;
      for (n_words = uVar3 >> 2; n_words != 0; n_words = n_words - 1) {
        *(undefined4 *)pcVar5 = *(undefined4 *)pcVar4;
        pcVar4 = pcVar4 + 4;
        pcVar5 = pcVar5 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar5 = *pcVar4;
        pcVar4 = pcVar4 + 1;
        pcVar5 = pcVar5 + 1;
      }
      uVar3 = 0xffffffff;
      pcVar4 = (char *)&stock_newline_pair_text;
      do {
        pcVar5 = pcVar4;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar5 = pcVar4 + 1;
        ch = *pcVar4;
        pcVar4 = pcVar5;
      } while (ch != '\0');
      uVar3 = ~uVar3;
      iVar2 = -1;
      pcVar4 = message_text;
      do {
        pcVar7 = pcVar4;
        if (iVar2 == 0) break;
        iVar2 = iVar2 + -1;
        pcVar7 = pcVar4 + 1;
        ch = *pcVar4;
        pcVar4 = pcVar7;
      } while (ch != '\0');
      pcVar4 = pcVar5 + -uVar3;
      pcVar5 = pcVar7 + -1;
      for (n_words = uVar3 >> 2; n_words != 0; n_words = n_words - 1) {
        *(undefined4 *)pcVar5 = *(undefined4 *)pcVar4;
        pcVar4 = pcVar4 + 4;
        pcVar5 = pcVar5 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar5 = *pcVar4;
        pcVar4 = pcVar4 + 1;
        pcVar5 = pcVar5 + 1;
      }
      uVar3 = 0xffffffff;
      pcVar4 = *(char **)(iVar1 * 8 + SD(0x0045d27c));
      do {
        pcVar5 = pcVar4;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar5 = pcVar4 + 1;
        ch = *pcVar4;
        pcVar4 = pcVar5;
      } while (ch != '\0');
      uVar3 = ~uVar3;
      iVar1 = -1;
      pcVar4 = message_text;
      do {
        pcVar7 = pcVar4;
        if (iVar1 == 0) break;
        iVar1 = iVar1 + -1;
        pcVar7 = pcVar4 + 1;
        ch = *pcVar4;
        pcVar4 = pcVar7;
      } while (ch != '\0');
      pcVar4 = pcVar5 + -uVar3;
      pcVar5 = pcVar7 + -1;
      for (n_words = uVar3 >> 2; n_words != 0; n_words = n_words - 1) {
        *(undefined4 *)pcVar5 = *(undefined4 *)pcVar4;
        pcVar4 = pcVar4 + 4;
        pcVar5 = pcVar5 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar5 = *pcVar4;
        pcVar4 = pcVar4 + 1;
        pcVar5 = pcVar5 + 1;
      }
      ___crtMessageBoxA(message_text,s_Microsoft_Visual_C___Runtime_Lib_0045d304,0x12010);
      return;
    }
  }
  return;
#undef bytes_written
#undef message_text
#undef acStack_140
#undef program_path
}



