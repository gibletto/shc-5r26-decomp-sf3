#include "decls.h"
#include "imports.h"

// entry: 0042e064
// name : check_operand_registers
// size : 736
// sig  : void __cdecl check_operand_registers(ea *op)


int __cdecl check_operand_registers(ea *op)

{
  switch(op->type & 0x1f) {
  case 0:
  case 0xd:
    report_message_at_source_line(0,0,0x133b,(char *)0x0);
    break;
  case 1:
    if (((char)op->base < '\0') || ('`' < (char)op->base)) {
      report_message_at_source_line(0,0,0x133b,(char *)0x0);
    }
    break;
  case 2:
  case 3:
  case 4:
    if (((char)op->base < '\0') || ('\x0f' < (char)op->base)) {
      report_message_at_source_line(0,0,0x133b,(char *)0x0);
    }
    break;
  case 5:
    if (((char)op->base < 'a') || ('c' < (char)op->base)) {
      report_message_at_source_line(0,0,0x133b,(char *)0x0);
    }
    break;
  case 6:
    if (((char)op->base < 'd') || ('f' < (char)op->base)) {
      report_message_at_source_line(0,0,0x133b,(char *)0x0);
    }
    break;
  case 7:
    break;
  case 8:
    if (((char)op->base < '\0') || ('\x0f' < (char)op->base)) {
      report_message_at_source_line(0,0,0x133b,(char *)0x0);
    }
    if ((op->disp == 0) && (op->labels == (label_ref *)0x0)) {
      op->type = op->type & 0xf0 | 2;
    }
    break;
  case 9:
    if ((((char)op->base < '\0') || ('\x0f' < (char)op->base)) || (op->index != REG_R0)) {
      report_message_at_source_line(0,0,0x133b,(char *)0x0);
    }
    break;
  case 10:
    if (op->base != REG_PC) {
      report_message_at_source_line(0,0,0x133b,(char *)0x0);
    }
    break;
  case 0xb:
    if (op->base != REG_GBR) {
      report_message_at_source_line(0,0,0x133b,(char *)0x0);
    }
    break;
  case 0xc:
    if ((op->base != REG_GBR) || (op->index != REG_R0)) {
      report_message_at_source_line(0,0,0x133b,(char *)0x0);
    }
    break;
  default:
    report_message_at_source_line(0,0,0x133b,(char *)0x0);
    break;
  case 0xf:
    if (op->base != REG_FPUL) {
      report_message_at_source_line(0,0,0x133b,(char *)0x0);
    }
    break;
  case 0x10:
    if (op->base != REG_FPSCR) {
      report_message_at_source_line(0,0,0x133b,(char *)0x0);
    }
  }
  return;
}
