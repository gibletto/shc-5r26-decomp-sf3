#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 00416ff0
// name : expand_switch_jump
// size : 2383
// sig  : void __cdecl expand_switch_jump(psd *rec)


int __cdecl expand_switch_jump(psd *rec)

{
  unsigned char _frec_4c[76];
#define nop_rec (*(psd *)(_frec_4c + 0))
#define short_entries (*(char *)(_frec_4c + 24))
#define label_hi (*(undefined1 *)(_frec_4c + 28))
#define label_lo (*(undefined1 *)(_frec_4c + 29))
#define table_label (*(ushort (*)[2])(_frec_4c + 32))
#define i (*(int *)(_frec_4c + 36))
#define base_label (*(ushort (*)[2])(_frec_4c + 40))
#define tmp_rec (*(psd *)(_frec_4c + 44))
#define lref (*(label_ref * *)(_frec_4c + 68))
  short spool_byte;
  ea *operand;
  
  base_label[0] = 0;
  if (rec->ea1 != (ea *)0x0) {
    if (((int)rec->ea1 < -0x7f) || (0x80 < (int)rec->ea1)) {
      set_psd_record(&tmp_rec,'*','\x02','\0','\0',0,rec->expno,0,0);
      tmp_rec.ea1 = alloc_ea_operand('\a',0xff,0xff,(int)rec->ea1,(label_ref *)0x0);
      tmp_rec.ea2 = alloc_ea_operand('\x01','\x01',0xff,0,(label_ref *)0x0);
      expand_movi_record(&tmp_rec);
      set_psd_record(g_expanded_records + g_expanded_record_count,'c','\x02','\0','\0',0,rec->expno,
                     0,0);
      operand = alloc_ea_operand('\x01','\x01',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
    }
    else {
      set_psd_record(g_expanded_records + g_expanded_record_count,'`','\x02','\0','\0',0,rec->expno,
                     0,0);
      operand = alloc_ea_operand('\a',0xff,0xff,-(int)rec->ea1,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
    }
  }
  set_psd_record(&tmp_rec,'*','\x02','\0','\0',0,rec->expno,0,0);
  tmp_rec.ea1 = alloc_ea_operand('\a',0xff,0xff,(int)rec->ea2,(label_ref *)0x0);
  tmp_rec.ea2 = alloc_ea_operand('\x01','\x01',0xff,0,(label_ref *)0x0);
  expand_movi_record(&tmp_rec);
  set_psd_record(g_expanded_records + g_expanded_record_count,'Q','\x02','\0','\0',0,rec->expno,0,0)
  ;
  operand = alloc_ea_operand('\x01','\x01',0xff,0,(label_ref *)0x0);
  g_expanded_records[g_expanded_record_count].ea1 = operand;
  operand = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
  g_expanded_records[g_expanded_record_count].ea2 = operand;
  g_expanded_record_count = g_expanded_record_count + 1;
  set_psd_record(&tmp_rec,'%','\x02','\0','\0',0,rec->expno,0,0);
  lref = pool_alloc(8);
  lref->labno1 = rec->linno;
  tmp_rec.ea1 = alloc_ea_operand('\a',0xff,0xff,0,lref);
  tmp_rec.ea2 = (ea *)0x0;
  expand_conditional_jump(&tmp_rec);
  spool_byte = read_spool_byte();
  short_entries = (char)spool_byte;
  if (short_entries == '\0') {
    set_psd_record(g_expanded_records + g_expanded_record_count,'K','\x02','\0','\0',0,rec->expno,0,
                   0);
  }
  else {
    set_psd_record(g_expanded_records + g_expanded_record_count,'J','\x02','\0','\0',0,rec->expno,0,
                   0);
  }
  operand = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
  g_expanded_records[g_expanded_record_count].ea1 = operand;
  g_expanded_records[g_expanded_record_count].ea2 = (ea *)0x0;
  g_expanded_record_count = g_expanded_record_count + 1;
  if (g_current_request->cpu == 0) {
    set_psd_record(&tmp_rec,'*','\x02','\0','\0',0,rec->expno,0,0);
    spool_byte = read_spool_byte();
    label_hi = (undefined1)spool_byte;
    spool_byte = read_spool_byte();
    label_lo = (undefined1)spool_byte;
    store_u16_big_endian((ushort *)&label_hi,table_label);
    lref = pool_alloc(8);
    lref->labno1 = table_label[0];
    tmp_rec.ea1 = alloc_ea_operand('\a',0xff,0xff,0,lref);
    tmp_rec.ea2 = alloc_ea_operand('\x01','\x01',0xff,0,(label_ref *)0x0);
    expand_movi_record(&tmp_rec);
  }
  else {
    spool_byte = read_spool_byte();
    label_hi = (undefined1)spool_byte;
    spool_byte = read_spool_byte();
    label_lo = (undefined1)spool_byte;
    store_u16_big_endian((ushort *)&label_hi,base_label);
    set_psd_record(g_expanded_records + g_expanded_record_count,'@','\x02','\0','\0',0,rec->expno,0,
                   0);
    operand = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x01','\x01',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
    g_expanded_record_count = g_expanded_record_count + 1;
    set_psd_record(g_expanded_records + g_expanded_record_count,'D','\x02','\0','\0',0,rec->expno,0,
                   0);
    spool_byte = read_spool_byte();
    label_hi = (undefined1)spool_byte;
    spool_byte = read_spool_byte();
    label_lo = (undefined1)spool_byte;
    store_u16_big_endian((ushort *)&label_hi,table_label);
    lref = pool_alloc(8);
    lref->labno1 = table_label[0];
    operand = alloc_ea_operand('\n','k',0xff,0,lref);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
    g_expanded_record_count = g_expanded_record_count + 1;
  }
  if ((short_entries == '\0') && (g_current_request->cpu == 0)) {
    set_psd_record(g_expanded_records + g_expanded_record_count,'@','\x02','\0','\0',0,rec->expno,0,
                   0);
    operand = alloc_ea_operand('\t','\x01','\0',0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
    g_expanded_record_count = g_expanded_record_count + 1;
  }
  else {
    set_psd_record(g_expanded_records + g_expanded_record_count,'@',(short_entries == '\0') + '\x01'
                   ,'\0','\0',0,rec->expno,0,0);
    operand = alloc_ea_operand('\t','\x01','\0',0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
    g_expanded_record_count = g_expanded_record_count + 1;
    if (g_current_request->cpu == 0) {
      set_psd_record(g_expanded_records + g_expanded_record_count,'`','\x02','\0','\0',0,rec->expno,
                     0,0);
      operand = alloc_ea_operand('\x01','\x01',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
    }
  }
  set_psd_record(g_expanded_records + g_expanded_record_count,
                 (-(g_current_request->cpu == 0) & 0xfaU) + 0x9a,'\x02','\0','\0',0,rec->expno,0,0);
  operand = alloc_ea_operand('\x02','\0',0xff,0,(label_ref *)0x0);
  g_expanded_records[g_expanded_record_count].ea1 = operand;
  g_expanded_records[g_expanded_record_count].ea2 = (ea *)0x0;
  g_expanded_record_count = g_expanded_record_count + 1;
  for (i = 0; i < g_expanded_record_count; i = i + 1) {
    stock_memcpy(&tmp_rec,g_expanded_records + i,0x18);
    if ((g_current_request->debug != 0) && (g_current_section_kind == 0)) {
      update_debug_info_for_record(&tmp_rec);
    }
    if (tmp_rec.op == OP_LABEL) {
      emit_label_record(&tmp_rec);
    }
    else {
      assemble_instruction(&tmp_rec);
      if ((((tmp_rec.op == OP_BRA) || (tmp_rec.op == OP_BT_S)) || (tmp_rec.op == OP_BF_S)) ||
         ((tmp_rec.op == OP_BRAF || (tmp_rec.op == OP_JMP)))) {
        stock_memcpy(&nop_rec,&g_zero_psd,0x18);
        nop_rec.op = OP_NOP;
        nop_rec.flg = 'B';
        nop_rec.expno = tmp_rec.expno;
        nop_rec.filno = tmp_rec.filno;
        nop_rec.linno = tmp_rec.linno;
        assemble_instruction(&nop_rec);
      }
    }
    if (OP_SWEND < tmp_rec.op) {
      if (tmp_rec.ea1 != (ea *)0x0) {
        free_ea_operand(tmp_rec.ea1);
      }
      if (tmp_rec.ea2 != (ea *)0x0) {
        free_ea_operand(tmp_rec.ea2);
      }
    }
    stock_memcpy(g_expanded_records + i,&g_zero_psd,0x18);
  }
  if (g_current_request->cpu != 0) {
    tmp_rec.op = OP_LABEL;
    tmp_rec.ea1 = (ea *)CONCAT22((*(unsigned short *)((char *)&tmp_rec.ea1 + 2)),base_label[0]);
    emit_label_record(&tmp_rec);
  }
  g_expanded_record_count = 0;
  if ((g_word_literal_table.count != 0) || (g_long_literal_table.count != 0)) {
    emit_literal_pool();
  }
  emit_switch_table(table_label[0],base_label[0],(int)short_entries);
  return;
#undef nop_rec
#undef short_entries
#undef label_hi
#undef label_lo
#undef table_label
#undef i
#undef base_label
#undef tmp_rec
#undef lref
}
