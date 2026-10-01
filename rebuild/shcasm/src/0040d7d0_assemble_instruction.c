#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 0040d7d0
// name : assemble_instruction
// size : 1339
// sig  : void __cdecl assemble_instruction(psd *rec)


int __cdecl assemble_instruction(psd *rec)

{
  ushort bits;
  short channel;
  byte *alt;
  ushort opcode_word;
  byte format_no;
  
  if (rec->ea1 != (ea *)0x0) {
    check_operand_registers(rec->ea1);
  }
  if (rec->ea2 != (ea *)0x0) {
    check_operand_registers(rec->ea2);
  }
  if (g_opcode_format_index[rec->op].format == 0xff) {
    if (g_opcode_format_index[rec->op].alternatives == (void *)0x0) {
      report_message_at_source_line(rec->filno,(uint)rec->linno,0x1338,(char *)0x0);
    }
    else {
      for (alt = g_opcode_format_index[rec->op].alternatives; *alt != 0xff; alt = alt + 8) {
        if ((((rec->flg & 3) == alt[1]) &&
            ((rec->ea1 == (ea *)0x0 || ((rec->ea1->type & 0x1f) == alt[2])))) &&
           ((rec->ea2 == (ea *)0x0 || ((rec->ea2->type & 0x1f) == alt[3])))) {
          if ((rec->op == OP_LDC) || (rec->op == OP_LDS)) {
            if (rec->ea2->base == alt[4]) break;
          }
          else if (((rec->op != OP_STC) && (rec->op != OP_STS)) || (rec->ea1->base == alt[4]))
          break;
        }
      }
      format_no = *alt;
      if (format_no == 0xff) {
        report_message_at_source_line(rec->filno,(uint)rec->linno,0x1338,(char *)0x0);
      }
    }
  }
  else {
    format_no = g_opcode_format_index[rec->op].format;
  }
  if ((g_current_request->show & 2) != 0) {
    format_listing_location(g_location_counter);
  }
  opcode_word = g_instruction_format_table[format_no].opcode;
  if ((g_current_request->show & 2) == 0) {
    if (g_current_request->code != 1) {
      channel = 2;
    }
  }
  else {
    channel = 3;
  }
  if ((((g_current_request->show & 2) != 0) || (g_current_request->code != 1)) &&
     (put_text_at_column(channel,g_instruction_format_table[format_no].mnemonic,1),
     rec->op == OP_FMAC)) {
    write_register_name(channel,0x10);
    put_char_at_column(channel,',',2);
  }
  if (rec->ea1 != (ea *)0x0) {
    bits = (*(code *)g_instruction_format_table[format_no].encode1)
                     (rec->ea1,(int)g_instruction_format_table[format_no].shift1a,
                      (int)g_instruction_format_table[format_no].shift1b,rec->flg & 3,
                      (int)rec->filno,rec->linno);
    opcode_word = bits | opcode_word;
    if (rec->ea2 != (ea *)0x0) {
      if (((g_current_request->show & 2) != 0) || (g_current_request->code != 1)) {
        put_char_at_column(channel,',',2);
      }
      bits = (*(code *)g_instruction_format_table[format_no].encode2)
                       (rec->ea2,(int)g_instruction_format_table[format_no].shift2a,
                        (int)g_instruction_format_table[format_no].shift2b,rec->flg & 3,
                        (int)rec->filno,rec->linno);
      opcode_word = bits | opcode_word;
    }
  }
  if ((((g_current_request->flags_13c & 4) != 0) && ((g_current_request->show & 2) != 0)) &&
     (g_current_request->optimize != 0)) {
    put_text_at_column(channel,s___Line_0043c7b0,3);
    write_decimal(channel,(uint)rec->linno,3);
  }
  if ((g_current_request->show & 2) != 0) {
    list_object_code_word(opcode_word,0);
  }
  if (((g_current_request->show & 2) != 0) || (g_current_request->code != 1)) {
    if ((rec->op == OP_MOV) && ((rec->ea1->type & 0x1f) == 10)) {
      print_pc_relative_literal_comment(channel,rec);
    }
    flush_output_line(channel);
  }
  if (g_current_request->code == 1) {
    if (g_current_request->endian == '\0') {
      append_object_record_word((int)(short)opcode_word,0x1c);
    }
    else {
      append_object_record_word
                ((uint)CONCAT11((undefined1)opcode_word,(char)(opcode_word >> 8)),0x1c);
    }
  }
  g_location_counter = g_location_counter + 2;
  return;
}
