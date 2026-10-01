#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_asa_file
#define g_asa_file (*(FILE * *)(g_sd + 0x1f988))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00408180
// name : write_asa_global_symbol_record
// size : 1563
// sig  : void write_asa_global_symbol_record(short kind, short symx)


int __cdecl write_asa_global_symbol_record(short kind,short symx)

{
  unsigned char _frec_e[14];
#define ext_byte (*(byte *)(_frec_e + 0))
#define rec_kind (*(byte *)(_frec_e + 1))
#define n_ranges (*(char *)(_frec_e + 2))
#define out_byte (*(byte *)(_frec_e + 3))
#define zero_word (*(undefined2 *)(_frec_e + 4))
#define ext_value (*(int *)(_frec_e + 6))
#define zero_dword (*(undefined4 *)(_frec_e + 10))
  byte bVar1;
  sym_entry *sym;
  byte *buf;
  sym_extension **ext_slot;
  undefined4 *range;
  
  zero_word = 0;
  bVar1 = (byte)kind;
  zero_dword = 0;
  sym = g_symbol_table + symx;
  if ((((sym->sclass == '\x01') || (rec_kind = bVar1, sym->sclass == '\x02')) &&
      (rec_kind = bVar1 | 0x80, sym->sclass == '\x02')) && ((sym->flags & 8) == 0)) {
    rec_kind = bVar1 | 0xc0;
  }
  write_bytes_or_fail((char *)&rec_kind,1,g_asa_file);
  write_bytes_or_fail((char *)&symx,2,g_asa_file);
  if ((kind == 10) || (kind == 0xb)) {
    write_bytes_or_fail((char *)&zero_word,2,g_asa_file);
    write_bytes_or_fail((char *)&zero_dword,4,g_asa_file);
    write_asa_symbol_name(g_symbol_table[symx].name);
    goto LAB_004086d6;
  }
  write_bytes_or_fail((char *)(g_symbol_table[symx].func_index * 0x44 + g_aux_records),4,g_asa_file)
  ;
  write_bytes_or_fail((char *)(g_symbol_table[symx].func_index * 0x44 + g_aux_records + 0xc),4,
                      g_asa_file);
  write_bytes_or_fail((char *)(g_symbol_table[symx].func_index * 0x44 + g_aux_records + 0x24),4,
                      g_asa_file);
  write_bytes_or_fail((char *)(g_symbol_table[symx].func_index * 0x44 + g_aux_records + 6),2,
                      g_asa_file);
  write_bytes_or_fail((char *)(g_symbol_table[symx].func_index * 0x44 + g_aux_records + 4),2,
                      g_asa_file);
  write_bytes_or_fail((char *)(g_symbol_table[symx].func_index * 0x44 + g_aux_records + 0x17),1,
                      g_asa_file);
  write_bytes_or_fail((char *)(g_symbol_table[symx].func_index * 0x44 + g_aux_records + 8),1,
                      g_asa_file);
  n_ranges = *(char *)(g_aux_records + 0x14 + g_symbol_table[symx].func_index * 0x44);
  write_bytes_or_fail(&n_ranges,1,g_asa_file);
  range = *(undefined4 **)(g_aux_records + 0x18 + g_symbol_table[symx].func_index * 0x44);
  for (; n_ranges != '\0'; n_ranges = n_ranges + -1) {
    write_bytes_or_fail((char *)(range + 1),1,g_asa_file);
    write_bytes_or_fail((char *)((int)range + 5),1,g_asa_file);
    write_bytes_or_fail((char *)(range + 2),4,g_asa_file);
    write_bytes_or_fail((char *)(range + 3),4,g_asa_file);
    range = (undefined4 *)*range;
  }
  out_byte = 1 - ((*(ushort *)(g_aux_records + 10 + g_symbol_table[symx].func_index * 0x44) & 0x8000
                  ) == 0);
  write_bytes_or_fail((char *)&out_byte,1,g_asa_file);
  out_byte = (g_symbol_table[symx].sym_flags & 0x10) >> 4;
  write_bytes_or_fail((char *)&out_byte,1,g_asa_file);
  if (out_byte == 0) {
    out_byte = 0;
    write_bytes_or_fail((char *)&out_byte,1,g_asa_file);
    buf = &out_byte;
LAB_0040862b:
    write_bytes_or_fail((char *)buf,1,g_asa_file);
  }
  else {
    ext_slot = &g_symbol_table[symx].ext;
    bVar1 = (*ext_slot)->flags & 2;
    out_byte = bVar1 << 6;
    if (bVar1 != 0) {
      out_byte = out_byte | ((*ext_slot)->flags & 8) >> 2 | ((*ext_slot)->flags & 4) >> 2;
    }
    write_bytes_or_fail((char *)&out_byte,1,g_asa_file);
    if ((out_byte & 0x80) != 0) {
      if ((out_byte & 1) == 0) {
        ext_value = (g_symbol_table[symx].ext)->value;
      }
      else {
        ext_value = (int)(short)(g_symbol_table[symx].ext)->value;
      }
      write_bytes_or_fail((char *)&ext_value,4,g_asa_file);
    }
    out_byte = (g_symbol_table[symx].ext)->flags << 7;
    write_bytes_or_fail((char *)&out_byte,1,g_asa_file);
    if ((out_byte & 0x80) != 0) {
      ext_byte = (byte)(g_symbol_table[symx].ext)->value2;
      buf = &ext_byte;
      goto LAB_0040862b;
    }
  }
  write_asa_symbol_name(g_symbol_table[symx].name);
  write_bytes_or_fail((char *)(g_symbol_table[symx].func_index * 0x44 + g_aux_records + 0x20),4,
                      g_asa_file);
LAB_004086d6:
  write_asa_attribute_byte(g_symbol_table[symx].attr);
  if (kind != 0xc) {
    write_bytes_or_fail(&g_symbol_table[symx].reg,1,g_asa_file);
    return;
  }
  write_bytes_or_fail((char *)(g_symbol_table[symx].func_index * 0x44 + g_aux_records + 0x2c),0x17,
                      g_asa_file);
  write_bytes_or_fail((char *)(g_symbol_table[symx].func_index * 0x44 + g_aux_records + 0x28),1,
                      g_asa_file);
  return;
#undef ext_byte
#undef rec_kind
#undef n_ranges
#undef out_byte
#undef zero_word
#undef ext_value
#undef zero_dword
}



