#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_issue_group_names
#define g_issue_group_names (*(unsigned char * *)(g_sd + 0x4298))
#undef g_op_names
#define g_op_names (*(unsigned char * *)(g_sd + 0x3e98))
#undef g_register_names
#define g_register_names (*(unsigned char * *)(g_sd + 0x3cc8))
#undef g_stage_pattern_names
#define g_stage_pattern_names (*(unsigned char * *)(g_sd + 0x42f0))
#undef g_superscalar_dump_file
#define g_superscalar_dump_file (*(FILE * *)(g_sd + 0x1298c))


// entry: 0040ba89
// name : dump_superscalar_window
// size : 4016
// sig  : void __cdecl dump_superscalar_window(char view)


int __cdecl dump_superscalar_window(char view)

{
  char printed;
  short line_len;
  uchar k;
  char pad;
  uchar entry_no;
  char shown;
  uchar shown_entry;
  
  if (view == '\0') {
    _fputs(s_Data_Dependency_List_0043c248,g_superscalar_dump_file);
    _fputs(s_No_Instruction_Read_0043c260,g_superscalar_dump_file);
    _fputs(s_FlowChild_AntiChild_AmbiChild_Ki_0043c2a0,g_superscalar_dump_file);
    _fputs(s_Write_0043c2e0,g_superscalar_dump_file);
    _fputs(s_FlowParent_AntiParent_AmbiParent_0043c320,g_superscalar_dump_file);
    _fputs(s__________________________________0043c360,g_superscalar_dump_file);
    _fputs(s__________________________________0043c3a0,g_superscalar_dump_file);
    for (entry_no = '\0'; (char)entry_no <= g_pipeline_window_last_index;
        entry_no = entry_no + '\x01') {
      _sprintf(&g_superscalar_dump_line,s__2d__5s_0043c644,(int)(char)entry_no,
               (&g_op_names)[g_superscalar_window[(char)entry_no].rec.op]);
      _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
      print_superscalar_entry_operands(entry_no);
      printed = '\0';
      for (k = '\0'; (char)k < g_superscalar_window[(char)entry_no].read_count; k = k + '\x01') {
        if (k == '\x03') {
          _sprintf(&g_superscalar_dump_line,&s_dot_dot_0043c654);
          _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
          printed = printed + '\x02';
          break;
        }
        _sprintf(&g_superscalar_dump_line,&s_lt_pct_s_gt_0043c658,
                 (&g_register_names)[*(char *)((char)entry_no * 0xe0 + SD(0x0044bcd0) + (int)(char)k)]);
        _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
        for (line_len = 0; (line_len < 0x200 && ((&g_superscalar_dump_line)[line_len] != '\0'));
            line_len = line_len + 1) {
        }
        printed = printed + (char)line_len;
      }
      for (printed = '\x16' - printed; printed != '\0'; printed = printed + -1) {
        _sprintf(&g_superscalar_dump_line,&s_sp_0043c660);
        _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
      }
      printed = '\0';
      shown = '\0';
      for (k = '\0'; (char)k < ' '; k = k + '\x01') {
        if (shown == '\x04') {
          _sprintf(&g_superscalar_dump_line,&s_dot_dot_0043c664);
          _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
          printed = printed + '\x02';
          break;
        }
        if ((*(uint *)(&g_window_entry_bit_masks + (char)k * 4) &
            g_superscalar_window[(char)entry_no].flow_children) != 0) {
          _sprintf(&g_superscalar_dump_line,&s_pct_d_colon_0043c668,(int)(char)k);
          _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
          for (line_len = 0; (line_len < 0x200 && ((&g_superscalar_dump_line)[line_len] != '\0'));
              line_len = line_len + 1) {
          }
          printed = printed + (char)line_len;
          shown = shown + '\x01';
        }
      }
      for (printed = '\x0f' - printed; printed != '\0'; printed = printed + -1) {
        _sprintf(&g_superscalar_dump_line,&s_sp_0043c66c);
        _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
      }
      printed = '\0';
      shown = '\0';
      for (k = '\0'; (char)k < ' '; k = k + '\x01') {
        if (shown == '\x04') {
          _sprintf(&g_superscalar_dump_line,&s_dot_dot_0043c670);
          _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
          printed = printed + '\x02';
          break;
        }
        if ((*(uint *)(&g_window_entry_bit_masks + (char)k * 4) &
            g_superscalar_window[(char)entry_no].anti_children) != 0) {
          _sprintf(&g_superscalar_dump_line,&s_pct_d_colon_0043c674,(int)(char)k);
          _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
          for (line_len = 0; (line_len < 0x200 && ((&g_superscalar_dump_line)[line_len] != '\0'));
              line_len = line_len + 1) {
          }
          printed = printed + (char)line_len;
          shown = shown + '\x01';
        }
      }
      for (printed = '\x0f' - printed; printed != '\0'; printed = printed + -1) {
        _sprintf(&g_superscalar_dump_line,&s_sp_0043c678);
        _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
      }
      printed = '\0';
      shown = '\0';
      for (k = '\0'; (char)k < ' '; k = k + '\x01') {
        if (shown == '\x04') {
          _sprintf(&g_superscalar_dump_line,&s_dot_dot_0043c67c);
          _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
          printed = printed + '\x02';
          break;
        }
        if ((*(uint *)(&g_window_entry_bit_masks + (char)k * 4) &
            g_superscalar_window[(char)entry_no].ambi_children) != 0) {
          _sprintf(&g_superscalar_dump_line,&s_pct_d_colon_0043c680,(int)(char)k);
          _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
          for (line_len = 0; (line_len < 0x200 && ((&g_superscalar_dump_line)[line_len] != '\0'));
              line_len = line_len + 1) {
          }
          printed = printed + (char)line_len;
          shown = shown + '\x01';
        }
      }
      for (printed = '\x0f' - printed; printed != '\0'; printed = printed + -1) {
        _sprintf(&g_superscalar_dump_line,&s_sp_0043c684);
        _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
      }
      _sprintf(&g_superscalar_dump_line,s__4s_0043c688,
               (&g_issue_group_names)[g_superscalar_window[(char)entry_no].issue_group]);
      _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
      for (line_len = 0; (line_len < 0x200 && ((&g_superscalar_dump_line)[line_len] != '\0'));
          line_len = line_len + 1) {
      }
      for (printed = '\a' - (char)line_len; printed != '\0'; printed = printed + -1) {
        _sprintf(&g_superscalar_dump_line,&s_sp_0043c690);
        _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
      }
      _sprintf(&g_superscalar_dump_line,&s_pct_2d_nl_0043c694,
               (int)g_superscalar_window[(char)entry_no].latency);
      _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
      for (printed = '\"'; printed != '\0'; printed = printed + -1) {
        _sprintf(&g_superscalar_dump_line,&s_sp_0043c69c);
        _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
      }
      printed = '\0';
      for (k = '\0'; (char)k < g_superscalar_window[(char)entry_no].write_count; k = k + '\x01') {
        if (k == '\x03') {
          _sprintf(&g_superscalar_dump_line,&s_dot_dot_0043c6a0);
          _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
          printed = printed + '\x02';
          break;
        }
        _sprintf(&g_superscalar_dump_line,&s_lt_pct_s_gt_0043c6a4,
                 (&g_register_names)[*(char *)((char)entry_no * 0xe0 + SD(0x0044bce8) + (int)(char)k)]);
        _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
        for (line_len = 0; (line_len < 0x200 && ((&g_superscalar_dump_line)[line_len] != '\0'));
            line_len = line_len + 1) {
        }
        printed = printed + (char)line_len;
      }
      for (printed = '\x16' - printed; printed != '\0'; printed = printed + -1) {
        _sprintf(&g_superscalar_dump_line,&s_sp_0043c6ac);
        _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
      }
      printed = '\0';
      shown = '\0';
      for (k = '\0'; (char)k < ' '; k = k + '\x01') {
        if (shown == '\x04') {
          _sprintf(&g_superscalar_dump_line,&s_dot_dot_0043c6b0);
          _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
          printed = printed + '\x02';
          break;
        }
        if ((*(uint *)(&g_window_entry_bit_masks + (char)k * 4) &
            g_superscalar_window[(char)entry_no].flow_parents) != 0) {
          _sprintf(&g_superscalar_dump_line,&s_pct_d_colon_0043c6b4,(int)(char)k);
          _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
          for (line_len = 0; (line_len < 0x200 && ((&g_superscalar_dump_line)[line_len] != '\0'));
              line_len = line_len + 1) {
          }
          printed = printed + (char)line_len;
          shown = shown + '\x01';
        }
      }
      for (printed = '\x0f' - printed; printed != '\0'; printed = printed + -1) {
        _sprintf(&g_superscalar_dump_line,&s_sp_0043c6b8);
        _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
      }
      printed = '\0';
      shown = '\0';
      for (k = '\0'; (char)k < ' '; k = k + '\x01') {
        if (shown == '\x04') {
          _sprintf(&g_superscalar_dump_line,&s_dot_dot_0043c6bc);
          _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
          printed = printed + '\x02';
          break;
        }
        if ((*(uint *)(&g_window_entry_bit_masks + (char)k * 4) &
            g_superscalar_window[(char)entry_no].anti_parents) != 0) {
          _sprintf(&g_superscalar_dump_line,&s_pct_d_colon_0043c6c0,(int)(char)k);
          _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
          for (line_len = 0; (line_len < 0x200 && ((&g_superscalar_dump_line)[line_len] != '\0'));
              line_len = line_len + 1) {
          }
          printed = printed + (char)line_len;
          shown = shown + '\x01';
        }
      }
      for (printed = '\x0f' - printed; printed != '\0'; printed = printed + -1) {
        _sprintf(&g_superscalar_dump_line,&s_sp_0043c6c4);
        _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
      }
      printed = '\0';
      shown = '\0';
      for (k = '\0'; (char)k < ' '; k = k + '\x01') {
        if (shown == '\x04') {
          _sprintf(&g_superscalar_dump_line,&s_dot_dot_0043c6c8);
          _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
          printed = printed + '\x02';
          break;
        }
        if ((*(uint *)(&g_window_entry_bit_masks + (char)k * 4) &
            g_superscalar_window[(char)entry_no].ambi_parents) != 0) {
          _sprintf(&g_superscalar_dump_line,&s_pct_d_colon_0043c6cc,(int)(char)k);
          _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
          for (line_len = 0; (line_len < 0x200 && ((&g_superscalar_dump_line)[line_len] != '\0'));
              line_len = line_len + 1) {
          }
          printed = printed + (char)line_len;
          shown = shown + '\x01';
        }
      }
      for (printed = '\x0f' - printed; printed != '\0'; printed = printed + -1) {
        _sprintf(&g_superscalar_dump_line,&s_sp_0043c6d0);
        _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
      }
      _sprintf(&g_superscalar_dump_line,&s_pct_4d_nl_0043c6d4,
               g_superscalar_window[(char)entry_no].path_length);
      _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
    }
    _sprintf(&g_superscalar_dump_line,&s_nl_nl_0043c6dc);
    _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
    _fputs(s__________________________________0043c360,g_superscalar_dump_file);
    _fputs(s__________________________________0043c3a0,g_superscalar_dump_file);
  }
  else if ((view == '\x01') || (view == '\x02')) {
    if (view == '\x01') {
      _fputs(s_Original_Easy_View_0043c3e0,g_superscalar_dump_file);
    }
    else {
      _fputs(s_Scheduled_Easy_View_0043c3f8,g_superscalar_dump_file);
    }
    _fputs(s_Count_Cycle_Node_Instruction_0043c410,g_superscalar_dump_file);
    _fputs(s_Pipeline_0043c448,g_superscalar_dump_file);
    _fputs(s_No_0043c458,g_superscalar_dump_file);
    _fputs(s_012345678901234567890123456789_0043c490,g_superscalar_dump_file);
    _fputs(s__________________________________0043c4b0,g_superscalar_dump_file);
    _fputs(s________________________________0043c4e8,g_superscalar_dump_file);
    for (entry_no = '\0'; (char)entry_no <= g_pipeline_window_last_index;
        entry_no = entry_no + '\x01') {
      if (view == '\x01') {
        shown_entry = entry_no;
      }
      else {
        sort_array(g_superscalar_order,g_pipeline_window_last_index + 1,0xc,
                   compare_order_entries_by_index);
        k = '\0';
        while (g_superscalar_window[(char)k].order != entry_no) {
          k = k + '\x01';
        }
        shown_entry = k;
      }
      _sprintf(&g_superscalar_dump_line,s__5d__5d__5d__5s_0043c6e0,(int)(char)entry_no,
               g_superscalar_order[(char)shown_entry].cycle,(int)(char)entry_no,
               (&g_op_names)[g_superscalar_window[(char)shown_entry].rec.op]);
      _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
      print_superscalar_entry_operands(shown_entry);
      for (pad = (char)g_superscalar_order[(char)shown_entry].cycle; pad != '\0'; pad = pad + -1) {
        _sprintf(&g_superscalar_dump_line,&s_sp_0043c6f8);
        _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
      }
      _sprintf(&g_superscalar_dump_line,&s_pct_s_nl_0043c6fc,
               (&g_stage_pattern_names)
               [(char)(&g_superscalar_entry_stage_pattern)[(char)shown_entry * 4]]);
      _fputs(&g_superscalar_dump_line,g_superscalar_dump_file);
    }
  }
  return;
}
