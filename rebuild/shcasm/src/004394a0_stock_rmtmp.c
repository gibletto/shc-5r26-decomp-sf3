#include "decls.h"
#include "imports.h"

// entry: 004394a0
// name : stock_rmtmp
// size : 75
// sig  : int stock_rmtmp(void)


int __cdecl stock_rmtmp(void)

{
  GhFILE *_File;
  int ofs;
  int count;
  int i;
  
  count = 0;
  i = 0;
  if (0 < stock_nstream) {
    ofs = 0;
    do {
      _File = *(GhFILE **)(stock_piob + ofs);
      if (((_File != (GhFILE *)0x0) && ((_File->_flag & 0x83U) != 0)) &&
         (_File->_tmpfname != (char *)0x0)) {
        count = count + 1;
        _fclose(_File);
      }
      ofs = ofs + 4;
      i = i + 1;
    } while (i < stock_nstream);
  }
  return count;
}



