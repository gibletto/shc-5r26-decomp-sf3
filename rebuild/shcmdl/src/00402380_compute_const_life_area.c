#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))


// entry: 00402380
// name : compute_const_life_area
// size : 721
// sig  : void compute_const_life_area(lreg * reg)


int __cdecl compute_const_life_area(lreg *reg)

{
  int iVar1;
  int iVar2;
  ushort start_pp;
  ushort end_pp;
  il_node *piVar3;
  undefined4 *puVar4;
  il_node *piVar5;
  bblock *block;
  int *last_use;
  short sVar6;
  void *cdata;
  char *dom_node;
  int *next_use;
  block_list *pred;
  char *stmt;
  int *use;
  
  choose_const_dominator(reg);
  cdata = reg->chain;
  sVar6 = *(short *)((int)cdata + 2);
  if (sVar6 == 0) {
    block = g_f_chain;
    if (g_f_chain != (bblock *)0x0) {
      do {
        puVar4 = make_life_area_entry(block->startpp,block->endpp);
        *puVar4 = reg->life;
        reg->life = puVar4;
        block = block->f_next;
      } while (block != (bblock *)0x0);
      return;
    }
  }
  else {
    if (sVar6 == 1) {
      for (puVar4 = *(undefined4 **)((int)cdata + 8); puVar4 != (undefined4 *)0x0;
          puVar4 = (undefined4 *)*puVar4) {
        if (*(int *)((int)reg->chain + 0x14) == puVar4[1]) {
          *(byte *)(puVar4 + 4) = *(byte *)(puVar4 + 4) | 1;
        }
        else {
          for (pred = *(block_list **)(puVar4[1] + 8); pred != (block_list *)0x0; pred = pred->next)
          {
            mark_const_uses_on_paths(pred->block,pred,reg);
          }
        }
      }
      for (iVar2 = *(int *)((int)reg->chain + 0x14); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x20)) {
        *(byte *)(iVar2 + 0x65) = *(byte *)(iVar2 + 0x65) & 0xfd;
      }
      use = *(int **)((int)reg->chain + 8);
      do {
        if (use == (int *)0x0) {
          for (iVar2 = *(int *)((int)reg->chain + 0x14); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x20))
          {
            *(byte *)(iVar2 + 0x65) = *(byte *)(iVar2 + 0x65) & 0xfd;
          }
          cdata = reg->chain;
          iVar2 = *(int *)((int)cdata + 0x18);
          if (iVar2 == 0) {
            sVar6 = *(short *)(*(int *)((int)cdata + 0x14) + 0x5a);
            start_pp = *(ushort *)(*(int *)((int)cdata + 0x14) + 0x58);
          }
          else {
            start_pp = *(ushort *)(iVar2 + 0x5e);
            while ((start_pp & 0x200) == 0) {
              iVar2 = *(int *)(iVar2 + 0x10);
              start_pp = *(ushort *)(iVar2 + 0x5e);
            }
            iVar1 = *(int *)(iVar2 + 0x14);
            while (iVar1 != 0) {
              iVar2 = *(int *)(iVar2 + 0x14);
              iVar1 = *(int *)(iVar2 + 0x14);
            }
            sVar6 = *(short *)(*(int *)((int)cdata + 0x14) + 0x5a);
            start_pp = *(ushort *)(iVar2 + 0x44);
          }
          puVar4 = make_life_area_entry(start_pp,sVar6);
          *puVar4 = reg->life;
          reg->life = puVar4;
          return;
        }
        last_use = use;
        if (*(int *)((int)reg->chain + 0x14) != use[1]) {
          for (pred = *(block_list **)(use[1] + 8); pred != (block_list *)0x0; pred = pred->next) {
            extend_const_life_area_backward(pred->block,pred,reg);
          }
          piVar3 = (il_node *)use[2];
          if (piVar3->op == IL_CONST) {
            piVar5 = piVar3->refchn;
            if (piVar3->refchn == (il_node *)0x0) {
              piVar5 = piVar3;
            }
            if (*use != 0) {
              do {
                next_use = (int *)*last_use;
                if (next_use[1] != use[1]) break;
                piVar3 = ((il_node *)next_use[2])->refchn;
                if (piVar3 == (il_node *)0x0) {
                  piVar3 = (il_node *)next_use[2];
                }
                if (piVar5->pp < piVar3->pp) {
                  piVar5 = piVar3;
                }
                last_use = next_use;
              } while (*next_use != 0);
            }
          }
          else {
            iVar2 = *use;
            while ((iVar2 != 0 && (next_use = (int *)*last_use, last_use[1] == next_use[1]))) {
              iVar2 = *next_use;
              last_use = next_use;
            }
            piVar5 = ((il_node *)last_use[2])->refchn;
            if (piVar5 == (il_node *)0x0) {
              piVar5 = (il_node *)last_use[2];
            }
          }
          iVar2 = *use;
          while ((iVar2 != 0 && (*(int *)(*use + 4) == use[1]))) {
            use[3] = (int)piVar5;
            use = (int *)*use;
            iVar2 = *use;
          }
          use[3] = (int)piVar5;
          start_pp = statement_pp(piVar5);
          puVar4 = make_life_area_entry(*(ushort *)(last_use[1] + 0x58),start_pp);
          *puVar4 = reg->life;
          reg->life = puVar4;
        }
        use = (int *)*last_use;
      } while( true );
    }
    if (sVar6 != 2) {
      return;
    }
    dom_node = *(char **)((int)cdata + 0x18);
    start_pp = *(ushort *)(dom_node + 0x5e);
    stmt = dom_node;
    while ((start_pp & 0x200) == 0) {
      stmt = *(char **)(stmt + 0x10);
      start_pp = *(ushort *)(stmt + 0x5e);
    }
    iVar2 = *(int *)(stmt + 0x14);
    while (iVar2 != 0) {
      stmt = *(char **)(stmt + 0x14);
      iVar2 = *(int *)(stmt + 0x14);
    }
    start_pp = *(ushort *)(stmt + 0x44);
    if (*dom_node == 'q') {
      piVar5 = (il_node *)(*(undefined4 **)((int)cdata + 8))[2];
      piVar3 = piVar5->refchn;
      if (piVar3 == (il_node *)0x0) {
        piVar3 = piVar5;
      }
      for (puVar4 = (undefined4 *)**(undefined4 **)((int)cdata + 8); puVar4 != (undefined4 *)0x0;
          puVar4 = (undefined4 *)*puVar4) {
        piVar5 = ((il_node *)puVar4[2])->refchn;
        if (piVar5 == (il_node *)0x0) {
          piVar5 = (il_node *)puVar4[2];
        }
        if (piVar3->pp < piVar5->pp) {
          piVar3 = piVar5;
        }
      }
    }
    else {
      use = *(int **)((int)cdata + 8);
      iVar2 = *use;
      while (iVar2 != 0) {
        use = (int *)*use;
        iVar2 = *use;
      }
      piVar3 = ((il_node *)use[2])->refchn;
      if (piVar3 == (il_node *)0x0) {
        piVar3 = (il_node *)use[2];
      }
    }
    for (puVar4 = *(undefined4 **)((int)cdata + 8); puVar4 != (undefined4 *)0x0;
        puVar4 = (undefined4 *)*puVar4) {
      puVar4[3] = piVar3;
    }
    end_pp = statement_pp(piVar3);
    puVar4 = make_life_area_entry(start_pp,end_pp);
    *puVar4 = reg->life;
    reg->life = puVar4;
  }
  return;
}



