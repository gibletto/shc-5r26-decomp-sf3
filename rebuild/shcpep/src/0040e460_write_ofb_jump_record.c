#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ofb_record_out
#define g_ofb_record_out (*(FILE * *)(g_sd + 0x5358))


// entry: 0040e460
// name : write_ofb_jump_record
// size : 481
// sig  : void write_ofb_jump_record(psd * rec, int location, short pool_size)


int __cdecl write_ofb_jump_record(psd *rec,int location,short pool_size)

{
  unsigned char _frec_104[260];
#define local_104 (*(undefined4 *)(_frec_104 + 0))
#define out_buf (*(undefined2 *)(_frec_104 + 4))
#define out_location (*(undefined1 *)(_frec_104 + 6))
#define local_fd (*(undefined1 *)(_frec_104 + 7))
#define local_fc (*(undefined1 *)(_frec_104 + 8))
#define local_fb (*(undefined1 *)(_frec_104 + 9))
#define local_fa (*(undefined1 *)(_frec_104 + 10))
#define local_f9 (*(undefined1 *)(_frec_104 + 11))
#define local_f8 (*(undefined1 *)(_frec_104 + 12))
#define local_f7 (*(undefined1 *)(_frec_104 + 13))
#define local_f6 (*(undefined1 *)(_frec_104 + 14))
#define local_f5 (*(undefined1 *)(_frec_104 + 15))
#define local_f4 (*(undefined1 *)(_frec_104 + 16))
#define local_f3 (*(undefined1 *)(_frec_104 + 17))
  short sVar1;
  uint uVar2;
  uint uVar3;
  int label_count;
  label_ref *lref;
  ea *opnd;
  
  (*(unsigned char *)((char *)&out_buf + 0)) = rec->op;
  sVar1 = compute_record_code_size(rec);
  (*(unsigned char *)((char *)&out_buf + 1)) = (undefined1)sVar1;
  local_fd = (*(unsigned char *)((char *)&location + 1));
  local_fc = (*(unsigned char *)((char *)&location + 2));
  out_location = (undefined1)location;
  opnd = rec->ea1;
  local_fb = (*(unsigned char *)((char *)&location + 3));
  local_fa = (undefined1)opnd->disp;
  local_f9 = *(undefined1 *)((int)&opnd->disp + 1);
  local_f8 = *(undefined1 *)((int)&opnd->disp + 2);
  local_f7 = *(undefined1 *)((int)&opnd->disp + 3);
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
  local_f6 = (undefined1)local_104;
  local_f5 = (*(unsigned char *)((char *)&local_104 + 1));
  (*(unsigned char *)((char *)&local_104 + 3)) = (undefined1)((uint)label_count >> 0x18);
  local_f4 = (*(unsigned char *)((char *)&local_104 + 2));
  local_f3 = (*(unsigned char *)((char *)&local_104 + 3));
  uVar2 = write_file_bytes(g_ofb_record_out,(char *)&out_buf,0xe);
  if (uVar2 == 0xffffffff) {
    report_compiler_message(0,0,0xce7,(char *)0x0);
  }
  uVar2 = 0;
  for (lref = rec->ea1->labels; lref != (label_ref *)0x0; lref = lref->next) {
    uVar3 = uVar2;
    if (lref->labno1 != 0) {
      *(char *)((int)&out_buf + uVar2) = (char)lref->labno1;
      uVar3 = uVar2 + 2;
      *(undefined1 *)((int)&out_buf + uVar2 + 1) = *(undefined1 *)((int)&lref->labno1 + 1);
    }
    uVar2 = uVar3;
    if (lref->labno2 != 0) {
      *(char *)((int)&out_buf + uVar3) = (char)lref->labno2;
      uVar2 = uVar3 + 2;
      *(undefined1 *)((int)&out_buf + uVar3 + 1) = *(undefined1 *)((int)&lref->labno2 + 1);
    }
    if (0xfe < (int)(uVar2 + 2)) {
      uVar2 = write_file_bytes(g_ofb_record_out,(char *)&out_buf,uVar2);
      if (uVar2 == 0xffffffff) {
        report_compiler_message(0,0,0xce7,(char *)0x0);
      }
      uVar2 = 0;
    }
  }
  if ((uVar2 != 0) &&
     (uVar2 = write_file_bytes(g_ofb_record_out,(char *)&out_buf,uVar2), uVar2 == 0xffffffff)) {
    report_compiler_message(0,0,0xce7,(char *)0x0);
  }
  out_buf = pool_size;
  uVar2 = write_file_bytes(g_ofb_record_out,(char *)&out_buf,2);
  if (uVar2 == 0xffffffff) {
    report_compiler_message(0,0,0xce7,(char *)0x0);
  }
  return;
#undef local_104
#undef out_buf
#undef out_location
#undef local_fd
#undef local_fc
#undef local_fb
#undef local_fa
#undef local_f9
#undef local_f8
#undef local_f7
#undef local_f6
#undef local_f5
#undef local_f4
#undef local_f3
}



