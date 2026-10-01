#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_register_names
#define g_register_names (*(unsigned char * *)(g_sd + 0x3cc8))


// entry: 00407518
// name : describe_superscalar_window_entry
// size : 14420
// sig  : void describe_superscalar_window_entry(void)


int __cdecl describe_superscalar_window_entry(void)

{
  unsigned char _frec_b4[180];
#define size_code (*(char *)(_frec_b4 + 0))
#define expr_buf (*(uint (*)[16])(_frec_b4 + 4))
#define defs_buf (*(uint (*)[16])(_frec_b4 + 68))
#define cur_op (*(ushort *)(_frec_b4 + 132))
#define issue_grp (*(char *)(_frec_b4 + 136))
#define vec_reg (*(char *)(_frec_b4 + 140))
#define dest_kind (*(char *)(_frec_b4 + 144))
#define dest_reg (*(reg *)(_frec_b4 + 148))
#define i (*(char *)(_frec_b4 + 152))
#define cur_entry (*(superscalar_entry * *)(_frec_b4 + 156))
#define source_reg (*(reg *)(_frec_b4 + 164))
#define access_bytes (*(undefined1 *)(_frec_b4 + 168))
#define source_kind (*(char *)(_frec_b4 + 172))
  int entry_no;
  
  for (i = '\0'; i < '@'; i = i + '\x01') {
    *(undefined1 *)((int)defs_buf + (int)i) = 0;
    *(undefined1 *)((int)expr_buf + (int)i) = 0;
  }
  entry_no = (int)g_superscalar_current_entry;
  cur_entry = g_superscalar_window + entry_no;
  cur_op = (ushort)(cur_entry->rec).op;
  source_reg = g_superscalar_window[g_superscalar_current_entry].src_reg;
  source_kind = g_superscalar_window[g_superscalar_current_entry].src_kind;
  dest_reg = g_superscalar_window[g_superscalar_current_entry].dst_reg;
  dest_kind = g_superscalar_window[g_superscalar_current_entry].dst_kind;
  if ((g_superscalar_window[entry_no].rec.flg & 3) == 2) {
    size_code = '\x03';
    access_bytes = 4;
  }
  else if ((g_superscalar_window[entry_no].rec.flg & 3) == 1) {
    access_bytes = 2;
    size_code = '\x02';
  }
  else {
    access_bytes = 1;
    size_code = '\x01';
  }
  if ((cur_op == 0xb3) || (cur_op == 0xb4)) {
    add_superscalar_entry_read_register('h');
    add_superscalar_entry_written_register(source_reg);
    set_superscalar_entry_timing('\0','\a',1,defs_buf,expr_buf);
  }
  else if (cur_op == 0xb0) {
    if (source_kind == '\x04') {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_read_register('h');
      add_superscalar_entry_written_register(source_reg);
      add_superscalar_entry_written_register(dest_reg);
      stock_memcpy(defs_buf,(&g_register_names)[dest_reg],5);
      stock_strcat(defs_buf,(uint *)&s_eq_at_lp_0043c508);
      stock_strcat(defs_buf,(uint *)(&g_register_names)[source_reg]);
      stock_strcat(defs_buf,(uint *)&s_rp_colon_0043c50c);
      stock_strcat(defs_buf,(uint *)(&g_register_names)[source_reg]);
      stock_strcat(defs_buf,(uint *)&s_eq_0043c510);
      stock_strcat(defs_buf,(uint *)(&g_register_names)[source_reg]);
      stock_strcat(defs_buf,(uint *)&s_plus_8_0043c514);
      set_superscalar_entry_timing('\x02','\f',0,defs_buf,expr_buf);
    }
    else if (source_kind == '\x02') {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_read_register('h');
      add_superscalar_entry_written_register(dest_reg);
      stock_memcpy(expr_buf,(&g_register_names)[dest_reg],5);
      stock_strcat(expr_buf,(uint *)&s_eq_at_lp_0043c518);
      stock_strcat(expr_buf,(uint *)(&g_register_names)[source_reg]);
      stock_strcat(expr_buf,(uint *)&s_rp_0043c51c);
      set_superscalar_entry_timing('\x02','\f',0,defs_buf,expr_buf);
    }
    else if (source_kind == '\t') {
      add_superscalar_entry_read_register('\0');
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_read_register('h');
      add_superscalar_entry_written_register(dest_reg);
      stock_memcpy(expr_buf,(&g_register_names)[dest_reg],5);
      stock_strcat(expr_buf,(uint *)s____R0__0043c520);
      stock_strcat(expr_buf,(uint *)(&g_register_names)[source_reg]);
      stock_strcat(expr_buf,(uint *)&s_rp_0043c528);
      set_superscalar_entry_timing('\x02','\f',0,defs_buf,expr_buf);
    }
    else if (dest_kind == '\x03') {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_read_register(dest_reg);
      add_superscalar_entry_read_register('h');
      add_superscalar_entry_written_register(dest_reg);
      stock_memcpy(defs_buf,(&g_register_names)[dest_reg],5);
      stock_strcat(defs_buf,(uint *)&s_eq_0043c52c);
      stock_strcat(defs_buf,(uint *)(&g_register_names)[dest_reg]);
      stock_strcat(defs_buf,(uint *)s__8____0043c530);
      stock_strcat(defs_buf,(uint *)(&g_register_names)[dest_reg]);
      stock_strcat(defs_buf,(uint *)&s_rp_eq_0043c538);
      stock_strcat(defs_buf,(uint *)(&g_register_names)[source_reg]);
      set_superscalar_entry_timing('\x01','\x11',0,defs_buf,expr_buf);
    }
    else if (dest_kind == '\x02') {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_read_register(dest_reg);
      add_superscalar_entry_read_register('h');
      stock_memcpy(expr_buf,&s_at_lp_0043c53c,2);
      stock_strcat(expr_buf,(uint *)(&g_register_names)[dest_reg]);
      stock_strcat(expr_buf,(uint *)&s_rp_eq_0043c540);
      stock_strcat(expr_buf,(uint *)(&g_register_names)[source_reg]);
      set_superscalar_entry_timing('\x01','\x11',5,defs_buf,expr_buf);
    }
    else if (dest_kind == '\t') {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_read_register('\0');
      add_superscalar_entry_read_register('h');
      add_superscalar_entry_read_register(dest_reg);
      stock_memcpy(expr_buf,s___R0__0043c544,5);
      stock_strcat(expr_buf,(uint *)(&g_register_names)[dest_reg]);
      stock_strcat(expr_buf,(uint *)&s_rp_eq_0043c54c);
      stock_strcat(expr_buf,(uint *)(&g_register_names)[source_reg]);
      set_superscalar_entry_timing('\x01','\x11',5,defs_buf,expr_buf);
    }
    else {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_read_register('h');
      add_superscalar_entry_written_register(dest_reg);
      stock_memcpy(expr_buf,(&g_register_names)[dest_reg],5);
      stock_strcat(expr_buf,(uint *)&s_eq_0043c550);
      stock_strcat(expr_buf,(uint *)(&g_register_names)[source_reg]);
      set_superscalar_entry_timing('\0','\a',0,defs_buf,expr_buf);
    }
  }
  else if (cur_op == 0xdf) {
    add_superscalar_entry_read_register(source_reg);
    add_superscalar_entry_read_register('h');
    add_superscalar_entry_written_register('g');
    set_superscalar_entry_timing('\0','\a',0,defs_buf,expr_buf);
  }
  else if (cur_op == 0xde) {
    add_superscalar_entry_read_register('g');
    add_superscalar_entry_read_register('h');
    add_superscalar_entry_written_register(dest_reg);
    set_superscalar_entry_timing('\0','\a',0,defs_buf,expr_buf);
  }
  else if (cur_op == 0xd2) {
    add_superscalar_entry_read_register(source_reg);
    add_superscalar_entry_read_register('h');
    add_superscalar_entry_written_register(source_reg);
    set_superscalar_entry_timing('\0','\a',1,defs_buf,expr_buf);
  }
  else if (cur_op == 0xb8) {
    add_superscalar_entry_read_register(source_reg);
    add_superscalar_entry_read_register(dest_reg);
    add_superscalar_entry_read_register('h');
    add_superscalar_entry_written_register(dest_reg);
    if ((source_reg < REG_FR0) || (REG_FR15 < source_reg)) {
      set_superscalar_entry_timing('\t','\x02',0xb,defs_buf,expr_buf);
    }
    else {
      set_superscalar_entry_timing('\x04','\x02',0xb,defs_buf,expr_buf);
    }
  }
  else if ((cur_op == 0xc0) || (cur_op == 0xc1)) {
    add_superscalar_entry_read_register(source_reg);
    add_superscalar_entry_read_register(dest_reg);
    add_superscalar_entry_read_register('h');
    add_superscalar_entry_written_register('m');
    if ((source_reg < REG_FR0) || (REG_FR15 < source_reg)) {
      set_superscalar_entry_timing('\x05','\x02',0xb,defs_buf,expr_buf);
    }
    else {
      set_superscalar_entry_timing('\x04','\x02',9,defs_buf,expr_buf);
    }
  }
  else if ((cur_op == 0xb5) || (cur_op == 0xb6)) {
    add_superscalar_entry_read_register(source_reg);
    add_superscalar_entry_read_register('h');
    add_superscalar_entry_written_register(dest_reg);
    set_superscalar_entry_timing('\x05','\x02',9,defs_buf,expr_buf);
  }
  else if (cur_op == 0xbe) {
    add_superscalar_entry_read_register(source_reg);
    add_superscalar_entry_read_register(dest_reg);
    add_superscalar_entry_read_register('h');
    add_superscalar_entry_written_register(dest_reg);
    if ((source_reg < REG_FR0) || (REG_FR15 < source_reg)) {
      set_superscalar_entry_timing('\x1a','\x02',0x15,defs_buf,expr_buf);
    }
    else {
      set_superscalar_entry_timing('\r','\x02',0x13,defs_buf,expr_buf);
    }
  }
  else if (cur_op == 0xdc) {
    add_superscalar_entry_read_register('g');
    add_superscalar_entry_read_register('h');
    add_superscalar_entry_written_register(dest_reg);
    if ((source_reg < REG_FR0) || (REG_FR15 < source_reg)) {
      set_superscalar_entry_timing('\x05','\x02',0xb,defs_buf,expr_buf);
    }
    else {
      set_superscalar_entry_timing('\x04','\x02',0xb,defs_buf,expr_buf);
    }
  }
  else if (cur_op == 0xcc) {
    add_superscalar_entry_read_register(source_reg);
    add_superscalar_entry_read_register(dest_reg);
    add_superscalar_entry_read_register('\x10');
    add_superscalar_entry_read_register('h');
    add_superscalar_entry_written_register(dest_reg);
    set_superscalar_entry_timing('\x04','\x02',0xb,defs_buf,expr_buf);
  }
  else if (cur_op == 0xbc) {
    add_superscalar_entry_read_register(source_reg);
    add_superscalar_entry_read_register(dest_reg);
    add_superscalar_entry_read_register('h');
    add_superscalar_entry_written_register(dest_reg);
    if ((source_reg < REG_FR0) || (REG_FR15 < source_reg)) {
      set_superscalar_entry_timing('\t','\x02',0xf,defs_buf,expr_buf);
    }
    else {
      set_superscalar_entry_timing('\x04','\x02',0xb,defs_buf,expr_buf);
    }
  }
  else if (cur_op == 0xd0) {
    add_superscalar_entry_read_register(source_reg);
    add_superscalar_entry_read_register('h');
    add_superscalar_entry_written_register(source_reg);
    set_superscalar_entry_timing('\0','\a',1,defs_buf,expr_buf);
  }
  else if (cur_op == 0xd4) {
    add_superscalar_entry_read_register(source_reg);
    add_superscalar_entry_read_register('h');
    add_superscalar_entry_written_register(source_reg);
    if ((source_reg < REG_FR0) || (REG_FR15 < source_reg)) {
      set_superscalar_entry_timing('\x19','\x02',0x14,defs_buf,expr_buf);
    }
    else {
      set_superscalar_entry_timing('\f','\x02',0x12,defs_buf,expr_buf);
    }
  }
  else if (cur_op == 0xba) {
    add_superscalar_entry_read_register(source_reg);
    add_superscalar_entry_read_register(dest_reg);
    add_superscalar_entry_read_register('h');
    add_superscalar_entry_written_register(dest_reg);
    if ((source_reg < REG_FR0) || (REG_FR15 < source_reg)) {
      set_superscalar_entry_timing('\t','\x02',0x10,defs_buf,expr_buf);
    }
    else {
      set_superscalar_entry_timing('\x04','\x02',0xb,defs_buf,expr_buf);
    }
  }
  else if (cur_op == 0xdd) {
    add_superscalar_entry_read_register(source_reg);
    add_superscalar_entry_read_register('h');
    add_superscalar_entry_written_register('g');
    if ((source_reg < REG_FR0) || (REG_FR15 < source_reg)) {
      set_superscalar_entry_timing('\x05','\x02',0xc,defs_buf,expr_buf);
    }
    else {
      set_superscalar_entry_timing('\x04','\x02',0xb,defs_buf,expr_buf);
    }
  }
  else if (cur_op == 0xd6) {
    add_superscalar_entry_read_register(source_reg);
    add_superscalar_entry_read_register(dest_reg);
    add_superscalar_entry_read_register('h');
    vec_reg = dest_reg - REG_FR13;
    add_superscalar_entry_written_register(vec_reg);
    set_superscalar_entry_timing('\x05','\x02',0xc,defs_buf,expr_buf);
  }
  else if (cur_op == 0xee) {
    add_superscalar_entry_written_register('h');
    set_superscalar_entry_timing('\x01','\x02',9,defs_buf,expr_buf);
  }
  else if (cur_op == 0xd8) {
    add_superscalar_entry_read_register(source_reg);
    add_superscalar_entry_read_register(dest_reg);
    add_superscalar_entry_read_register('h');
    add_superscalar_entry_written_register(dest_reg);
    set_superscalar_entry_timing('\b','\x02',0xf,defs_buf,expr_buf);
  }
  else if (cur_op == 0xf1) {
    add_superscalar_entry_read_register(source_reg);
    add_superscalar_entry_read_register('h');
    add_superscalar_entry_written_register(source_reg);
    set_superscalar_entry_timing('\x04','\x02',0xf,defs_buf,expr_buf);
  }
  else if (cur_op == 0xf0) {
    add_superscalar_entry_read_register('g');
    add_superscalar_entry_read_register('h');
    add_superscalar_entry_written_register(dest_reg);
    set_superscalar_entry_timing('\x04','\x02',0xf,defs_buf,expr_buf);
  }
  else if (cur_op == 0x40) {
    if (source_kind == '\a') {
      add_superscalar_entry_written_register(dest_reg);
      stock_memcpy(expr_buf,(&g_register_names)[dest_reg],5);
      stock_strcat(expr_buf,(uint *)&s_eq_IMM_0043c554);
      set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
    }
    else if ((source_kind == '\x01') && (dest_kind == '\x01')) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_written_register(dest_reg);
      stock_memcpy(expr_buf,(&g_register_names)[dest_reg],5);
      stock_strcat(expr_buf,(uint *)&s_eq_0043c55c);
      stock_strcat(expr_buf,(uint *)(&g_register_names)[source_reg]);
      set_superscalar_entry_timing('\0','\x03',1,defs_buf,expr_buf);
    }
    else if ((source_kind == '\x04') && (dest_kind == '\x01')) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_written_register(dest_reg);
      add_superscalar_entry_written_register(source_reg);
      stock_memcpy(defs_buf,(&g_register_names)[dest_reg],5);
      stock_strcat(defs_buf,(uint *)&s_eq_at_lp_0043c560);
      stock_strcat(defs_buf,(uint *)(&g_register_names)[source_reg]);
      stock_strcat(defs_buf,(uint *)&s_rp_colon_0043c564);
      stock_strcat(defs_buf,(uint *)(&g_register_names)[source_reg]);
      if (size_code == '\x03') {
        stock_strcat(defs_buf,(uint *)&s_eq_4_plus_0043c568);
      }
      else if (size_code == '\x02') {
        stock_strcat(defs_buf,(uint *)&s_eq_2_plus_0043c56c);
      }
      else {
        stock_strcat(defs_buf,(uint *)&s_eq_1_plus_0043c570);
      }
      stock_strcat(defs_buf,(uint *)(&g_register_names)[source_reg]);
      stock_strcat(defs_buf,(uint *)&s_colon_0043c574);
      issue_grp = size_code + '\f';
      set_superscalar_entry_timing('\x02',issue_grp,0,defs_buf,expr_buf);
    }
    else if ((source_kind == '\x02') && (dest_kind == '\x01')) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_written_register(dest_reg);
      stock_memcpy(expr_buf,(&g_register_names)[dest_reg],5);
      stock_strcat(expr_buf,(uint *)&s_eq_at_lp_0043c578);
      stock_strcat(expr_buf,(uint *)(&g_register_names)[source_reg]);
      stock_strcat(expr_buf,(uint *)&s_rp_0043c57c);
      issue_grp = size_code + '\f';
      set_superscalar_entry_timing('\x02',issue_grp,0,defs_buf,expr_buf);
    }
    else if ((source_kind == '\t') && (dest_kind == '\x01')) {
      add_superscalar_entry_read_register('\0');
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_written_register(dest_reg);
      stock_memcpy(expr_buf,(&g_register_names)[dest_reg],5);
      stock_strcat(expr_buf,(uint *)s____R0__0043c580);
      stock_strcat(expr_buf,(uint *)(&g_register_names)[source_reg]);
      stock_strcat(expr_buf,(uint *)&s_rp_0043c588);
      issue_grp = size_code + '\f';
      set_superscalar_entry_timing('\x02',issue_grp,0,defs_buf,expr_buf);
    }
    else if (source_kind == '\v') {
      add_superscalar_entry_read_register('b');
      add_superscalar_entry_written_register('\0');
      stock_memcpy(expr_buf,s_R0___DISP_GBR___0043c58c,0xf);
      issue_grp = size_code + '\f';
      set_superscalar_entry_timing('\x02',issue_grp,0,defs_buf,expr_buf);
    }
    else if (source_kind == '\b') {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_written_register(dest_reg);
      stock_memcpy(expr_buf,(&g_register_names)[dest_reg],5);
      stock_strcat(expr_buf,(uint *)s____DISP__0043c59c);
      stock_strcat(expr_buf,(uint *)(&g_register_names)[source_reg]);
      stock_strcat(expr_buf,(uint *)&s_rp_0043c5a8);
      issue_grp = size_code + '\f';
      set_superscalar_entry_timing('\x02',issue_grp,0,defs_buf,expr_buf);
    }
    else if (source_kind == '\n') {
      add_superscalar_entry_read_register('k');
      add_superscalar_entry_written_register(dest_reg);
      stock_memcpy(expr_buf,(&g_register_names)[dest_reg],5);
      stock_strcat(expr_buf,(uint *)s____disp_PC__0043c5ac);
      issue_grp = size_code + '\f';
      set_superscalar_entry_timing('\x02',issue_grp,0,defs_buf,expr_buf);
    }
    else if ((source_kind == '\x01') && (dest_kind == '\x03')) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_read_register(dest_reg);
      add_superscalar_entry_written_register(dest_reg);
      stock_memcpy(defs_buf,(&g_register_names)[dest_reg],5);
      stock_strcat(defs_buf,(uint *)&s_eq_0043c5b8);
      stock_strcat(defs_buf,(uint *)(&g_register_names)[dest_reg]);
      if (size_code == '\x03') {
        stock_strcat(defs_buf,(uint *)s__4_____0043c5bc);
      }
      else if (size_code == '\x02') {
        stock_strcat(defs_buf,(uint *)s__2_____0043c5c4);
      }
      else {
        stock_strcat(defs_buf,(uint *)s__1_____0043c5cc);
      }
      stock_strcat(defs_buf,(uint *)(&g_register_names)[dest_reg]);
      stock_strcat(defs_buf,(uint *)&s_rp_eq_0043c5d4);
      stock_strcat(defs_buf,(uint *)(&g_register_names)[source_reg]);
      issue_grp = size_code + '\x11';
      set_superscalar_entry_timing('\x01',issue_grp,0,defs_buf,expr_buf);
    }
    else if ((source_kind == '\x01') && (dest_kind == '\x02')) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_read_register(dest_reg);
      stock_memcpy(expr_buf,&s_at_lp_0043c5d8,2);
      stock_strcat(expr_buf,(uint *)(&g_register_names)[dest_reg]);
      stock_strcat(expr_buf,(uint *)&s_rp_eq_0043c5dc);
      stock_strcat(expr_buf,(uint *)(&g_register_names)[source_reg]);
      issue_grp = size_code + '\x11';
      set_superscalar_entry_timing('\x01',issue_grp,5,defs_buf,expr_buf);
    }
    else if ((source_kind == '\x01') && (dest_kind == '\t')) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_read_register('\0');
      add_superscalar_entry_read_register(dest_reg);
      stock_memcpy(expr_buf,s___R0__0043c5e0,5);
      stock_strcat(expr_buf,(uint *)(&g_register_names)[dest_reg]);
      stock_strcat(expr_buf,(uint *)&s_rp_eq_0043c5e8);
      stock_strcat(expr_buf,(uint *)(&g_register_names)[source_reg]);
      issue_grp = size_code + '\x11';
      set_superscalar_entry_timing('\x01',issue_grp,5,defs_buf,expr_buf);
    }
    else if ((source_kind == '\x01') && (dest_kind == '\v')) {
      add_superscalar_entry_read_register('\0');
      add_superscalar_entry_read_register('b');
      stock_memcpy(expr_buf,s___DISP_GBR__R0_0043c5ec,0xe);
      issue_grp = size_code + '\x11';
      set_superscalar_entry_timing('\x01',issue_grp,5,defs_buf,expr_buf);
    }
    else if ((source_kind == '\x01') && (dest_kind == '\b')) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_read_register(dest_reg);
      stock_memcpy(expr_buf,s___DISP__0043c5fc,7);
      stock_strcat(expr_buf,(uint *)(&g_register_names)[dest_reg]);
      stock_strcat(expr_buf,(uint *)&s_rp_eq_R0_0043c604);
      issue_grp = size_code + '\x11';
      set_superscalar_entry_timing('\x01',issue_grp,5,defs_buf,expr_buf);
    }
  }
  else if (cur_op == 0x44) {
    add_superscalar_entry_read_register('k');
    add_superscalar_entry_written_register('\0');
    set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
  }
  else if (cur_op == 0x42) {
    add_superscalar_entry_read_register('m');
    add_superscalar_entry_written_register(source_reg);
    set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
  }
  else if (cur_op == 0xa0) {
    add_superscalar_entry_read_register(source_reg);
    set_superscalar_entry_timing('\x01','\a',1,defs_buf,expr_buf);
  }
  else if (cur_op == 0x46) {
    add_superscalar_entry_read_register(source_reg);
    add_superscalar_entry_written_register(dest_reg);
    set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
  }
  else if (cur_op == 0x47) {
    add_superscalar_entry_read_register(source_reg);
    add_superscalar_entry_read_register(dest_reg);
    add_superscalar_entry_written_register(dest_reg);
    set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
  }
  else if (cur_op == 0x61) {
    add_superscalar_entry_read_register(source_reg);
    add_superscalar_entry_read_register(dest_reg);
    add_superscalar_entry_read_register('m');
    add_superscalar_entry_written_register(dest_reg);
    add_superscalar_entry_written_register('m');
    stock_memcpy(defs_buf,(&g_register_names)[dest_reg],5);
    stock_strcat(defs_buf,(uint *)&s_eq_0043c60c);
    stock_strcat(defs_buf,(uint *)(&g_register_names)[source_reg]);
    stock_strcat(defs_buf,(uint *)&s_plus_0043c610);
    stock_strcat(defs_buf,(uint *)(&g_register_names)[dest_reg]);
    set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
  }
  else if (cur_op == 0x62) {
    add_superscalar_entry_read_register(source_reg);
    add_superscalar_entry_read_register(dest_reg);
    add_superscalar_entry_written_register(dest_reg);
    add_superscalar_entry_written_register('m');
    stock_memcpy(defs_buf,(&g_register_names)[dest_reg],5);
    stock_strcat(defs_buf,(uint *)&s_eq_0043c614);
    stock_strcat(defs_buf,(uint *)(&g_register_names)[source_reg]);
    stock_strcat(defs_buf,(uint *)&s_plus_0043c618);
    stock_strcat(defs_buf,(uint *)(&g_register_names)[dest_reg]);
    set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
  }
  else if (cur_op == 0x60) {
    if (source_kind == '\a') {
      add_superscalar_entry_read_register(dest_reg);
      add_superscalar_entry_written_register(dest_reg);
      stock_memcpy(defs_buf,(&g_register_names)[dest_reg],5);
      stock_strcat(defs_buf,(uint *)s__IMM__0043c61c);
      stock_strcat(defs_buf,(uint *)(&g_register_names)[dest_reg]);
      set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
    }
    else {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_read_register(dest_reg);
      add_superscalar_entry_written_register(dest_reg);
      stock_memcpy(defs_buf,(&g_register_names)[dest_reg],5);
      stock_strcat(defs_buf,(uint *)&s_eq_0043c624);
      stock_strcat(defs_buf,(uint *)(&g_register_names)[source_reg]);
      stock_strcat(defs_buf,(uint *)&s_plus_0043c628);
      stock_strcat(defs_buf,(uint *)(&g_register_names)[dest_reg]);
      set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
    }
  }
  else if ((cur_op == 0x55) || (cur_op == 0x56)) {
    add_superscalar_entry_read_register(source_reg);
    add_superscalar_entry_written_register('m');
    set_superscalar_entry_timing('\x01','\x03',1,defs_buf,expr_buf);
  }
  else if ((cur_op < 0x50) || (0x57 < cur_op)) {
    if (cur_op == 0x74) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_read_register(dest_reg);
      add_superscalar_entry_written_register(dest_reg);
      set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
    }
    else if (cur_op == 0x75) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_read_register(dest_reg);
      add_superscalar_entry_written_register('m');
      set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
    }
    else if (cur_op == 0x76) {
      add_superscalar_entry_written_register('m');
      set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
    }
    else if (cur_op == 0x8a) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_written_register(source_reg);
      add_superscalar_entry_written_register('m');
      set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
    }
    else if ((cur_op == 0x7b) || (cur_op == 0x7c)) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_written_register(dest_reg);
      set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
    }
    else if (cur_op == 0x72) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_read_register(dest_reg);
      add_superscalar_entry_read_register('d');
      add_superscalar_entry_read_register('e');
      add_superscalar_entry_written_register(source_reg);
      add_superscalar_entry_written_register(dest_reg);
      add_superscalar_entry_written_register('d');
      add_superscalar_entry_written_register('e');
      set_superscalar_entry_timing('\x04','\x04',3,defs_buf,expr_buf);
    }
    else if ((cur_op == 0x70) || (cur_op == 0x71)) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_read_register(dest_reg);
      add_superscalar_entry_written_register('e');
      set_superscalar_entry_timing('\x04','\x04',3,defs_buf,expr_buf);
    }
    else if ((cur_op == 0x6f) && (size_code == '\x03')) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_read_register(dest_reg);
      add_superscalar_entry_written_register('e');
      set_superscalar_entry_timing('\x04','\x04',3,defs_buf,expr_buf);
    }
    else if (cur_op == 0x78) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_written_register(dest_reg);
      set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
    }
    else if (cur_op == 0x79) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_read_register('m');
      add_superscalar_entry_written_register(dest_reg);
      add_superscalar_entry_written_register('m');
      set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
    }
    else if (cur_op == 99) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_read_register(dest_reg);
      add_superscalar_entry_written_register(dest_reg);
      stock_memcpy(expr_buf,(&g_register_names)[dest_reg],5);
      stock_strcat(expr_buf,(uint *)&s_eq_0043c62c);
      stock_strcat(expr_buf,(uint *)(&g_register_names)[dest_reg]);
      stock_strcat(expr_buf,(uint *)&s_minus_0043c630);
      stock_strcat(expr_buf,(uint *)(&g_register_names)[source_reg]);
      set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
    }
    else if (cur_op == 100) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_read_register(dest_reg);
      add_superscalar_entry_read_register('m');
      add_superscalar_entry_written_register(dest_reg);
      add_superscalar_entry_written_register('m');
      stock_memcpy(expr_buf,(&g_register_names)[dest_reg],5);
      stock_strcat(expr_buf,(uint *)&s_eq_0043c634);
      stock_strcat(expr_buf,(uint *)(&g_register_names)[dest_reg]);
      stock_strcat(expr_buf,(uint *)&s_minus_0043c638);
      stock_strcat(expr_buf,(uint *)(&g_register_names)[source_reg]);
      set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
    }
    else if (cur_op == 0x65) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_read_register(dest_reg);
      add_superscalar_entry_written_register(dest_reg);
      add_superscalar_entry_written_register('m');
      stock_memcpy(expr_buf,(&g_register_names)[dest_reg],5);
      stock_strcat(expr_buf,(uint *)&s_eq_0043c63c);
      stock_strcat(expr_buf,(uint *)(&g_register_names)[dest_reg]);
      stock_strcat(expr_buf,(uint *)&s_minus_0043c640);
      stock_strcat(expr_buf,(uint *)(&g_register_names)[source_reg]);
      set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
    }
    else if ((cur_op == 0x80) && (size_code == '\x01')) {
      add_superscalar_entry_read_register('b');
      add_superscalar_entry_read_register('\0');
      set_superscalar_entry_timing('\x04','\x04',4,defs_buf,expr_buf);
    }
    else if ((cur_op == 0x80) && (size_code != '\x01')) {
      if (source_kind == '\a') {
        add_superscalar_entry_read_register('\0');
        add_superscalar_entry_written_register('\0');
        set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
      }
      else {
        add_superscalar_entry_read_register(source_reg);
        add_superscalar_entry_read_register(dest_reg);
        add_superscalar_entry_written_register(dest_reg);
        set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
      }
    }
    else if ((cur_op == 0x85) && (size_code == '\x01')) {
      add_superscalar_entry_read_register('b');
      add_superscalar_entry_read_register('\0');
      add_superscalar_entry_written_register('m');
      set_superscalar_entry_timing('\x04','\x04',4,defs_buf,expr_buf);
    }
    else if ((cur_op == 0x85) && (size_code != '\x01')) {
      if (source_kind == '\a') {
        add_superscalar_entry_read_register('\0');
        add_superscalar_entry_written_register('m');
        set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
      }
      else {
        add_superscalar_entry_read_register(source_reg);
        add_superscalar_entry_read_register(dest_reg);
        add_superscalar_entry_written_register('m');
        set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
      }
    }
    else if (cur_op == 0x83) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_written_register(dest_reg);
      set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
    }
    else if ((cur_op == 0x81) && (size_code == '\x01')) {
      add_superscalar_entry_read_register('b');
      add_superscalar_entry_read_register('\0');
      set_superscalar_entry_timing('\x04','\x04',4,defs_buf,expr_buf);
    }
    else if ((cur_op == 0x81) && (size_code != '\x01')) {
      if (source_kind == '\a') {
        add_superscalar_entry_read_register('\0');
        add_superscalar_entry_written_register('\0');
        set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
      }
      else {
        add_superscalar_entry_read_register(source_reg);
        add_superscalar_entry_read_register(dest_reg);
        add_superscalar_entry_written_register(dest_reg);
        set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
      }
    }
    else if ((cur_op == 0x86) && (size_code == '\x01')) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_written_register('m');
      set_superscalar_entry_timing('\x05','\x04',4,defs_buf,expr_buf);
    }
    else if ((cur_op == 0x82) && (size_code == '\x01')) {
      add_superscalar_entry_read_register('b');
      add_superscalar_entry_read_register('\0');
      set_superscalar_entry_timing('\x04','\x04',4,defs_buf,expr_buf);
    }
    else if ((cur_op == 0x82) && (size_code != '\x01')) {
      if (source_kind == '\a') {
        add_superscalar_entry_read_register('\0');
        add_superscalar_entry_written_register('\0');
        set_superscalar_entry_timing('\x01','\x01',4,defs_buf,expr_buf);
      }
      else {
        add_superscalar_entry_read_register(source_reg);
        add_superscalar_entry_read_register(dest_reg);
        add_superscalar_entry_written_register(dest_reg);
        set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
      }
    }
    else if ((cur_op == 0x4f) || (cur_op == 0x5f)) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_read_register('m');
      add_superscalar_entry_written_register(source_reg);
      add_superscalar_entry_written_register('m');
      set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
    }
    else if ((cur_op == 0x4e) || (cur_op == 0x5e)) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_written_register(source_reg);
      add_superscalar_entry_written_register('m');
      set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
    }
    else if (cur_op == 0x48) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_read_register(dest_reg);
      add_superscalar_entry_written_register(dest_reg);
      set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
    }
    else if (cur_op == 0x49) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_written_register(source_reg);
      add_superscalar_entry_written_register('m');
      set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
    }
    else if (cur_op == 0x59) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_written_register(source_reg);
      add_superscalar_entry_written_register('m');
      set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
    }
    else if (cur_op == 0x58) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_read_register(dest_reg);
      add_superscalar_entry_written_register(dest_reg);
      set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
    }
    else if (cur_op == 0x4a) {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_written_register(source_reg);
      add_superscalar_entry_written_register('m');
      set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
    }
    else if ((cur_op < 0x4b) || (0x4d < cur_op)) {
      if (cur_op == 0x5a) {
        add_superscalar_entry_read_register(source_reg);
        add_superscalar_entry_written_register(source_reg);
        add_superscalar_entry_written_register('m');
        set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
      }
      else if ((cur_op < 0x5b) || (0x5d < cur_op)) {
        if ((cur_op == 0x90) || (((cur_op == 0x91 || (cur_op == 0x98)) || (cur_op == 0x97)))) {
          add_superscalar_entry_read_register('m');
          for (i = '\0'; i <= g_pipeline_window_last_index; i = i + '\x01') {
            if (g_superscalar_current_entry != i) {
              g_superscalar_window[i].flow_children =
                   g_superscalar_window[i].flow_children |
                   *(uint *)(&g_window_entry_bit_masks + g_superscalar_current_entry * 4);
              g_superscalar_window[i].flow_child_count =
                   g_superscalar_window[i].flow_child_count + '\x01';
              g_superscalar_window[g_superscalar_current_entry].flow_parents =
                   g_superscalar_window[g_superscalar_current_entry].flow_parents |
                   *(uint *)(&g_window_entry_bit_masks + i * 4);
              g_superscalar_window[g_superscalar_current_entry].flow_parent_count =
                   g_superscalar_window[g_superscalar_current_entry].flow_parent_count + '\x01';
            }
          }
          set_superscalar_entry_timing('\x01','\x06',6,defs_buf,expr_buf);
        }
        else if ((cur_op == 0x92) || (cur_op == 0x93)) {
          for (i = '\0'; i <= g_pipeline_window_last_index; i = i + '\x01') {
            if (g_superscalar_current_entry != i) {
              g_superscalar_window[i].flow_children =
                   g_superscalar_window[i].flow_children |
                   *(uint *)(&g_window_entry_bit_masks + g_superscalar_current_entry * 4);
              g_superscalar_window[i].flow_child_count =
                   g_superscalar_window[i].flow_child_count + '\x01';
              g_superscalar_window[g_superscalar_current_entry].flow_parents =
                   g_superscalar_window[g_superscalar_current_entry].flow_parents |
                   *(uint *)(&g_window_entry_bit_masks + i * 4);
              g_superscalar_window[g_superscalar_current_entry].flow_parent_count =
                   g_superscalar_window[g_superscalar_current_entry].flow_parent_count + '\x01';
            }
          }
          set_superscalar_entry_timing('\x02','\x06',6,defs_buf,expr_buf);
        }
        else if ((cur_op == 0x9a) || (cur_op == 0x99)) {
          add_superscalar_entry_read_register(source_reg);
          add_superscalar_entry_read_register('k');
          add_superscalar_entry_written_register('k');
          if (cur_op == 0x99) {
            add_superscalar_entry_written_register('f');
          }
          for (i = '\0'; i <= g_pipeline_window_last_index; i = i + '\x01') {
            if (g_superscalar_current_entry != i) {
              g_superscalar_window[i].flow_children =
                   g_superscalar_window[i].flow_children |
                   *(uint *)(&g_window_entry_bit_masks + g_superscalar_current_entry * 4);
              g_superscalar_window[i].flow_child_count =
                   g_superscalar_window[i].flow_child_count + '\x01';
              g_superscalar_window[g_superscalar_current_entry].flow_parents =
                   g_superscalar_window[g_superscalar_current_entry].flow_parents |
                   *(uint *)(&g_window_entry_bit_masks + i * 4);
              g_superscalar_window[g_superscalar_current_entry].flow_parent_count =
                   g_superscalar_window[g_superscalar_current_entry].flow_parent_count + '\x01';
            }
          }
          set_superscalar_entry_timing('\x03','\x04',6,defs_buf,expr_buf);
        }
        else if (cur_op == 0x94) {
          add_superscalar_entry_read_register(source_reg);
          add_superscalar_entry_written_register('k');
          for (i = '\0'; i <= g_pipeline_window_last_index; i = i + '\x01') {
            if (g_superscalar_current_entry != i) {
              g_superscalar_window[i].flow_children =
                   g_superscalar_window[i].flow_children |
                   *(uint *)(&g_window_entry_bit_masks + g_superscalar_current_entry * 4);
              g_superscalar_window[i].flow_child_count =
                   g_superscalar_window[i].flow_child_count + '\x01';
              g_superscalar_window[g_superscalar_current_entry].flow_parents =
                   g_superscalar_window[g_superscalar_current_entry].flow_parents |
                   *(uint *)(&g_window_entry_bit_masks + i * 4);
              g_superscalar_window[g_superscalar_current_entry].flow_parent_count =
                   g_superscalar_window[g_superscalar_current_entry].flow_parent_count + '\x01';
            }
          }
          set_superscalar_entry_timing('\x03','\x05',6,defs_buf,expr_buf);
        }
        else if (cur_op == 0x95) {
          add_superscalar_entry_read_register(source_reg);
          add_superscalar_entry_read_register('k');
          add_superscalar_entry_written_register('k');
          add_superscalar_entry_written_register('f');
          for (i = '\0'; i <= g_pipeline_window_last_index; i = i + '\x01') {
            if (g_superscalar_current_entry != i) {
              g_superscalar_window[i].flow_children =
                   g_superscalar_window[i].flow_children |
                   *(uint *)(&g_window_entry_bit_masks + g_superscalar_current_entry * 4);
              g_superscalar_window[i].flow_child_count =
                   g_superscalar_window[i].flow_child_count + '\x01';
              g_superscalar_window[g_superscalar_current_entry].flow_parents =
                   g_superscalar_window[g_superscalar_current_entry].flow_parents |
                   *(uint *)(&g_window_entry_bit_masks + i * 4);
              g_superscalar_window[g_superscalar_current_entry].flow_parent_count =
                   g_superscalar_window[g_superscalar_current_entry].flow_parent_count + '\x01';
            }
          }
          set_superscalar_entry_timing('\x03','\x05',6,defs_buf,expr_buf);
        }
        else if (cur_op == 0x96) {
          add_superscalar_entry_read_register('f');
          add_superscalar_entry_written_register('k');
          for (i = '\0'; i <= g_pipeline_window_last_index; i = i + '\x01') {
            if (g_superscalar_current_entry != i) {
              g_superscalar_window[i].flow_children =
                   g_superscalar_window[i].flow_children |
                   *(uint *)(&g_window_entry_bit_masks + g_superscalar_current_entry * 4);
              g_superscalar_window[i].flow_child_count =
                   g_superscalar_window[i].flow_child_count + '\x01';
              g_superscalar_window[g_superscalar_current_entry].flow_parents =
                   g_superscalar_window[g_superscalar_current_entry].flow_parents |
                   *(uint *)(&g_window_entry_bit_masks + i * 4);
              g_superscalar_window[g_superscalar_current_entry].flow_parent_count =
                   g_superscalar_window[g_superscalar_current_entry].flow_parent_count + '\x01';
            }
          }
          set_superscalar_entry_timing('\x03','\x05',6,defs_buf,expr_buf);
        }
        else if (cur_op == 0x9b) {
          add_superscalar_entry_written_register('d');
          add_superscalar_entry_written_register('e');
          set_superscalar_entry_timing('\x03','\x04',2,defs_buf,expr_buf);
        }
        else if (cur_op == 0x8b) {
          add_superscalar_entry_written_register('m');
          set_superscalar_entry_timing('\x01','\x03',1,defs_buf,expr_buf);
        }
        else if ((cur_op == 0x8c) && (source_kind == '\x04')) {
          add_superscalar_entry_read_register(source_reg);
          add_superscalar_entry_written_register(source_reg);
          add_superscalar_entry_written_register(dest_reg);
          if (source_reg == REG_FPUL) {
            set_superscalar_entry_timing('\x03','\x04',1,defs_buf,expr_buf);
          }
          else if (source_reg == REG_PR) {
            set_superscalar_entry_timing('\x03','\x04',2,defs_buf,expr_buf);
          }
          else {
            set_superscalar_entry_timing('\x03','\x04',0,defs_buf,expr_buf);
          }
        }
        else if ((cur_op == 0x8d) && (source_kind == '\x04')) {
          add_superscalar_entry_read_register(source_reg);
          add_superscalar_entry_written_register(source_reg);
          add_superscalar_entry_written_register(dest_reg);
          if (source_reg == REG_FPSCR) {
            set_superscalar_entry_timing('\x03','\x04',1,defs_buf,expr_buf);
          }
          else if (source_reg == REG_PR) {
            set_superscalar_entry_timing('\x03','\x04',2,defs_buf,expr_buf);
          }
          else {
            set_superscalar_entry_timing('\x03','\x04',0,defs_buf,expr_buf);
          }
        }
        else if (cur_op == 0x8c) {
          add_superscalar_entry_read_register(source_reg);
          add_superscalar_entry_written_register(dest_reg);
          set_superscalar_entry_timing('\x03','\x04',1,defs_buf,expr_buf);
        }
        else if (cur_op == 0x8d) {
          add_superscalar_entry_read_register(source_reg);
          add_superscalar_entry_written_register(dest_reg);
          if (dest_reg == REG_FPUL) {
            set_superscalar_entry_timing('\x03','\a',1,defs_buf,expr_buf);
          }
          else {
            set_superscalar_entry_timing('\x03','\x04',1,defs_buf,expr_buf);
          }
        }
        else if (cur_op == 0x88) {
          set_superscalar_entry_timing('\0','\x03',6,defs_buf,expr_buf);
        }
        else if (cur_op == 0x8e) {
          add_superscalar_entry_read_register('q');
          add_superscalar_entry_read_register('r');
          add_superscalar_entry_written_register('a');
          add_superscalar_entry_written_register('k');
          for (i = '\0'; i <= g_pipeline_window_last_index; i = i + '\x01') {
            if (g_superscalar_current_entry != i) {
              g_superscalar_window[i].flow_children =
                   g_superscalar_window[i].flow_children |
                   *(uint *)(&g_window_entry_bit_masks + g_superscalar_current_entry * 4);
              g_superscalar_window[i].flow_child_count =
                   g_superscalar_window[i].flow_child_count + '\x01';
              g_superscalar_window[g_superscalar_current_entry].flow_parents =
                   g_superscalar_window[g_superscalar_current_entry].flow_parents |
                   *(uint *)(&g_window_entry_bit_masks + i * 4);
              g_superscalar_window[g_superscalar_current_entry].flow_parent_count =
                   g_superscalar_window[g_superscalar_current_entry].flow_parent_count + '\x01';
            }
          }
          set_superscalar_entry_timing('\x05','\x04',8,defs_buf,expr_buf);
        }
        else if (cur_op == 0x8f) {
          add_superscalar_entry_written_register('m');
          set_superscalar_entry_timing('\x01','\x03',1,defs_buf,expr_buf);
        }
        else if (cur_op == 0x9f) {
          set_superscalar_entry_timing('\x04','\x04',6,defs_buf,expr_buf);
        }
        else if (cur_op == 0x9c) {
          if (dest_kind == '\x03') {
            add_superscalar_entry_read_register(source_reg);
            add_superscalar_entry_read_register(dest_reg);
            add_superscalar_entry_written_register(dest_reg);
            set_superscalar_entry_timing('\x03','\x04',1,defs_buf,expr_buf);
          }
          else {
            add_superscalar_entry_read_register(source_reg);
            add_superscalar_entry_written_register(dest_reg);
            set_superscalar_entry_timing('\x03','\x04',6,defs_buf,expr_buf);
          }
        }
        else if (cur_op == 0x9d) {
          if (dest_kind == '\x03') {
            add_superscalar_entry_read_register(source_reg);
            add_superscalar_entry_read_register(dest_reg);
            add_superscalar_entry_written_register(dest_reg);
            set_superscalar_entry_timing('\x03','\x04',1,defs_buf,expr_buf);
          }
          else {
            add_superscalar_entry_read_register(source_reg);
            add_superscalar_entry_written_register(dest_reg);
            if (source_reg == REG_FPUL) {
              set_superscalar_entry_timing('\x03','\a',6,defs_buf,expr_buf);
            }
            else {
              set_superscalar_entry_timing('\x03','\x04',6,defs_buf,expr_buf);
            }
          }
        }
        else if (cur_op == 0x9e) {
          add_superscalar_entry_read_register('k');
          add_superscalar_entry_read_register('a');
          add_superscalar_entry_written_register('r');
          add_superscalar_entry_written_register('q');
          add_superscalar_entry_written_register('s');
          set_superscalar_entry_timing('\a','\x04',8,defs_buf,expr_buf);
        }
      }
      else {
        add_superscalar_entry_read_register(source_reg);
        add_superscalar_entry_written_register(source_reg);
        set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
      }
    }
    else {
      add_superscalar_entry_read_register(source_reg);
      add_superscalar_entry_written_register(source_reg);
      set_superscalar_entry_timing('\x01','\x01',1,defs_buf,expr_buf);
    }
  }
  else if (source_kind == '\a') {
    add_superscalar_entry_read_register('\0');
    add_superscalar_entry_written_register('m');
    set_superscalar_entry_timing('\x01','\x03',1,defs_buf,expr_buf);
  }
  else {
    add_superscalar_entry_read_register(source_reg);
    add_superscalar_entry_read_register(dest_reg);
    add_superscalar_entry_written_register('m');
    set_superscalar_entry_timing('\x01','\x03',1,defs_buf,expr_buf);
  }
  return;
#undef size_code
#undef expr_buf
#undef defs_buf
#undef cur_op
#undef issue_grp
#undef vec_reg
#undef dest_kind
#undef dest_reg
#undef i
#undef cur_entry
#undef source_reg
#undef access_bytes
#undef source_kind
}
