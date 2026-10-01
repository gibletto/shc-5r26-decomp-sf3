#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_loaded_request
#define g_loaded_request (*(request * *)(g_sd + 0x1ff84))


// entry: 00435520
// name : skip_ilb_function
// size : 1393
// sig  : FILE * skip_ilb_function(FILE * in)


FILE * __cdecl skip_ilb_function(FILE *in)

{
  unsigned char _frec_21[33];
#define op_byte (*(char *)(_frec_21 + 0))
#define record (*(byte (*)[32])(_frec_21 + 1))
  byte type_class;
  uint uVar1;
  int iVar2;
  byte *cursor;
  bool done;
  
  done = false;
  do {
    uVar1 = read_file_bytes(in,&op_byte,1);
    if (uVar1 != 1) {
      if (uVar1 == 0) {
        report_message_by_code((char *)0x0,0,0x12d9,(char *)0x0);
        stock_exit(0xb);
      }
      report_message_by_code((char *)0x0,0,0xce6,(char *)0x0);
      stock_exit(9);
    }
    cursor = record;
    for (iVar2 = 8; iVar2 != 0; iVar2 = iVar2 + -1) {
      cursor[0] = 0;
      cursor[1] = 0;
      cursor[2] = 0;
      cursor[3] = 0;
      cursor = cursor + 4;
    }
    switch(op_byte) {
    case '\0':
    case '\t':
    case '\x0f':
    case '\x12':
    case '\x14':
    case '\x16':
    case '\x17':
    case '\x19':
    case '\x1a':
    case 'o':
    case 'x':
    case 'y':
      if ((g_loaded_request->stage == 1) || (op_byte != '\t')) {
        uVar1 = read_file_bytes(in,(char *)record,6);
        if (uVar1 != 6) goto LAB_00435a34;
      }
      else {
        uVar1 = read_file_bytes(in,(char *)record,7);
        if (uVar1 != 7) goto LAB_00435a34;
      }
      break;
    case '\x01':
    case '\x04':
    case '\x05':
      done = true;
      break;
    default:
      report_message_by_code((char *)0x0,0,0x12d4,(char *)0x0);
      uVar1 = 0xb;
LAB_00435a49:
      stock_exit(uVar1);
      break;
    case '\b':
    case '\x10':
    case '\x1b':
    case '\x1c':
    case '\x1d':
    case '\x1e':
    case 'p':
      if ((g_loaded_request->stage == 1) || ((op_byte != 'p' && (op_byte != '\b')))) {
        uVar1 = read_file_bytes(in,(char *)record,8);
joined_r0x0043586c:
        if (uVar1 != 8) goto LAB_00435a34;
      }
      else if (op_byte == '\b') {
        uVar1 = read_file_bytes(in,(char *)record,9);
        if (uVar1 != 9) goto LAB_00435a34;
      }
      else {
        uVar1 = read_file_bytes(in,(char *)record,10);
        if (uVar1 != 10) goto LAB_00435a34;
        if (g_loaded_request->stage == 2) {
          uVar1 = read_file_bytes(in,(char *)record,1);
          goto joined_r0x00435805;
        }
      }
      break;
    case '\x18':
    case ' ':
    case '$':
    case '%':
    case '(':
    case ')':
    case ',':
    case '-':
    case '@':
    case 'A':
    case 'D':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'L':
    case 'M':
    case 'N':
    case 'P':
    case 'Q':
    case 'T':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case '\\':
    case ']':
    case '^':
    case '_':
    case '`':
    case 'a':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case 'l':
    case '\x7f':
      uVar1 = read_file_bytes(in,(char *)record,1);
      if (uVar1 != 1) {
        report_message_by_code((char *)0x0,0,0xce6,(char *)0x0);
        stock_exit(9);
      }
      if (((record[0] & 0xe0) == 0x60) || ((record[0] & 0xe0) == 0x80)) {
        uVar1 = read_file_bytes(in,(char *)record,10);
        if (uVar1 != 10) {
          report_message_by_code((char *)0x0,0,0xce6,(char *)0x0);
          stock_exit(9);
        }
        if ((g_loaded_request->stage == 2) &&
           (((((op_byte == 'l' || (op_byte == '_')) || (op_byte == 'P')) ||
             ((op_byte == 'Q' || (op_byte == 'T')))) || (op_byte == 'V')))) {
          uVar1 = read_file_bytes(in,(char *)record,1);
joined_r0x00435805:
          if (uVar1 != 1) goto LAB_00435a34;
        }
      }
      else {
        uVar1 = read_file_bytes(in,(char *)record,6);
        if (uVar1 != 6) goto LAB_00435a34;
        if ((g_loaded_request->stage == 2) &&
           (((op_byte == 'l' || (op_byte == '_')) ||
            ((op_byte == 'P' || (((op_byte == 'Q' || (op_byte == 'T')) || (op_byte == 'V')))))))) {
          uVar1 = read_file_bytes(in,(char *)record,1);
          goto joined_r0x00435805;
        }
      }
      break;
    case '0':
      uVar1 = read_file_bytes(in,(char *)record,1);
      if (uVar1 != 1) {
        report_message_by_code((char *)0x0,0,0xce6,(char *)0x0);
        stock_exit(9);
      }
      if (((record[0] & 0xe0) != 0x60) && ((record[0] & 0xe0) != 0x80)) {
        uVar1 = read_file_bytes(in,(char *)record,8);
        goto joined_r0x0043586c;
      }
      uVar1 = read_file_bytes(in,(char *)record,0xc);
joined_r0x00435a32:
      if (uVar1 != 0xc) goto LAB_00435a34;
      break;
    case '4':
      uVar1 = read_file_bytes(in,(char *)record,1);
      if (uVar1 != 1) {
        report_message_by_code((char *)0x0,0,0xce6,(char *)0x0);
        stock_exit(9);
      }
      if (((record[0] & 0xe0) == 0x60) || ((record[0] & 0xe0) == 0x80)) {
        uVar1 = read_file_bytes(in,(char *)record,0xe);
joined_r0x00435a04:
        if (uVar1 != 0xe) goto LAB_00435a34;
      }
      else {
        uVar1 = read_file_bytes(in,(char *)record,10);
joined_r0x004359bb:
        if (uVar1 != 10) goto LAB_00435a34;
      }
      break;
    case '5':
      uVar1 = read_file_bytes(in,(char *)record,0xd);
      if (uVar1 != 0xd) {
LAB_00435a34:
        report_message_by_code((char *)0x0,0,0xce6,(char *)0x0);
        uVar1 = 9;
        goto LAB_00435a49;
      }
      break;
    case '8':
    case '9':
    case '<':
    case '=':
      uVar1 = read_file_bytes(in,(char *)record,0xb);
      if (uVar1 != 0xb) goto LAB_00435a34;
      break;
    case 'q':
      uVar1 = read_file_bytes(in,(char *)record,1);
      if (uVar1 != 1) {
        report_message_by_code((char *)0x0,0,0xce6,(char *)0x0);
        stock_exit(9);
      }
      if ((record[0] & 0xe0) == 0) {
        uVar1 = read_file_bytes(in,(char *)record,10);
        goto joined_r0x004359bb;
      }
      if ((record[0] & 0xe0) == 0x20) {
        type_class = record[0] & 0xf8;
        if (type_class == 0x28) {
          uVar1 = read_file_bytes(in,(char *)record,10);
          goto joined_r0x004359bb;
        }
        if (type_class == 0x30) {
          uVar1 = read_file_bytes(in,(char *)record,0xe);
          goto joined_r0x00435a04;
        }
        if ((type_class == 0x38) && (uVar1 = read_file_bytes(in,(char *)record,0x12), uVar1 != 0x12)
           ) goto LAB_00435a34;
      }
      else if ((record[0] & 0xe0) == 0x40) {
        uVar1 = read_file_bytes(in,(char *)record,0xc);
        goto joined_r0x00435a32;
      }
    }
    if (done) {
      iVar2 = stock_fseek(in,-1,1);
      if (iVar2 != 0) {
        report_message_by_code((char *)0x0,0,0x12d8,(char *)0x0);
        stock_exit(0xb);
      }
      return in;
    }
  } while( true );
#undef op_byte
#undef record
}



