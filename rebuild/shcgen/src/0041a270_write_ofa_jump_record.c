#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ofa_record_out
#define g_ofa_record_out (*(FILE * *)(g_sd + 0x1e5e8))


// entry: 0041a270
// name : write_ofa_jump_record
// size : 481
// sig  : void write_ofa_jump_record(psd * rec, int location, short pool_size)


int __cdecl write_ofa_jump_record(psd *rec,int location,short pool_size)

{
  unsigned char _frec_104[260];
#define nlabels (*(undefined4 *)(_frec_104 + 0))
#define out_buf (*(undefined2 *)(_frec_104 + 4))
#define local_fe (*(undefined1 *)(_frec_104 + 6))
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
  int iVar1;
  uint uVar2;
  uint uVar3;
  label_ref *lab;
  ea *target;
  
  (*(unsigned char *)((char *)&out_buf + 0)) = rec->op;
  iVar1 = compute_record_code_size(rec);
  (*(unsigned char *)((char *)&out_buf + 1)) = (undefined1)iVar1;
  local_fd = (*(unsigned char *)((char *)&location + 1));
  local_fc = (*(unsigned char *)((char *)&location + 2));
  local_fe = (undefined1)location;
  target = rec->ea1;
  local_fb = (*(unsigned char *)((char *)&location + 3));
  local_fa = (undefined1)target->disp;
  local_f9 = *(undefined1 *)((int)&target->disp + 1);
  local_f8 = *(undefined1 *)((int)&target->disp + 2);
  local_f7 = *(undefined1 *)((int)&target->disp + 3);
  nlabels = 0;
  iVar1 = nlabels;
  for (lab = target->labels; lab != (label_ref *)0x0; lab = lab->next) {
    nlabels = iVar1;
    if (lab->labno1 != 0) {
      nlabels = iVar1 + 1;
    }
    if (lab->labno2 != 0) {
      nlabels = nlabels + 1;
    }
    iVar1 = nlabels;
  }
  (*(unsigned char *)((char *)&nlabels + 0)) = (undefined1)iVar1;
  (*(unsigned char *)((char *)&nlabels + 1)) = (undefined1)((uint)iVar1 >> 8);
  (*(unsigned char *)((char *)&nlabels + 2)) = (undefined1)((uint)iVar1 >> 0x10);
  local_f6 = (undefined1)nlabels;
  local_f5 = (*(unsigned char *)((char *)&nlabels + 1));
  (*(unsigned char *)((char *)&nlabels + 3)) = (undefined1)((uint)iVar1 >> 0x18);
  local_f4 = (*(unsigned char *)((char *)&nlabels + 2));
  local_f3 = (*(unsigned char *)((char *)&nlabels + 3));
  uVar2 = write_file_bytes(g_ofa_record_out,(char *)&out_buf,0xe);
  if (uVar2 == 0xffffffff) {
    report_compiler_message(0,0,0xce7,(char *)0x0);
  }
  uVar2 = 0;
  for (lab = rec->ea1->labels; lab != (label_ref *)0x0; lab = lab->next) {
    uVar3 = uVar2;
    if (lab->labno1 != 0) {
      *(char *)((int)&out_buf + uVar2) = (char)lab->labno1;
      uVar3 = uVar2 + 2;
      *(undefined1 *)((int)&out_buf + uVar2 + 1) = *(undefined1 *)((int)&lab->labno1 + 1);
    }
    uVar2 = uVar3;
    if (lab->labno2 != 0) {
      *(char *)((int)&out_buf + uVar3) = (char)lab->labno2;
      uVar2 = uVar3 + 2;
      *(undefined1 *)((int)&out_buf + uVar3 + 1) = *(undefined1 *)((int)&lab->labno2 + 1);
    }
    if (0xfe < (int)(uVar2 + 2)) {
      uVar2 = write_file_bytes(g_ofa_record_out,(char *)&out_buf,uVar2);
      if (uVar2 == 0xffffffff) {
        report_compiler_message(0,0,0xce7,(char *)0x0);
      }
      uVar2 = 0;
    }
  }
  if ((uVar2 != 0) &&
     (uVar2 = write_file_bytes(g_ofa_record_out,(char *)&out_buf,uVar2), uVar2 == 0xffffffff)) {
    report_compiler_message(0,0,0xce7,(char *)0x0);
  }
  out_buf = pool_size;
  uVar2 = write_file_bytes(g_ofa_record_out,(char *)&out_buf,2);
  if (uVar2 == 0xffffffff) {
    report_compiler_message(0,0,0xce7,(char *)0x0);
  }
  return;
#undef nlabels
#undef out_buf
#undef local_fe
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



