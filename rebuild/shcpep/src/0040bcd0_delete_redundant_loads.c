#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_node_list
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 0040bcd0
// name : delete_redundant_loads
// size : 721
// sig  : void delete_redundant_loads(code_node * block)


int __cdecl delete_redundant_loads(code_node *block)

{
  uchar reg;
  byte bVar1;
  uchar changed;
  char cVar2;
  uint is_vol;
  psd *rec;
  psd *load;
  byte cmp_flg;
  psd_op op;
  
  if (((*(unsigned char *)((char *)&g_stage_flags + 1)) & 0x20) != 0) {
    _printf(s_delload_start__node_pointer___08_00426258,block);
    dump_node_list_debug(block);
  }
  load = block->psd;
  while( true ) {
    if (load == (psd *)0x0) {
      if (((*(unsigned char *)((char *)&g_stage_flags + 1)) & 0x20) != 0) {
        dump_node_list_debug(g_current_node_list);
        _printf(s_delload_end__00426210);
      }
      return;
    }
    op = load->op;
    if (((byte)g_stage_flags & 2) != 0) {
      _printf(s_code_pointer___08lx_00426240,load);
    }
    if ((((op == OP_MOV) || (op == OP_NON_B0)) ||
        ((op == OP_MOV_LOC && ((load->misc & 0x80U) == 0)))) &&
       (((((load->ea1->type & 0x80) == 0 && (is_vol = is_record_volatile(load), is_vol == 0)) &&
         (bVar1 = load->ea1->type & 0x1f, bVar1 != 3)) &&
        ((bVar1 != 4 && ((load->ea2->type & 0x1f) == 1)))))) break;
LAB_0040bf46:
    load = find_next_psd_record(block,load);
    if (((byte)g_stage_flags & 2) != 0) {
      _printf(s_code_pointer___08lx_00426240,load);
    }
  }
  reg = load->ea2->base;
  rec = find_next_psd_record(block,load);
  if (((byte)g_stage_flags & 2) != 0) {
    _printf(s_compare_code_pointer___08lx_00426220,rec);
  }
  do {
    if (((rec == (psd *)0x0) || (op = rec->op, op == OP_CASEJMP)) ||
       (((op == OP_SLEEP || (((op == OP_NON_10 || (op == OP_CALL)) || (op == OP_JSR)))) ||
        (((op == OP_BSR || (op == OP_TRAPA)) || (op == OP_BSRF)))))) goto LAB_0040bf46;
    if (((op == OP_MOV) || (op == OP_NON_B0)) || ((op == OP_MOV_LOC && ((rec->misc & 0x80U) == 0))))
    {
      bVar1 = load->flg;
      cmp_flg = rec->flg;
      cVar2 = operands_equal(load->ea2,rec->ea2);
      if (((cVar2 == '\x01') && ((cmp_flg & 3) == (bVar1 & 3))) &&
         ((op == OP_MOV_LOC || (cVar2 = operand_uses_register(rec,reg,'\x01'), cVar2 == '\0')))) {
        delete_psd_record(load);
        goto LAB_0040bf46;
      }
      changed = record_changes_register(rec,reg);
      if ((changed != '\0') || (cVar2 = operand_uses_register(rec,reg,'\x01'), cVar2 != '\0'))
      goto LAB_0040bf46;
      cVar2 = operand_uses_register(rec,reg,'\x02');
joined_r0x0040bf0a:
      if (cVar2 != '\0') goto LAB_0040bf46;
    }
    else {
      changed = record_changes_register(rec,reg);
      if ((changed != '\0') ||
         ((rec->ea2 != (ea *)0x0 && (cVar2 = operand_uses_register(rec,reg,'\x02'), cVar2 != '\0')))
         ) goto LAB_0040bf46;
      if (rec->ea1 != (ea *)0x0) {
        cVar2 = operand_uses_register(rec,reg,'\x01');
        goto joined_r0x0040bf0a;
      }
    }
    rec = find_next_psd_record(block,rec);
    if (((byte)g_stage_flags & 2) != 0) {
      _printf(s_compare_code_pointer___08lx_00426220,rec);
    }
  } while( true );
}



