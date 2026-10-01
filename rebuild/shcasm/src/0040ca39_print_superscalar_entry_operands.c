#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_register_names
#define g_register_names (*(unsigned char * *)(g_sd + 0x3cc8))
#undef g_superscalar_dump_file
#define g_superscalar_dump_file (*(FILE * *)(g_sd + 0x1298c))
#undef g_superscalar_dump_line
#define g_superscalar_dump_line (*(char *)(g_sd + 0x8fc8))


// entry: 0040ca39
// name : print_superscalar_entry_operands
// size : 1113
// sig  : void __cdecl print_superscalar_entry_operands(char index)


int __cdecl print_superscalar_entry_operands(char index)

{
  char pad;
  char dst_width;
  char src_width;
  reg opnd_reg;
  
  opnd_reg = g_superscalar_window[index].src_reg;
  switch(g_superscalar_window[index].src_kind) {
  case '\x01':
    _sprintf(&g_superscalar_dump_line,&s_pct_s_0043c700,(&g_register_names)[(char)opnd_reg]);
    break;
  case '\x02':
    _sprintf(&g_superscalar_dump_line,&s_at_pct_s_0043c704,(&g_register_names)[(char)opnd_reg]);
    break;
  case '\x03':
    _sprintf(&g_superscalar_dump_line,&s_at_minus_pct_s_0043c708,(&g_register_names)[(char)opnd_reg]
            );
    break;
  case '\x04':
    _sprintf(&g_superscalar_dump_line,&s_at_pct_s_plus_0043c710,(&g_register_names)[(char)opnd_reg])
    ;
    break;
  default:
    _sprintf(&g_superscalar_dump_line,&s_pct_s_0043c74c,(&g_register_names)[(char)opnd_reg]);
    break;
  case '\a':
    _sprintf(&g_superscalar_dump_line,&s_IMM_0043c748);
    break;
  case '\b':
    _sprintf(&g_superscalar_dump_line,s___disp__s__0043c718,(&g_register_names)[(char)opnd_reg]);
    break;
  case '\t':
    _sprintf(&g_superscalar_dump_line,s___R0__s__0043c724,(&g_register_names)[(char)opnd_reg]);
    break;
  case '\v':
    _sprintf(&g_superscalar_dump_line,s___disp_GBR__0043c730);
    break;
  case '\f':
    _sprintf(&g_superscalar_dump_line,s____s_GBR__0043c73c,(&g_register_names)[(char)opnd_reg]);
  }
  if (g_superscalar_dump_line != '\0') {
    _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
  }
  for (src_width = '\0'; (src_width < ' ' && ((&g_superscalar_dump_line)[src_width] != '\0'));
      src_width = src_width + '\x01') {
  }
  opnd_reg = g_superscalar_window[index].dst_reg;
  if (opnd_reg == REG_NON_FF) {
    dst_width = '\0';
  }
  else {
    switch(g_superscalar_window[index].dst_kind) {
    case '\x01':
      _sprintf(&g_superscalar_dump_line,&s_comma_pct_s_0043c750,(&g_register_names)[(char)opnd_reg])
      ;
      break;
    case '\x02':
      _sprintf(&g_superscalar_dump_line,&s_comma_at_pct_s_0043c754,
               (&g_register_names)[(char)opnd_reg]);
      break;
    case '\x03':
      _sprintf(&g_superscalar_dump_line,s_____s_0043c75c,(&g_register_names)[(char)opnd_reg]);
      break;
    case '\x04':
      _sprintf(&g_superscalar_dump_line,s____s__0043c764,(&g_register_names)[(char)opnd_reg]);
      break;
    default:
      _sprintf(&g_superscalar_dump_line,&s_comma_pct_s_0043c7a4,(&g_register_names)[(char)opnd_reg])
      ;
      break;
    case '\a':
      _sprintf(&g_superscalar_dump_line,&DAT_0043c7a0);
      break;
    case '\b':
      _sprintf(&g_superscalar_dump_line,s____disp__s__0043c76c,(&g_register_names)[(char)opnd_reg]);
      break;
    case '\t':
      _sprintf(&g_superscalar_dump_line,s____R0__s__0043c778,(&g_register_names)[(char)opnd_reg]);
      break;
    case '\v':
      _sprintf(&g_superscalar_dump_line,s____disp_GBR__0043c784);
      break;
    case '\f':
      _sprintf(&g_superscalar_dump_line,s_____s_GBR__0043c794,(&g_register_names)[(char)opnd_reg]);
    }
    if (g_superscalar_dump_line != '\0') {
      _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
    }
    for (dst_width = '\0'; (dst_width < ' ' && ((&g_superscalar_dump_line)[dst_width] != '\0'));
        dst_width = dst_width + '\x01') {
    }
  }
  for (pad = '\x12' - (dst_width + src_width); pad != '\0'; pad = pad + -1) {
    _sprintf(&g_superscalar_dump_line,&s_sp_0043c7a8);
    _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
  }
  return;
}
