#include "decls.h"
#include "imports.h"

// entry: 0041ed70
// name : stock_flsall
// size : 107
// sig  : int stock_flsall(int flushflag)


int __cdecl stock_flsall(int flushflag)

{
  GhFILE *_File;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = 0;
  iVar4 = 0;
  iVar3 = 0;
  do {
    _File = *(GhFILE **)(stock_piob + iVar4);
    if ((_File != (GhFILE *)0x0) && ((_File->_flag & 0x83U) != 0)) {
      if (flushflag == 1) {
        iVar1 = _fflush(_File);
        if (iVar1 != -1) {
          iVar2 = iVar2 + 1;
        }
      }
      else if ((flushflag == 0) && ((_File->_flag & 2U) != 0)) {
        iVar1 = _fflush(_File);
        if (iVar1 == -1) {
          iVar3 = -1;
        }
      }
    }
    iVar4 = iVar4 + 4;
  } while (iVar4 < 0x800);
  if (flushflag != 1) {
    iVar2 = iVar3;
  }
  return iVar2;
}



