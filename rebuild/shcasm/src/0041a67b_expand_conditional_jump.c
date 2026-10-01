#include "decls.h"
#include "imports.h"

// entry: 0041a67b
// name : expand_conditional_jump
// size : 775
// sig  : void __cdecl expand_conditional_jump(psd *rec)


int __cdecl expand_conditional_jump(psd *rec)

{
  unsigned char _frec_2c[44];
#define label_hi (*(undefined1 *)(_frec_2c + 0))
#define label_lo (*(undefined1 *)(_frec_2c + 1))
#define skip_label (*(ushort (*)[2])(_frec_2c + 4))
#define jump_kind (*(char *)(_frec_2c + 8))
#define jump_rec (*(psd *)(_frec_2c + 12))
#define skip_ref (*(label_ref * *)(_frec_2c + 36))
  short spool_byte;
  ea *operand;
  
  spool_byte = read_spool_byte();
  jump_kind = (char)spool_byte;
  if ((jump_kind == '\0') || (jump_kind == '\x02')) {
    if (rec->op == OP_JUMPT) {
      set_psd_record(g_expanded_records + g_expanded_record_count,
                     (-(jump_kind == '\0') & 0xfaU) + 0x97,'\x02','\0','\0',0,rec->expno,rec->filno,
                     rec->linno);
    }
    else {
      set_psd_record(g_expanded_records + g_expanded_record_count,
                     (-(jump_kind == '\0') & 0xf8U) + 0x98,'\x02','\0','\0',0,rec->expno,rec->filno,
                     rec->linno);
    }
    g_expanded_records[g_expanded_record_count].ea1 = rec->ea1;
    rec->ea1 = (ea *)0x0;
    g_expanded_records[g_expanded_record_count].ea2 = (ea *)0x0;
  }
  else {
    if (rec->op == OP_JUMPT) {
      set_psd_record(g_expanded_records + g_expanded_record_count,
                     (-(jump_kind == '\x01') & 0xf8U) + 0x98,'\x02','\0','\0',0,rec->expno,
                     rec->filno,rec->linno);
    }
    else {
      set_psd_record(g_expanded_records + g_expanded_record_count,
                     (-(jump_kind == '\x01') & 0xfaU) + 0x97,'\x02','\0','\0',0,rec->expno,
                     rec->filno,rec->linno);
    }
    spool_byte = read_spool_byte();
    label_hi = (undefined1)spool_byte;
    spool_byte = read_spool_byte();
    label_lo = (undefined1)spool_byte;
    store_u16_big_endian((ushort *)&label_hi,skip_label);
    skip_ref = pool_alloc(8);
    skip_ref->labno1 = skip_label[0];
    operand = alloc_ea_operand('\a',0xff,0xff,0,skip_ref);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    g_expanded_records[g_expanded_record_count].ea2 = (ea *)0x0;
    g_expanded_record_count = g_expanded_record_count + 1;
    set_psd_record(&jump_rec,'$','\x02','\0',rec->tmp,0,rec->expno,rec->filno,rec->linno);
    jump_rec.ea1 = rec->ea1;
    rec->ea1 = (ea *)0x0;
    jump_rec.ea2 = (ea *)0x0;
    jump_rec.flg = jump_rec.flg | 0x10;
    expand_jump(&jump_rec);
    g_expanded_records[g_expanded_record_count].op = OP_LABEL;
    g_expanded_records[g_expanded_record_count].expno = rec->expno;
    g_expanded_records[g_expanded_record_count].filno = rec->filno;
    g_expanded_records[g_expanded_record_count].linno = rec->linno;
    *(ushort *)&g_expanded_records[g_expanded_record_count].ea1 = skip_label[0];
  }
  g_expanded_record_count = g_expanded_record_count + 1;
  return;
#undef label_hi
#undef label_lo
#undef skip_label
#undef jump_kind
#undef jump_rec
#undef skip_ref
}
