#include "decls.h"
#include "imports.h"

// entry: 00412f3f
// name : month_name_to_digits
// size : 407
// sig  : void __cdecl month_name_to_digits(char *out,char *month)


int __cdecl month_name_to_digits(char *out,char *month)

{
  if (*month == 'J') {
    if (month[1] == 'u') {
      if (month[2] == 'n') {
        *out = '0';
        out[1] = '6';
      }
      else {
        *out = '0';
        out[1] = '7';
      }
    }
    else {
      *out = '0';
      out[1] = '1';
    }
  }
  else if (*month == 'M') {
    if (month[1] == 'a') {
      if (month[2] == 'r') {
        *out = '0';
        out[1] = '3';
      }
      else {
        *out = '0';
        out[1] = '5';
      }
    }
  }
  else if (*month == 'A') {
    if (month[1] == 'p') {
      *out = '0';
      out[1] = '4';
    }
    else {
      *out = '0';
      out[1] = '8';
    }
  }
  else if (*month == 'F') {
    *out = '0';
    out[1] = '2';
  }
  else if (*month == 'S') {
    *out = '0';
    out[1] = '9';
  }
  else if (*month == 'O') {
    *out = '1';
    out[1] = '0';
  }
  else if (*month == 'N') {
    *out = '1';
    out[1] = '1';
  }
  else {
    *out = '1';
    out[1] = '2';
  }
  return;
}
