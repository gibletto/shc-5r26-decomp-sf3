#include "decls.h"
#include "imports.h"

// entry: 004127d0
// name : dump_casejmp_record
// size : 77
// sig  : void dump_casejmp_record(psd * rec)


int __cdecl dump_casejmp_record(psd *rec)

{
  _printf(s_str_0042741c,(int)rec->filno);
  _printf(s___default_lab__x_00427408,(int)(short)rec->linno);
  _printf(s___casmin__x_004273f8,rec->ea1);
  _printf(s___caslab_max_min___x_004273e0,rec->ea2);
  return;
}



