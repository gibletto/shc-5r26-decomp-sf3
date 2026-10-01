#include "decls.h"
#include "imports.h"

// entry: 00435f90
// name : stock_flsall
// size : 107
// sig  : int stock_flsall(int flushflag)


int __cdecl stock_flsall(int flushflag)

{
  int rc;
  int count;
  int err;
  int ofs;
  GhFILE *stream;
  
  count = 0;
  ofs = 0;
  err = 0;
  do {
    stream = *(GhFILE **)(stock_piob + ofs);
    if ((stream != (GhFILE *)0x0) && ((stream->_flag & 0x83U) != 0)) {
      if (flushflag == 1) {
        rc = _fflush(stream);
        if (rc != -1) {
          count = count + 1;
        }
      }
      else if ((flushflag == 0) && ((stream->_flag & 2U) != 0)) {
        rc = _fflush(stream);
        if (rc == -1) {
          err = -1;
        }
      }
    }
    ofs = ofs + 4;
  } while (ofs < 0x800);
  if (flushflag != 1) {
    count = err;
  }
  return count;
}



