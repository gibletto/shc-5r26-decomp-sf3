#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef PTR_s_DUMMY_00426c68
#define PTR_s_DUMMY_00426c68 (*(unsigned char * *)(g_sd + 0x2c68))


// entry: 00412460
// name : dump_node_list_debug
// size : 368
// sig  : void dump_node_list_debug(code_node * list)


int __cdecl dump_node_list_debug(code_node *list)

{
  psd *rec;
  int node_no;
  int rec_no;
  int block_no;
  code_node *node;
  
  block_no = 1;
  for (; list != (code_node *)0x0; list = list->next_block) {
    node_no = 1;
    _printf(s_Base_Next_Block______d_____00427158,block_no);
    for (node = list; node != (code_node *)0x0; node = node->next) {
      rec = node->psd;
      rec_no = 1;
      _printf(s_Base_Next_Node______d_____00427138,node_no);
      do {
        _printf(s_PSEUDO_CODE_TABLE_DUMP___________00427104,rec_no);
        _printf(s_str_004270e8,(&PTR_s_DUMMY_00426c68)[rec->op]);
        _printf(s___psdflg__x_004270d8,(int)rec->flg);
        _printf(s___psdmisc__x_004270c8,(int)rec->misc);
        _printf(s___psdtmp__x_004270b8,(int)rec->tmp);
        _printf(s_psdsptravel__x_004270a0,rec->sptravel);
        _printf(s___psdexpno__d_00427090,rec->expno);
        switch(rec->op) {
        case OP_DUMMY:
          break;
        default:
          _printf(s_psdfilno__d_0042707c,(int)rec->filno);
          _printf(s___psdlinno__d_0042706c,(uint)rec->linno);
          dump_psd_operands(rec);
          break;
        case OP_CASEJMP:
          dump_casejmp_record(rec);
          break;
        case OP_CTBL:
        case OP_CENT:
          dump_case_table_record(rec);
          break;
        case OP_LABEL:
        case OP_CLABEL:
        case OP_DLABEL:
        case OP_FLABEL:
          dump_label_record(rec);
          break;
        case OP_LINE:
          dump_line_record(rec);
        }
        rec = rec + 1;
        rec_no = rec_no + 1;
      } while (rec_no < 0x10);
      node_no = node_no + 1;
    }
    block_no = block_no + 1;
  }
  return;
}



