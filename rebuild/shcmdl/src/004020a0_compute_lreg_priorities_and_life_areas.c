#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_lreg
#define g_current_lreg (*(lreg * *)(g_sd + 0x1e4c4))
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))
#undef g_lreg_list
#define g_lreg_list (*(lreg * *)(g_sd + 0x16264))
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 004020a0
// name : compute_lreg_priorities_and_life_areas
// size : 733
// sig  : void compute_lreg_priorities_and_life_areas(void)


int __cdecl compute_lreg_priorities_and_life_areas(void)

{
  dutbl *chain_node;
  lreg *reg;
  bool bVar1;
  void *pvVar2;
  int depth;
  byte type;
  uint uVar3;
  int priority;
  void *local_4;
  bblock *block;
  byte *block_flag;
  void *du;
  ushort flag;
  int lp;
  il_node *node;
  int outer;
  short symx;
  
  reg = g_lreg_list;
  do {
    if (reg == (lreg *)0x0) {
      return;
    }
    g_current_lreg = reg;
    if (reg->set == 1) {
      sort_web_chain_by_pp(reg);
      du = reg->chain;
      bVar1 = false;
      priority = 0;
      pvVar2 = local_4;
      for (; du != (void *)0x0; du = *(void **)((int)du + 8)) {
        uVar3 = 0;
        node = *(il_node **)((int)du + 0x10);
        if (node->cmnexp == node) {
          uVar3 = (uint)node->refcnt;
        }
        local_4 = du;
        if (((node->op != IL_ID) && (local_4 = pvVar2, **(short **)((int)du + 0xc) != 1)) &&
           (node->op == IL_ASSIGN)) {
          uVar3 = uVar3 + 1;
        }
        if (**(short **)((int)du + 0xc) == 1) {
          bVar1 = true;
        }
        lp = *(int *)(*(short **)((int)du + 0xc) + 0x18);
        if (lp == 0) {
          depth = count_enclosing_loops(node);
          if (depth != 0) {
            depth = depth + 1;
            goto LAB_0040215a;
          }
        }
        else {
          depth = 2;
          outer = *(int *)(lp + 0x14);
          while (outer != 0) {
            depth = depth + 1;
            lp = *(int *)(lp + 0x14);
            outer = *(int *)(lp + 0x14);
          }
LAB_0040215a:
          bVar1 = false;
          uVar3 = depth * uVar3;
        }
        priority = priority + uVar3;
        block_flag = (byte *)(*(int *)((int)du + 0xc) + 100);
        *block_flag = *block_flag | 0x10;
        pvVar2 = local_4;
      }
      node = *(il_node **)((int)pvVar2 + 0x10);
      symx = node->symx;
      if (symx < 0) {
LAB_004022e7:
        if ((g_options->cpu == 4) && ((*(byte *)(*(int *)((int)pvVar2 + 0x10) + 3) & 0xf8) == 0x30))
        {
          priority = priority / 2;
        }
        reg->priori = priority;
        g_first_chain_node = '\x01';
        for (chain_node = reg->chain; block = g_f_chain, chain_node != (dutbl *)0x0;
            chain_node = chain_node->next) {
          compute_web_node_life_area(chain_node);
        }
      }
      else {
        if ((g_symtab[symx].sclass == '\x06') || (g_symtab[symx].sclass == '\b')) {
          priority = priority + 0xffff;
        }
        if ((((symx < 0) || ((g_symtab[symx].sclass != '\a' && (g_symtab[symx].sclass != '\b')))) ||
            (!bVar1)) || (2 < priority)) goto LAB_004022e7;
        if (g_options->cpu == 4) {
          if ((node->type & 0xe0) == 0x20) {
            uVar3 = parameter_register_index(node);
            bVar1 = true;
            if (g_float_arg_regs < (int)uVar3) {
LAB_00402235:
              bVar1 = false;
            }
          }
          else {
            uVar3 = parameter_register_index(node);
            bVar1 = true;
            if (4 < (int)uVar3) goto LAB_00402235;
          }
          if (bVar1) goto LAB_004022e7;
          reg->set = 3;
          block = g_f_chain;
        }
        else {
          if ((g_options->cpu == 2) && (g_options->fpu_mode == '\x03')) {
            if ((node->type & 0xf8) == 0x28) {
              uVar3 = parameter_register_index(node);
              bVar1 = true;
              if (g_float_arg_regs < (int)uVar3) {
LAB_0040228e:
                bVar1 = false;
              }
            }
            else {
              uVar3 = parameter_register_index(node);
              bVar1 = true;
              if (4 < (int)uVar3) goto LAB_0040228e;
            }
            if (bVar1) goto LAB_004022e7;
          }
          if ((g_options->cpu != 2) || (g_options->fpu_mode != '\x03')) {
            type = (*(il_node **)((int)pvVar2 + 0x10))->type;
            if (((type & 0xe0) == 0) || ((type = type & 0xf8, type == 0x40 || (type == 0x28)))) {
              uVar3 = parameter_register_index(*(il_node **)((int)pvVar2 + 0x10));
              bVar1 = true;
              if (4 < (int)uVar3) {
                bVar1 = false;
              }
            }
            else {
              bVar1 = false;
            }
            if (bVar1) goto LAB_004022e7;
          }
          reg->set = 3;
          block = g_f_chain;
        }
      }
      for (; local_4 = pvVar2, block != (bblock *)0x0; block = block->f_next) {
        flag = block->flag;
        block->flag = flag & 0xffef;
        block->flag = flag & 0xffe7;
      }
    }
    else if (reg->set == 0) {
      compute_const_life_area(reg);
    }
    reg = reg->next;
  } while( true );
}



