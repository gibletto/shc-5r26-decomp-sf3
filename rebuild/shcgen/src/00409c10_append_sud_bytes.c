#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sud_buffer_cursor
#define g_sud_buffer_cursor (*(char * *)(g_sd + 0x1f9f4))
#undef g_sud_buffer_start
#define g_sud_buffer_start (*(char * *)(g_sd + 0x1fe64))
#undef g_sud_const_dc_count_field
#define g_sud_const_dc_count_field (*(char * *)(g_sd + 0x1fe58))
#undef g_sud_data_dc_count_field
#define g_sud_data_dc_count_field (*(char * *)(g_sd + 0x1fa1c))
#undef g_sud_file
#define g_sud_file (*(FILE * *)(g_sd + 0x1f9f0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00409c10
// name : append_sud_bytes
// size : 1733
// sig  : void append_sud_bytes(char * bytes, int count, char mode)


int __cdecl append_sud_bytes(char *bytes,int count,char mode)

{
  short sVar1;
  uint uVar2;
  short i;
  int iVar3;
  int iVar4;
  char ch;
  char *old_count_field;
  
  uVar2 = (int)g_sud_symx >> 0x1f;
  if (((g_symbol_table[((int)g_sud_symx ^ uVar2) - uVar2].type & 1) == 0) ||
     ((g_symbol_table[((int)g_sud_symx ^ uVar2) - uVar2].type & 2) != 0)) {
    if (g_sud_buffer_holds_data == '\x01') {
      if ((int)(g_sud_buffer_start + 0xa8c) < (int)(g_sud_buffer_cursor + count)) {
        if (g_sud_hold_length != 0) {
          write_bytes_or_fail(&g_sud_hold_buffer,g_sud_hold_length,g_sud_file);
          g_sud_hold_length = 0;
        }
        if (g_sud_data_dc_count_field == (char *)0x0) {
          write_bytes_or_fail(g_sud_buffer_start,(int)g_sud_buffer_cursor - (int)g_sud_buffer_start,
                              g_sud_file);
          if (mode == '\0') {
            write_bytes_or_fail(bytes,count,g_sud_file);
          }
          else {
            i = 0;
            if (0 < count) {
              do {
                ch = *bytes;
                bytes = bytes + 1;
                iVar4 = (int)i;
                i = i + 1;
                (&g_sud_hold_buffer)[iVar4] = ch;
              } while (i < count);
            }
            g_sud_data_dc_count_field = &DAT_0045d81a;
            g_sud_hold_length = count;
          }
        }
        else {
          write_bytes_or_fail(g_sud_buffer_start,
                              (uint)(g_sud_data_dc_count_field + (-2 - (int)g_sud_buffer_start)),
                              g_sud_file);
          old_count_field = g_sud_data_dc_count_field;
          g_sud_data_dc_count_field = g_sud_data_dc_count_field + -2;
          g_sud_hold_length = (int)(g_sud_buffer_cursor + (2 - (int)old_count_field));
          i = 0;
          if (0 < g_sud_hold_length) {
            do {
              sVar1 = i + 1;
              (&g_sud_hold_buffer)[i] = g_sud_data_dc_count_field[i];
              i = sVar1;
            } while (sVar1 < g_sud_hold_length);
          }
          i = 0;
          if (0 < count) {
            do {
              ch = *bytes;
              iVar4 = (int)i;
              i = i + 1;
              bytes = bytes + 1;
              (&g_sud_hold_buffer)[g_sud_hold_length + iVar4] = ch;
            } while (i < count);
          }
          g_sud_data_dc_count_field = &DAT_0045d81a;
          g_sud_hold_length = g_sud_hold_length + count;
        }
        g_sud_buffer_cursor = g_sud_buffer_start;
        g_sud_const_section = 0;
        g_sud_buffer_holds_data = '\0';
        return;
      }
      if (mode == '\x02') {
        g_sud_data_dc_count_field = g_sud_buffer_cursor + 2;
      }
      i = 0;
      if (0 < count) {
        do {
          i = i + 1;
          ch = *bytes;
          bytes = bytes + 1;
          *g_sud_buffer_cursor = ch;
          g_sud_buffer_cursor = g_sud_buffer_cursor + 1;
        } while (i < count);
        return;
      }
    }
    else {
      iVar4 = g_sud_hold_length + count;
      if (iVar4 < 0xa8d) {
        if (mode == '\x02') {
          g_sud_data_dc_count_field = &DAT_0045d81a + g_sud_hold_length;
        }
        i = 0;
        if (0 < count) {
          do {
            ch = *bytes;
            iVar3 = (int)i;
            i = i + 1;
            bytes = bytes + 1;
            (&g_sud_hold_buffer)[g_sud_hold_length + iVar3] = ch;
          } while (i < count);
        }
        g_sud_hold_length = iVar4;
        return;
      }
      if (g_sud_data_dc_count_field != (char *)0x0) {
        write_bytes_or_fail(&g_sud_hold_buffer,(uint)(g_sud_data_dc_count_field + -SD(0x0045d81a)),
                            g_sud_file);
        old_count_field = g_sud_data_dc_count_field;
        g_sud_data_dc_count_field = g_sud_data_dc_count_field + -2;
        g_sud_hold_length = (int)&DAT_0045d81a + (g_sud_hold_length - (int)old_count_field);
        i = 0;
        if (0 < g_sud_hold_length) {
          do {
            sVar1 = i + 1;
            (&g_sud_hold_buffer)[i] = g_sud_data_dc_count_field[i];
            i = sVar1;
          } while (sVar1 < g_sud_hold_length);
        }
        i = 0;
        if (0 < count) {
          do {
            ch = *bytes;
            iVar4 = (int)i;
            i = i + 1;
            bytes = bytes + 1;
            (&g_sud_hold_buffer)[g_sud_hold_length + iVar4] = ch;
          } while (i < count);
        }
        g_sud_hold_length = g_sud_hold_length + count;
        g_sud_data_dc_count_field = &DAT_0045d81a;
        return;
      }
      write_bytes_or_fail(&g_sud_hold_buffer,g_sud_hold_length,g_sud_file);
      g_sud_hold_length = 0;
      if (mode == '\0') {
        write_bytes_or_fail(bytes,count,g_sud_file);
        return;
      }
      i = 0;
      if (0 < count) {
        do {
          ch = *bytes;
          bytes = bytes + 1;
          iVar4 = (int)i;
          i = i + 1;
          (&g_sud_hold_buffer)[iVar4] = ch;
        } while (i < count);
      }
      if (mode == '\x02') {
        g_sud_data_dc_count_field = &DAT_0045d81a;
      }
      g_sud_hold_length = count;
    }
  }
  else {
    if (g_sud_buffer_holds_data == '\x01') {
      iVar4 = g_sud_hold_length + count;
      if (iVar4 < 0xa8d) {
        if (mode == '\x02') {
          g_sud_const_dc_count_field = &DAT_0045d81a + g_sud_hold_length;
        }
        i = 0;
        if (0 < count) {
          do {
            ch = *bytes;
            iVar3 = (int)i;
            i = i + 1;
            bytes = bytes + 1;
            (&g_sud_hold_buffer)[g_sud_hold_length + iVar3] = ch;
          } while (i < count);
        }
        g_sud_hold_length = iVar4;
        return;
      }
      if (g_sud_const_dc_count_field == (char *)0x0) {
        write_bytes_or_fail(&g_sud_hold_buffer,g_sud_hold_length,g_sud_file);
        g_sud_hold_length = 0;
        if (mode != '\0') {
          i = 0;
          if (0 < count) {
            do {
              ch = *bytes;
              bytes = bytes + 1;
              iVar4 = (int)i;
              i = i + 1;
              (&g_sud_hold_buffer)[iVar4] = ch;
            } while (i < count);
          }
          if (mode == '\x02') {
            g_sud_const_dc_count_field = &DAT_0045d81a;
          }
          g_sud_hold_length = count;
          return;
        }
        write_bytes_or_fail(bytes,count,g_sud_file);
        return;
      }
      write_bytes_or_fail(&g_sud_hold_buffer,(uint)(g_sud_const_dc_count_field + -SD(0x0045d81a)),
                          g_sud_file);
      old_count_field = g_sud_const_dc_count_field;
      g_sud_const_dc_count_field = g_sud_const_dc_count_field + -2;
      g_sud_hold_length = (int)&DAT_0045d81a + (g_sud_hold_length - (int)old_count_field);
      i = 0;
      if (0 < g_sud_hold_length) {
        do {
          sVar1 = i + 1;
          (&g_sud_hold_buffer)[i] = g_sud_const_dc_count_field[i];
          i = sVar1;
        } while (sVar1 < g_sud_hold_length);
      }
      i = 0;
      if (0 < count) {
        do {
          ch = *bytes;
          iVar4 = (int)i;
          i = i + 1;
          bytes = bytes + 1;
          (&g_sud_hold_buffer)[g_sud_hold_length + iVar4] = ch;
        } while (i < count);
      }
      g_sud_hold_length = g_sud_hold_length + count;
      g_sud_const_dc_count_field = &DAT_0045d81a;
      return;
    }
    if ((int)(g_sud_buffer_start + 0xa8c) < (int)(g_sud_buffer_cursor + count)) {
      if (g_sud_hold_length != 0) {
        write_bytes_or_fail(&g_sud_hold_buffer,g_sud_hold_length,g_sud_file);
        g_sud_hold_length = 0;
      }
      if (g_sud_const_dc_count_field == (char *)0x0) {
        write_bytes_or_fail(g_sud_buffer_start,(int)g_sud_buffer_cursor - (int)g_sud_buffer_start,
                            g_sud_file);
        if (mode == '\0') {
          write_bytes_or_fail(bytes,count,g_sud_file);
        }
        else {
          i = 0;
          if (0 < count) {
            do {
              ch = *bytes;
              bytes = bytes + 1;
              iVar4 = (int)i;
              i = i + 1;
              (&g_sud_hold_buffer)[iVar4] = ch;
            } while (i < count);
          }
          g_sud_const_dc_count_field = &DAT_0045d81a;
          g_sud_hold_length = count;
        }
      }
      else {
        write_bytes_or_fail(g_sud_buffer_start,
                            (uint)(g_sud_const_dc_count_field + (-2 - (int)g_sud_buffer_start)),
                            g_sud_file);
        old_count_field = g_sud_const_dc_count_field;
        g_sud_const_dc_count_field = g_sud_const_dc_count_field + -2;
        g_sud_hold_length = (int)(g_sud_buffer_cursor + (2 - (int)old_count_field));
        i = 0;
        if (0 < g_sud_hold_length) {
          do {
            sVar1 = i + 1;
            (&g_sud_hold_buffer)[i] = g_sud_const_dc_count_field[i];
            i = sVar1;
          } while (sVar1 < g_sud_hold_length);
        }
        i = 0;
        if (0 < count) {
          do {
            ch = *bytes;
            iVar4 = (int)i;
            i = i + 1;
            bytes = bytes + 1;
            (&g_sud_hold_buffer)[g_sud_hold_length + iVar4] = ch;
          } while (i < count);
        }
        g_sud_const_dc_count_field = &DAT_0045d81a;
        g_sud_hold_length = g_sud_hold_length + count;
      }
      g_sud_buffer_cursor = g_sud_buffer_start;
      g_sud_buffer_holds_data = '\x01';
      g_sud_data_section = 0;
      return;
    }
    if (mode == '\x02') {
      g_sud_const_dc_count_field = g_sud_buffer_cursor + 2;
    }
    i = 0;
    if (0 < count) {
      do {
        i = i + 1;
        ch = *bytes;
        bytes = bytes + 1;
        *g_sud_buffer_cursor = ch;
        g_sud_buffer_cursor = g_sud_buffer_cursor + 1;
      } while (i < count);
      return;
    }
  }
  return;
}



