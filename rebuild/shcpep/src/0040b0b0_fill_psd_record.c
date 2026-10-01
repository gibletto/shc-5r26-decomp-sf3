#include "decls.h"
#include "imports.h"

// entry: 0040b0b0
// name : fill_psd_record
// size : 78
// sig  : void __cdecl fill_psd_record(psd *rec,uchar op,char flg,char misc,char tmp,int sptravel,int expno,short filno,ushort linno,ea *ea1,ea *ea2)


int __cdecl fill_psd_record(psd *rec,uchar op,char flg,char misc,char tmp,int sptravel,int expno,short filno,
               ushort linno,ea *ea1,ea *ea2)

{
  rec->op = op;
  rec->flg = flg;
  rec->misc = misc;
  rec->tmp = tmp;
  rec->sptravel = sptravel;
  rec->expno = expno;
  rec->filno = filno;
  rec->linno = linno;
  rec->ea1 = ea1;
  rec->ea2 = ea2;
  return;
}
