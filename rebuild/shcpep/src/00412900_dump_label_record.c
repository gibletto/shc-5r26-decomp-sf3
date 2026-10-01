#include "decls.h"
#include "imports.h"

// entry: 00412900
// name : dump_label_record
// size : 98
// sig  : void dump_label_record(psd * rec)


int __cdecl dump_label_record(psd *rec)

{
  _printf(s_str_00427528,(int)*(short *)&rec->ea1);
  _printf(s___psdfilno__x_00427518,(int)rec->filno);
  _printf(s___psdlinno__x_004274e4,(uint)rec->linno);
  _printf(s___psddmy1__x_00427450,(int)*(short *)((int)&rec->ea1 + 2));
  _printf(s___psddmy2__x_00427440,rec->ea2);
  return;
}



