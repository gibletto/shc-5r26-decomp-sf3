#include "decls.h"
#include "imports.h"

// entry: 00405f44
// name : entries_access_disjoint_memory
// size : 1533
// sig  : int entries_access_disjoint_memory(char entry_a, char entry_b)


int __cdecl entries_access_disjoint_memory(char entry_a,char entry_b)

{
  unsigned char _frec_2034[8244];
#define term_pos (*(int *)(_frec_2034 + 0))
#define pos (*(int *)(_frec_2034 + 4))
#define j (*(char *)(_frec_2034 + 8200))
#define size_b (*(char *)(_frec_2034 + 8204))
#define i (*(char *)(_frec_2034 + 8208))
#define size_a (*(undefined4 *)(_frec_2034 + 8212))
  int iVar1;
  int iVar2;
  uchar terms_b [4096];
  uchar terms_a [4096];
  byte term_count_a;
  byte term_count_b;
  
  __chkstk();
  term_count_a = 0;
  term_count_b = 0;
  if ((g_superscalar_window[entry_a].expr_text[0] == '\0') ||
     (g_superscalar_window[entry_b].expr_text[0] == '\0')) {
    iVar1 = 0;
  }
  else {
    for (i = '\0'; i < '@'; i = i + '\x01') {
      for (j = '\0'; j < '@'; j = j + '\x01') {
        terms_a[i * 0x40 + (int)j] = '\0';
        terms_b[i * 0x40 + (int)j] = '\0';
      }
    }
    for (pos = 0; g_superscalar_window[entry_a].expr[pos] != '\0'; pos = pos + 1) {
      if (((g_superscalar_window[entry_a].expr[pos] == '+') ||
          (g_superscalar_window[entry_a].expr[pos] == '-')) ||
         (g_superscalar_window[entry_a].expr[pos] == '=')) {
        term_count_a = term_count_a + 1;
        if (term_count_a == 0x40) break;
        term_pos = 0;
      }
      else if (((g_superscalar_window[entry_a].expr[pos] == '@') ||
               (g_superscalar_window[entry_a].expr[pos] == '(')) ||
              (g_superscalar_window[entry_a].expr[pos] == ')')) {
        term_pos = 0;
      }
      else {
        terms_a[(uint)term_count_a * 0x40 + term_pos] = g_superscalar_window[entry_a].expr[pos];
        term_pos = term_pos + 1;
        terms_a[(uint)term_count_a * 0x40 + term_pos] = '\0';
      }
    }
    for (pos = 0; g_superscalar_window[entry_b].expr[pos] != '\0'; pos = pos + 1) {
      if (((g_superscalar_window[entry_b].expr[pos] == '+') ||
          (g_superscalar_window[entry_b].expr[pos] == '-')) ||
         (g_superscalar_window[entry_b].expr[pos] == '=')) {
        term_count_b = term_count_b + 1;
        if (term_count_b == 0x40) break;
        term_pos = 0;
      }
      else if (((g_superscalar_window[entry_b].expr[pos] == '@') ||
               (g_superscalar_window[entry_b].expr[pos] == '(')) ||
              (g_superscalar_window[entry_b].expr[pos] == ')')) {
        term_pos = 0;
      }
      else {
        terms_b[(uint)term_count_b * 0x40 + term_pos] = g_superscalar_window[entry_b].expr[pos];
        term_pos = term_pos + 1;
        terms_b[(uint)term_count_b * 0x40 + term_pos] = '\0';
      }
    }
    if (term_count_b == term_count_a) {
      iVar1 = (int)entry_a;
      iVar2 = (int)entry_b;
      if ((g_superscalar_window[iVar1].rec.flg & 3) == 2) {
        (*(unsigned char *)((char *)&size_a + 0)) = '\x04';
      }
      else if ((g_superscalar_window[iVar1].rec.flg & 3) == 1) {
        (*(unsigned char *)((char *)&size_a + 0)) = '\x02';
      }
      else {
        (*(unsigned char *)((char *)&size_a + 0)) = '\x01';
      }
      if ((g_superscalar_window[iVar2].rec.flg & 3) == 2) {
        size_b = '\x04';
      }
      else if ((g_superscalar_window[iVar2].rec.flg & 3) == 1) {
        size_b = '\x02';
      }
      else {
        size_b = '\x01';
      }
      if ((((char)(g_superscalar_window[iVar1].rec.ea1)->index < '\x01') ||
          ((char)(g_superscalar_window[iVar2].rec.ea1)->index < '\x01')) ||
         (((int)(char)(g_superscalar_window[iVar2].rec.ea1)->index <
           (int)(char)(g_superscalar_window[iVar1].rec.ea1)->index + (int)(char)size_a &&
          ((int)(char)(g_superscalar_window[iVar1].rec.ea1)->index <
           (int)(char)(g_superscalar_window[iVar2].rec.ea1)->index + (int)size_b)))) {
        for (i = '\0'; (int)i <= (int)(uint)term_count_a; i = i + '\x01') {
          size_a = 0x406520;
          iVar1 = stock_memcmp(terms_a + i * 0x40,terms_b + i * 0x40,0x40);
          if (iVar1 == 0) break;
        }
        iVar1 = 0;
      }
      else {
        iVar1 = 0xff;
      }
    }
    else {
      iVar1 = 0;
    }
  }
  return iVar1;
#undef term_pos
#undef pos
#undef j
#undef size_b
#undef i
#undef size_a
}



