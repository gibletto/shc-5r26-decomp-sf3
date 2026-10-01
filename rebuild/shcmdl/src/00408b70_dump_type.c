#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_str_empty
#define g_str_empty (*(char *)(g_sd + 0x2650))


// entry: 00408b70
// name : dump_type
// size : 434
// sig  : void dump_type(uchar type)


int __cdecl dump_type(uchar type)

{
  unsigned char _frec_14[20];
#define text (*(char (*)[4])(_frec_14 + 0))
#define local_10 (*(char (*)[2])(_frec_14 + 4))
#define local_e (*(char *)(_frec_14 + 6))
  byte kind;
  uint uVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  char c;
  
  FID_conflict__wprintf(s_type__00434b08);
  if ((type & 1) == 0) {
    text[0] = g_str_empty;
  }
  else {
    text[0] = s_const_00434b00[0];
    text[1] = s_const_00434b00[1];
    text[2] = s_const_00434b00[2];
    text[3] = s_const_00434b00[3];
    local_10[0] = s_const_00434b00[4];
    local_10[1] = s_const_00434b00[5];
    local_e = s_const_00434b00[6];
  }
  if ((type & 2) == 0) {
    pcVar4 = &g_str_empty;
  }
  else {
    pcVar4 = s_volatile_00434af4;
  }
  uVar1 = 0xffffffff;
  do {
    pcVar6 = pcVar4;
    if (uVar1 == 0) break;
    uVar1 = uVar1 - 1;
    pcVar6 = pcVar4 + 1;
    c = *pcVar4;
    pcVar4 = pcVar6;
  } while (c != '\0');
  uVar1 = ~uVar1;
  iVar2 = -1;
  pcVar4 = text;
  do {
    pcVar5 = pcVar4;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar5 = pcVar4 + 1;
    c = *pcVar4;
    pcVar4 = pcVar5;
  } while (c != '\0');
  pcVar4 = pcVar6 + -uVar1;
  pcVar6 = pcVar5 + -1;
  for (uVar3 = uVar1 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar1 = uVar1 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *pcVar6 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar6 = pcVar6 + 1;
  }
  kind = type & 0xe0;
  if ((type & 0xe0) == 0) {
    switch(type & 0x18) {
    case 0:
      pcVar4 = &g_str_char;
      break;
    case 8:
      pcVar4 = s_short_00434ae4;
      break;
    case 0x10:
      pcVar4 = &g_str_int;
      break;
    case 0x18:
      pcVar4 = &g_str_long;
      break;
    default:
      goto switchD_00408c12_default;
    }
  }
  else {
    if ((type & 0xe0) == 0x20) {
      kind = type & 0x18;
      if (kind == 8) {
        pcVar4 = s_float_00434ac8;
        goto LAB_00408cca;
      }
      if (kind == 0x10) {
        pcVar4 = s_double_00434ac0;
        goto LAB_00408cca;
      }
      if (kind == 0x18) {
        pcVar4 = s_long_double_00434ab4;
        goto LAB_00408cca;
      }
    }
    else {
      if ((type & 0x48) == 0x48) {
        pcVar4 = &g_str_func;
        goto LAB_00408cca;
      }
      if (kind == 0x40) {
        pcVar4 = s_pointer_00434aac;
        goto LAB_00408cca;
      }
      if (kind == 0x60) {
        pcVar4 = s_struct_00434aa4;
        goto LAB_00408cca;
      }
      if (kind == 0x80) {
        pcVar4 = s_array_00434a9c;
        goto LAB_00408cca;
      }
      if ((type & 0x18) == 0x10) {
        pcVar4 = &g_str_void;
        goto LAB_00408cca;
      }
    }
switchD_00408c12_default:
    pcVar4 = &g_str_empty;
    FID_conflict__wprintf(s___02x__00434ad0,(uint)type);
  }
LAB_00408cca:
  if ((type & 4) != 0) {
    FID_conflict__wprintf(s_unsigned_00434a88);
  }
  uVar1 = 0xffffffff;
  do {
    pcVar6 = pcVar4;
    if (uVar1 == 0) break;
    uVar1 = uVar1 - 1;
    pcVar6 = pcVar4 + 1;
    c = *pcVar4;
    pcVar4 = pcVar6;
  } while (c != '\0');
  uVar1 = ~uVar1;
  iVar2 = -1;
  pcVar4 = text;
  do {
    pcVar5 = pcVar4;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar5 = pcVar4 + 1;
    c = *pcVar4;
    pcVar4 = pcVar5;
  } while (c != '\0');
  pcVar4 = pcVar6 + -uVar1;
  pcVar6 = pcVar5 + -1;
  for (uVar3 = uVar1 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar4;
    pcVar4 = pcVar4 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar1 = uVar1 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *pcVar6 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    pcVar6 = pcVar6 + 1;
  }
  FID_conflict__wprintf(&g_str_percent_s_close_bracket,text);
  return;
#undef text
#undef local_10
#undef local_e
}



