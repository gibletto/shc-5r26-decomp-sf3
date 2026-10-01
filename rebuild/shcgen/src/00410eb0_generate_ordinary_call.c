#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 00410eb0
// name : generate_ordinary_call
// size : 804
// sig  : void generate_ordinary_call(gen_node * call)


int __cdecl generate_ordinary_call(gen_node *call)

{
  uchar *puVar1;
  ushort *puVar2;
  gen_node *pgVar3;
  byte bVar4;
  byte bVar5;
  gen_node *args;
  short cpu;
  node_desc *desc;
  
  args = (gen_node *)0x0;
  pgVar3 = call->child;
  if (pgVar3 != (gen_node *)0x0) {
    args = pgVar3->next;
  }
  if (((call->type & 0xe0) == 0x60) &&
     (((((call->parent != (gen_node *)0x0 && (call->parent->op == IL_COND)) &&
        (bVar4 = (call->desc->dest).type & 0x1f, bVar4 != 0)) && (bVar4 == 1)) ||
      (((desc = call->desc, desc->usage != '\0' && ((desc->flags2 & 8) == 0)) &&
       (((desc->dest).type & 0x1f) == 0)))))) {
    allocate_temp_frame_slot(call,call->val,&call->desc->value);
  }
  pgVar3->desc->busy_regs = call->desc->busy_regs;
  pgVar3->desc->fbusy_regs = call->desc->fbusy_regs;
  pgVar3->desc->frame_top = call->desc->frame_top;
  puVar1 = &pgVar3->desc->flags7;
  *puVar1 = *puVar1 | call->desc->flags7 & 0x40;
  desc = pgVar3->desc;
  if ((desc->pref_regs == 0) && (desc->fpref_regs == 0)) {
    desc->pref_regs = call->desc->pref_regs;
    pgVar3->desc->fpref_regs = call->desc->fpref_regs;
  }
  dispatch_and_finalize_code_node(pgVar3);
  args->desc->busy_regs = pgVar3->desc->busy_regs;
  args->desc->fbusy_regs = pgVar3->desc->fbusy_regs;
  args->desc->frame_top = pgVar3->desc->frame_top;
  puVar1 = &args->desc->flags7;
  *puVar1 = *puVar1 | pgVar3->desc->flags7 & 0x40;
  desc = args->desc;
  if ((desc->pref_regs == 0) && (desc->fpref_regs == 0)) {
    desc->pref_regs = call->desc->pref_regs;
    args->desc->fpref_regs = call->desc->fpref_regs;
  }
  dispatch_and_finalize_code_node(args);
  bVar4 = call->type & 0xf8;
  if (bVar4 != 0x50) {
    cpu = g_request->cpu;
    if ((cpu == 4) && (bVar4 == 0x30)) {
      fill_ea(&call->desc->value,'\x01',' ',-1,'\0',0,(label_ref *)0x0);
      puVar2 = &call->desc->fbusy_regs;
      *(byte *)puVar2 = (byte)*puVar2 | 3;
      g_used_fpr_mask = g_used_fpr_mask | call->desc->fbusy_regs;
      puVar2 = &call->desc->ftemp_regs;
      *(byte *)puVar2 = (byte)*puVar2 | 3;
    }
    else {
      if ((cpu == 2) && (g_request->fpu_mode == '\x03')) {
        bVar5 = 1;
      }
      else {
        bVar5 = -(cpu == 4) & 2;
      }
      if ((bVar5 == 0) || (bVar4 != 0x28)) {
        bVar5 = call->type & 0xe0;
        if ((bVar5 != 0) && ((bVar5 != 0x40 && (bVar4 != 0x28)))) {
          call->desc->opnd_class = '\x03';
          goto LAB_00411105;
        }
        fill_ea(&call->desc->value,'\x01','\0',-1,'\0',0,(label_ref *)0x0);
        puVar2 = &call->desc->busy_regs;
        *(byte *)puVar2 = (byte)*puVar2 | 1;
        g_used_gpr_mask = g_used_gpr_mask | call->desc->busy_regs;
        puVar2 = &call->desc->temp_regs;
        *(byte *)puVar2 = (byte)*puVar2 | 1;
      }
      else {
        fill_ea(&call->desc->value,'\x01','\x10',-1,'\0',0,(label_ref *)0x0);
        puVar2 = &call->desc->fbusy_regs;
        *(byte *)puVar2 = (byte)*puVar2 | 1;
        g_used_fpr_mask = g_used_fpr_mask | call->desc->fbusy_regs;
        puVar2 = &call->desc->ftemp_regs;
        *(byte *)puVar2 = (byte)*puVar2 | 1;
      }
    }
    call->desc->opnd_class = '\0';
  }
LAB_00411105:
  pgVar3 = call->parent;
  if ((((pgVar3 == (gen_node *)0x0) || (pgVar3->op != IL_ASSIGN)) || (pgVar3->desc->usage != '\0'))
     || (((call->type & 0xe0) != 0x60 && ((g_request->cpu == 4 || ((call->type & 0xf8) != 0x30))))))
  {
    *(undefined1 *)&call->desc->temp_regs = 0xff;
    puVar2 = &call->desc->ftemp_regs;
    *puVar2 = *puVar2 | ((1 << (g_request->scratch_bank_reg_count & 0x1fU)) + -1) * 0x10 | 0xfU;
  }
  else {
    *(undefined1 *)&pgVar3->desc->temp_regs = 0xff;
    puVar2 = &call->parent->desc->ftemp_regs;
    *puVar2 = *puVar2 | ((1 << (g_request->scratch_bank_reg_count & 0x1fU)) + -1) * 0x10 | 0xfU;
  }
  g_used_gpr_mask = CONCAT11((*(unsigned char *)((char *)&g_used_gpr_mask + 1)),0xff);
  g_used_fpr_mask =
       g_used_fpr_mask | ((1 << (g_request->scratch_bank_reg_count & 0x1fU)) + -1) * 0x10 | 0xfU;
  invalidate_register_contents(0xf000f);
  g_r0_used = 1;
  return;
}



