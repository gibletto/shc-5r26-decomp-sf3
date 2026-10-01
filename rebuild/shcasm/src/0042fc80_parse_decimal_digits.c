#include "decls.h"
#include "imports.h"

// entry: 0042fc80
// name : parse_decimal_digits
// size : 46
// sig  : void __cdecl parse_decimal_digits(char *digits,int *value,int *length)


int __cdecl parse_decimal_digits(char *digits,int *value,int *length)

{
  byte *pbVar1;
  char cVar2;
  int n;
  int number;
  
  n = 0;
  number = 0;
  cVar2 = *digits;
  while (cVar2 != '\0') {
    pbVar1 = (byte *)(digits + n);
    n = n + 1;
    number = (*pbVar1 - 0x30) + number * 10;
    cVar2 = digits[n];
  }
  *value = number;
  *length = n;
  return;
}
