#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 0040ff00
// name : generate_call_node
// size : 2284
// sig  : void generate_call_node(gen_node * call)


int __cdecl generate_call_node(gen_node *call)

{
  uchar *puVar1;
  ushort *puVar2;
  short filno;
  byte bVar3;
  char cVar4;
  short sVar5;
  uint uVar6;
  tmpl_header *tmpl;
  gen_node *pgVar7;
  int arg_count;
  gen_node *pgVar8;
  ea *src;
  ushort uVar9;
  int iVar10;
  uint uVar11;
  gen_node *args;
  char *text;
  ushort saved_var_gpr_mask;
  gen_node *arg;
  il_op arg_op;
  node_desc *desc;
  bool var_regs_narrowed;
  
  iVar10 = 0;
  args = (gen_node *)0x0;
  if (call->child != (gen_node *)0x0) {
    args = call->child->next;
  }
  cVar4 = call->desc->builtin;
  if (cVar4 == '\0') {
LAB_004107cd:
    generate_ordinary_call(call);
    goto switchD_0041070b_caseD_11;
  }
  args->desc->builtin = cVar4;
  cVar4 = call->desc->builtin;
  if (cVar4 == '\x1d') {
    if (args->child->op != IL_CONST) {
      report_codegen_message(0x1239,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    }
    invalidate_register_contents(0xf000f);
    *(undefined1 *)&call->desc->temp_regs = 0xff;
    g_used_gpr_mask = CONCAT11((*(unsigned char *)((char *)&g_used_gpr_mask + 1)),0xff);
    puVar2 = &call->desc->ftemp_regs;
    *puVar2 = *puVar2 | ((1 << (g_request->scratch_bank_reg_count & 0x1fU)) + -1) * 0x10 | 0xfU;
    g_r0_used = 1;
    g_used_fpr_mask =
         g_used_fpr_mask | ((1 << (g_request->scratch_bank_reg_count & 0x1fU)) + -1) * 0x10 | 0xfU;
    goto switchD_0041070b_caseD_11;
  }
  var_regs_narrowed = false;
  sVar5 = g_request->cpu;
  if (((sVar5 == 0) && ((cVar4 == '\x1a' || (cVar4 == '\x1b')))) ||
     ((sVar5 < 2 && (cVar4 == '\x1e')))) {
    iVar10 = 0xaf4;
  }
  if (sVar5 == 4) {
    if (g_request->unknown_155[2] == '\x02') {
      if ((cVar4 < '#') || ('/' < cVar4)) {
        if ((cVar4 == '\x1f') || (cVar4 == ' ')) {
LAB_00410004:
          iVar10 = 0x7e4;
        }
      }
      else {
        iVar10 = 0xaf4;
      }
    }
    else if (g_request->unknown_155[2] == '\x01') goto joined_r0x0040ffd6;
  }
  else if ((sVar5 == 2) && (g_request->fpu_mode == '\x03')) {
    if ((cVar4 < '#') || ('/' < cVar4)) {
joined_r0x0040ffd6:
      if ((cVar4 == '0') || (cVar4 == '1')) goto LAB_00410004;
    }
    else {
      iVar10 = 0xaf4;
    }
  }
  else {
    if ((cVar4 < '!') || ('/' < cVar4)) {
      if ((cVar4 == '\x1f') || (cVar4 == ' ')) goto LAB_00410004;
      goto joined_r0x0040ffd6;
    }
    iVar10 = 0xaf4;
  }
  if (iVar10 != 0) {
    if (iVar10 == 0xaf4) {
      text = (char *)0x0;
      iVar10 = 0xaf4;
      filno = g_msg_filn;
      uVar9 = g_msg_line;
      sVar5 = g_msg_listno;
LAB_00410077:
      report_codegen_message(iVar10,filno,(uint)uVar9,(int)sVar5,text);
    }
    else if (iVar10 == 0x7e4) {
      pgVar7 = call->child;
      uVar6 = (int)pgVar7->symx + 0xb6;
      uVar11 = (int)uVar6 >> 0x1f;
      text = g_symbol_table[(uVar6 ^ uVar11) - uVar11].name;
      sVar5 = pgVar7->listno;
      uVar9 = pgVar7->line;
      filno = pgVar7->filn;
      iVar10 = 0x7e4;
      goto LAB_00410077;
    }
    call->desc->builtin = '\0';
    args->desc->builtin = '\0';
    goto LAB_004107cd;
  }
  args->desc->busy_regs = call->desc->busy_regs;
  args->desc->fbusy_regs = call->desc->fbusy_regs;
  args->desc->frame_top = call->desc->frame_top;
  puVar1 = &args->desc->flags7;
  *puVar1 = *puVar1 | call->desc->flags7 & 0x40;
  desc = args->desc;
  if ((desc->pref_regs == 0) && (desc->fpref_regs == 0)) {
    desc->pref_regs = call->desc->pref_regs;
    args->desc->fpref_regs = call->desc->fpref_regs;
  }
  tmpl = select_builtin_template('\x01',args);
  args->desc->tmpl = tmpl;
  tmpl = args->desc->tmpl;
  if (tmpl != (tmpl_header *)0x0) {
    puVar2 = &args->desc->busy_regs;
    *puVar2 = *puVar2 & ~(ushort)tmpl->clobbers;
  }
  if (call->desc->builtin == '\x1c') {
    check_trapa_svc_arguments(args);
    assign_argument_registers(args,2);
    iVar10 = count_operands(args);
    pgVar7 = nth_operand(args,iVar10 + -2);
    pgVar7->desc->target_regs = 1;
  }
  bVar3 = args->desc->tmpl->flags2;
  if ((bVar3 & 0x40) == 0) {
    if ((bVar3 & 0x20) == 0) {
      iVar10 = ((bVar3 & 0x10) == 0) - 1;
    }
    else {
      iVar10 = 2;
    }
  }
  else {
    iVar10 = 1;
  }
  if (iVar10 != 0) {
    if (iVar10 < 1) {
      arg_count = count_operands(args);
      iVar10 = arg_count + iVar10;
    }
    pgVar7 = nth_operand(args,iVar10);
    if (pgVar7 != (gen_node *)0x0) {
      puVar1 = &pgVar7->desc->flags7;
      *puVar1 = *puVar1 | 0x40;
    }
  }
  apply_template_operand_constraints(args);
  arg_op = args->child->op;
  pgVar8 = args->child;
  pgVar7 = args;
  saved_var_gpr_mask = g_var_gpr_mask;
  while (arg = pgVar8, g_var_gpr_mask = saved_var_gpr_mask, arg_op != IL_E_ARG) {
    arg->desc->busy_regs = pgVar7->desc->busy_regs;
    arg->desc->fbusy_regs = pgVar7->desc->fbusy_regs;
    arg->desc->frame_top = pgVar7->desc->frame_top;
    dispatch_and_finalize_code_node(arg);
    if ((((call->desc->builtin == '\x1c') &&
         ((desc = arg->desc, desc->target_regs != 0 || (desc->ftarget_regs != 0)))) &&
        ((desc->cached_regs != 0 || (desc->fcached_regs != 0)))) &&
       ((call->desc->flags7 & 0x10) != 0)) {
      invalidate_register_contents
                ((int)(short)desc->fcached_regs << 0x10 | (int)(short)desc->cached_regs);
    }
    pgVar8 = arg->next;
    pgVar7 = arg;
    saved_var_gpr_mask = g_var_gpr_mask;
    arg_op = arg->next->op;
  }
  switch(call->desc->builtin) {
  case '\n':
  case '\v':
  case '\f':
  case '\x16':
  case '\x17':
  case '#':
  case '$':
  case '+':
    pgVar7 = args->child;
    pgVar8 = (gen_node *)0x0;
    if (pgVar7 != (gen_node *)0x0) {
      pgVar8 = pgVar7->next;
    }
    resolve_operand_register_conflicts(args,pgVar7,pgVar8);
    puVar2 = &call->desc->temp_regs;
    *puVar2 = *puVar2 | args->child->desc->temp_regs;
    puVar2 = &call->desc->ftemp_regs;
    *puVar2 = *puVar2 | args->child->desc->ftemp_regs;
    if (args->child == (gen_node *)0x0) {
      pgVar7 = (gen_node *)0x0;
    }
    else {
      pgVar7 = args->child->next;
    }
    puVar2 = &call->desc->temp_regs;
    *puVar2 = *puVar2 | pgVar7->desc->temp_regs;
    if (args->child == (gen_node *)0x0) {
      pgVar7 = (gen_node *)0x0;
    }
    else {
      pgVar7 = args->child->next;
    }
    puVar2 = &call->desc->ftemp_regs;
    *puVar2 = *puVar2 | pgVar7->desc->ftemp_regs;
    break;
  case '\x18':
  case '\x19':
  case '\x1a':
  case '\x1b':
  case '\'':
  case '(':
  case ')':
  case '*':
  case ',':
  case '-':
  case '.':
    if ((((*(short *)g_request->unknown_004 != 0) && (g_no_reg_ranges == '\0')) ||
        (uVar6 = (int)g_current_function >> 0x1f,
        (g_symbol_table[((int)g_current_function ^ uVar6) - uVar6].sym_flags & 4) == 0)) ||
       ((g_symbol_table[((int)g_current_function ^ uVar6) - uVar6].sym_flags & 0x20) != 0)) {
      g_var_gpr_mask = saved_var_gpr_mask & 0xff00;
    }
    move_builtin_arguments_clobbered_by_later_ones(args);
    g_var_gpr_mask = saved_var_gpr_mask;
    for (pgVar7 = args->child; (pgVar7 != (gen_node *)0x0 && (pgVar7->op != IL_E_ARG));
        pgVar7 = pgVar7->next) {
      puVar2 = &call->desc->temp_regs;
      *puVar2 = *puVar2 | pgVar7->desc->temp_regs;
      puVar2 = &call->desc->ftemp_regs;
      *puVar2 = *puVar2 | pgVar7->desc->ftemp_regs;
    }
    goto LAB_004103aa;
  case '\x1c':
    save_register_arguments_clobbered_by_later_ones(args,1);
    for (pgVar7 = args->child; (pgVar7 != (gen_node *)0x0 && (pgVar7->op != IL_E_ARG));
        pgVar7 = pgVar7->next) {
      puVar2 = &call->desc->temp_regs;
      *puVar2 = *puVar2 | pgVar7->desc->temp_regs;
      puVar2 = &call->desc->ftemp_regs;
      *puVar2 = *puVar2 | pgVar7->desc->ftemp_regs;
    }
  }
  saved_var_gpr_mask = 0;
LAB_004103aa:
  if (((&g_builtin_info)[call->desc->builtin * 8] & 0x80) != 0) {
    check_builtin_immediate_argument(args);
  }
  if (((&g_builtin_info)[call->desc->builtin * 8] & 0x40) != 0) {
    tmpl = select_builtin_template('\0',args);
    args->desc->tmpl = tmpl;
  }
  desc = call->desc;
  bVar3 = (desc->dest).type & 0x1f;
  if ((bVar3 == 0) || (bVar3 != 1)) {
    if (desc->target_regs == 0) {
      if (desc->ftarget_regs == 0) goto LAB_00410451;
      sVar5 = float_mask_to_register(desc->ftarget_regs);
      cVar4 = (char)sVar5;
    }
    else {
      sVar5 = mask_to_register((int)(short)desc->target_regs);
      cVar4 = (char)sVar5;
    }
    fill_ea(&args->desc->dest,'\x01',cVar4,-1,'\0',0,(label_ref *)0x0);
  }
  else {
    copy_ea_into(&args->desc->dest,&desc->dest);
  }
LAB_00410451:
  args->type = call->type;
  uVar9 = g_var_gpr_mask;
  cVar4 = call->desc->builtin;
  if ((cVar4 < '\x18') || ('\x1b' < cVar4)) {
    uVar6 = 0;
  }
  else {
    uVar6 = 0;
    if ((((*(short *)g_request->unknown_004 == 0) || (g_no_reg_ranges != '\0')) &&
        (uVar11 = (int)g_current_function >> 0x1f,
        (g_symbol_table[((int)g_current_function ^ uVar11) - uVar11].sym_flags & 4) != 0)) &&
       ((g_symbol_table[((int)g_current_function ^ uVar11) - uVar11].sym_flags & 0x20) == 0)) {
      g_var_gpr_mask = (ushort)(*(unsigned char *)((char *)&g_var_gpr_mask + 1)) << 8;
      uVar6 = 0xf0;
    }
    else {
      g_var_gpr_mask = (ushort)(*(unsigned char *)((char *)&g_var_gpr_mask + 1)) << 8;
      puVar2 = &args->desc->busy_regs;
      *puVar2 = *puVar2 & (~uVar9 | 0xff0f);
    }
    var_regs_narrowed = true;
    saved_var_gpr_mask = uVar9;
  }
  pgVar7 = call;
  uVar11 = result_reg_exclusion_mask(args);
  apply_template_to_node(args,args->desc->tmpl,'\x10',(ea *)0x0,(ea *)0x0,uVar11,pgVar7);
  if (call->desc->usage == '\x02') {
    cVar4 = call->desc->builtin;
    if (cVar4 == '\x10') {
      bVar3 = 0;
    }
    else {
      if (cVar4 != '\x14') goto LAB_00410579;
      bVar3 = args->desc->regs_2c[0];
    }
    fill_ea(&args->desc->value,'\x01',bVar3,-1,'\0',0,(label_ref *)0x0);
    uVar9 = 1 << (bVar3 & 0x1f);
    puVar2 = &args->desc->busy_regs;
    *puVar2 = *puVar2 | uVar9;
    g_used_gpr_mask = g_used_gpr_mask | args->desc->busy_regs;
    puVar2 = &args->desc->temp_regs;
    *puVar2 = *puVar2 | uVar9;
  }
LAB_00410579:
  if ((var_regs_narrowed) && (g_var_gpr_mask = saved_var_gpr_mask, uVar6 != 0)) {
    uVar11 = 0;
    do {
      bVar3 = args->desc->regs_2c[uVar11];
      if (bVar3 == 0xff) break;
      if ((uVar6 & 1 << (bVar3 & 0x1f)) != 0) {
        puVar2 = &args->desc->saved_regs;
        *puVar2 = *puVar2 | 1 << (bVar3 & 0x1f) & (ushort)uVar6;
      }
      uVar11 = uVar11 + 1;
    } while (uVar11 < 5);
    uVar11 = 0;
    do {
      desc = args->desc;
      if (desc->tmpl->reg_spec2[uVar11] == 0) break;
      bVar3 = desc->regs_34[uVar11];
      if ((bVar3 != 0xff) && ((uVar6 & 1 << (bVar3 & 0x1f)) != 0)) {
        desc->saved_regs = desc->saved_regs | 1 << (bVar3 & 0x1f) & (ushort)uVar6;
      }
      uVar11 = uVar11 + 1;
    } while (uVar11 < 4);
  }
  if (args->desc->opnd_class == '\x02') {
    puVar1 = &call->desc->flags3;
    *puVar1 = *puVar1 | 8;
    if (call->desc->tmpl == (tmpl_header *)0x0) {
      puVar1 = &call->desc->flags3;
      *puVar1 = *puVar1 | 0x80;
    }
  }
  call->desc->busy_regs = args->desc->busy_regs;
  call->desc->fbusy_regs = args->desc->fbusy_regs;
  call->desc->frame_top = args->desc->frame_top;
  bVar3 = 0;
  desc = args->desc;
  src = desc->mem_ea;
  if (src != (ea *)0x0) {
    bVar3 = src->type & 0x1f;
  }
  if (((bVar3 == 0) && (src = &desc->dest, (src->type & 0x1f) == 0)) &&
     (src = &g_ea_pop, (desc->flags2 & 8) == 0)) {
    src = &desc->value;
  }
  copy_ea_into(&call->desc->value,src);
  call->desc->opnd_class = args->desc->opnd_class;
  desc = call->desc;
  if ((desc->usage == '\x01') && ((desc->builtin == '\x10' || (desc->builtin == '\x14')))) {
    desc->flags2 = desc->flags2 | 0x20;
    cVar4 = '\0';
    uVar9 = 0;
    uVar6 = result_reg_exclusion_mask(call);
    sVar5 = choose_general_register((ushort)uVar6,uVar9,cVar4);
    if (sVar5 == -1) {
      sVar5 = choose_general_register(0,0,'\0');
    }
    puVar2 = &call->desc->temp_regs;
    *puVar2 = *puVar2 | 1 << ((byte)sVar5 & 0x1f);
    call->desc->cond_regs[0] = (byte)sVar5;
  }
  if ((args->desc->flags3 & 1) != 0) {
    puVar1 = &call->desc->flags3;
    *puVar1 = *puVar1 | 1;
  }
  switch(call->desc->builtin) {
  case '\a':
  case '\b':
  case '\t':
  case '\n':
  case '\v':
  case '\f':
  case '\r':
  case '\x0e':
  case '\x0f':
  case '\x10':
  case '\x14':
  case '\x16':
  case '\x17':
  case '\x18':
  case '\x19':
  case '\x1a':
  case '\x1b':
  case '\x1e':
  case '!':
  case '#':
  case '$':
  case '%':
  case '&':
  case '\'':
  case '(':
  case ')':
  case '*':
  case '+':
  case ',':
  case '-':
  case '.':
  case '/':
    invalidate_variable_register_contents(0xf000f);
    break;
  case '\x13':
  case '\x15':
  case '\x1c':
    invalidate_register_contents(0xf000f);
  }
switchD_0041070b_caseD_11:
  puVar1 = &call->desc->flags3;
  *puVar1 = *puVar1 | 0x80;
  puVar1 = &call->desc->flags3;
  *puVar1 = *puVar1 | 8;
  return;
}



