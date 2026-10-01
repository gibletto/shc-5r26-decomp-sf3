#include "decls.h"
#include "imports.h"

#if SHC_REBUILD_UPDATED
#include <stdlib.h>
static int asm_specreg(void) {
    static int v = -1;
    if (v < 0) { char *p = getenv("ASM_SPECREG"); v = (p && *p) ? atoi(p) : 1; }   /* unset = the fix (1); 0 = Release 26 */
    return v;
}
static unsigned int specreg_index(unsigned int reg) {
    return (asm_specreg() && reg >= 0x61 && reg <= 0x7f) ? reg - 0x20 : reg;
}
#endif
/* the types Ghidra's decompiler used for these globals in this function */
#undef PTR_s__sta_sftrl12_0043ccfc
#define PTR_s__sta_sftrl12_0043ccfc (*(unsigned char * *)(g_sd + 0x1cfc))


// entry: 004156e9
// name : accumulate_operand_register_mask
// size : 206
// sig  : void __cdecl accumulate_operand_register_mask(uint *mask,ea *operand)


int __cdecl accumulate_operand_register_mask(uint *mask,ea *operand)

{
  if ((operand != (ea *)0x0) && ((operand->type & 0x1f) != 7)) {
    if (operand->base < REG_DR0) {
      *mask = *mask | g_register_bit_masks[operand->base];
    }
    else {
#if SHC_REBUILD_UPDATED
      mask[1] = mask[1] | (uint)(&PTR_s__sta_sftrl12_0043ccfc)[specreg_index(operand->base)];
#else
      mask[1] = mask[1] | (uint)(&PTR_s__sta_sftrl12_0043ccfc)[operand->base];
#endif
    }
    if (((operand->type & 0x1f) == 9) || ((operand->type & 0x1f) == 0xc)) {
      if ((char)operand->index < ' ') {
        *mask = *mask | g_register_bit_masks[(char)operand->index];
      }
      else {
        mask[1] = mask[1] | (uint)(&PTR_s__sta_sftrl12_0043ccfc)[(char)operand->index];
      }
    }
  }
  return;
}
