#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00403200
// name : fuse_and_imm_with_zero_test
// size : 243
// sig  : void fuse_and_imm_with_zero_test(psd * test, psd * prev)


int __cdecl fuse_and_imm_with_zero_test(psd *test,psd *prev)

{
  if ((((prev->ea1->type & 0x1f) == 7) && ((prev->ea2->type & 0x1f) == 1)) &&
     (prev->ea2->base == '\0')) {
    if (((test->op == OP_TST) && ((test->ea1->type & 0x1f) == 1)) &&
       ((test->ea1->base == '\0' && (((test->ea2->type & 0x1f) == 1 && (test->ea2->base == '\0')))))
       ) {
      delete_psd_record(test);
      prev->op = OP_TST;
      if (((byte)g_stage_flags & 2) != 0) {
        dump_memory_hex(&prev->op,s_TST_code_0042508c,0x18);
        return;
      }
    }
    else if ((test->op == OP_CMP_EQ) &&
            (((((test->ea1->type & 0x1f) == 7 && (test->ea1->disp == 0)) &&
              ((test->ea2->type & 0x1f) == 1)) && (test->ea2->base == '\0')))) {
      delete_psd_record(test);
      prev->op = OP_TST;
      if (((byte)g_stage_flags & 2) != 0) {
        dump_memory_hex(&prev->op,s_TST_code_0042508c,0x18);
      }
    }
  }
  return;
}



