#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 004113d0
// name : select_cpu_variant
// size : 237
// sig  : int select_cpu_variant(char * variants, tmpl_select * * unary_out, tmpl_select * * binary_out)


int __cdecl select_cpu_variant(char *variants,tmpl_select **unary_out,tmpl_select **binary_out)

{
  byte bit;
  char matched;
  uint flag_bit;
  char bits_set;
  char variant_index;
  bool failed;
  char variant_flags;
  
  variant_flags = *variants;
  variant_index = '\0';
  while (variant_flags != '\0') {
    bit = 0;
    matched = '\0';
    failed = false;
    bits_set = '\0';
    do {
      flag_bit = 1 << (bit & 0x1f) & (int)variant_flags;
      if (flag_bit != 0) {
        bits_set = bits_set + '\x01';
        switch(flag_bit) {
        case 1:
          if (g_request->cpu == 0) break;
LAB_00411450:
          matched = matched + '\x01';
          goto LAB_00411456;
        case 2:
          if (g_request->switch_density_rule != 0) goto LAB_00411450;
          break;
        case 4:
          if (g_request->cpu == 0) goto LAB_00411450;
          break;
        case 8:
          if (1 < g_request->cpu) goto LAB_00411450;
        }
        failed = true;
LAB_00411456:
        if (failed) break;
      }
      bit = bit + 1;
    } while ((char)bit < '\b');
    if ((bit == 8) && (bits_set == matched)) break;
    variant_index = variant_index + '\x01';
    variant_flags = variants[variant_index * 8];
  }
  if (variants[variant_index * 8 + 1] != '\x01') {
    *binary_out = *(tmpl_select **)(variants + variant_index * 8 + 4);
    return (uint)binary_out & 0xffff0000;
  }
  *unary_out = *(tmpl_select **)(variants + variant_index * 8 + 4);
  return CONCAT22((short)((uint)unary_out >> 0x10),1);
}



