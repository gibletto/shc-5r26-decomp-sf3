#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))
#undef g_func_node
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_reg_file
#define g_reg_file (*(FILE * *)(g_sd + 0x1e72c))


// entry: 00413aa0
// name : write_register_allocation_table
// size : 681
// sig  : void write_register_allocation_table(void)


int __cdecl write_register_allocation_table(void)

{
  unsigned char _frec_5[5];
#define type_byte (*(char *)(_frec_5 + 0))
#define lreg_no (*(ushort *)(_frec_5 + 1))
#define preg (*(ushort *)(_frec_5 + 3))
  bool bVar1;
  int node_addr;
  uint got;
  byte kind2;
  lreg **slot;
  int i;
  short unaff_retaddr;
  void *chain;
  short kind;
  lreg *lr;
  
  set_expression_life();
  write_reg_header(g_func_node->symx,1,1);
  if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 3) != 0) {
    FID_conflict__wprintf(s_____REGISTER_ALLOCCATION_TABLE___00435544);
    FID_conflict__wprintf(s________________________0043552c);
    FID_conflict__wprintf(s__lregno_pregno__type___00435514);
    FID_conflict__wprintf(s________________________0043552c);
  }
  i = 1;
  if (0 < g_lreg_count) {
    slot = g_lreg_table;
    do {
      slot = slot + 1;
      lr = *slot;
      if ((lr->set != 3) && (lr->pregno != 0)) {
        lreg_no = lr->lregno;
        chain = lr->chain;
        if (lr->set == 1) {
          node_addr = *(int *)((int)chain + 0x10);
        }
        else {
          node_addr = *(int *)(*(int *)((int)chain + 8) + 8);
        }
        preg = lr->pregno;
        if ((short)preg < 1) {
          bVar1 = false;
        }
        else {
          bVar1 = false;
          if ((lr->set == 0) && ((kind = *(short *)lr->chain, kind == 1 || (kind == 4)))) {
            bVar1 = true;
          }
          if (g_options->cpu == 4) {
            kind2 = *(byte *)(node_addr + 3) & 0xf8;
            if ((kind2 != 0x30) || (bVar1)) {
              if ((kind2 != 0x28) || (bVar1)) {
                preg = (ushort)*(byte *)((short)preg + -1 + g_preg_map_general);
              }
              else {
                preg = (ushort)*(byte *)((short)preg + -1 + g_preg_map_float);
              }
            }
            else {
              preg = (ushort)*(byte *)((short)preg + -1 + g_preg_map_double);
            }
          }
          else if ((((g_options->cpu != 2) || (g_options->fpu_mode != '\x03')) ||
                   ((*(byte *)(node_addr + 3) & 0xf8) != 0x28)) || (bVar1)) {
            preg = (ushort)*(byte *)((short)preg + -1 + g_preg_map_general);
          }
          else {
            preg = (ushort)*(byte *)((short)preg + -1 + g_preg_map_float);
          }
        }
        type_byte = *(char *)(node_addr + 3);
        if (((g_options->cpu == 2) && (g_options->fpu_mode == '\x03')) &&
           (((*(byte *)(node_addr + 3) & 0xf8) == 0x28 && (bVar1)))) {
          type_byte = '@';
        }
        if (((g_options->cpu == 4) && ((*(byte *)(node_addr + 3) & 0xe0) == 0x20)) && (bVar1)) {
          type_byte = '@';
        }
        got = write_bytes(g_reg_file,(char *)&lreg_no,4);
        if (got == 0xffffffff) {
          fatal_error(0xce7);
        }
        got = write_bytes(g_reg_file,&type_byte,1);
        if (got == 0xffffffff) {
          fatal_error(0xce7);
        }
        write_lreg_symbols(*slot);
        write_lreg_expression_ranges(*slot);
        if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 3) != 0) {
          FID_conflict__wprintf
                    (s___6d__6d__6X__00435504,(int)(short)lreg_no,(int)(short)preg,
                     (int)unaff_retaddr);
          FID_conflict__wprintf(s________________________0043552c);
        }
      }
      i = i + 1;
    } while (i <= g_lreg_count);
  }
  write_reg_trailer(g_func_node->symx);
  return;
#undef type_byte
#undef lreg_no
#undef preg
}



