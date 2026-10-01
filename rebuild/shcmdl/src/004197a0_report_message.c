#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))


// entry: 004197a0
// name : report_message
// size : 87
// sig  : void report_message(int errcode, il_node * node, char * text)


int __cdecl report_message(int errcode,il_node *node,char *text)

{
  int level;
  char *file_name;
  uint line;
  
  level = errcode / 1000 + 1;
  if (g_max_error_level < level) {
    g_max_error_level = level;
  }
  if (node == (il_node *)0x0) {
    line = 0;
    file_name = g_options->source_name;
  }
  else {
    file_name = source_file_name((int)node->filn);
    line = (uint)node->line;
  }
  write_error_record(file_name,line,errcode,text);
  return;
}



