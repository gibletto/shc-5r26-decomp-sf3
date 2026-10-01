#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_node_alloc_hook
#define g_node_alloc_hook (*(unsigned char * *)(g_sd + 0x1e4ec))
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))
#undef g_tree_in_file
#define g_tree_in_file (*(FILE * *)(g_sd + 0x26eec))


// entry: 0041ef30
// name : load_inline_bodies
// size : 519
// sig  : void load_inline_bodies(void)


int __cdecl load_inline_bodies(void)

{
  il_node *tree;
  inline_body *body;
  int nparams;
  short *params;
  int loaded;
  uint count;
  byte flags;
  undefined4 *rec;
  
  g_node_alloc_hook = alloc_inline_node;
  count = g_options->node_pool_size;
  if (0x13b13b1 < count) {
    count = 0x13b13b1;
  }
  loaded = 0;
  allocate_il_node_block(count);
  rec = g_options->inline_records;
  do {
    if (rec == (undefined4 *)0x0) {
LAB_0041f115:
      if (loaded == 0) {
        g_inline_flags = g_inline_flags & 0xfd;
      }
      stock_fseek(g_tree_in_file,0,0);
      return;
    }
    stock_fseek(g_tree_in_file,rec[1],0);
    tree = read_il_node();
    if (tree == (il_node *)0x0) {
      if ((*(byte *)(rec + 3) & 1) == 0) {
        g_symtab[*(short *)((int)rec + 0xe)].no_inline = '\x01';
      }
    }
    else {
      tree = read_il_operands(tree);
      if (tree == (il_node *)0x0) {
        if ((*(byte *)(rec + 3) & 1) == 0) {
          g_symtab[*(short *)((int)rec + 0xe)].no_inline = '\x01';
        }
      }
      else {
        body = stock_calloc(1,0xc);
        g_symtab[tree->symx].inline_body = body;
        if (g_symtab[tree->symx].inline_body == (inline_body *)0x0) {
          flags = *(byte *)(rec + 3);
joined_r0x0041f0ba:
          if ((flags & 1) == 0) {
            g_symtab[*(short *)((int)rec + 0xe)].no_inline = '\x01';
          }
          goto LAB_0041f115;
        }
        (g_symtab[tree->symx].inline_body)->tree = tree;
        g_symtab[tree->symx].inline_flags = *(uchar *)(rec + 3);
        nparams = (int)*(char *)((int)g_symtab[tree->symx].info + 6);
        if (0 < nparams) {
          params = stock_calloc(1,nparams * 2 + 2);
          if (params == (short *)0x0) {
            stock_free(g_symtab[tree->symx].inline_body);
            g_symtab[tree->symx].inline_body = (inline_body *)0x0;
            flags = *(byte *)(rec + 3);
            goto joined_r0x0041f0ba;
          }
          order_params_stack_then_register((int)tree->symx,params);
          (g_symtab[tree->symx].inline_body)->params = params;
        }
        loaded = loaded + 1;
      }
    }
    rec = (undefined4 *)*rec;
  } while( true );
}



