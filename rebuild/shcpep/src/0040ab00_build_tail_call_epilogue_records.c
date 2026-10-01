#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x6d50))


// entry: 0040ab00
// name : build_tail_call_epilogue_records
// size : 1443
// sig  : char build_tail_call_epilogue_records(code_node * node, psd * call)


char __cdecl build_tail_call_epilogue_records(code_node *node,psd *call)

{
  int disp;
  ea *src;
  ea *dst;
  int slot;
  psd *ppVar1;
  psd *ppVar2;
  int regno;
  psd_op op;
  
  slot = 1;
  ppVar1 = node->psd;
  disp = g_aux_record_table[g_current_aux_index].sp_adjust +
         g_aux_record_table[g_current_aux_index].frame_size;
  if (disp != 0) {
    if (disp < 0x80) {
      src = new_ea_operand('\a','\0','\0',disp,(label_ref *)0x0);
      dst = new_ea_operand('\x01','\x0f','\0',0,(label_ref *)0x0);
      slot = 2;
      fill_psd_record(ppVar1,'`','\x02','\0',-1,0,call->expno,call->filno,call->linno,src,dst);
      ppVar1 = node->psd + 1;
    }
    else {
      src = new_ea_operand('\a','\0','\0',disp,(label_ref *)0x0);
      dst = new_ea_operand('\x01','\x01','\0',0,(label_ref *)0x0);
      fill_psd_record(ppVar1,'*','\x02','\0',-1,0,call->expno,call->filno,call->linno,src,dst);
      src = new_ea_operand('\x01','\x01','\0',0,(label_ref *)0x0);
      dst = new_ea_operand('\x01','\x0f','\0',0,(label_ref *)0x0);
      fill_psd_record(node->psd + 1,'`','\x02','\0',-1,0,call->expno,call->filno,call->linno,src,dst
                     );
      ppVar1 = node->psd + 2;
      slot = 3;
    }
  }
  ppVar2 = ppVar1;
  if ((g_aux_record_table[g_current_aux_index].saved_sys & 2) != 0) {
    src = new_ea_operand('\x04','\x0f','\0',0,(label_ref *)0x0);
    dst = new_ea_operand('\x10','h','\0',0,(label_ref *)0x0);
    slot = slot + 1;
    ppVar2 = ppVar1 + 1;
    fill_psd_record(ppVar1,0x8d,'\x02','\0',-1,0,call->expno,call->filno,call->linno,src,dst);
  }
  ppVar1 = ppVar2;
  if ((g_aux_record_table[g_current_aux_index].saved_sys & 1) != 0) {
    src = new_ea_operand('\x04','\x0f','\0',0,(label_ref *)0x0);
    dst = new_ea_operand('\x0f','g','\0',0,(label_ref *)0x0);
    slot = slot + 1;
    ppVar1 = ppVar2 + 1;
    fill_psd_record(ppVar2,0x8d,'\x02','\0',-1,0,call->expno,call->filno,call->linno,src,dst);
  }
  ppVar2 = ppVar1;
  if ((g_aux_record_table[g_current_aux_index].saved_mac & 1) != 0) {
    src = new_ea_operand('\x04','\x0f','\0',0,(label_ref *)0x0);
    dst = new_ea_operand('\x06','e','\0',0,(label_ref *)0x0);
    slot = slot + 1;
    ppVar2 = ppVar1 + 1;
    fill_psd_record(ppVar1,0x8d,'\x02','\0',-1,0,call->expno,call->filno,call->linno,src,dst);
  }
  ppVar1 = ppVar2;
  if ((g_aux_record_table[g_current_aux_index].saved_mac & 2) != 0) {
    src = new_ea_operand('\x04','\x0f','\0',0,(label_ref *)0x0);
    dst = new_ea_operand('\x06','d','\0',0,(label_ref *)0x0);
    slot = slot + 1;
    ppVar1 = ppVar2 + 1;
    fill_psd_record(ppVar2,0x8d,'\x02','\0',-1,0,call->expno,call->filno,call->linno,src,dst);
  }
  ppVar2 = ppVar1;
  if ((g_aux_record_table[g_current_aux_index].flags & 0x8000) == 0) {
    src = new_ea_operand('\x04','\x0f','\0',0,(label_ref *)0x0);
    dst = new_ea_operand('\x06','f','\0',0,(label_ref *)0x0);
    slot = slot + 1;
    ppVar2 = ppVar1 + 1;
    fill_psd_record(ppVar1,0x8d,'\x02','\0',-1,0,call->expno,call->filno,call->linno,src,dst);
  }
  regno = 0;
  do {
    if ((1 << ((byte)regno & 0x1f) & (int)g_aux_record_table[g_current_aux_index].saved_regs2) != 0)
    {
      src = new_ea_operand('\x04','\x0f','\0',0,(label_ref *)0x0);
      dst = new_ea_operand('\x01',(byte)regno + 0x10,'\0',0,(label_ref *)0x0);
      fill_psd_record(ppVar2,0xb0,'\x02','\0',-1,0,call->expno,call->filno,call->linno,src,dst);
      if (slot == 0xf) {
        slot = 1;
        node = node->next;
        ppVar2 = node->psd;
      }
      else {
        slot = slot + 1;
        ppVar2 = ppVar2 + 1;
      }
    }
    regno = regno + 1;
  } while (regno < 0x10);
  regno = 0;
  do {
    if ((1 << ((byte)regno & 0x1f) & (int)g_aux_record_table[g_current_aux_index].saved_regs) != 0)
    {
      src = new_ea_operand('\x04','\x0f','\0',0,(label_ref *)0x0);
      dst = new_ea_operand('\x01',(byte)regno,'\0',0,(label_ref *)0x0);
      fill_psd_record(ppVar2,'@','\x02','\0',-1,0,call->expno,call->filno,call->linno,src,dst);
      if (slot == 0xf) {
        slot = 1;
        node = node->next;
        ppVar2 = node->psd;
      }
      else {
        slot = slot + 1;
        ppVar2 = ppVar2 + 1;
      }
    }
    regno = regno + 1;
  } while (regno < 0x10);
  op = call->op;
  if (op == OP_CALL) {
    src = copy_ea(call->ea1);
    fill_psd_record(ppVar2,'$','\x02','\0',call->tmp,0,call->expno,call->filno,call->linno,src,
                    (ea *)0x0);
    return '\x01';
  }
  if (op == OP_BSR) {
    src = copy_ea(call->ea1);
    fill_psd_record(ppVar2,0x92,'\x02','\0',-1,0,call->expno,call->filno,call->linno,src,(ea *)0x0);
    return '\x01';
  }
  if (op == OP_JSR) {
    src = copy_ea(call->ea1);
    fill_psd_record(ppVar2,0x94,'\x02','\0',-1,0,call->expno,call->filno,call->linno,src,(ea *)0x0);
    return '\0';
  }
  return (byte)regno;
}



