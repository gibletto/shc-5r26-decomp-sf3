#include "decls.h"
#include "imports.h"

// entry: 00429590
// name : compare_multiword
// size : 278
// sig  : int compare_multiword(uint * a, uint * b, int nwords)


int __cdecl compare_multiword(uint *a,uint *b,int nwords)

{
  unsigned char _frec_24[36];
#define local_24 (*(uint *)(_frec_24 + 0))
#define local_20 (*(undefined2 *)(_frec_24 + 4))
  ushort uVar1;
  int iVar2;
  int i;
  uint *puVar3;
  uint *puVar4;
  uint auStack_14 [5];
  uint a_word;
  uint b_word;
  
  local_24 = 0;
  if (((*a & 0x80000000) != 0) && ((*b & 0x80000000) != 0)) {
    if (0 < nwords) {
      puVar3 = a + nwords + -1;
      puVar4 = &local_24 + nwords;
      for (iVar2 = nwords; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + -1;
        puVar4 = puVar4 + -1;
      }
      if (0 < nwords) {
        puVar3 = b + nwords + -1;
        puVar4 = auStack_14 + nwords;
        for (iVar2 = nwords; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar4 = *puVar3;
          puVar3 = puVar3 + -1;
          puVar4 = puVar4 + -1;
        }
      }
    }
    *a = *a & 0x7fffffff;
    *b = *b & 0x7fffffff;
    negate_multiword(a,nwords);
    negate_multiword(b,nwords);
    local_24 = 1;
  }
  a_word = *a;
  b_word = *b;
  uVar1 = (ushort)(a_word >> 0x10);
  if ((int)b_word < (int)a_word) {
    iVar2 = CONCAT22(uVar1,1);
  }
  else if ((int)a_word < (int)b_word) {
    iVar2 = CONCAT22(uVar1,0xffff);
  }
  else if (b_word == a_word) {
    iVar2 = (uint)uVar1 << 0x10;
    i = 1;
    puVar3 = b;
    puVar4 = a;
    if (1 < nwords) {
      do {
        a_word = puVar4[1];
        b_word = puVar3[1];
        if (b_word < a_word) {
          iVar2 = CONCAT22(uVar1,1);
          break;
        }
        if (b_word != a_word) {
          iVar2 = CONCAT22(uVar1,0xffff);
          break;
        }
        i = i + 1;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      } while (i < nwords);
    }
  }
  else {
    iVar2 = CONCAT22(uVar1,local_20);
  }
  if ((local_24 != 0) && (0 < nwords)) {
    puVar3 = &local_24 + nwords;
    puVar4 = a + nwords + -1;
    for (i = nwords; i != 0; i = i + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + -1;
      puVar4 = puVar4 + -1;
    }
    if (0 < nwords) {
      puVar3 = auStack_14 + nwords;
      puVar4 = b + nwords + -1;
      for (; nwords != 0; nwords = nwords + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + -1;
        puVar4 = puVar4 + -1;
      }
    }
  }
  return iVar2;
#undef local_24
#undef local_20
}



