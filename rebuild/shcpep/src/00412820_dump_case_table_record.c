#include "decls.h"
#include "imports.h"

// entry: 00412820
// name : dump_case_table_record
// size : 96
// sig  : void dump_case_table_record(psd * rec)


int __cdecl dump_case_table_record(psd *rec)

{
  _printf(s_str_00427480,(int)rec->filno);
  _printf(s___psdswexit__x_00427470,(int)(short)rec->linno);
  _printf(s___psdlabno__x_00427460,(int)*(short *)&rec->ea1);
  _printf(s___psddmy1__x_00427450,(int)*(short *)((int)&rec->ea1 + 2));
  _printf(s___psddmy2__x_00427440,rec->ea2);
  return;
}



