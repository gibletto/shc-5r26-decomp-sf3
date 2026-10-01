#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x10c74))
#undef g_expno_register_variables
#define g_expno_register_variables (*(register_variable ** *)(g_sd + 0x13008))
#undef g_register_variable_input
#define g_register_variable_input (*(FILE * *)(g_sd + 0x128c0))


// entry: 0041eaa6
// name : load_function_register_variable_map
// size : 2028
// sig  : void load_function_register_variable_map(void)


int __cdecl load_function_register_variable_map(void)

{
  unsigned char _frec_40[64];
#define reg_list (*(void * *)(_frec_40 + 0))
#define reg_ix (*(short *)(_frec_40 + 4))
#define var_node (*(register_variable * *)(_frec_40 + 16))
#define expno_ix (*(int *)(_frec_40 + 20))
#define var_id (*(short (*)[2])(_frec_40 + 24))
#define n_ranges (*(short (*)[2])(_frec_40 + 28))
#define reg_count (*(short (*)[2])(_frec_40 + 32))
#define range_first (*(int *)(_frec_40 + 36))
#define skip_reg (*(char (*)[4])(_frec_40 + 40))
#define skip_word (*(char (*)[4])(_frec_40 + 44))
#define skip_byte (*(char (*)[4])(_frec_40 + 48))
#define range_last (*(int *)(_frec_40 + 52))
#define func_label (*(short (*)[2])(_frec_40 + 56))
  short sVar1;
  uint nread;
  symbol *func_sym;
  register_variable *new_var;
  bool bVar2;
  int expno_count;
  
  while( true ) {
    nread = read_file_bytes(g_register_variable_input,(char *)func_label,2);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_register_variable_input,skip_word,2);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    if (g_debug_function_label + -0xb6 == (int)func_label[0]) break;
    while( true ) {
      nread = read_file_bytes(g_register_variable_input,(char *)var_id,2);
      if (nread == 0xffffffff) {
        report_message_at_source_line(0,0,0xce6,(char *)0x0);
      }
      if (var_id[0] == 0) break;
      nread = read_file_bytes(g_register_variable_input,skip_word,2);
      if (nread == 0xffffffff) {
        report_message_at_source_line(0,0,0xce6,(char *)0x0);
      }
      nread = read_file_bytes(g_register_variable_input,skip_byte,1);
      if (nread == 0xffffffff) {
        report_message_at_source_line(0,0,0xce6,(char *)0x0);
      }
      nread = read_file_bytes(g_register_variable_input,(char *)reg_count,2);
      if (nread == 0xffffffff) {
        report_message_at_source_line(0,0,0xce6,(char *)0x0);
      }
      for (reg_ix = 0; reg_ix < reg_count[0]; reg_ix = reg_ix + 1) {
        nread = read_file_bytes(g_register_variable_input,skip_reg,2);
        if (nread == 0xffffffff) {
          report_message_at_source_line(0,0,0xce6,(char *)0x0);
        }
      }
      nread = read_file_bytes(g_register_variable_input,(char *)n_ranges,2);
      if (nread == 0xffffffff) {
        report_message_at_source_line(0,0,0xce6,(char *)0x0);
      }
      while (sVar1 = n_ranges[0] + -1, bVar2 = n_ranges[0] != 0, n_ranges[0] = sVar1, bVar2) {
        nread = read_file_bytes(g_register_variable_input,(char *)&range_first,4);
        if (nread == 0xffffffff) {
          report_message_at_source_line(0,0,0xce6,(char *)0x0);
        }
        nread = read_file_bytes(g_register_variable_input,(char *)&range_last,4);
        if (nread == 0xffffffff) {
          report_message_at_source_line(0,0,0xce6,(char *)0x0);
        }
      }
    }
    nread = read_file_bytes(g_register_variable_input,skip_word,2);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
  }
  while( true ) {
    nread = read_file_bytes(g_register_variable_input,(char *)var_id,2);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    if (var_id[0] == 0) break;
    nread = read_file_bytes(g_register_variable_input,skip_word,2);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_register_variable_input,skip_byte,1);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_register_variable_input,(char *)reg_count,2);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    if ((reg_count[0] != 0) &&
       (reg_list = stock_calloc(1,reg_count[0] * 2), reg_list == (void *)0x0)) {
      report_message_at_source_line(0,0,0xbcd,(char *)0x0);
    }
    for (reg_ix = 0; reg_ix < reg_count[0]; reg_ix = reg_ix + 1) {
      nread = read_file_bytes(g_register_variable_input,(char *)(reg_ix * 2 + (int)reg_list),2);
      if (nread == 0xffffffff) {
        report_message_at_source_line(0,0,0xce6,(char *)0x0);
      }
    }
    nread = read_file_bytes(g_register_variable_input,(char *)n_ranges,2);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    func_sym = find_symbol_by_id(g_debug_function_label);
    expno_count = g_aux_record_table[func_sym->aux_index].expno_count;
    if ((((g_expno_register_variables == (register_variable **)0x0) && (reg_count[0] != 0)) &&
        (expno_count != 0)) &&
       (g_expno_register_variables = stock_calloc(1,expno_count * 4 + 4),
       g_expno_register_variables == (register_variable **)0x0)) {
      report_message_at_source_line(0,0,0xbcd,(char *)0x0);
    }
    if (((n_ranges[0] == 0) && (reg_count[0] != 0)) && (expno_count != 0)) {
      for (expno_ix = 1; expno_ix <= expno_count; expno_ix = expno_ix + 1) {
        for (var_node = g_expno_register_variables[expno_ix];
            (var_node != (register_variable *)0x0 && (var_node->variable != var_id[0]));
            var_node = var_node->next) {
        }
        if (var_node == (register_variable *)0x0) {
          for (reg_ix = 0; reg_ix < reg_count[0]; reg_ix = reg_ix + 1) {
            new_var = pool_alloc(8);
            new_var->reg = *(short *)((int)reg_list + reg_ix * 2);
            new_var->variable = var_id[0];
            new_var->next = g_expno_register_variables[expno_ix];
            g_expno_register_variables[expno_ix] = new_var;
          }
        }
      }
    }
    else {
      while (sVar1 = n_ranges[0] + -1, bVar2 = n_ranges[0] != 0, n_ranges[0] = sVar1, bVar2) {
        nread = read_file_bytes(g_register_variable_input,(char *)&range_first,4);
        if (nread == 0xffffffff) {
          report_message_at_source_line(0,0,0xce6,(char *)0x0);
        }
        nread = read_file_bytes(g_register_variable_input,(char *)&range_last,4);
        if (nread == 0xffffffff) {
          report_message_at_source_line(0,0,0xce6,(char *)0x0);
        }
        if (reg_count[0] != 0) {
          for (expno_ix = range_first; expno_ix <= range_last; expno_ix = expno_ix + 1) {
            for (var_node = g_expno_register_variables[expno_ix];
                (var_node != (register_variable *)0x0 && (var_node->variable != var_id[0]));
                var_node = var_node->next) {
            }
            if (var_node == (register_variable *)0x0) {
              for (reg_ix = 0; reg_ix < reg_count[0]; reg_ix = reg_ix + 1) {
                new_var = pool_alloc(8);
                new_var->reg = *(short *)((int)reg_list + reg_ix * 2);
                new_var->variable = var_id[0];
                new_var->next = g_expno_register_variables[expno_ix];
                g_expno_register_variables[expno_ix] = new_var;
              }
            }
          }
        }
      }
    }
    if (reg_count[0] != 0) {
      stock_free(reg_list);
    }
  }
  nread = read_file_bytes(g_register_variable_input,skip_word,2);
  if (nread == 0xffffffff) {
    report_message_at_source_line(0,0,0xce6,(char *)0x0);
  }
  return;
#undef reg_list
#undef reg_ix
#undef var_node
#undef expno_ix
#undef var_id
#undef n_ranges
#undef reg_count
#undef range_first
#undef skip_reg
#undef skip_word
#undef skip_byte
#undef range_last
#undef func_label
}
