#include "decls.h"
#include "imports.h"

// entry: 004383f0
// name : stock_NMSG_WRITE
// size : 494
// sig  : void __cdecl stock_NMSG_WRITE(int rterrnum)


int __cdecl stock_NMSG_WRITE(int rterrnum)

{
  unsigned char _frec_1a8[1204];
#define nwritten (*(DWORD *)(_frec_1a8 + 0))
#define msg_buf (*(char (*)[100])(_frec_1a8 + 4))
#define acStack_140 (*(char (*)[60])(_frec_1a8 + 104))
#define prog_name (*(CHAR (*)[260])(_frec_1a8 + 164))
  int iVar1;
  DWORD name_len;
  HANDLE hFile;
  int *rterr;
  int n;
  uint len;
  uint n4;
  char *pcVar2;
  char *pcVar3;
  CHAR *pCVar4;
  char *pcVar5;
  char ch;
  
  iVar1 = 0;
  rterr = &stock_rterrs;
  do {
    if (*rterr == rterrnum) break;
    rterr = rterr + 2;
    iVar1 = iVar1 + 1;
  } while (rterr < &stock_adbgmsg);
  if ((&stock_rterrs)[iVar1 * 2] == rterrnum) {
    if ((stock_error_mode == 1) || ((stock_error_mode == 0 && (stock_app_type == 1)))) {
      hFile = *(HANDLE *)(stock_pioinfo + 0x10);
      if (hFile == (HANDLE)0xffffffff) {
        hFile = GetStdHandle(0xfffffff4);
      }
      pcVar2 = *(char **)(iVar1 * 8 + SD(0x00443a3c));
      len = 0xffffffff;
      pcVar3 = pcVar2;
      do {
        if (len == 0) break;
        len = len - 1;
        ch = *pcVar3;
        pcVar3 = pcVar3 + 1;
      } while (ch != '\0');
      WriteFile(hFile,pcVar2,~len - 1,&nwritten,(LPOVERLAPPED)0x0);
    }
    else if (rterrnum != 0xfc) {
      name_len = GetModuleFileNameA((HMODULE)0x0,prog_name,0x104);
      if (name_len == 0) {
        pcVar2 = s_str_00443b0c;
        pCVar4 = prog_name;
        for (n = 5; n != 0; n = n + -1) {
          *(undefined4 *)pCVar4 = *(undefined4 *)pcVar2;
          pcVar2 = pcVar2 + 4;
          pCVar4 = pCVar4 + 4;
        }
        *(undefined2 *)pCVar4 = *(undefined2 *)pcVar2;
        pCVar4[2] = pcVar2[2];
      }
      pcVar2 = prog_name;
      len = 0xffffffff;
      pcVar3 = prog_name;
      do {
        if (len == 0) break;
        len = len - 1;
        ch = *pcVar3;
        pcVar3 = pcVar3 + 1;
      } while (ch != '\0');
      if (0x3c < ~len) {
        len = 0xffffffff;
        pcVar2 = prog_name;
        do {
          if (len == 0) break;
          len = len - 1;
          ch = *pcVar2;
          pcVar2 = pcVar2 + 1;
        } while (ch != '\0');
        pcVar2 = acStack_140 + ~len;
        stock_strncpy(pcVar2,&DAT_004427d0,3);
      }
      pcVar3 = s_Runtime_Error__Program__00443af0;
      pcVar5 = msg_buf;
      for (n = 6; n != 0; n = n + -1) {
        *(undefined4 *)pcVar5 = *(undefined4 *)pcVar3;
        pcVar3 = pcVar3 + 4;
        pcVar5 = pcVar5 + 4;
      }
      *(undefined2 *)pcVar5 = *(undefined2 *)pcVar3;
      len = 0xffffffff;
      do {
        pcVar3 = pcVar2;
        if (len == 0) break;
        len = len - 1;
        pcVar3 = pcVar2 + 1;
        ch = *pcVar2;
        pcVar2 = pcVar3;
      } while (ch != '\0');
      len = ~len;
      n = -1;
      pcVar2 = msg_buf;
      do {
        pcVar5 = pcVar2;
        if (n == 0) break;
        n = n + -1;
        pcVar5 = pcVar2 + 1;
        ch = *pcVar2;
        pcVar2 = pcVar5;
      } while (ch != '\0');
      pcVar2 = pcVar3 + -len;
      pcVar3 = pcVar5 + -1;
      for (n4 = len >> 2; n4 != 0; n4 = n4 - 1) {
        *(undefined4 *)pcVar3 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar3 = pcVar3 + 4;
      }
      for (len = len & 3; len != 0; len = len - 1) {
        *pcVar3 = *pcVar2;
        pcVar2 = pcVar2 + 1;
        pcVar3 = pcVar3 + 1;
      }
      len = 0xffffffff;
      pcVar2 = (char *)&DAT_00443aec;
      do {
        pcVar3 = pcVar2;
        if (len == 0) break;
        len = len - 1;
        pcVar3 = pcVar2 + 1;
        ch = *pcVar2;
        pcVar2 = pcVar3;
      } while (ch != '\0');
      len = ~len;
      n = -1;
      pcVar2 = msg_buf;
      do {
        pcVar5 = pcVar2;
        if (n == 0) break;
        n = n + -1;
        pcVar5 = pcVar2 + 1;
        ch = *pcVar2;
        pcVar2 = pcVar5;
      } while (ch != '\0');
      pcVar2 = pcVar3 + -len;
      pcVar3 = pcVar5 + -1;
      for (n4 = len >> 2; n4 != 0; n4 = n4 - 1) {
        *(undefined4 *)pcVar3 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar3 = pcVar3 + 4;
      }
      for (len = len & 3; len != 0; len = len - 1) {
        *pcVar3 = *pcVar2;
        pcVar2 = pcVar2 + 1;
        pcVar3 = pcVar3 + 1;
      }
      len = 0xffffffff;
      pcVar2 = *(char **)(iVar1 * 8 + SD(0x00443a3c));
      do {
        pcVar3 = pcVar2;
        if (len == 0) break;
        len = len - 1;
        pcVar3 = pcVar2 + 1;
        ch = *pcVar2;
        pcVar2 = pcVar3;
      } while (ch != '\0');
      len = ~len;
      iVar1 = -1;
      pcVar2 = msg_buf;
      do {
        pcVar5 = pcVar2;
        if (iVar1 == 0) break;
        iVar1 = iVar1 + -1;
        pcVar5 = pcVar2 + 1;
        ch = *pcVar2;
        pcVar2 = pcVar5;
      } while (ch != '\0');
      pcVar2 = pcVar3 + -len;
      pcVar3 = pcVar5 + -1;
      for (n4 = len >> 2; n4 != 0; n4 = n4 - 1) {
        *(undefined4 *)pcVar3 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar3 = pcVar3 + 4;
      }
      for (len = len & 3; len != 0; len = len - 1) {
        *pcVar3 = *pcVar2;
        pcVar2 = pcVar2 + 1;
        pcVar3 = pcVar3 + 1;
      }
      ___crtMessageBoxA(msg_buf,s_Microsoft_Visual_C___Runtime_Lib_00443ac4,0x12010);
      return;
    }
  }
  return;
#undef nwritten
#undef msg_buf
#undef acStack_140
#undef prog_name
}
