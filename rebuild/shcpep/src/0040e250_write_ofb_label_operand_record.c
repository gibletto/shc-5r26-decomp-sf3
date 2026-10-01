#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ofb_record_out
#define g_ofb_record_out (*(FILE * *)(g_sd + 0x5358))


// entry: 0040e250
// name : write_ofb_label_operand_record
// size : 524
// sig  : void write_ofb_label_operand_record(psd * rec, int location)


int __cdecl write_ofb_label_operand_record(psd *rec,int location)

{
  unsigned char _frec_104[260];
#define local_104 (*(undefined4 *)(_frec_104 + 0))
#define out_buf (*(psd_op (*)[5])(_frec_104 + 4))
#define local_fb (*(undefined1 *)(_frec_104 + 9))
#define local_fa (*(undefined1 *)(_frec_104 + 10))
#define local_f9 (*(undefined1 *)(_frec_104 + 11))
#define local_f8 (*(undefined1 *)(_frec_104 + 12))
#define local_f7 (*(undefined1 *)(_frec_104 + 13))
#define local_f6 (*(undefined1 *)(_frec_104 + 14))
#define local_f5 (*(undefined1 *)(_frec_104 + 15))
  short sVar1;
  uint uVar2;
  uint uVar3;
  int label_count;
  label_ref *lref;
  ea *opnd;
  
  out_buf[0] = rec->op;
  sVar1 = compute_record_code_size(rec);
  out_buf[1] = (psd_op)sVar1;
  uVar2 = write_file_bytes(g_ofb_record_out,(char *)out_buf,2);
  if (uVar2 == 0xffffffff) {
    report_compiler_message(0,0,0xce7,(char *)0x0);
  }
  if ((rec->op == OP_JUMPT) || (rec->op == OP_JUMPF)) {
    out_buf[0] = rec->misc;
    uVar2 = write_file_bytes(g_ofb_record_out,(char *)out_buf,1);
    if (uVar2 == 0xffffffff) {
      report_compiler_message(0,0,0xce7,(char *)0x0);
    }
  }
  out_buf[0] = (psd_op)location;
  out_buf[1] = (*(unsigned char *)((char *)&location + 1));
  out_buf[2] = (*(unsigned char *)((char *)&location + 2));
  out_buf[3] = (*(unsigned char *)((char *)&location + 3));
  opnd = rec->ea1;
  out_buf[4] = (psd_op)opnd->disp;
  local_fb = *(undefined1 *)((int)&opnd->disp + 1);
  local_fa = *(undefined1 *)((int)&opnd->disp + 2);
  local_f9 = *(undefined1 *)((int)&opnd->disp + 3);
  local_104 = 0;
  label_count = local_104;
  for (lref = opnd->labels; lref != (label_ref *)0x0; lref = lref->next) {
    local_104 = label_count;
    if (lref->labno1 != 0) {
      local_104 = label_count + 1;
    }
    if (lref->labno2 != 0) {
      local_104 = local_104 + 1;
    }
    label_count = local_104;
  }
  (*(unsigned char *)((char *)&local_104 + 0)) = (undefined1)label_count;
  (*(unsigned char *)((char *)&local_104 + 1)) = (undefined1)((uint)label_count >> 8);
  (*(unsigned char *)((char *)&local_104 + 2)) = (undefined1)((uint)label_count >> 0x10);
  local_f8 = (undefined1)local_104;
  local_f7 = (*(unsigned char *)((char *)&local_104 + 1));
  (*(unsigned char *)((char *)&local_104 + 3)) = (undefined1)((uint)label_count >> 0x18);
  local_f6 = (*(unsigned char *)((char *)&local_104 + 2));
  local_f5 = (*(unsigned char *)((char *)&local_104 + 3));
  uVar2 = write_file_bytes(g_ofb_record_out,(char *)out_buf,0xc);
  if (uVar2 == 0xffffffff) {
    report_compiler_message(0,0,0xce7,(char *)0x0);
  }
  uVar2 = 0;
  for (lref = rec->ea1->labels; lref != (label_ref *)0x0; lref = lref->next) {
    uVar3 = uVar2;
    if (lref->labno1 != 0) {
      out_buf[uVar2] = (psd_op)lref->labno1;
      uVar3 = uVar2 + 2;
      out_buf[uVar2 + 1] = *(psd_op *)((int)&lref->labno1 + 1);
    }
    uVar2 = uVar3;
    if (lref->labno2 != 0) {
      out_buf[uVar3] = (psd_op)lref->labno2;
      uVar2 = uVar3 + 2;
      out_buf[uVar3 + 1] = *(psd_op *)((int)&lref->labno2 + 1);
    }
    if (0xfe < (int)(uVar2 + 2)) {
      uVar2 = write_file_bytes(g_ofb_record_out,(char *)out_buf,uVar2);
      if (uVar2 == 0xffffffff) {
        report_compiler_message(0,0,0xce7,(char *)0x0);
      }
      uVar2 = 0;
    }
  }
  if ((uVar2 != 0) &&
     (uVar2 = write_file_bytes(g_ofb_record_out,(char *)out_buf,uVar2), uVar2 == 0xffffffff)) {
    report_compiler_message(0,0,0xce7,(char *)0x0);
  }
  return;
#undef local_104
#undef out_buf
#undef local_fb
#undef local_fa
#undef local_f9
#undef local_f8
#undef local_f7
#undef local_f6
#undef local_f5
}



