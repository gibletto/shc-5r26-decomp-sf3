#include "decls.h"
#include "imports.h"

// entry: 00427b17
// name : immediate_bit_width
// size : 376
// sig  : int immediate_bit_width(char signedness, uint value)


int __cdecl immediate_bit_width(char signedness,uint value)

{
  int bit_width;
  
  bit_width = 0;
  if (value != 0) {
    bit_width = 0x20;
    if (signedness == 's') {
      if (((int)value < -0x80) || (0x7f < (int)value)) {
        if (((int)value < -0x100) || (0xff < (int)value)) {
          if (((int)value < -0x200) || (0x1ff < (int)value)) {
            if ((-0x1001 < (int)value) && ((int)value < 0x1000)) {
              bit_width = 0xd;
            }
          }
          else {
            bit_width = 10;
          }
        }
        else {
          bit_width = 9;
        }
      }
      else {
        bit_width = 8;
      }
    }
    else if (signedness == 'u') {
      if (value < 0x10) {
        bit_width = 4;
      }
      else if (value < 0x20) {
        bit_width = 5;
      }
      else if (value < 0x40) {
        bit_width = 6;
      }
      else if (value < 0x100) {
        bit_width = 8;
      }
      else if (value < 0x200) {
        bit_width = 9;
      }
      else if (value < 0x400) {
        bit_width = 10;
      }
    }
  }
  return bit_width;
}



