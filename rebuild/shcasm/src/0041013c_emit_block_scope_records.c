#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_current_section
#define g_current_section (*(request_section * *)(g_sd + 0x10b2c))
#undef g_register_map_temp
#define g_register_map_temp (*(FILE * *)(g_sd + 0x13020))


// entry: 0041013c
// name : emit_block_scope_records
// size : 1451
// sig  : void emit_block_scope_records(void)


int __cdecl emit_block_scope_records(void)

{
  unsigned char _frec_24[36];
#define scope_length (*(uint *)(_frec_24 + 0))
#define dbg_loc (*(debug_location * *)(_frec_24 + 4))
#define rec_len (*(int *)(_frec_24 + 8))
#define name_pos (*(byte *)(_frec_24 + 12))
#define sym_id (*(short (*)[2])(_frec_24 + 16))
#define loc_id (*(short (*)[2])(_frec_24 + 20))
#define dbg_sym (*(debug_symbol * *)(_frec_24 + 24))
#define name_length (*(byte *)(_frec_24 + 28))
  int iVar1;
  int iVar2;
  symbol *func_sym;
  uint uVar3;
  uint uVar4;
  ushort *out;
  
  while (g_scope_stack[g_scope_top]->child != (debug_scope *)0x0) {
    g_object_record_buffer[0] = '\t';
    g_object_record_buffer[1] = (uchar)g_current_request->optimize;
    out = (ushort *)(g_object_record_buffer + 2);
    func_sym = find_symbol_by_id(g_debug_function_label);
    store_u16_big_endian((ushort *)&func_sym->section_number,out);
    g_scope_stack[g_scope_top + 1] = g_scope_stack[g_scope_top]->child;
    g_scope_top = g_scope_top + 1;
    store_u32_big_endian((uint *)g_scope_stack[g_scope_top],(uint *)(g_object_record_buffer + 4));
    scope_length = g_scope_stack[g_scope_top]->end - g_scope_stack[g_scope_top]->start;
    store_u32_big_endian(&scope_length,(uint *)(g_object_record_buffer + 8));
    g_object_record_buffer[0xc] = '\x01';
    store_u16_big_endian((ushort *)&g_debug_word_1001,(ushort *)(g_object_record_buffer + 0xd));
    append_object_record_bytes(g_object_record_buffer,0xf,0x32);
    append_object_record_bytes((uchar *)0x0,0,0xff);
    while( true ) {
      uVar3 = read_file_bytes(g_register_map_temp,(char *)sym_id,2);
      if (uVar3 == 0xffffffff) {
        report_message_at_source_line(0,0,0xce6,(char *)0x0);
      }
      if (sym_id[0] == -1) break;
      uVar3 = read_file_bytes(g_register_map_temp,(char *)loc_id,2);
      if (uVar3 == 0xffffffff) {
        report_message_at_source_line(0,0,0xce6,(char *)0x0);
      }
      if (((int)sym_id[0] <= g_current_request->int_0b4) ||
         (g_current_request->int_0b0 < (int)sym_id[0])) {
        for (dbg_sym = g_debug_symbol_hash[(int)sym_id[0] % 0x7f]; dbg_sym->id != sym_id[0];
            dbg_sym = dbg_sym->next) {
        }
        for (dbg_loc = g_debug_location_hash[(int)loc_id[0] % 0x7f]; dbg_loc->id != loc_id[0];
            dbg_loc = dbg_loc->next) {
        }
        g_object_record_buffer[0] = dbg_sym->kind;
        rec_len = 1;
        store_u16_big_endian((ushort *)&dbg_sym->id,(ushort *)(g_object_record_buffer + 1));
        rec_len = rec_len + 2;
        append_object_record_bytes(g_object_record_buffer,rec_len,0x34);
        for (name_length = 0; dbg_sym->name[name_length] != '\0'; name_length = name_length + 1) {
        }
        g_object_record_buffer[0] = name_length;
        rec_len = 1;
        name_pos = 0;
        while (name_length != 0) {
          g_object_record_buffer[rec_len] = dbg_sym->name[name_pos];
          name_pos = name_pos + 1;
          rec_len = rec_len + 1;
          name_length = name_length - 1;
        }
        name_length = name_length - 1;
        append_object_record_bytes(g_object_record_buffer,rec_len,0x34);
        rec_len = 0;
        store_u16_big_endian((ushort *)&dbg_sym->scope_depth,(ushort *)g_object_record_buffer);
        iVar1 = rec_len + 2;
        if ((dbg_sym->kind & 1) != 0) {
          g_object_record_buffer[rec_len + 2] = dbg_loc->kind;
          iVar1 = rec_len + 3;
          rec_len = rec_len + 3;
          store_u32_big_endian((uint *)&dbg_sym->word_10,(uint *)(g_object_record_buffer + iVar1));
          iVar1 = rec_len + 4;
          if (dbg_loc->kind == '\x06') {
            iVar2 = rec_len + 4;
            rec_len = iVar1;
            store_u32_big_endian((uint *)&dbg_loc->value,(uint *)(g_object_record_buffer + iVar2));
            iVar1 = rec_len + 4;
          }
          else if ((char)dbg_loc->value < '\x10') {
            g_object_record_buffer[rec_len + 5] = 'R';
            iVar2 = rec_len + 6;
            rec_len = iVar1;
            _sprintf((char *)(g_object_record_buffer + iVar2),&s_pct_d_00440ce0,
                     (int)(char)dbg_loc->value);
            g_object_record_buffer[rec_len] = ('\t' < (char)dbg_loc->value) + '\x02';
            iVar1 = rec_len + ('\t' < (char)dbg_loc->value) + 3;
          }
          else {
            g_object_record_buffer[rec_len + 5] = 'F';
            g_object_record_buffer[rec_len + 6] = 'R';
            uVar3 = (uint)(char)dbg_loc->value;
            uVar4 = (int)uVar3 >> 0x1f;
            iVar2 = rec_len + 7;
            rec_len = iVar1;
            _sprintf((char *)(g_object_record_buffer + iVar2),&s_pct_d_00440ce4,
                     ((uVar3 ^ uVar4) - uVar4 & 0xf ^ uVar4) - uVar4);
            uVar3 = (uint)(char)dbg_loc->value;
            uVar4 = (int)uVar3 >> 0x1f;
            g_object_record_buffer[rec_len] =
                 (9 < (int)(((uVar3 ^ uVar4) - uVar4 & 0xf ^ uVar4) - uVar4)) + '\x03';
            uVar3 = (uint)(char)dbg_loc->value;
            uVar4 = (int)uVar3 >> 0x1f;
            iVar1 = rec_len + (9 < (int)(((uVar3 ^ uVar4) - uVar4 & 0xf ^ uVar4) - uVar4)) + 4;
          }
        }
        rec_len = iVar1;
        store_u16_big_endian((ushort *)&dbg_sym->value,(ushort *)(g_object_record_buffer + rec_len))
        ;
        iVar1 = rec_len + 2;
        rec_len = rec_len + 2;
        store_u16_big_endian((ushort *)dbg_sym->word_0a,(ushort *)(g_object_record_buffer + iVar1));
        iVar1 = rec_len + 2;
        rec_len = rec_len + 2;
        store_u16_big_endian
                  ((ushort *)&g_debug_word_1001,(ushort *)(g_object_record_buffer + iVar1));
        iVar1 = rec_len + 2;
        if (((byte)((uint)(int)(char)dbg_sym->kind >> 1) & 0x7f) == 0xe) {
          g_object_record_buffer[rec_len + 2] = dbg_sym->type_ext->byte0;
          g_object_record_buffer[rec_len + 3] = '\0';
          iVar1 = rec_len + 4;
        }
        rec_len = iVar1;
        append_object_record_bytes(g_object_record_buffer,rec_len,0x34);
        append_object_record_bytes((uchar *)0x0,0,0xff);
      }
    }
    (&g_current_section)[g_scope_top]->size[1] = (int)g_scope_stack[g_scope_top]->next;
    g_scope_stack[g_scope_top] = (debug_scope *)(&g_current_section)[g_scope_top]->size[1];
    g_scope_top = g_scope_top + -1;
    g_object_record_buffer[0] = 0x89;
    append_object_record_bytes(g_object_record_buffer,1,0x32);
    append_object_record_bytes((uchar *)0x0,0,0xff);
  }
  return;
#undef scope_length
#undef dbg_loc
#undef rec_len
#undef name_pos
#undef sym_id
#undef loc_id
#undef dbg_sym
#undef name_length
}
