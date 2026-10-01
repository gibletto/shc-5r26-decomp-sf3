#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_aux_index
#define g_current_aux_index (*(int *)(g_sd + 0xf8ec))
#undef g_ofb_input
#define g_ofb_input (*(FILE * *)(g_sd + 0xd12c))


// entry: 004298b6
// name : layout_next_ofb_record
// size : 630
// sig  : char layout_next_ofb_record(void)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

char __cdecl layout_next_ofb_record(void)

{
  unsigned char _frec_8[8];
#define tag_byte (*(char (*)[4])(_frec_8 + 0))
  uint nread;
  symbol *func_sym;
  layout_record *item;
  
  nread = read_file_bytes(g_ofb_input,tag_byte,1);
  if (nread == 0xffffffff) {
    report_message_at_source_line(0,0,0xce6,(char *)0x0);
  }
  else if (nread == 0) {
    g_ofb_at_end = 1;
    return '\0';
  }
  if ((((tag_byte[0] == '\x18') || (tag_byte[0] == '\x19')) || (tag_byte[0] == '\x1a')) ||
     (tag_byte[0] == '\x1b')) {
    nread = read_file_bytes(g_ofb_input,(char *)&g_ofb_current_label,2);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    if (tag_byte[0] == '\x1b') {
      g_function_label_pass0 = g_ofb_current_label;
      func_sym = find_symbol_by_id(g_ofb_current_label);
      _g_current_aux_index = (int)func_sym->aux_index;
    }
  }
  else {
    item = read_ofb_layout_record(tag_byte[0]);
    switch(tag_byte[0]) {
    case '\x10':
      relax_inline_asm_record(item,0);
      break;
    case '\x11':
      relax_switch_jump_record(item,0);
      break;
    case '\x12':
    case '\x13':
    case '\x14':
    case '\x15':
    case '\x16':
    case '\x17':
    case '\x18':
    case '\x19':
    case '\x1a':
    case '\x1b':
    case '\x1c':
    case '\x1d':
    case '\x1e':
    case '\x1f':
    case '-':
    case '/':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case ':':
    case ';':
    case '<':
    case '=':
    case '>':
    case '?':
    case '@':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
    case '[':
    case '\\':
    case ']':
    case '^':
    case '_':
    case '`':
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 'r':
    case 's':
    case 't':
    case 'u':
    case 'v':
    case 'w':
    case 'x':
    case 'y':
    case 'z':
    case '{':
    case '|':
    case '}':
    case '~':
    case '\x7f':
    case -0x80:
    case -0x7f:
    case -0x7e:
    case -0x7d:
    case -0x7c:
    case -0x7b:
    case -0x7a:
    case -0x79:
    case -0x78:
    case -0x77:
    case -0x76:
    case -0x75:
    case -0x74:
    case -0x73:
    case -0x71:
    case -0x70:
    case -0x6f:
    case -0x6d:
    case -0x6b:
      break;
    case ' ':
      compute_enter_expansion_size(item,0);
      break;
    case '!':
      relax_exit_record(item,0);
      break;
    case '\"':
      relax_return_record(item,0);
      break;
    case '#':
      relax_call_record(item,0);
      break;
    case '$':
      relax_jump_record(item,0);
      break;
    case '%':
    case '&':
      relax_conditional_jump_record(item,0);
      break;
    case '\'':
      relax_mv_loc_record(item,0);
      break;
    case '(':
      relax_mva_lc_record(item,0);
      break;
    case ')':
      relax_mva_pc_record(item,0);
      break;
    case '*':
      relax_movi_record(item,0);
      break;
    case '+':
      relax_mva_fc_record(item,0);
      break;
    case ',':
      relax_movif_record(item,0);
      break;
    case '.':
      relax_fprset_record(item,0);
      break;
    case -0x72:
    case -0x6e:
    case -0x6c:
    case -0x6a:
      relax_unconditional_branch_record(item,0);
    }
  }
  return tag_byte[0];
#undef tag_byte
}



