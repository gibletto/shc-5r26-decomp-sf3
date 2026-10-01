#include "decls.h"
#include "imports.h"
int shcgen_knob_tst_r0(void);
int shcgen_knob_mul_l(void);
void regtrace_site(int site, char *node);
char regtrace_chooser_enter(char ascending, unsigned ret);
void regtrace_chooser_exit(unsigned short p1, unsigned short p2, char p3, short *slots, int chosen);
void regtrace_function(char *rec);
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_records
#define g_aux_records (*(unsigned int * *)(g_sd + 0x1f9bc))
#undef g_current_aux_record
#define g_current_aux_record (*(unsigned int * *)(g_sd + 0x1f950))
#undef g_current_section
#define g_current_section (*(request_section * *)(g_sd + 0x1f9b8))
#undef g_ilb_file
#define g_ilb_file (*(FILE * *)(g_sd + 0x1f980))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00415cd0
// name : generate_ilb_stream
// size : 490
// sig  : void generate_ilb_stream(void)


int __cdecl generate_ilb_stream(void)

{
  short status;
  gen_node *node;
  uint uVar1;
  uint uVar2;
  il_op op;
  
  if (g_function_count != 0) {
    g_current_aux_record = stock_malloc(g_function_count * 0x44);
    g_aux_records = g_current_aux_record;
    if (g_current_aux_record == (uint *)0x0) {
      report_codegen_message(0xbcd,1,0,0,(char *)0x0);
    }
    zero_words(g_current_aux_record,g_function_count * 0x11);
  }
  status = init_gen_node_pool(0x2c,0x800);
  if (status == -1) {
    report_codegen_message(0xbcd,1,0,0,(char *)0x0);
  }
  g_current_section = find_section_record(g_request,1);
  fill_section_record((psd *)&g_psd_scratch,OP_PROGRAM,1);
  emit_psd_record((psd *)&g_psd_scratch,0);
  node = read_ilb_node(g_ilb_file);
  if (node == (gen_node *)0x0) {
    report_codegen_message(0xce6,1,0,0,(char *)0x0);
  }
  op = node->op;
  do {
    if (op == IL_E_FILE) {
      write_asa_record(6,0);
      write_asa_record(0x10,0);
      return;
    }
    node = read_ilb_node(g_ilb_file);
    if (node == (gen_node *)0x0) {
      report_codegen_message(0xce6,1,0,0,(char *)0x0);
    }
    if (node->op == IL_FUNC) {
      uVar1 = (int)node->symx + 0xb6;
      uVar2 = (int)uVar1 >> 0x1f;
      if ((g_symbol_table[(uVar1 ^ uVar2) - uVar2].attr & 0x80) == 0) {
        regtrace_function((char *)node);
        generate_function(node);
LAB_00415e8c:
        unlink_and_free_subtree(node);
      }
      else {
        skip_ilb_function(g_ilb_file);
        unlink_and_free_subtree(node);
        if (*(short *)g_request->unknown_004 != 0) {
          read_reg_file_lreg_table();
        }
      }
    }
    else if (node->op == IL_ASM) {
      fill_psd_record_at_line
                ((psd *)&g_psd_scratch,OP_NON_10,node->filn,node->line,node->val,node->val2);
      emit_psd_record((psd *)&g_psd_scratch,0);
      goto LAB_00415e8c;
    }
    op = node->op;
  } while( true );
}



