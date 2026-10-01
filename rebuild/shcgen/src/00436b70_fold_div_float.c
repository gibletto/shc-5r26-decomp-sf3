#include "decls.h"
#include "imports.h"

// entry: 00436b70
// name : fold_div_float
// size : 368
// sig  : uint fold_div_float(uint * lhs, uint * rhs, uint * result)


uint __cdecl fold_div_float(uint *lhs,uint *rhs,uint *result)

{
  unsigned char _frec_2c[44];
#define b_exp (*(ushort *)(_frec_2c + 0))
#define a_exp (*(ushort *)(_frec_2c + 2))
#define quot (*(uint *)(_frec_2c + 4))
#define quot_1 (*(uint *)(_frec_2c + 8))
#define rem (*(uint *)(_frec_2c + 12))
#define result_sign (*(uint *)(_frec_2c + 16))
#define action (*(int *)(_frec_2c + 20))
#define b_mant (*(uint *)(_frec_2c + 24))
#define b_class (*(int *)(_frec_2c + 28))
#define b_sign (*(uint *)(_frec_2c + 32))
#define a_class (*(int *)(_frec_2c + 36))
#define a_sign (*(uint *)(_frec_2c + 40))
  short sVar1;
  undefined2 extraout_var = 0;
  uint uVar2;
  
  unpack_float(lhs,&a_sign,&a_exp,&rem,&a_class);
  unpack_float(rhs,&b_sign,&b_exp,&b_mant,&b_class);
  sVar1 = classify_div_operands(a_sign,a_class,b_sign,b_class,&action,&result_sign);
  uVar2 = CONCAT22(extraout_var,sVar1);
  if (action == 0) {
    sVar1 = 0x1a;
    quot_1 = 0;
    quot = 0;
    do {
      quot = quot * 2;
      if ((int)b_mant <= (int)rem) {
        quot = quot + 1;
        rem = rem - b_mant;
      }
      rem = rem << 1;
      sVar1 = sVar1 + -1;
    } while (sVar1 != 0);
    sVar1 = 2;
    do {
      if ((quot & 1) == 0) {
        quot_1 = (int)quot_1 >> 1 & 0x7fffffff;
      }
      else {
        quot_1 = (int)quot_1 >> 1 | 0x80000000;
      }
      quot = (int)quot >> 1;
      sVar1 = sVar1 + -1;
    } while (sVar1 != 0);
    if (rem != 0) {
      quot_1 = quot_1 | 0x20000000;
    }
    a_exp = a_exp + (0x7f - b_exp);
    uVar2 = pack_round_float(result_sign,a_exp,&quot,result);
    return uVar2;
  }
  if (action == 1) {
    *result = 0;
    *result = result_sign;
    return uVar2;
  }
  if (action == 2) {
    *result = 0x7f800000;
    *result = result_sign | 0x7f800000;
    return uVar2;
  }
  if (action != 3) {
    return uVar2;
  }
  *result = 0x7f800001;
  return CONCAT22(extraout_var,1);
#undef b_exp
#undef a_exp
#undef quot
#undef quot_1
#undef rem
#undef result_sign
#undef action
#undef b_mant
#undef b_class
#undef b_sign
#undef a_class
#undef a_sign
}



