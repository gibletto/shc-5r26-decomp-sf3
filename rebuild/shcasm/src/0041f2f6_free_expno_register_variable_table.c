#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x10c74))
#undef g_expno_register_variables
#define g_expno_register_variables (*(register_variable ** *)(g_sd + 0x13008))


// entry: 0041f2f6
// name : free_expno_register_variable_table
// size : 180
// sig  : void free_expno_register_variable_table(void)


int __cdecl free_expno_register_variable_table(void)

{
  symbol *func_sym;
  uint expno_ix;
  register_variable *var_node;
  register_variable *next_var;
  
  if (g_expno_register_variables != (register_variable **)0x0) {
    expno_ix = 1;
    while( true ) {
      func_sym = find_symbol_by_id(g_debug_function_label);
      if ((uint)g_aux_record_table[func_sym->aux_index].expno_count < expno_ix) break;
      var_node = g_expno_register_variables[expno_ix];
      while (var_node != (register_variable *)0x0) {
        next_var = var_node->next;
        pool_free(var_node,8);
        var_node = next_var;
      }
      expno_ix = expno_ix + 1;
    }
    stock_free(g_expno_register_variables);
    g_expno_register_variables = (register_variable **)0x0;
  }
  return;
}
