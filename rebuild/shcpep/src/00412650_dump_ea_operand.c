#include "decls.h"
#include "imports.h"

// entry: 00412650
// name : dump_ea_operand
// size : 244
// sig  : int dump_ea_operand(ea * op, int number)


int __cdecl dump_ea_operand(ea *op,int number)

{
  int result;
  int extraout_EAX;
  char *format;
  
  _printf(s_EA__d_TABLE_00427384,number);
  switch(op->type & 0x1f) {
  case 0:
    _printf(s_str_00427364);
    return 0;
  case 1:
    format = s_str_00427344;
    break;
  case 2:
    format = s_str_00427324;
    break;
  case 3:
    format = s_str_00427304;
    break;
  case 4:
    format = s_str_004272e4;
    break;
  case 5:
    format = s_str_004272c4;
    break;
  case 6:
    format = s_str_004272a4;
    break;
  case 7:
    format = s_str_00427284;
    break;
  case 8:
    format = s_str_00427264;
    break;
  case 9:
    format = s_str_00427244;
    break;
  case 10:
    format = s_str_00427224;
    break;
  case 0xb:
    format = s_str_00427200;
    break;
  case 0xc:
    format = s_str_004271dc;
    break;
  case 0xd:
    format = s_str_004271bc;
    break;
  default:
    goto switchD_00412673_default;
  }
  _printf(format);
switchD_00412673_default:
  _printf(s___eabase__d_004271a4,(int)op->base);
  _printf(s___eaindex__d_00427194,(int)op->index);
  _printf(s___eamisc__x_00427184,(int)op->misc);
  result = _printf(s___eadisp__x_00427174,op->disp);
  if (op->labels != (label_ref *)0x0) {
    dump_ea_label_list(op);
    result = extraout_EAX;
  }
  return result;
}



