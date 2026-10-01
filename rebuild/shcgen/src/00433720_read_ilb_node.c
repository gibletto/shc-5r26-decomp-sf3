#include "decls.h"
#include "imports.h"

// entry: 00433720
// name : read_ilb_node
// size : 736
// sig  : gen_node * read_ilb_node(FILE * in)


gen_node * __cdecl read_ilb_node(FILE *in)

{
  unsigned char _frec_1[1];
#define ilb_byte (*(uchar *)(_frec_1 + 0))
  byte bVar1;
  uint got;
  gen_node *new_node;
  int i;
  undefined4 *cell;
  
  got = read_file_bytes(in,(char *)&ilb_byte,1);
  if (got != 1) {
    if (got == 0) {
      return (gen_node *)0xffffffff;
    }
    report_message_by_code((char *)0x0,0,0xce6,(char *)0x0);
    stock_exit(9);
  }
  new_node = alloc_gen_node(ilb_byte);
  if (new_node != (gen_node *)0x0) {
    cell = (undefined4 *)&g_ilb_record_buffer;
    for (i = 8; i != 0; i = i + -1) {
      *cell = 0;
      cell = cell + 1;
    }
    switch(ilb_byte) {
    case '\0':
    case '\x01':
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
      read_ilb_untyped_node(new_node,in);
      break;
    default:
      report_message_by_code((char *)0x0,0,0x12d4,(char *)0x0);
      stock_exit(0xb);
      break;
    case '\x04':
    case '\b':
    case '\x10':
    case '\x1b':
    case '\x1c':
    case '\x1d':
    case '\x1e':
    case 'p':
      read_ilb_symbol_node(new_node,in);
      break;
    case '\x05':
      read_ilb_asm_node(new_node,in);
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
      got = read_file_bytes(in,(char *)&ilb_byte,1);
      if (got != 1) {
        report_message_by_code((char *)0x0,0,0xce6,(char *)0x0);
        stock_exit(9);
      }
      new_node->type = ilb_byte;
      if (((ilb_byte & 0xe0) == 0x60) || ((ilb_byte & 0xe0) == 0x80)) {
        read_ilb_aggregate_node(new_node,in);
      }
      else {
        read_ilb_typed_node(new_node,in);
      }
      break;
    case '0':
      got = read_file_bytes(in,(char *)&ilb_byte,1);
      if (got != 1) {
        report_message_by_code((char *)0x0,0,0xce6,(char *)0x0);
        stock_exit(9);
      }
      new_node->type = ilb_byte;
      if (((ilb_byte & 0xe0) == 0x60) || ((ilb_byte & 0xe0) == 0x80)) {
        read_ilb_aggregate_call_node(new_node,in);
      }
      else {
        read_ilb_call_node(new_node,in);
      }
      break;
    case '4':
      got = read_file_bytes(in,(char *)&ilb_byte,1);
      if (got != 1) {
        report_message_by_code((char *)0x0,0,0xce6,(char *)0x0);
        stock_exit(9);
      }
      new_node->type = ilb_byte;
      if (((ilb_byte & 0xe0) == 0x60) || ((ilb_byte & 0xe0) == 0x80)) {
        read_ilb_aggregate_qualify_node(new_node,in);
      }
      else {
        read_ilb_qualify_node(new_node,in);
      }
      break;
    case '5':
      read_ilb_bit_qualify_node(new_node,in);
      break;
    case '8':
    case '9':
    case '<':
    case '=':
      read_ilb_incdec_node(new_node,in);
      break;
    case 'q':
      got = read_file_bytes(in,(char *)&ilb_byte,1);
      if (got != 1) {
        report_message_by_code((char *)0x0,0,0xce6,(char *)0x0);
        stock_exit(9);
      }
      new_node->type = ilb_byte;
      if ((ilb_byte & 0xe0) == 0) {
        read_ilb_word_const_node(new_node,in);
      }
      else if ((ilb_byte & 0xe0) == 0x20) {
        bVar1 = ilb_byte & 0xf8;
        if (bVar1 == 0x28) {
          read_ilb_word_const_node(new_node,in);
        }
        else if (bVar1 == 0x30) {
          read_ilb_double_const_node(new_node,in);
        }
        else if (bVar1 == 0x38) {
          read_ilb_long_double_const_node(new_node,in);
        }
      }
      else if ((ilb_byte & 0xe0) == 0x40) {
        read_ilb_pointer_const_node(new_node,in);
      }
    }
    new_node = attach_ilb_node(new_node);
    return (gen_node *)((new_node == (gen_node *)0x0) - 1 & (uint)new_node);
  }
  return (gen_node *)0x0;
#undef ilb_byte
}



