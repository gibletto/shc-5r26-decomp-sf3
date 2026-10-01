#include "decls.h"
#include "imports.h"

// entry: 004219a0
// name : stock_fcloseall
// size : 115
// sig  : int stock_fcloseall(void)


int __cdecl stock_fcloseall(void)

{
  GhFILE *file;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = 0;
  iVar4 = 3;
  if (3 < stock_nstream) {
    iVar2 = 0xc;
    do {
      file = *(GhFILE **)(stock_piob + iVar2);
      if (file != (GhFILE *)0x0) {
        if ((file->_flag & 0x83U) != 0) {
          iVar1 = _fclose(file);
          if (iVar1 != -1) {
            iVar3 = iVar3 + 1;
          }
        }
        if (0x4f < iVar2) {
          stock_free(*(void **)(stock_piob + iVar2));
          *(undefined4 *)(stock_piob + iVar2) = 0;
        }
      }
      iVar2 = iVar2 + 4;
      iVar4 = iVar4 + 1;
    } while (iVar4 < stock_nstream);
  }
  return iVar3;
}



