#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x10c74))
#undef g_debug_symbol_input
#define g_debug_symbol_input (*(FILE * *)(g_sd + 0xcf24))


// entry: 00401000
// name : load_debug_symbol_tables
// size : 1358
// sig  : void load_debug_symbol_tables(void)


int __cdecl load_debug_symbol_tables(void)

{
  unsigned char _frec_11c[284];
#define location_count (*(undefined2 *)(_frec_11c + 0))
#define rec_len (*(byte *)(_frec_11c + 4))
#define rec_body (*(char *)(_frec_11c + 5))
#define local_116 (*(undefined1 *)(_frec_11c + 6))
#define local_115 (*(uchar *)(_frec_11c + 7))
#define local_114 (*(uchar *)(_frec_11c + 8))
#define local_113 (*(undefined1 *)(_frec_11c + 9))
#define rec_rest (*(uchar (*)[250])(_frec_11c + 10))
#define ext_offset (*(short *)(_frec_11c + 260))
#define symbol_count (*(undefined2 *)(_frec_11c + 264))
#define dsym (*(debug_symbol * *)(_frec_11c + 268))
#define dloc (*(debug_location * *)(_frec_11c + 276))
  short saved_count;
  uint nread;
  symbol *func_sym;
  debug_type_ext *new_ext;
  short aux_idx;
  
  nread = read_file_bytes(g_debug_symbol_input,(char *)&rec_len,2);
  if (nread == 0xffffffff) {
    report_message_at_source_line(0,0,0xce6,(char *)0x0);
  }
  symbol_count = CONCAT11(rec_body,rec_len);
  while (symbol_count != 0) {
    symbol_count = symbol_count + -1;
    nread = read_file_bytes(g_debug_symbol_input,(char *)&rec_len,1);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_debug_symbol_input,&rec_body,(uint)rec_len);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    dsym = pool_alloc(0x20);
    dsym->kind = rec_body * '\x02' | 1;
    *(undefined1 *)&dsym->id = local_116;
    *(uchar *)((int)&dsym->id + 1) = local_115;
    dsym->loc_kind = local_114;
    if (dsym->loc_kind == '\x06') {
      *(undefined1 *)&dsym->loc = local_113;
      *(uchar *)((int)&dsym->loc + 1) = rec_rest[0];
      *(uchar *)((int)&dsym->loc + 2) = rec_rest[1];
      *(uchar *)((int)&dsym->loc + 3) = rec_rest[2];
      if (dsym->loc < 0) {
        dsym->loc = dsym->loc + 4;
        func_sym = find_symbol_by_id(g_debug_function_label);
        aux_idx = func_sym->aux_index;
        saved_count = count_saved_registers(aux_idx);
        dsym->loc = dsym->loc + saved_count * -4;
        if (((int)(short)g_aux_record_table[aux_idx].flags & 0x8000U) == 0) {
          dsym->loc = dsym->loc + -4;
        }
      }
      ext_offset = 3;
    }
    else {
      *(undefined1 *)&dsym->loc = local_113;
      ext_offset = 0;
    }
    if (((byte)((uint)(int)(char)dsym->kind >> 1) & 0x7f) == 0xe) {
      new_ext = pool_alloc(8);
      dsym->type_ext = new_ext;
      dsym->type_ext->byte0 = rec_rest[ext_offset];
      dsym->type_ext->flags = rec_rest[ext_offset + 1];
      if ((dsym->type_ext->flags & 0x80) != 0) {
        if ((dsym->type_ext->flags & 0x40) == 0) {
          *(uchar *)&dsym->type_ext->value = rec_rest[ext_offset + 2];
          *(uchar *)((int)&dsym->type_ext->value + 1) = rec_rest[ext_offset + 3];
          *(uchar *)((int)&dsym->type_ext->value + 2) = rec_rest[ext_offset + 4];
          *(uchar *)((int)&dsym->type_ext->value + 3) = rec_rest[ext_offset + 5];
        }
        else {
          *(uchar *)&dsym->type_ext->value = rec_rest[ext_offset + 2];
        }
      }
    }
    dsym->next = g_debug_symbol_hash[(int)dsym->id % 0x7f];
    g_debug_symbol_hash[(int)dsym->id % 0x7f] = dsym;
  }
  symbol_count = symbol_count + -1;
  nread = read_file_bytes(g_debug_symbol_input,(char *)&rec_len,2);
  if (nread == 0xffffffff) {
    report_message_at_source_line(0,0,0xce6,(char *)0x0);
  }
  location_count = CONCAT11(rec_body,rec_len);
  while (location_count != 0) {
    nread = read_file_bytes(g_debug_symbol_input,(char *)&rec_len,1);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_debug_symbol_input,&rec_body,(uint)rec_len);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    dloc = pool_alloc(0xc);
    *(char *)&dloc->id = rec_body;
    *(undefined1 *)((int)&dloc->id + 1) = local_116;
    dloc->kind = local_115;
    if (dloc->kind == '\x06') {
      *(uchar *)&dloc->value = local_114;
      *(undefined1 *)((int)&dloc->value + 1) = local_113;
      *(uchar *)((int)&dloc->value + 2) = rec_rest[0];
      *(uchar *)((int)&dloc->value + 3) = rec_rest[1];
      if (dloc->value < 0) {
        dloc->value = dloc->value + 4;
        func_sym = find_symbol_by_id(g_debug_function_label);
        aux_idx = func_sym->aux_index;
        saved_count = count_saved_registers(aux_idx);
        dloc->value = dloc->value + saved_count * -4;
        if (((int)(short)g_aux_record_table[aux_idx].flags & 0x8000U) == 0) {
          dloc->value = dloc->value + -4;
        }
      }
    }
    else {
      *(uchar *)&dloc->value = local_114;
    }
    dloc->next = g_debug_location_hash[(int)dloc->id % 0x7f];
    g_debug_location_hash[(int)dloc->id % 0x7f] = dloc;
    location_count = location_count + -1;
  }
  return;
#undef location_count
#undef rec_len
#undef rec_body
#undef local_116
#undef local_115
#undef local_114
#undef local_113
#undef rec_rest
#undef ext_offset
#undef symbol_count
#undef dsym
#undef dloc
}
