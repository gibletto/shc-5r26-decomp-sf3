#include "decls.h"
#include "imports.h"

// entry: 0041e2b5
// name : set_psd_record
// size : 86
// sig  : void __cdecl set_psd_record(psd *rec,uchar op,uchar flg,char misc,char tmp,int sptravel,int expno,short filno,ushort linno)


int __cdecl set_psd_record(psd *rec,uchar op,uchar flg,char misc,char tmp,int sptravel,int expno,short filno,
              ushort linno)

{
  rec->op = op;
  rec->flg = flg;
  rec->misc = misc;
  rec->tmp = tmp;
  rec->sptravel = sptravel;
  rec->expno = expno;
  rec->filno = filno;
  rec->linno = linno;
  return;
}
