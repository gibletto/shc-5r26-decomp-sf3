#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef DAT_00434bd4
#define DAT_00434bd4 (*(char *)(g_sd + 0x2bd4))
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 00408d60
// name : dump_leaf_table
// size : 519
// sig  : void dump_leaf_table(void)


int __cdecl dump_leaf_table(void)

{
  unsigned char _frec_10[16];
#define name_buf (*(undefined4 *)(_frec_10 + 0))
#define local_c (*(char (*)[12])(_frec_10 + 4))
  byte len;
  int leafno;
  uchar *flag_ptr;
  int symno;
  
  FID_conflict__wprintf(s_____LEAF_TABLE_____00434c48);
  leafno = 1;
  FID_conflict__wprintf(s__________________________________00434c10);
  FID_conflict__wprintf(s___No___id_name__symno_flag__gen___00434bd8);
  if (0 < g_leaf_count) {
    flag_ptr = &g_leaf_table[1].flag;
    do {
      FID_conflict__wprintf(s__________________________________00434c10);
      symno = (int)*(short *)(flag_ptr + -2);
      if (symno < 1) {
        name_buf = g_str_temp_upper;
        local_c[0] = DAT_00434bd4;
        _sprintf(local_c,&g_str_percent_d,-symno);
      }
      else {
        len = g_symtab[symno].name_len;
        if (0xc < len) {
          len = 0xd;
        }
        stock_strncpy((char *)&name_buf,g_symtab[symno].name,(uint)len);
        local_c[len - 4] = '\0';
      }
      FID_conflict__wprintf
                (s___4d____13s___5d__04X__08lX__08l_00434ba8,leafno,&name_buf,symno,
                 (int)*(short *)flag_ptr,((leaf *)(flag_ptr + -0xe))->gen,*(uint **)(flag_ptr + -10)
                );
      if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 8) != 0) {
        FID_conflict__wprintf(s_flag___0_00434b9c);
        if ((*flag_ptr & 0x20) != 0) {
          FID_conflict__wprintf(s___LF_NODEF_00434b90);
        }
        if ((*flag_ptr & 0x10) != 0) {
          FID_conflict__wprintf(s___LF_INDVAR_00434b80);
        }
        if ((*flag_ptr & 8) != 0) {
          FID_conflict__wprintf(s___LF_EXPVOL_00434b70);
        }
        if ((*flag_ptr & 4) != 0) {
          FID_conflict__wprintf(s___LF_IMPVOL_00434b60);
        }
        if ((*flag_ptr & 2) != 0) {
          FID_conflict__wprintf(s___LF_CNDASS_00434b50);
        }
        if ((*flag_ptr & 1) != 0) {
          FID_conflict__wprintf(s___LF_STATIC_00434b40);
        }
        FID_conflict__wprintf(&g_str_semicolon_newline);
        FID_conflict__wprintf(s_lastnd___00434b30);
        if (*(il_node **)(flag_ptr + -6) == (il_node *)0x0) {
          FID_conflict__wprintf(s_NULL_00434b28);
        }
        else {
          FID_conflict__wprintf(&g_str_newline);
          dump_tree_rec(*(il_node **)(flag_ptr + -6),0);
        }
        if (((leaf *)(flag_ptr + -0xe))->gen != (uint *)0x0) {
          dump_bitset(((leaf *)(flag_ptr + -0xe))->gen,8,s_str_00434b1c);
        }
        if (*(uint **)(flag_ptr + -10) != (uint *)0x0) {
          dump_bitset(*(uint **)(flag_ptr + -10),0x10,s_str_00434b10);
        }
      }
      flag_ptr = flag_ptr + 0x10;
      leafno = leafno + 1;
    } while (leafno <= g_leaf_count);
  }
  FID_conflict__wprintf(s__________________________________00434c10);
  return;
#undef name_buf
#undef local_c
}



