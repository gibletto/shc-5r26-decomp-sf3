#include "decls.h"
#include "imports.h"
#include "argconst.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))


// entry: 00417fb0
// name : strength_reduce_induction_vars
// size : 70
// sig  : void strength_reduce_induction_vars(void)


int __cdecl strength_reduce_induction_vars(void)

{
  int ok;
  iv_entry *entry;
  
  entry = g_iv_table + 1;
  do {
    if ((g_options->option_bits & 1) != 0 || IV_TEST_REPLACE()) {
      g_test_replace_ok = 1;
    }
    ok = check_induction_entry(entry);
    if (ok != 0) {
      reduce_induction_variable(entry);
      g_tree_changed = 1;
    }
    entry = entry + 1;
  } while (entry < (iv_entry *)&g_iv_negated_count);
  return;
}



