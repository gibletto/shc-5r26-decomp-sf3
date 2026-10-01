#include "decls.h"
#include "imports.h"

// entry: 00430270
// name : compose_type_pieces
// size : 175
// sig  : void __cdecl compose_type_pieces(short *count,char *out)


int __cdecl compose_type_pieces(short *count,char *out)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  short i;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  
  iVar2 = (int)*count;
  if (((-1 < iVar2 + -2) && (*(short *)(&DAT_0044f748 + iVar2 * 8) == 2)) &&
     ((short)(&g_demangle_placeholder_name_pool_used)[iVar2 * 2] == 7)) {
    g_demangle_type_pieces[iVar2].text = *(char **)(&DAT_0044f74c + iVar2 * 8);
    *(undefined4 **)(&DAT_0044f74c + *count * 8) = &s_space;
    *count = *count + 1;
  }
  i = *count;
  if (0 < i) {
    do {
      uVar3 = 0xffffffff;
      pcVar5 = *(char **)(&DAT_0044f74c + i * 8);
      do {
        pcVar7 = pcVar5;
        if (uVar3 == 0) break;
        uVar3 = uVar3 - 1;
        pcVar7 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar7;
      } while (cVar1 != '\0');
      uVar3 = ~uVar3;
      iVar2 = -1;
      pcVar5 = out;
      do {
        pcVar6 = pcVar5;
        if (iVar2 == 0) break;
        iVar2 = iVar2 + -1;
        pcVar6 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar6;
      } while (cVar1 != '\0');
      pcVar5 = pcVar7 + -uVar3;
      pcVar7 = pcVar6 + -1;
      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)pcVar7 = *(undefined4 *)pcVar5;
        pcVar5 = pcVar5 + 4;
        pcVar7 = pcVar7 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar7 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        pcVar7 = pcVar7 + 1;
      }
      g_demangle_type_pieces[i].kind = 0;
      i = i + -1;
    } while (i != 0);
  }
  *count = 0;
  return;
}
