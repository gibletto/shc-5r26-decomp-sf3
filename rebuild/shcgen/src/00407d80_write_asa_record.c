#include "decls.h"
#include "imports.h"

// entry: 00407d80
// name : write_asa_record
// size : 112
// sig  : void write_asa_record(short kind, short symx)


int __cdecl write_asa_record(short kind,short symx)

{
  char kind_byte;
  
  kind_byte = (char)kind;
  switch(kind) {
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
    write_asa_symbol_record(kind,symx);
    return;
  case 6:
    write_asa_tag6_record(kind_byte);
    return;
  case 7:
  case 8:
  case 9:
  case 0x10:
    write_asa_global_records(kind,symx);
    return;
  default:
    report_codegen_message(0x123e,1,0,0,(char *)0x0);
    return;
  case 0xd:
    write_asa_label_count_record(kind_byte);
    return;
  case 0xe:
    write_asa_trailer_record(kind_byte);
    return;
  }
}



