#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_record_cursor
#define g_debug_record_cursor (*(unsigned int * *)(g_sd + 0x13030))
#undef g_debug_record_input
#define g_debug_record_input (*(FILE * *)(g_sd + 0xcf20))
#undef g_object_record_cursor
#define g_object_record_cursor (*(unsigned char * *)(g_sd + 0x13154))


// entry: 0041080f
// name : translate_debug_symbol_record
// size : 4598
// sig  : void translate_debug_symbol_record(void)


int __cdecl translate_debug_symbol_record(void)

{
  unsigned char _frec_23c[572];
#define storage_class (*(uchar *)(_frec_23c + 0))
#define ext_shift (*(int *)(_frec_23c + 4))
#define name_buf (*(char (*)[256])(_frec_23c + 8))
#define has_storage (*(byte *)(_frec_23c + 264))
#define local_12c (*(undefined1 *)(_frec_23c + 272))
#define local_12b (*(undefined1 *)(_frec_23c + 273))
#define local_12a (*(undefined1 *)(_frec_23c + 274))
#define local_129 (*(undefined1 *)(_frec_23c + 275))
#define cur_loc_kind (*(uchar *)(_frec_23c + 276))
#define local_127 (*(byte *)(_frec_23c + 277))
#define local_126 (*(uchar *)(_frec_23c + 278))
#define local_125 (*(byte *)(_frec_23c + 279))
#define local_124 (*(undefined4 *)(_frec_23c + 280))
#define name_length (*(ushort *)(_frec_23c + 528))
#define saved_name_len (*(ushort *)(_frec_23c + 532))
#define sym_kind (*(byte *)(_frec_23c + 536))
#define sym (*(symbol * *)(_frec_23c + 540))
#define created (*(uint *)(_frec_23c + 544))
#define no_name (*(uint *)(_frec_23c + 548))
#define dbg_sym (*(debug_symbol * *)(_frec_23c + 552))
#define adj_value (*(ushort (*)[2])(_frec_23c + 556))
#define sym_id (*(ushort *)(_frec_23c + 560))
#define label_no (*(short *)(_frec_23c + 564))
  ushort uVar1;
  uchar *puVar2;
  uint uVar3;
  char *pooled_name;
  uint uVar4;
  bool bVar5;
  ushort *id_src;
  byte kind_byte;
  
  if (g_debug_group_depth == 0) {
    g_suppress_debug_record = 0;
  }
  dbg_sym = (debug_symbol *)0x0;
  created = 0;
  *g_object_record_cursor = *(uchar *)g_debug_record_cursor;
  g_debug_record_cursor = (uint *)((int)g_debug_record_cursor + 1);
  kind_byte = *g_object_record_cursor;
  g_object_record_cursor = g_object_record_cursor + 1;
  has_storage = kind_byte & 1;
  sym_kind = (byte)((uint)(int)(char)kind_byte >> 1) & 0x7f;
  store_u16_big_endian((ushort *)g_debug_record_cursor,(ushort *)g_object_record_cursor);
  puVar2 = g_object_record_cursor;
  id_src = (ushort *)g_debug_record_cursor;
  sym_id = *(ushort *)g_debug_record_cursor;
  label_no = sym_id + 0xb6;
  if ((sym_kind == 3) && (g_function_debug_loaded == 0)) {
    g_debug_function_label = label_no;
  }
  g_debug_record_cursor = (uint *)((int)g_debug_record_cursor + 2);
  g_object_record_cursor = g_object_record_cursor + 2;
  name_length = (ushort)(byte)*(ushort *)g_debug_record_cursor;
  if (has_storage != 0) {
    storage_class = *(uchar *)((int)id_src + 3);
    if ((sym_kind == 3) && ((storage_class == '\x02' || (storage_class == '\x04')))) {
      g_drop_function_debug = 0;
    }
    if ((sym_kind != 0xe) &&
       ((sym_kind != 0 || ((storage_class != '\x01' && (storage_class != '\x06')))))) {
      if ((storage_class == '\x02') || (storage_class == '\x03')) {
        for (sym = g_symbol_hash[(int)label_no % 0x3fd];
            (sym != (symbol *)0x0 && (sym->number != label_no)); sym = sym->hash_next) {
        }
        if (sym == (symbol *)0x0) {
          g_suppress_debug_record = 1;
          g_drop_function_debug = 1;
        }
        if (((storage_class == '\x03') && (sym != (symbol *)0x0)) &&
           (((sym->kind != '\n' && (sym->kind != '\v')) || ((sym->flags & 0x40) != 0)))) {
          g_suppress_debug_record = 1;
        }
      }
      else if (storage_class == '\x04') {
        for (sym = g_symbol_hash[(int)label_no % 0x3fd];
            (sym != (symbol *)0x0 && (sym->number != label_no)); sym = sym->hash_next) {
        }
        if (sym == (symbol *)0x0) {
          g_suppress_debug_record = 1;
          g_drop_function_debug = 1;
        }
      }
      if (((sym != (symbol *)0x0) &&
          ((((sym->kind == '\a' || (sym->kind == '\b')) || (sym->kind == '\t')) ||
           (sym->kind == '\n')))) && (sym->attr2 != 0xff)) {
        g_suppress_debug_record = 1;
      }
    }
  }
  if (g_suppress_debug_record == 0) {
    append_object_record_bytes
              (g_object_record_buffer,(int)(puVar2 + -SD(0x0044812e)),(uint)g_debug_record_tag);
  }
  g_object_record_buffer[0] = (uchar)*(ushort *)g_debug_record_cursor;
  g_debug_record_cursor = (uint *)((int)g_debug_record_cursor + 1);
  g_object_record_cursor = g_object_record_buffer + 1;
  saved_name_len = name_length;
  no_name = (uint)(name_length == 0);
  if ((name_length != 0) &&
     (uVar3 = read_file_bytes(g_debug_record_input,name_buf,(int)(short)name_length),
     uVar3 == 0xffffffff)) {
    report_message_at_source_line(0,0,0xce6,(char *)0x0);
  }
  stock_strncpy((char *)g_object_record_cursor,name_buf,(int)(short)name_length);
  g_object_record_cursor = g_object_record_cursor + (short)name_length;
  if (g_suppress_debug_record == 0) {
    append_object_record_bytes
              (g_object_record_buffer,(int)(g_object_record_cursor + -SD(0x00448130)),
               (uint)g_debug_record_tag);
  }
  g_object_record_cursor = g_object_record_buffer;
  store_u16_big_endian((ushort *)&g_debug_scope_depth,(ushort *)g_object_record_buffer);
  g_object_record_cursor = g_object_record_cursor + 2;
  if (has_storage != 0) {
    g_debug_record_cursor = (uint *)((int)g_debug_record_cursor + 1);
    if ((sym_kind == 0xe) ||
       ((sym_kind == 0 && ((storage_class == '\x01' || (storage_class == '\x06')))))) {
      if ((no_name == 0) && ((g_function_debug_loaded == 0 && (g_drop_function_debug == 0)))) {
        load_debug_symbol_tables();
        g_function_debug_loaded = 1;
      }
      for (dbg_sym = g_debug_symbol_hash[(int)(short)sym_id % 0x7f];
          (dbg_sym != (debug_symbol *)0x0 && (dbg_sym->id != sym_id)); dbg_sym = dbg_sym->next) {
      }
      bVar5 = dbg_sym == (debug_symbol *)0x0;
      if (bVar5) {
        dbg_sym = pool_alloc(0x20);
        dbg_sym->kind = sym_kind * '\x02' | 1;
        dbg_sym->id = sym_id;
        dbg_sym->loc_kind = '\0';
        dbg_sym->next = g_debug_symbol_hash[(int)(short)sym_id % 0x7f];
        g_debug_symbol_hash[(int)(short)sym_id % 0x7f] = dbg_sym;
      }
      created = (uint)bVar5;
      if (saved_name_len != 0) {
        pooled_name = store_string_in_pool((char)saved_name_len,name_buf);
        dbg_sym->name = pooled_name;
      }
      dbg_sym->scope_depth = g_debug_scope_depth;
      if (no_name == 0) {
        cur_loc_kind = dbg_sym->loc_kind;
        if (cur_loc_kind == '\x06') {
          local_127 = (byte)dbg_sym->loc;
          local_126 = *(uchar *)((int)&dbg_sym->loc + 1);
          local_125 = *(byte *)((int)&dbg_sym->loc + 2);
          (*(unsigned char *)((char *)&local_124 + 0)) = *(undefined1 *)((int)&dbg_sym->loc + 3);
        }
        else if (cur_loc_kind == '\x01') {
          local_127 = (byte)dbg_sym->loc;
        }
        if (sym_kind == 0xe) {
          if (created == 0) {
            if (cur_loc_kind == '\x06') {
              ext_shift = 3;
            }
            else {
              ext_shift = 0;
            }
            (&local_126)[ext_shift] = dbg_sym->type_ext->byte0;
            (&local_125)[ext_shift] = dbg_sym->type_ext->flags;
            if (((&local_125)[ext_shift] & 0x80) != 0) {
              if (((&local_125)[ext_shift] & 0x40) == 0) {
                *(char *)((int)&local_124 + ext_shift) = (char)dbg_sym->type_ext->value;
                *(undefined1 *)((int)&local_124 + ext_shift + 1) =
                     *(undefined1 *)((int)&dbg_sym->type_ext->value + 1);
                *(undefined1 *)((int)&local_124 + ext_shift + 2) =
                     *(undefined1 *)((int)&dbg_sym->type_ext->value + 2);
                *(undefined1 *)((int)&local_124 + ext_shift + 3) =
                     *(undefined1 *)((int)&dbg_sym->type_ext->value + 3);
              }
              else {
                *(char *)((int)&local_124 + ext_shift) = (char)dbg_sym->type_ext->value;
              }
            }
          }
          else {
            local_126 = '\0';
            local_125 = 0;
          }
        }
      }
      else {
        local_12c = 10;
        local_12b = 0xe;
        local_12a = 0;
        local_129 = 0;
        cur_loc_kind = '\x06';
        local_127 = 0;
        local_126 = '\0';
        local_125 = 0;
        (*(unsigned char *)((char *)&local_124 + 0)) = 0;
        (*(unsigned char *)((char *)&local_124 + 1)) = g_debug_record_body[0xf];
        (*(unsigned char *)((char *)&local_124 + 2)) = 0;
      }
      *g_object_record_cursor = cur_loc_kind;
      g_object_record_cursor = g_object_record_cursor + 1;
      if ((created == 0) || (no_name == 1)) {
        store_u32_big_endian(g_debug_record_cursor,(uint *)g_object_record_cursor);
      }
      else {
        *g_object_record_cursor = '\0';
        g_object_record_cursor[1] = '\0';
        g_object_record_cursor[2] = '\0';
        g_object_record_cursor[3] = '\0';
      }
      *(char *)&dbg_sym->word_10 = (char)*g_debug_record_cursor;
      *(undefined1 *)((int)&dbg_sym->word_10 + 1) = *(undefined1 *)((int)g_debug_record_cursor + 1);
      *(undefined1 *)((int)&dbg_sym->word_10 + 2) = *(undefined1 *)((int)g_debug_record_cursor + 2);
      *(undefined1 *)((int)&dbg_sym->word_10 + 3) = *(undefined1 *)((int)g_debug_record_cursor + 3);
      puVar2 = g_object_record_cursor;
      g_debug_record_cursor = g_debug_record_cursor + 1;
      g_object_record_cursor = g_object_record_cursor + 4;
      if (cur_loc_kind == '\x06') {
        store_u32_big_endian((uint *)&local_127,(uint *)g_object_record_cursor);
        g_object_record_cursor = g_object_record_cursor + 4;
      }
      else if (cur_loc_kind == '\x01') {
        uVar3 = (uint)local_127;
        if (uVar3 < 0x10) {
          puVar2[5] = 'R';
          _sprintf((char *)(g_object_record_cursor + 2),&s_pct_d_00440ce8,uVar3);
          *g_object_record_cursor = (9 < uVar3) + '\x02';
          g_object_record_cursor = g_object_record_cursor + (9 < uVar3) + 3;
        }
        else {
          if ((uVar3 < 0x10) || (0x1f < uVar3)) {
            if ((0x1f < uVar3) && (uVar3 < 0x2f)) {
              puVar2[5] = 'D';
              g_object_record_cursor[2] = 'R';
            }
          }
          else {
            puVar2[5] = 'F';
            g_object_record_cursor[2] = 'R';
          }
          _sprintf((char *)(g_object_record_cursor + 3),&s_pct_d_00440cec,uVar3 & 0xf);
          *g_object_record_cursor = (9 < (uVar3 & 0xf)) + '\x03';
          g_object_record_cursor = g_object_record_cursor + (9 < (uVar3 & 0xf)) + 4;
        }
      }
    }
    else if ((sym == (symbol *)0x0) ||
            (((((sym->kind != '\a' && (sym->kind != '\b')) && (sym->kind != '\t')) &&
              (sym->kind != '\n')) || (sym->attr2 == 0xff)))) {
      *g_object_record_cursor = storage_class;
      g_object_record_cursor = g_object_record_cursor + 1;
      store_u32_big_endian(g_debug_record_cursor,(uint *)g_object_record_cursor);
      puVar2 = g_object_record_cursor;
      g_debug_record_cursor = g_debug_record_cursor + 1;
      g_object_record_cursor = g_object_record_cursor + 4;
      if ((storage_class == '\x02') || (storage_class == '\x04')) {
        for (sym = g_symbol_hash[(int)label_no % 0x3fd];
            (sym != (symbol *)0x0 && (sym->number != label_no)); sym = sym->hash_next) {
        }
        if (sym == (symbol *)0x0) {
          puVar2[-1] = '\0';
        }
        else {
          store_u16_big_endian((ushort *)&sym->section_number,(ushort *)g_object_record_cursor);
          g_object_record_cursor = g_object_record_cursor + 2;
          store_u32_big_endian((uint *)&sym->value,(uint *)g_object_record_cursor);
          g_object_record_cursor = g_object_record_cursor + 4;
        }
      }
      if ((storage_class == '\x02') || (storage_class == '\x03')) {
        if (g_suppress_debug_record == 0) {
          append_object_record_bytes
                    (g_object_record_buffer,(int)(g_object_record_cursor + -SD(0x00448130)),
                     (uint)g_debug_record_tag);
        }
        g_object_record_cursor = g_object_record_buffer;
        if (sym != (symbol *)0x0) {
          g_object_record_buffer[1] = '_';
          stock_strcpy((uint *)(g_object_record_buffer + 2),(uint *)sym->name);
          uVar3 = stock_strlen(sym->name);
          *g_object_record_cursor = (char)uVar3 + '\x01';
          uVar3 = stock_strlen(sym->name);
          g_object_record_cursor = g_object_record_cursor + uVar3 + 2;
        }
        if (g_suppress_debug_record == 0) {
          append_object_record_bytes
                    (g_object_record_buffer,(int)(g_object_record_cursor + -SD(0x00448130)),
                     (uint)g_debug_record_tag);
        }
        g_object_record_cursor = g_object_record_buffer;
      }
    }
    else {
      *g_object_record_cursor = '\x01';
      g_object_record_cursor = g_object_record_cursor + 1;
      store_u32_big_endian(g_debug_record_cursor,(uint *)g_object_record_cursor);
      puVar2 = g_object_record_cursor;
      g_debug_record_cursor = g_debug_record_cursor + 1;
      g_object_record_cursor = g_object_record_cursor + 4;
      uVar3 = (uint)(char)sym->attr2;
      if (((int)uVar3 < 0) || (0xf < (int)uVar3)) {
        if (((int)uVar3 < 0x10) || (0x1f < (int)uVar3)) {
          if ((0x1f < (int)uVar3) && ((int)uVar3 < 0x2f)) {
            puVar2[5] = 'D';
            g_object_record_cursor[2] = 'R';
          }
        }
        else {
          puVar2[5] = 'F';
          g_object_record_cursor[2] = 'R';
        }
        uVar4 = (int)uVar3 >> 0x1f;
        _sprintf((char *)(g_object_record_cursor + 3),&s_pct_d_00440cf4,
                 ((uVar3 ^ uVar4) - uVar4 & 0xf ^ uVar4) - uVar4);
        *g_object_record_cursor =
             (9 < (int)(((uVar3 ^ uVar4) - uVar4 & 0xf ^ uVar4) - uVar4)) + '\x03';
        g_object_record_cursor =
             g_object_record_cursor +
             (9 < (int)(((uVar3 ^ uVar4) - uVar4 & 0xf ^ uVar4) - uVar4)) + 4;
      }
      else {
        puVar2[5] = 'R';
        _sprintf((char *)(g_object_record_cursor + 2),&s_pct_d_00440cf0,uVar3);
        *g_object_record_cursor = (9 < (int)uVar3) + '\x02';
        g_object_record_cursor = g_object_record_cursor + (9 < (int)uVar3) + 3;
      }
    }
  }
  if (sym_kind == 7) {
    *g_object_record_cursor = (byte)*g_debug_record_cursor;
    store_u32_big_endian
              ((uint *)((int)g_debug_record_cursor + 1),(uint *)(g_object_record_cursor + 1));
    store_u32_big_endian
              ((uint *)((int)g_debug_record_cursor + 5),(uint *)(g_object_record_cursor + 5));
    if ((*g_object_record_cursor & 0x80) != 0) {
      store_u32_big_endian
                ((uint *)((int)g_debug_record_cursor + 9),(uint *)(g_object_record_cursor + 9));
      g_debug_record_cursor = g_debug_record_cursor + 1;
      g_object_record_cursor = g_object_record_cursor + 4;
    }
    g_debug_record_cursor = (uint *)((int)g_debug_record_cursor + 9);
    g_object_record_cursor = g_object_record_cursor + 9;
  }
  else if (sym_kind == 8) {
    *g_object_record_cursor = (byte)*g_debug_record_cursor;
    name_length = (short)(char)*g_object_record_cursor;
    while( true ) {
      g_object_record_cursor = g_object_record_cursor + 1;
      g_debug_record_cursor = (uint *)((int)g_debug_record_cursor + 1);
      uVar1 = name_length - 1;
      bVar5 = name_length == 0;
      name_length = uVar1;
      if (bVar5) break;
      *g_object_record_cursor = *(byte *)g_debug_record_cursor;
    }
  }
  adj_value[0] = (short)*g_debug_record_cursor - 1;
  if (dbg_sym != (debug_symbol *)0x0) {
    dbg_sym->value = adj_value[0];
  }
  store_u16_big_endian(adj_value,(ushort *)g_object_record_cursor);
  g_debug_record_cursor = (uint *)((int)g_debug_record_cursor + 2);
  g_object_record_cursor = g_object_record_cursor + 2;
  if (dbg_sym != (debug_symbol *)0x0) {
    dbg_sym->word_0a[0] = *(byte *)g_debug_record_cursor;
    dbg_sym->word_0a[1] = *(byte *)((int)g_debug_record_cursor + 1);
  }
  store_u16_big_endian((ushort *)g_debug_record_cursor,(ushort *)g_object_record_cursor);
  g_debug_record_cursor = (uint *)((int)g_debug_record_cursor + 2);
  g_object_record_cursor = g_object_record_cursor + 2;
  store_u16_big_endian((ushort *)g_debug_record_cursor,(ushort *)g_object_record_cursor);
  g_debug_record_cursor = (uint *)((int)g_debug_record_cursor + 2);
  g_object_record_cursor = g_object_record_cursor + 2;
  if (sym_kind == 9) {
    *g_object_record_cursor = (uchar)*(ushort *)g_debug_record_cursor;
    g_debug_record_cursor = (uint *)((int)g_debug_record_cursor + 1);
    g_object_record_cursor = g_object_record_cursor + 1;
  }
  else if (sym_kind == 0xe) {
    if (cur_loc_kind == '\x06') {
      ext_shift = 3;
    }
    else {
      ext_shift = 0;
    }
    *g_object_record_cursor = (&local_126)[ext_shift];
    g_object_record_cursor = g_object_record_cursor + 1;
    *g_object_record_cursor = (&local_125)[ext_shift];
    puVar2 = g_object_record_cursor;
    g_object_record_cursor = g_object_record_cursor + 1;
    if (((&local_125)[ext_shift] & 0x80) != 0) {
      if (((&local_125)[ext_shift] & 0x40) == 0) {
        store_u32_big_endian((uint *)((int)&local_124 + ext_shift),(uint *)g_object_record_cursor);
        g_object_record_cursor = g_object_record_cursor + 4;
      }
      else {
        uVar3 = (uint)*(byte *)((int)&local_124 + ext_shift);
        if (uVar3 < 0x10) {
          puVar2[2] = 'R';
          _sprintf((char *)(g_object_record_cursor + 2),&s_pct_d_00440cf8,uVar3);
          *g_object_record_cursor = (9 < uVar3) + '\x02';
          g_object_record_cursor = g_object_record_cursor + (9 < uVar3) + 3;
        }
        else {
          if ((uVar3 < 0x10) || (0x1f < uVar3)) {
            if ((0x1f < uVar3) && (uVar3 < 0x2f)) {
              puVar2[2] = 'D';
              g_object_record_cursor[2] = 'R';
            }
          }
          else {
            puVar2[2] = 'F';
            g_object_record_cursor[2] = 'R';
          }
          _sprintf((char *)(g_object_record_cursor + 3),&s_pct_d_00440cfc,uVar3 & 0xf);
          *g_object_record_cursor = (9 < (uVar3 & 0xf)) + '\x03';
          g_object_record_cursor = g_object_record_cursor + (9 < (uVar3 & 0xf)) + 4;
        }
      }
    }
  }
  if (g_suppress_debug_record == 0) {
    append_object_record_bytes
              (g_object_record_buffer,(int)(g_object_record_cursor + -SD(0x00448130)),
               (uint)g_debug_record_tag);
  }
  return;
#undef storage_class
#undef ext_shift
#undef name_buf
#undef has_storage
#undef local_12c
#undef local_12b
#undef local_12a
#undef local_129
#undef cur_loc_kind
#undef local_127
#undef local_126
#undef local_125
#undef local_124
#undef name_length
#undef saved_name_len
#undef sym_kind
#undef sym
#undef created
#undef no_name
#undef dbg_sym
#undef adj_value
#undef sym_id
#undef label_no
}
