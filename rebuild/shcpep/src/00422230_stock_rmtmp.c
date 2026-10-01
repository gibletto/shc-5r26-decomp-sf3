#include "decls.h"
#include "imports.h"

// entry: 00422230
// name : stock_rmtmp
// size : 75
// sig  : int stock_rmtmp(void)


int __cdecl stock_rmtmp(void)

{
  GhFILE *file;
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  iVar3 = 0;
  if (0 < stock_nstream) {
    iVar1 = 0;
    do {
      file = *(GhFILE **)(stock_piob + iVar1);
      if (((file != (GhFILE *)0x0) && ((file->_flag & 0x83U) != 0)) &&
         (file->_tmpfname != (char *)0x0)) {
        iVar2 = iVar2 + 1;
        _fclose(file);
      }
      iVar1 = iVar1 + 4;
      iVar3 = iVar3 + 1;
    } while (iVar3 < stock_nstream);
  }
  return iVar2;
}



