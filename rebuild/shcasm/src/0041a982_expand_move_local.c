#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 0041a982
// name : expand_move_local
// size : 6999
// sig  : void expand_move_local(psd *rec)


int __cdecl expand_move_local(psd *rec)

{
  unsigned char _frec_24[36];
#define label_hi (*(undefined1 *)(_frec_24 + 0))
#define label_lo (*(undefined1 *)(_frec_24 + 1))
#define lit_table (*(literal_table * *)(_frec_24 + 4))
#define flag40 (*(char *)(_frec_24 + 8))
#define sp_disp (*(uint *)(_frec_24 + 12))
#define lit_size (*(uchar *)(_frec_24 + 16))
#define pool_disp (*(int *)(_frec_24 + 20))
#define pool_ref (*(label_ref * *)(_frec_24 + 24))
#define is_fpu_reg (*(char *)(_frec_24 + 28))
  short spool_byte;
  ea *operand;
  int lit_index;
  symbol *pool_sym;
  layout_record *pool_start;
  
  is_fpu_reg = '\0';
  flag40 = (rec->flg & 0x40) != 0;
  if ((rec->misc & 0x80U) == 0) {
    sp_disp = frame_offset_to_sp_displacement_for_pass(rec->ea1->disp,rec->sptravel,2);
    if (('\x0f' < (char)rec->ea2->base) && ((char)rec->ea2->base < ' ')) {
      is_fpu_reg = '\x01';
    }
    if (rec->tmp == '\0') {
      if (sp_disp == 0) {
        set_psd_record(g_expanded_records + g_expanded_record_count,
                       (-(is_fpu_reg == '\0') & 0x90U) + 0xb0,rec->flg & 3,'\0','\0',0,rec->expno,
                       rec->filno,rec->linno);
        operand = alloc_ea_operand('\x02','\x0f',0xff,0,(label_ref *)0x0);
        g_expanded_records[g_expanded_record_count].ea1 = operand;
        operand = alloc_ea_operand('\x01',rec->ea2->base,0xff,0,(label_ref *)0x0);
        g_expanded_records[g_expanded_record_count].ea2 = operand;
        g_expanded_record_count = g_expanded_record_count + 1;
      }
      else if ((((int)sp_disp < 1) || (0x10 << (rec->flg & 3) <= (int)sp_disp)) ||
              (is_fpu_reg != '\0')) {
        if (((int)sp_disp < -0x80) || (0x7f < (int)sp_disp)) {
          if (((int)sp_disp < -0x8000) || (0x7fff < (int)sp_disp)) {
            lit_size = '\x02';
            lit_table = &g_long_literal_table;
          }
          else {
            lit_size = '\x01';
            lit_table = &g_word_literal_table;
          }
          set_psd_record(g_expanded_records + g_expanded_record_count,'@',lit_size,'\0','\0',0,
                         rec->expno,rec->filno,rec->linno);
          if ((g_word_literal_table.count == 0) && (g_long_literal_table.count == 0)) {
            spool_byte = read_spool_byte();
            label_hi = (undefined1)spool_byte;
            spool_byte = read_spool_byte();
            label_lo = (undefined1)spool_byte;
            store_u16_big_endian((ushort *)&label_hi,(ushort *)&g_literal_pool_label);
          }
          lit_index = find_pool_literal(lit_table,sp_disp,(label_ref *)0x0);
          if (lit_index == 0) {
            add_pool_literal(lit_table,sp_disp,(label_ref *)0x0);
          }
          lit_index = find_literal_pool_index(lit_table,sp_disp,(label_ref *)0x0);
          if (lit_size == '\x02') {
            pool_sym = find_symbol_by_id(g_literal_pool_label);
            pool_start = pool_sym->layout_records;
            pool_sym = find_symbol_by_id(g_literal_pool_label);
            pool_disp = (int)pool_start + ((lit_index * 4 + -4) - pool_sym->value);
          }
          else {
            pool_disp = lit_index * 2 + -2;
          }
          pool_ref = pool_alloc(8);
          pool_ref->labno1 = g_literal_pool_label;
          operand = alloc_ea_operand('\n','k',0xff,pool_disp,pool_ref);
          g_expanded_records[g_expanded_record_count].ea1 = operand;
          operand = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
          g_expanded_records[g_expanded_record_count].ea2 = operand;
          g_expanded_record_count = g_expanded_record_count + 1;
          set_psd_record(g_expanded_records + g_expanded_record_count,
                         (-(is_fpu_reg == '\0') & 0x90U) + 0xb0,rec->flg & 3,'\0','\0',0,rec->expno,
                         rec->filno,rec->linno);
          operand = alloc_ea_operand('\t','\x0f','\0',0,(label_ref *)0x0);
          g_expanded_records[g_expanded_record_count].ea1 = operand;
          operand = alloc_ea_operand('\x01',rec->ea2->base,0xff,0,(label_ref *)0x0);
          g_expanded_records[g_expanded_record_count].ea2 = operand;
          g_expanded_record_count = g_expanded_record_count + 1;
        }
        else {
          set_psd_record(g_expanded_records + g_expanded_record_count,'@','\x02','\0','\0',0,
                         rec->expno,rec->filno,rec->linno);
          operand = alloc_ea_operand('\a',0xff,0xff,sp_disp,(label_ref *)0x0);
          g_expanded_records[g_expanded_record_count].ea1 = operand;
          operand = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
          g_expanded_records[g_expanded_record_count].ea2 = operand;
          g_expanded_record_count = g_expanded_record_count + 1;
          set_psd_record(g_expanded_records + g_expanded_record_count,
                         (-(is_fpu_reg == '\0') & 0x90U) + 0xb0,rec->flg & 3,'\0','\0',0,rec->expno,
                         rec->filno,rec->linno);
          operand = alloc_ea_operand('\t','\x0f','\0',0,(label_ref *)0x0);
          g_expanded_records[g_expanded_record_count].ea1 = operand;
          operand = alloc_ea_operand('\x01',rec->ea2->base,0xff,0,(label_ref *)0x0);
          g_expanded_records[g_expanded_record_count].ea2 = operand;
          g_expanded_record_count = g_expanded_record_count + 1;
        }
      }
      else {
        if (((rec->flg & 3) == 2) || (rec->ea2->base == REG_R0)) {
          set_psd_record(g_expanded_records + g_expanded_record_count,'@',rec->flg & 3,'\0','\0',0,
                         rec->expno,rec->filno,rec->linno);
          operand = alloc_ea_operand('\b','\x0f',0xff,sp_disp,(label_ref *)0x0);
          g_expanded_records[g_expanded_record_count].ea1 = operand;
          operand = alloc_ea_operand('\x01',rec->ea2->base,0xff,0,(label_ref *)0x0);
          g_expanded_records[g_expanded_record_count].ea2 = operand;
        }
        else {
          set_psd_record(g_expanded_records + g_expanded_record_count,'@',rec->flg & 3,'\0','\0',0,
                         rec->expno,rec->filno,rec->linno);
          operand = alloc_ea_operand('\b','\x0f',0xff,sp_disp,(label_ref *)0x0);
          g_expanded_records[g_expanded_record_count].ea1 = operand;
          operand = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
          g_expanded_records[g_expanded_record_count].ea2 = operand;
          g_expanded_record_count = g_expanded_record_count + 1;
          set_psd_record(g_expanded_records + g_expanded_record_count,'@','\x02','\0','\0',0,
                         rec->expno,rec->filno,rec->linno);
          operand = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
          g_expanded_records[g_expanded_record_count].ea1 = operand;
          operand = alloc_ea_operand('\x01',rec->ea2->base,0xff,0,(label_ref *)0x0);
          g_expanded_records[g_expanded_record_count].ea2 = operand;
        }
        g_expanded_record_count = g_expanded_record_count + 1;
      }
    }
    else if (sp_disp == 0) {
      set_psd_record(g_expanded_records + g_expanded_record_count,
                     (-(is_fpu_reg == '\0') & 0x90U) + 0xb0,rec->flg & 3,'\0','\0',0,rec->expno,
                     rec->filno,rec->linno);
      operand = alloc_ea_operand('\x02','\x0f',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x01',rec->ea2->base,0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
    }
    else if (((((rec->flg & 3) == 2) && (0 < (int)sp_disp)) &&
             ((int)sp_disp < 0x10 << (rec->flg & 3))) && (is_fpu_reg == '\0')) {
      set_psd_record(g_expanded_records + g_expanded_record_count,'@',rec->flg & 3,'\0','\0',0,
                     rec->expno,rec->filno,rec->linno);
      operand = alloc_ea_operand('\b','\x0f',0xff,sp_disp,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x01',rec->ea2->base,0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
    }
    else if (((int)sp_disp < -0x80) || (0x7f < (int)sp_disp)) {
      if (((int)sp_disp < -0x8000) || (0x7fff < (int)sp_disp)) {
        lit_size = '\x02';
        lit_table = &g_long_literal_table;
      }
      else {
        lit_size = '\x01';
        lit_table = &g_word_literal_table;
      }
      set_psd_record(g_expanded_records + g_expanded_record_count,'@',lit_size,'\0','\0',0,
                     rec->expno,rec->filno,rec->linno);
      if ((g_word_literal_table.count == 0) && (g_long_literal_table.count == 0)) {
        spool_byte = read_spool_byte();
        label_hi = (undefined1)spool_byte;
        spool_byte = read_spool_byte();
        label_lo = (undefined1)spool_byte;
        store_u16_big_endian((ushort *)&label_hi,(ushort *)&g_literal_pool_label);
      }
      lit_index = find_pool_literal(lit_table,sp_disp,(label_ref *)0x0);
      if (lit_index == 0) {
        add_pool_literal(lit_table,sp_disp,(label_ref *)0x0);
      }
      lit_index = find_literal_pool_index(lit_table,sp_disp,(label_ref *)0x0);
      if (lit_size == '\x02') {
        pool_sym = find_symbol_by_id(g_literal_pool_label);
        pool_start = pool_sym->layout_records;
        pool_sym = find_symbol_by_id(g_literal_pool_label);
        pool_disp = (int)pool_start + ((lit_index * 4 + -4) - pool_sym->value);
      }
      else {
        pool_disp = lit_index * 2 + -2;
      }
      pool_ref = pool_alloc(8);
      pool_ref->labno1 = g_literal_pool_label;
      operand = alloc_ea_operand('\n','k',0xff,pool_disp,pool_ref);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x01',rec->tmp,0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
      set_psd_record(g_expanded_records + g_expanded_record_count,'`','\x02','\0','\0',0,rec->expno,
                     rec->filno,rec->linno);
      operand = alloc_ea_operand('\x01','\x0f',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x01',rec->tmp,0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
      set_psd_record(g_expanded_records + g_expanded_record_count,
                     (-(is_fpu_reg == '\0') & 0x90U) + 0xb0,rec->flg & 3,'\0','\0',0,rec->expno,
                     rec->filno,rec->linno);
      operand = alloc_ea_operand('\x02',rec->tmp,0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x01',rec->ea2->base,0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
    }
    else {
      set_psd_record(g_expanded_records + g_expanded_record_count,'@','\x02','\0','\0',0,rec->expno,
                     rec->filno,rec->linno);
      operand = alloc_ea_operand('\x01','\x0f',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x01',rec->tmp,0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
      set_psd_record(g_expanded_records + g_expanded_record_count,'`','\x02','\0','\0',0,rec->expno,
                     rec->filno,rec->linno);
      operand = alloc_ea_operand('\a',0xff,0xff,sp_disp,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x01',rec->tmp,0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
      set_psd_record(g_expanded_records + g_expanded_record_count,
                     (-(is_fpu_reg == '\0') & 0x90U) + 0xb0,rec->flg & 3,'\0','\0',0,rec->expno,
                     rec->filno,rec->linno);
      operand = alloc_ea_operand('\x02',rec->tmp,0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x01',rec->ea2->base,0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
    }
  }
  else {
    sp_disp = frame_offset_to_sp_displacement_for_pass(rec->ea2->disp,rec->sptravel,2);
    if (('\x0f' < (char)rec->ea1->base) && ((char)rec->ea1->base < ' ')) {
      is_fpu_reg = '\x01';
    }
    if (rec->tmp == '\0') {
      if (sp_disp == 0) {
        set_psd_record(g_expanded_records + g_expanded_record_count,
                       (-(is_fpu_reg == '\0') & 0x90U) + 0xb0,rec->flg & 3,'\0','\0',0,rec->expno,
                       rec->filno,rec->linno);
        operand = alloc_ea_operand('\x01',rec->ea1->base,0xff,0,(label_ref *)0x0);
        g_expanded_records[g_expanded_record_count].ea1 = operand;
        operand = alloc_ea_operand('\x02','\x0f',0xff,0,(label_ref *)0x0);
        g_expanded_records[g_expanded_record_count].ea2 = operand;
        g_expanded_record_count = g_expanded_record_count + 1;
      }
      else if ((((int)sp_disp < 1) || (0x10 << (rec->flg & 3) <= (int)sp_disp)) ||
              (is_fpu_reg != '\0')) {
        if (((int)sp_disp < -0x80) || (0x7f < (int)sp_disp)) {
          if (((int)sp_disp < -0x8000) || (0x7fff < (int)sp_disp)) {
            lit_size = '\x02';
            lit_table = &g_long_literal_table;
          }
          else {
            lit_size = '\x01';
            lit_table = &g_word_literal_table;
          }
          set_psd_record(g_expanded_records + g_expanded_record_count,'@',lit_size,'\0','\0',0,
                         rec->expno,rec->filno,rec->linno);
          if ((g_word_literal_table.count == 0) && (g_long_literal_table.count == 0)) {
            spool_byte = read_spool_byte();
            label_hi = (undefined1)spool_byte;
            spool_byte = read_spool_byte();
            label_lo = (undefined1)spool_byte;
            store_u16_big_endian((ushort *)&label_hi,(ushort *)&g_literal_pool_label);
          }
          lit_index = find_pool_literal(lit_table,sp_disp,(label_ref *)0x0);
          if (lit_index == 0) {
            add_pool_literal(lit_table,sp_disp,(label_ref *)0x0);
          }
          lit_index = find_literal_pool_index(lit_table,sp_disp,(label_ref *)0x0);
          if (lit_size == '\x02') {
            pool_sym = find_symbol_by_id(g_literal_pool_label);
            pool_start = pool_sym->layout_records;
            pool_sym = find_symbol_by_id(g_literal_pool_label);
            pool_disp = (int)pool_start + ((lit_index * 4 + -4) - pool_sym->value);
          }
          else {
            pool_disp = lit_index * 2 + -2;
          }
          pool_ref = pool_alloc(8);
          pool_ref->labno1 = g_literal_pool_label;
          operand = alloc_ea_operand('\n','k',0xff,pool_disp,pool_ref);
          g_expanded_records[g_expanded_record_count].ea1 = operand;
          operand = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
          g_expanded_records[g_expanded_record_count].ea2 = operand;
          g_expanded_record_count = g_expanded_record_count + 1;
          set_psd_record(g_expanded_records + g_expanded_record_count,
                         (-(is_fpu_reg == '\0') & 0x90U) + 0xb0,rec->flg & 3,'\0','\0',0,rec->expno,
                         rec->filno,rec->linno);
          operand = alloc_ea_operand('\x01',rec->ea1->base,0xff,0,(label_ref *)0x0);
          g_expanded_records[g_expanded_record_count].ea1 = operand;
          operand = alloc_ea_operand('\t','\x0f','\0',0,(label_ref *)0x0);
          g_expanded_records[g_expanded_record_count].ea2 = operand;
          g_expanded_record_count = g_expanded_record_count + 1;
        }
        else {
          set_psd_record(g_expanded_records + g_expanded_record_count,'@','\x02','\0','\0',0,
                         rec->expno,rec->filno,rec->linno);
          operand = alloc_ea_operand('\a',0xff,0xff,sp_disp,(label_ref *)0x0);
          g_expanded_records[g_expanded_record_count].ea1 = operand;
          operand = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
          g_expanded_records[g_expanded_record_count].ea2 = operand;
          g_expanded_record_count = g_expanded_record_count + 1;
          set_psd_record(g_expanded_records + g_expanded_record_count,
                         (-(is_fpu_reg == '\0') & 0x90U) + 0xb0,rec->flg & 3,'\0','\0',0,rec->expno,
                         rec->filno,rec->linno);
          operand = alloc_ea_operand('\x01',rec->ea1->base,0xff,0,(label_ref *)0x0);
          g_expanded_records[g_expanded_record_count].ea1 = operand;
          operand = alloc_ea_operand('\t','\x0f','\0',0,(label_ref *)0x0);
          g_expanded_records[g_expanded_record_count].ea2 = operand;
          g_expanded_record_count = g_expanded_record_count + 1;
        }
      }
      else {
        if ((rec->flg & 3) == 2) {
          set_psd_record(g_expanded_records + g_expanded_record_count,'@','\x02','\0','\0',0,
                         rec->expno,rec->filno,rec->linno);
          operand = alloc_ea_operand('\x01',rec->ea1->base,0xff,0,(label_ref *)0x0);
          g_expanded_records[g_expanded_record_count].ea1 = operand;
          operand = alloc_ea_operand('\b','\x0f',0xff,sp_disp,(label_ref *)0x0);
          g_expanded_records[g_expanded_record_count].ea2 = operand;
        }
        else {
          set_psd_record(g_expanded_records + g_expanded_record_count,'@','\x02','\0','\0',0,
                         rec->expno,rec->filno,rec->linno);
          operand = alloc_ea_operand('\x01',rec->ea1->base,0xff,0,(label_ref *)0x0);
          g_expanded_records[g_expanded_record_count].ea1 = operand;
          operand = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
          g_expanded_records[g_expanded_record_count].ea2 = operand;
          if (((g_current_request->flags_13d & 4) != 0) && (flag40 == '\0')) {
            g_expanded_records[g_expanded_record_count].flg =
                 g_expanded_records[g_expanded_record_count].flg | 0x80;
            g_expanded_record_count = g_expanded_record_count + 1;
            set_psd_record(g_expanded_records + g_expanded_record_count,0x88,'\x02','\0','\0',0,
                           rec->expno,rec->filno,rec->linno);
            g_expanded_records[g_expanded_record_count].ea1 = (ea *)0x0;
            g_expanded_records[g_expanded_record_count].ea2 = (ea *)0x0;
            g_expanded_records[g_expanded_record_count].flg =
                 g_expanded_records[g_expanded_record_count].flg | 0x80;
          }
          g_expanded_record_count = g_expanded_record_count + 1;
          set_psd_record(g_expanded_records + g_expanded_record_count,'@',rec->flg & 3,'\0','\0',0,
                         rec->expno,rec->filno,rec->linno);
          operand = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
          g_expanded_records[g_expanded_record_count].ea1 = operand;
          operand = alloc_ea_operand('\b','\x0f',0xff,sp_disp,(label_ref *)0x0);
          g_expanded_records[g_expanded_record_count].ea2 = operand;
        }
        g_expanded_record_count = g_expanded_record_count + 1;
      }
    }
    else if (sp_disp == 0) {
      set_psd_record(g_expanded_records + g_expanded_record_count,
                     (-(is_fpu_reg == '\0') & 0x90U) + 0xb0,rec->flg & 3,'\0','\0',0,rec->expno,
                     rec->filno,rec->linno);
      operand = alloc_ea_operand('\x01',rec->ea1->base,0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x02','\x0f',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
    }
    else if (((((rec->flg & 3) == 2) || (rec->ea1->base == REG_R0)) && (0 < (int)sp_disp)) &&
            (((int)sp_disp < 0x10 << (rec->flg & 3) && (is_fpu_reg == '\0')))) {
      set_psd_record(g_expanded_records + g_expanded_record_count,'@',rec->flg & 3,'\0','\0',0,
                     rec->expno,rec->filno,rec->linno);
      operand = alloc_ea_operand('\x01',rec->ea1->base,0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\b','\x0f',0xff,sp_disp,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
    }
    else if (((int)sp_disp < -0x80) || (0x7f < (int)sp_disp)) {
      if (((int)sp_disp < -0x8000) || (0x7fff < (int)sp_disp)) {
        lit_size = '\x02';
        lit_table = &g_long_literal_table;
      }
      else {
        lit_size = '\x01';
        lit_table = &g_word_literal_table;
      }
      set_psd_record(g_expanded_records + g_expanded_record_count,'@',lit_size,'\0','\0',0,
                     rec->expno,rec->filno,rec->linno);
      if ((g_word_literal_table.count == 0) && (g_long_literal_table.count == 0)) {
        spool_byte = read_spool_byte();
        label_hi = (undefined1)spool_byte;
        spool_byte = read_spool_byte();
        label_lo = (undefined1)spool_byte;
        store_u16_big_endian((ushort *)&label_hi,(ushort *)&g_literal_pool_label);
      }
      lit_index = find_pool_literal(lit_table,sp_disp,(label_ref *)0x0);
      if (lit_index == 0) {
        add_pool_literal(lit_table,sp_disp,(label_ref *)0x0);
      }
      lit_index = find_literal_pool_index(lit_table,sp_disp,(label_ref *)0x0);
      if (lit_size == '\x02') {
        pool_sym = find_symbol_by_id(g_literal_pool_label);
        pool_start = pool_sym->layout_records;
        pool_sym = find_symbol_by_id(g_literal_pool_label);
        pool_disp = (int)pool_start + ((lit_index * 4 + -4) - pool_sym->value);
      }
      else {
        pool_disp = lit_index * 2 + -2;
      }
      pool_ref = pool_alloc(8);
      pool_ref->labno1 = g_literal_pool_label;
      operand = alloc_ea_operand('\n','k',0xff,pool_disp,pool_ref);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x01',rec->tmp,0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
      set_psd_record(g_expanded_records + g_expanded_record_count,'`','\x02','\0','\0',0,rec->expno,
                     rec->filno,rec->linno);
      operand = alloc_ea_operand('\x01','\x0f',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x01',rec->tmp,0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
      set_psd_record(g_expanded_records + g_expanded_record_count,
                     (-(is_fpu_reg == '\0') & 0x90U) + 0xb0,rec->flg & 3,'\0','\0',0,rec->expno,
                     rec->filno,rec->linno);
      operand = alloc_ea_operand('\x01',rec->ea1->base,0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x02',rec->tmp,0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
    }
    else {
      set_psd_record(g_expanded_records + g_expanded_record_count,'@','\x02','\0','\0',0,rec->expno,
                     rec->filno,rec->linno);
      operand = alloc_ea_operand('\x01','\x0f',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x01',rec->tmp,0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
      set_psd_record(g_expanded_records + g_expanded_record_count,'`','\x02','\0','\0',0,rec->expno,
                     rec->filno,rec->linno);
      operand = alloc_ea_operand('\a',0xff,0xff,sp_disp,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x01',rec->tmp,0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
      set_psd_record(g_expanded_records + g_expanded_record_count,
                     (-(is_fpu_reg == '\0') & 0x90U) + 0xb0,rec->flg & 3,'\0','\0',0,rec->expno,
                     rec->filno,rec->linno);
      operand = alloc_ea_operand('\x01',rec->ea1->base,0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x02',rec->tmp,0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
    }
  }
  if (flag40 == '\x01') {
    g_expanded_records[g_expanded_record_count + -1].flg =
         g_expanded_records[g_expanded_record_count + -1].flg | 0x40;
  }
  return;
#undef label_hi
#undef label_lo
#undef lit_table
#undef flag40
#undef sp_disp
#undef lit_size
#undef pool_disp
#undef pool_ref
#undef is_fpu_reg
}
