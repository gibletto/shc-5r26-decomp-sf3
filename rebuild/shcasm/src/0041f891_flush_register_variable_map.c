#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_register_map_temp
#define g_register_map_temp (*(FILE * *)(g_sd + 0x13020))
#undef g_register_variable_map
#define g_register_variable_map (*(register_variable * *)(g_sd + 0x931c))


// entry: 0041f891
// name : flush_register_variable_map
// size : 297
// sig  : void flush_register_variable_map(void)


int __cdecl flush_register_variable_map(void)

{
  unsigned char _frec_14[20];
#define out_buf (*(char *)(_frec_14 + 0))
#define local_13 (*(undefined1 *)(_frec_14 + 1))
#define local_12 (*(undefined1 *)(_frec_14 + 2))
#define local_11 (*(undefined1 *)(_frec_14 + 3))
#define next_var (*(register_variable * *)(_frec_14 + 4))
#define local_c (*(undefined2 *)(_frec_14 + 8))
#define var_node (*(register_variable * *)(_frec_14 + 12))
  uint nwritten;
  
  if (g_register_variable_map == (register_variable *)0x0) {
    pool_free(g_scope_stack[g_scope_top]->child,0x10);
    g_scope_stack[g_scope_top]->child = (debug_scope *)0x0;
  }
  else {
    var_node = g_register_variable_map;
    while (var_node != (register_variable *)0x0) {
      next_var = var_node->next;
      out_buf = (char)var_node->reg;
      local_13 = *(undefined1 *)((int)&var_node->reg + 1);
      local_12 = (undefined1)var_node->variable;
      local_11 = *(undefined1 *)((int)&var_node->variable + 1);
      nwritten = write_file_bytes(g_register_map_temp,&out_buf,4);
      if (nwritten == 0xffffffff) {
        report_message_at_source_line(0,0,0xce7,(char *)0x0);
      }
      pool_free(var_node,8);
      var_node = next_var;
    }
    local_c = 0xffff;
    out_buf = -1;
    local_13 = 0xff;
    nwritten = write_file_bytes(g_register_map_temp,&out_buf,2);
    if (nwritten == 0xffffffff) {
      report_message_at_source_line(0,0,0xce7,(char *)0x0);
    }
    g_register_variable_map = (register_variable *)0x0;
  }
  return;
#undef out_buf
#undef local_13
#undef local_12
#undef local_11
#undef next_var
#undef local_c
#undef var_node
}
