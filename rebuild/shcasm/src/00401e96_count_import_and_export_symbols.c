#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_symbol_base
#define g_symbol_base (*(symbol * *)(g_sd + 0x1314c))


// entry: 00401e96
// name : count_import_and_export_symbols
// size : 732
// sig  : void count_import_and_export_symbols(void)


int __cdecl count_import_and_export_symbols(void)

{
  unsigned char _frec_4c[76];
#define used_ptr (*(byte * *)(_frec_4c + 0))
#define bit (*(byte *)(_frec_4c + 8))
#define bit_no (*(short *)(_frec_4c + 12))
#define i (*(short *)(_frec_4c + 16))
#define routine_no (*(short *)(_frec_4c + 20))
#define imported_ptr (*(byte * *)(_frec_4c + 32))
#define imported_bits (*(byte (*)[32])(_frec_4c + 40))
  char *str;
  byte bVar1;
  short byte_no;
  uint routine_len;
  uint name_len;
  int cmp;
  uchar sym_kind;
  
  for (i = 0; i < 0x20; i = i + 1) {
    imported_bits[i] = 0;
  }
  i = 0;
  do {
    if (g_current_request->label_count <= (int)i) {
      used_ptr = &g_runtime_routines_used;
      imported_ptr = imported_bits;
      for (i = 0; i < 0x20; i = i + 1) {
        bit = 0x80;
        for (bit_no = 0; bit_no < 8; bit_no = bit_no + 1) {
          if (((*used_ptr & bit) != 0) && ((bit & *imported_ptr) == 0)) {
            g_import_symbol_count = g_import_symbol_count + 1;
          }
          bit = (byte)((uint)(int)(char)bit >> 1) & 0x7f;
        }
        used_ptr = used_ptr + 1;
        imported_ptr = imported_ptr + 1;
      }
      return;
    }
    sym_kind = g_symbol_base[i].kind;
    if (((((char)sym_kind < '\a') || ('\t' < (char)sym_kind)) ||
        ((g_symbol_base[i].flags & 0x80) == 0)) || (g_symbol_base[i].attr2 == 0xff)) {
      if ((((sym_kind != '\n') || (g_symbol_base[i].attr2 == 0xff)) &&
          ((sym_kind == '\n' || (sym_kind == '\v')))) && ((g_symbol_base[i].flags & 0x40) == 0)) {
        str = g_symbol_base[i].name;
        for (routine_no = 1; routine_no < 0xb7; routine_no = routine_no + 1) {
          if (*(int *)(&g_runtime_routine_names + routine_no * 4) != 0) {
            routine_len = stock_strlen(*(char **)(&g_runtime_routine_names + routine_no * 4));
            name_len = stock_strlen(str);
            if ((routine_len == name_len) &&
               (cmp = _strcmp(str,*(char **)(&g_runtime_routine_names + routine_no * 4)), cmp == 0))
            {
              byte_no = (short)((int)(routine_no + -1 + (routine_no + -1 >> 0x1f & 7U)) >> 3);
              bVar1 = (byte)(routine_no + -1 >> 0x1f);
              imported_bits[byte_no] =
                   imported_bits[byte_no] |
                   (byte)(1 << (7 - ((((byte)(routine_no + -1) ^ bVar1) - bVar1 & 7 ^ bVar1) - bVar1
                                    ) & 0x1f));
              break;
            }
          }
        }
        g_import_symbol_count = g_import_symbol_count + 1;
      }
    }
    else {
      g_export_symbol_count = g_export_symbol_count + -1;
    }
    i = i + 1;
  } while( true );
#undef used_ptr
#undef bit
#undef bit_no
#undef i
#undef routine_no
#undef imported_ptr
#undef imported_bits
}
