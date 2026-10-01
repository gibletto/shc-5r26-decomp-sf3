#include "decls.h"
#include "imports.h"

// entry: 00411d00
// name : expand_multiply_by_constant
// size : 732
// sig  : int expand_multiply_by_constant(uint multiplier, ea * dest, ea * * source, short emit)


int __cdecl expand_multiply_by_constant(uint multiplier,ea *dest,ea **source,short emit)

{
  short shift_steps;
  ea *dst_copy;
  ea *src_copy;
  int run_length;
  int count;
  undefined2 uVar1;
  undefined2 extraout_var = 0;
  int max_bits;
  int cost;
  bool wide;
  bool negative;
  gen_node *pgVar2;
  int bits;
  bool negate;
  
  wide = 0xffff < multiplier;
  negate = false;
  negative = (int)multiplier < 0;
  if (multiplier == 0) {
    if (emit != 0) {
      pgVar2 = (gen_node *)0x0;
      dst_copy = copy_ea(dest);
      src_copy = new_ea_operand_with_flags('\a',-1,-1,0,'\0',(label_ref *)0x0);
      emit_psd_for_node(0x2a,-1,'\0','\x02',src_copy,dst_copy,pgVar2);
    }
  }
  else {
    if (negative) {
      multiplier = -multiplier;
    }
    negate = negative;
    if (emit != 0) {
      pgVar2 = (gen_node *)0x0;
      dst_copy = copy_ea(*source);
      src_copy = copy_ea(dest);
      emit_psd_for_node(0x40,-1,'\0','\x02',src_copy,dst_copy,pgVar2);
    }
  }
  cost = 1;
  run_length = count_leading_bits_equal(multiplier,0x20,0);
  bits = multiplier << ((byte)run_length & 0x1f);
  max_bits = 0x20 - run_length;
  do {
    if (max_bits == 0) {
      uVar1 = (undefined2)((uint)run_length >> 0x10);
      if (negate) {
        if (emit != 0) {
          pgVar2 = (gen_node *)0x0;
          dst_copy = copy_ea(dest);
          src_copy = copy_ea(dest);
          emit_psd_for_node(0x78,-1,'\0','\x02',src_copy,dst_copy,pgVar2);
          uVar1 = extraout_var;
        }
        cost = cost + 1;
      }
      return CONCAT22(uVar1,(ushort)(cost <= (int)((-(uint)wide & 0x14) + 0x19)));
    }
    run_length = count_leading_bits_equal(bits,max_bits,1);
    bits = bits << ((byte)run_length & 0x1f);
    if (run_length < 3) {
      if (run_length == 2) {
        if (emit != 0) {
          emit_shift_by_constant(dest,'\x02',1);
          pgVar2 = (gen_node *)0x0;
          dst_copy = copy_ea(dest);
          src_copy = copy_ea(*source);
          emit_psd_for_node(0x60,-1,'\0','\x02',src_copy,dst_copy,pgVar2);
        }
        cost = cost + 1;
        goto LAB_00411e9b;
      }
    }
    else {
      if (emit != 0) {
        emit_shift_by_constant(dest,'\x02',run_length);
        pgVar2 = (gen_node *)0x0;
        dst_copy = copy_ea(dest);
        src_copy = copy_ea(*source);
        emit_psd_for_node(99,-1,'\0','\x02',src_copy,dst_copy,pgVar2);
      }
      shift_steps = count_constant_shift_steps(run_length);
      cost = cost + shift_steps;
LAB_00411e9b:
      cost = cost + 1;
    }
    count = count_leading_bits_equal(bits,max_bits - run_length,0);
    bits = bits << ((byte)count & 0x1f);
    max_bits = (max_bits - run_length) - count;
    if (max_bits == 0) {
      if (emit != 0) {
        emit_shift_by_constant(dest,'\x02',count);
      }
      shift_steps = count_constant_shift_steps(count);
      run_length = (int)shift_steps;
      cost = cost + run_length;
    }
    else {
      run_length = count_leading_bits_equal(bits,max_bits,1);
      if (run_length < 3) {
        if (emit != 0) {
          emit_shift_by_constant(dest,'\x02',count + 1);
          pgVar2 = (gen_node *)0x0;
          dst_copy = copy_ea(dest);
          src_copy = copy_ea(*source);
          emit_psd_for_node(0x60,-1,'\0','\x02',src_copy,dst_copy,pgVar2);
        }
        count = count + 1;
      }
      else if (emit != 0) {
        emit_shift_by_constant(dest,'\x02',count);
        pgVar2 = (gen_node *)0x0;
        dst_copy = copy_ea(dest);
        src_copy = copy_ea(*source);
        emit_psd_for_node(0x60,-1,'\0','\x02',src_copy,dst_copy,pgVar2);
      }
      shift_steps = count_constant_shift_steps(count);
      run_length = (int)shift_steps;
      cost = cost + run_length + 1;
    }
  } while( true );
}



