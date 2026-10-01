#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_asb_output
#define g_asb_output (*(FILE * *)(g_sd + 0x5d20))
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x6d50))
#undef g_current_symbol
#define g_current_symbol (*(symbol * *)(g_sd + 0x6d4c))


// entry: 0040f160
// name : write_asb_function_aux_record
// size : 667
// sig  : void write_asb_function_aux_record(void)


/* WARNING: Type propagation algorithm not settling */

int __cdecl write_asb_function_aux_record(void)

{
  unsigned char _frec_1b[27];
#define uStack_1b (*(undefined1 *)(_frec_1b + 0))
#define cStack_1a (*(char *)(_frec_1b + 1))
#define out_rec (*(byte *)(_frec_1b + 3))
#define local_17 (*(uchar *)(_frec_1b + 4))
#define local_16 (*(byte *)(_frec_1b + 5))
#define local_15 (*(uchar (*)[6])(_frec_1b + 6))
#define local_f (*(undefined1 *)(_frec_1b + 12))
#define local_e (*(undefined1 *)(_frec_1b + 13))
#define local_d (*(undefined1 *)(_frec_1b + 14))
#define local_c (*(undefined1 *)(_frec_1b + 15))
#define local_b (*(undefined1 *)(_frec_1b + 16))
#define local_a (*(undefined1 *)(_frec_1b + 17))
#define local_9 (*(undefined1 *)(_frec_1b + 18))
#define local_8 (*(undefined1 *)(_frec_1b + 19))
#define local_7 (*(undefined1 *)(_frec_1b + 20))
#define local_6 (*(undefined1 *)(_frec_1b + 21))
#define local_5 (*(uchar *)(_frec_1b + 22))
#define local_4 (*(uchar *)(_frec_1b + 23))
#define local_3 (*(undefined1 *)(_frec_1b + 24))
  ushort stack_kind;
  uint written;
  aux_record *aux;
  int last;
  ushort aux_flags;
  aux_reg_range *next_range;
  aux_reg_range *range;
  short short_value;
  
  aux = g_aux_record_table + g_current_symbol->aux_index;
  out_rec = g_current_symbol->type | g_current_symbol->flags;
  local_17 = (uchar)g_current_symbol->number;
  local_16 = *(undefined1 *)((int)&g_current_symbol->number + 1);
  local_15[0] = (uchar)aux->frame_size;
  local_15[1] = *(undefined1 *)((int)&aux->frame_size + 1);
  local_15[2] = *(char *)((int)&aux->frame_size + 2);
  local_15[3] = *(char *)((int)&aux->frame_size + 3);
  local_15[4] = (uchar)aux->max_stack;
  local_15[5] = *(undefined1 *)((int)&aux->max_stack + 1);
  local_f = *(undefined1 *)((int)&aux->max_stack + 2);
  local_e = *(undefined1 *)((int)&aux->max_stack + 3);
  local_d = (undefined1)aux->sp_adjust;
  local_c = *(undefined1 *)((int)&aux->sp_adjust + 1);
  local_b = *(undefined1 *)((int)&aux->sp_adjust + 2);
  local_a = *(undefined1 *)((int)&aux->sp_adjust + 3);
  local_9 = (undefined1)aux->saved_regs2;
  local_8 = *(undefined1 *)((int)&aux->saved_regs2 + 1);
  local_7 = (undefined1)aux->saved_regs;
  local_6 = *(undefined1 *)((int)&aux->saved_regs + 1);
  local_5 = aux->saved_mac;
  local_4 = aux->saved_sys;
  local_3 = (undefined1)aux->range_count;
  written = write_file_bytes(g_asb_output,(char *)&out_rec,0x16);
  if (written == 0xffffffff) {
    report_fatal_message(0,0,0xce7);
  }
  for (range = aux->ranges; range != (aux_reg_range *)0x0; range = range->next) {
    out_rec = range->before_reg;
    local_17 = range->after_reg;
    local_16 = (byte)range->start_expno;
    local_15[0] = *(undefined1 *)((int)&range->start_expno + 1);
    local_15[1] = *(undefined1 *)((int)&range->start_expno + 2);
    local_15[2] = *(char *)((int)&range->start_expno + 3);
    local_15[3] = (uchar)range->end_expno;
    local_15[4] = *(undefined1 *)((int)&range->end_expno + 1);
    local_15[5] = *(undefined1 *)((int)&range->end_expno + 2);
    local_f = *(undefined1 *)((int)&range->end_expno + 3);
    written = write_file_bytes(g_asb_output,(char *)&out_rec,10);
    if (written == 0xffffffff) {
      report_fatal_message(0,0,0xce7);
    }
  }
  aux_flags = aux->flags;
  out_rec = (aux_flags & 0x8000) != 0;
  local_17 = (aux_flags & 0x4000) != 0;
  last = 2;
  stack_kind = aux_flags & 0x1800;
  if (stack_kind < 0x801) {
    if (stack_kind != 0x800) {
      if ((aux_flags & 0x1800) == 0) {
        local_16 = 0;
        last = 3;
        goto LAB_0040f395;
      }
LAB_0040f322:
      report_fatal_message(0,0,0x1270);
      goto LAB_0040f395;
    }
    local_16 = 0x80;
    local_15[0] = (uchar)aux->stack_value;
    local_15[1] = *(undefined1 *)((int)&aux->stack_value + 1);
    local_15[2] = *(char *)((int)&aux->stack_value + 2);
    cStack_1a = *(char *)((int)&aux->stack_value + 3);
  }
  else {
    if (stack_kind == 0x1000) {
      local_16 = 0x81;
    }
    else {
      if (stack_kind != 0x1800) goto LAB_0040f322;
      local_16 = 0x83;
    }
    short_value = (short)aux->stack_value;
    local_15[0] = (uchar)short_value;
    uStack_1b = (undefined1)((ushort)short_value >> 8);
    cStack_1a = (char)(short_value >> 0xf);
    local_15[1] = uStack_1b;
    local_15[2] = cStack_1a;
  }
  last = 7;
  local_15[3] = cStack_1a;
LAB_0040f395:
  if ((aux_flags & 0x2000) == 0) {
    (&out_rec)[last] = 0;
  }
  else {
    (&out_rec)[last] = 0x80;
    (&local_17)[last] = aux->unknown_byte;
    last = last + 1;
  }
  written = write_file_bytes(g_asb_output,(char *)&out_rec,last + 1);
  if (written == 0xffffffff) {
    report_fatal_message(0,0,0xce7);
  }
  range = aux->ranges;
  while (range != (aux_reg_range *)0x0) {
    next_range = range->next;
    pool_free(range,0x10);
    range = next_range;
  }
  return;
#undef uStack_1b
#undef cStack_1a
#undef out_rec
#undef local_17
#undef local_16
#undef local_15
#undef local_f
#undef local_e
#undef local_d
#undef local_c
#undef local_b
#undef local_a
#undef local_9
#undef local_8
#undef local_7
#undef local_6
#undef local_5
#undef local_4
#undef local_3
}



