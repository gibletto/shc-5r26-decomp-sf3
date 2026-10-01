#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x1f99c))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00401000
// name : read_symbol_table
// size : 1124
// sig  : void read_symbol_table(void)


int __cdecl read_symbol_table(void)

{
  unsigned char _frec_a[10];
#define sym_type (*(byte *)(_frec_a + 0))
#define storage_class (*(char *)(_frec_a + 1))
#define skipped (*(char (*)[2])(_frec_a + 2))
#define sym_index (*(short *)(_frec_a + 4))
#define sym_size (*(int *)(_frec_a + 6))
  short sVar1;
  uint uVar2;
  char *pcVar3;
  int iVar4;
  sym_entry *sym;
  uchar type;
  char base;
  label_ref *ref;
  
  g_function_count = 0;
  g_symbol_table = stock_malloc((*(int *)g_request->unknown_0b0 + 0xb7) * 0x30);
  if (g_symbol_table == (sym_entry *)0x0) {
    report_codegen_message(0xbcd,1,0,0,(char *)0x0);
  }
  zero_words((uint *)g_symbol_table,(uint)((*(int *)g_request->unknown_0b0 + 0xb7) * 0x30) >> 2);
  uVar2 = read_count_or_fail((char *)&sym_index,2,g_sym_file);
  sVar1 = (short)uVar2;
  do {
    if (sVar1 == 0) {
      g_request->aux_count = (int)g_function_count;
      return;
    }
    read_bytes_or_fail(&storage_class,1,g_sym_file);
    sym_index = sym_index + 0xb6;
    g_symbol_table[sym_index].flags = g_symbol_table[sym_index].flags | 0x80;
    g_symbol_table[sym_index].sclass = storage_class;
    if ((((storage_class == '\x03') || (storage_class == '\x04')) || (storage_class == '\t')) ||
       (storage_class == '\v')) {
      read_bytes_or_fail(skipped,2,g_sym_file);
    }
    pcVar3 = read_symbol_name();
    g_symbol_table[sym_index].name = pcVar3;
    read_bytes_or_fail((char *)&sym_type,1,g_sym_file);
    g_symbol_table[sym_index].type = sym_type;
    if (((sym_type & 0xe0) == 0x60) || ((sym_type & 0xe0) == 0x80)) {
      read_bytes_or_fail((char *)&sym_size,4,g_sym_file);
      g_symbol_table[sym_index].size = sym_size;
    }
    read_bytes_or_fail((char *)&g_symbol_table[sym_index].byte_03,1,g_sym_file);
    read_bytes_or_fail((char *)&g_symbol_table[sym_index].sym_flags,1,g_sym_file);
    read_bytes_or_fail((char *)&g_symbol_table[sym_index].attr,1,g_sym_file);
    read_bytes_or_fail((char *)&g_symbol_table[sym_index].short_06,2,g_sym_file);
    read_bytes_or_fail(&g_symbol_table[sym_index].reg,1,g_sym_file);
    sVar1 = sym_index;
    sym = g_symbol_table;
    if ((sym_type & 0xf8) == 0x48) {
      if ((storage_class == '\x01') || (storage_class == '\x03')) {
        read_function_info(g_symbol_table + sym_index);
      }
      else {
        iVar4 = lookup_builtin_function_id(g_symbol_table[sym_index].name);
        sym[sVar1].size = iVar4;
        sym = g_symbol_table + sym_index;
        if (sym->size != 0) {
          sym->flags = sym->flags | 0x10;
        }
      }
    }
    else if (((storage_class == '\x01') || (storage_class == '\x03')) &&
            ((g_symbol_table[sym_index].name != (char *)0x0 &&
             (iVar4 = is_unreserved_function_name(sym_index), (short)iVar4 == 0)))) {
      report_codegen_message(0x7e4,1,0,0,g_symbol_table[sym_index].name);
    }
    if (storage_class == '\n') {
      read_scope_info(g_symbol_table + sym_index);
LAB_0040136d:
      if (storage_class != '\t') goto LAB_00401374;
LAB_00401393:
      uVar2 = (uint)sym_index;
      base = g_symbol_table[(uVar2 ^ (int)uVar2 >> 0x1f) - ((int)uVar2 >> 0x1f)].reg;
      if (base == -1) {
        ref = alloc_zeroed(8);
        if (ref == (label_ref *)0x0) {
          report_codegen_message(0xbcd,1,0,0,(char *)0x0);
          goto LAB_0040142d;
        }
        fill_label_ref(ref,sym_index,0);
        sym = g_symbol_table + sym_index;
        base = -1;
        type = '\r';
      }
      else {
        ref = (label_ref *)0x0;
        sym = g_symbol_table + uVar2;
        type = '\x01';
      }
      fill_ea(&sym->storage,type,base,-1,'\0',0,ref);
    }
    else {
      if (storage_class == '\t') {
        read_bytes_or_fail((char *)&g_symbol_table[sym_index].list_10,4,g_sym_file);
        goto LAB_0040136d;
      }
LAB_00401374:
      if ((((storage_class == '\x03') || (storage_class == '\x04')) || (storage_class == '\x01')) ||
         (storage_class == '\x02')) goto LAB_00401393;
    }
LAB_0040142d:
    uVar2 = read_count_or_fail((char *)&sym_index,2,g_sym_file);
    sVar1 = (short)uVar2;
  } while( true );
#undef sym_type
#undef storage_class
#undef skipped
#undef sym_index
#undef sym_size
}



