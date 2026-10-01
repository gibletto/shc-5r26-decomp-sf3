#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_extra_symbol_blocks
#define g_extra_symbol_blocks (*(short * *)(g_sd + 0x1c9c))


// entry: 0040a760
// name : create_symbol_record
// size : 245
// sig  : symbol * create_symbol_record(char type, char flags, short number)


symbol * __cdecl create_symbol_record(char type,char flags,short number)

{
  short *block;
  void *new_block;
  int iVar1;
  short *wp;
  symbol *chain;
  symbol *chain_next;
  symbol *sym;
  
  if (g_extra_symbol_blocks == (short *)0x0) {
    block = stock_malloc(0x588);
    g_extra_symbol_blocks = block;
    if (block == (short *)0x0) {
      report_compiler_message(0,0,0xbcd,(char *)0x0);
    }
  }
  else {
    iVar1 = *(int *)(g_extra_symbol_blocks + 2);
    block = g_extra_symbol_blocks;
    while (iVar1 != 0) {
      block = *(short **)(block + 2);
      iVar1 = *(int *)(block + 2);
    }
    if (*block < 0x20) goto LAB_0040a7ed;
    new_block = stock_malloc(0x588);
    *(void **)(block + 2) = new_block;
    if (new_block == (void *)0x0) {
      report_compiler_message(0,0,0xbcd,(char *)0x0);
    }
    block = *(short **)(block + 2);
  }
  wp = block;
  for (iVar1 = 0x162; iVar1 != 0; iVar1 = iVar1 + -1) {
    wp[0] = 0;
    wp[1] = 0;
    wp = wp + 2;
  }
LAB_0040a7ed:
  sym = (symbol *)(block + *block * 0x16 + 4);
  sym->type = type;
  sym->flags = flags;
  sym->number = number;
  chain = g_symbol_hash[number % 0x3fd];
  if (chain == (symbol *)0x0) {
    g_symbol_hash[number % 0x3fd] = sym;
  }
  else {
    chain_next = chain->hash_next;
    while (chain_next != (symbol *)0x0) {
      chain = chain->hash_next;
      chain_next = chain->hash_next;
    }
    chain->hash_next = sym;
  }
  *block = *block + 1;
  g_extra_symbol_blocks[1] = g_extra_symbol_blocks[1] + 1;
  return sym;
}



