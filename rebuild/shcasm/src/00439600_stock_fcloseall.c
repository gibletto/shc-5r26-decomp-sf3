#include "decls.h"
#include "imports.h"

// entry: 00439600
// name : stock_fcloseall
// size : 115
// sig  : int stock_fcloseall(void)


int __cdecl stock_fcloseall(void)

{
  GhFILE *_File;
  int close_result;
  int ofs;
  int count;
  int i;
  
  count = 0;
  i = 3;
  if (3 < stock_nstream) {
    ofs = 0xc;
    do {
      _File = *(GhFILE **)(stock_piob + ofs);
      if (_File != (GhFILE *)0x0) {
        if ((_File->_flag & 0x83U) != 0) {
          close_result = _fclose(_File);
          if (close_result != -1) {
            count = count + 1;
          }
        }
        if (0x4f < ofs) {
          stock_free(*(void **)(stock_piob + ofs));
          *(undefined4 *)(stock_piob + ofs) = 0;
        }
      }
      ofs = ofs + 4;
      i = i + 1;
    } while (i < stock_nstream);
  }
  return count;
}



