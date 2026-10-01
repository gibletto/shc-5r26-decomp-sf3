#include "decls.h"
#include "imports.h"

// entry: 00405bbb
// name : rewrite_entry_expression_with_earlier_definitions
// size : 905
// sig  : void __cdecl rewrite_entry_expression_with_earlier_definitions(char entry)


int __cdecl rewrite_entry_expression_with_earlier_definitions(char entry)

{
  unsigned char _frec_94[148];
#define char_pos (*(char *)(_frec_94 + 0))
#define def_list (*(char (*)[32])(_frec_94 + 4))
#define auStack_70 (*(undefined1 (*)[32])(_frec_94 + 36))
#define def_count (*(char *)(_frec_94 + 68))
#define rewritten (*(char * *)(_frec_94 + 72))
#define pos (*(char *)(_frec_94 + 76))
#define def_no (*(char *)(_frec_94 + 80))
#define earlier (*(char *)(_frec_94 + 84))
#define lhs (*(char (*)[24])(_frec_94 + 88))
#define after_eq (*(char *)(_frec_94 + 112))
#define i (*(char *)(_frec_94 + 116))
#define rhs (*(char (*)[24])(_frec_94 + 120))
  char acStackY_1110 [4180];
  char acStackY_bc [16];
  
  g_superscalar_window[entry].expr_rewritten = '\x01';
  for (i = '\0'; i < '\x18'; i = i + '\x01') {
    lhs[i] = '\0';
    rhs[i] = '\0';
  }
  if (g_superscalar_window[entry].expr_text[0] != '\0') {
    g_superscalar_window[entry].expr = (char *)(entry * 0xe0 + SD(0x0044bd48));
    for (earlier = entry + -1; -1 < earlier; earlier = earlier + -1) {
      for (i = '\0'; i < ' '; i = i + '\x01') {
        def_list[i] = '\0';
        auStack_70[i] = 0;
      }
      if (g_superscalar_window[earlier].defs_text[0] == '\0') {
        if (g_superscalar_window[earlier].expr_text[0] == '\0') {
          return;
        }
        stock_memcpy(def_list,g_superscalar_window[earlier].expr_text,0x20);
      }
      else {
        def_count = '\0';
        char_pos = '\0';
        for (def_no = '\0';
            (def_no < '@' && (*(char *)(earlier * 0xe0 + SD(0x0044bd08) + (int)def_no) != '\0'));
            def_no = def_no + '\x01') {
          if (*(char *)(earlier * 0xe0 + SD(0x0044bd08) + (int)def_no) == ':') {
            char_pos = '\0';
            def_count = def_count + '\x01';
          }
          else {
            def_list[(int)char_pos + def_count * 0x20] =
                 *(char *)(earlier * 0xe0 + SD(0x0044bd08) + (int)def_no);
            char_pos = char_pos + '\x01';
          }
        }
      }
      def_no = '\0';
      while (def_list[def_no * 0x20] != '\0') {
        pos = '\0';
        char_pos = '\0';
        after_eq = '\0';
        for (i = '\0'; i < '\x18'; i = i + '\x01') {
          lhs[i] = '\0';
          rhs[i] = '\0';
        }
        while (def_list[def_no * 0x20 + (int)pos] != '\0') {
          if (def_list[def_no * 0x20 + (int)pos] == '=') {
            after_eq = '\x01';
            char_pos = '\0';
          }
          else {
            if (after_eq == '\0') {
              lhs[char_pos] = def_list[def_no * 0x20 + (int)pos];
            }
            else {
              rhs[char_pos] = def_list[def_no * 0x20 + (int)pos];
            }
            char_pos = char_pos + '\x01';
          }
          pos = pos + '\x01';
        }
        def_no = def_no + '\x01';
        if ((lhs[0] != '\0') && (rhs[0] != '\0')) {
          rewritten = replace_first_substring(g_superscalar_window[entry].expr,lhs,rhs);
          if (rewritten != (char *)0x0) {
            g_superscalar_window[entry].expr = rewritten;
          }
        }
      }
    }
  }
  return;
#undef char_pos
#undef def_list
#undef auStack_70
#undef def_count
#undef rewritten
#undef pos
#undef def_no
#undef earlier
#undef lhs
#undef after_eq
#undef i
#undef rhs
}
