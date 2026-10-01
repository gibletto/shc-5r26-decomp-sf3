#include "decls.h"
#include "imports.h"

// entry: 00412880
// name : dump_line_record
// size : 116
// sig  : void dump_line_record(psd * rec)


int __cdecl dump_line_record(psd *rec)

{
  _printf(s_str_004274f4,(int)rec->filno);
  _printf(s___psdlinno__x_004274e4,(uint)rec->linno);
  _printf(s___psdstate__x_004274d4,(int)*(char *)&rec->ea1);
  _printf(s_str_004274b4,(int)*(char *)((int)&rec->ea1 + 1));
  _printf(s___psddmy2__x_00427440,(int)*(short *)((int)&rec->ea1 + 2));
  _printf(s___psddmy3__x_004274a4,rec->ea2);
  return;
}



