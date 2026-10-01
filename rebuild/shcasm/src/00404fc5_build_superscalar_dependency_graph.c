#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 00404fc5
// name : build_superscalar_dependency_graph
// size : 2611
// sig  : void build_superscalar_dependency_graph(void)


int __cdecl build_superscalar_dependency_graph(void)

{
  char write_no;
  char k;
  char j;
  char i;
  int flow_height;
  int anti_height;
  
  for (i = '\0'; i <= g_pipeline_window_last_index; i = i + '\x01') {
    if (g_superscalar_window[i].read_count != '\0') {
      for (j = '\0'; j <= g_superscalar_window[i].read_count; j = j + '\x01') {
        (&g_register_sort_buffer)[j] = *(undefined1 *)(j + SD(0x0044bcd0) + i * 0xe0);
      }
      sort_array(&g_register_sort_buffer,(int)g_superscalar_window[i].read_count,1,compare_bytes);
      for (j = '\0'; j <= g_superscalar_window[i].read_count; j = j + '\x01') {
        *(undefined *)(j + SD(0x0044bcd0) + i * 0xe0) = (&g_register_sort_buffer)[j];
      }
    }
    if (g_superscalar_window[i].write_count != '\0') {
      for (j = '\0'; j <= g_superscalar_window[i].write_count; j = j + '\x01') {
        (&g_register_sort_buffer)[j] = *(undefined1 *)(j + SD(0x0044bce8) + i * 0xe0);
      }
      sort_array(&g_register_sort_buffer,(int)g_superscalar_window[i].write_count,1,compare_bytes);
      for (j = '\0'; j <= g_superscalar_window[i].write_count; j = j + '\x01') {
        *(undefined *)(j + SD(0x0044bce8) + i * 0xe0) = (&g_register_sort_buffer)[j];
      }
    }
  }
  i = '\0';
  do {
    if (g_pipeline_window_last_index < i) {
      add_store_memory_order_dependencies();
      i = (char)g_pipeline_window_last_index;
      do {
        if (i < '\0') {
          for (i = (char)g_pipeline_window_last_index; -1 < i; i = i + -1) {
            if ((('\x10' < g_superscalar_window[i].issue_group) &&
                (g_superscalar_window[i].issue_group < '\x16')) &&
               (g_superscalar_window[i].write_count != '\0')) {
              for (write_no = '\0'; j = i, write_no < g_superscalar_window[i].write_count;
                  write_no = write_no + '\x01') {
                while (j = j + -1, -1 < j) {
                  if ((('\v' < g_superscalar_window[j].issue_group) &&
                      (g_superscalar_window[j].issue_group < '\x11')) &&
                     ((g_superscalar_window[j].rec.ea1)->type != '\n')) {
                    for (k = '\0'; k < g_superscalar_window[j].read_count; k = k + '\x01') {
                      if (*(char *)(write_no + SD(0x0044bce8) + i * 0xe0) ==
                          *(char *)(k + SD(0x0044bcd0) + j * 0xe0)) {
                        g_superscalar_window[j].ambi_children =
                             g_superscalar_window[j].ambi_children |
                             *(uint *)(&g_window_entry_bit_masks + i * 4);
                        g_superscalar_window[j].ambi_child_count =
                             g_superscalar_window[j].ambi_child_count + '\x01';
                        g_superscalar_window[i].ambi_parents =
                             g_superscalar_window[i].ambi_parents |
                             *(uint *)(&g_window_entry_bit_masks + j * 4);
                        g_superscalar_window[i].ambi_parent_count =
                             g_superscalar_window[i].ambi_parent_count + '\x01';
                      }
                    }
                  }
                }
              }
            }
          }
          for (i = (char)g_pipeline_window_last_index; -1 < i; i = i + -1) {
            flow_height = 0;
            if (g_superscalar_window[i].flow_child_count != '\0') {
              flow_height = 0;
              for (k = '\0'; k < ' '; k = k + '\x01') {
                if (((*(uint *)(&g_window_entry_bit_masks + k * 4) &
                     g_superscalar_window[i].flow_children) != 0) &&
                   (flow_height < g_superscalar_window[k].path_length)) {
                  flow_height = g_superscalar_window[k].path_length;
                }
              }
            }
            if (g_superscalar_window[i].latency == '\0') {
              flow_height = flow_height + 1;
            }
            else {
              flow_height = flow_height + g_superscalar_window[i].latency;
            }
            anti_height = 0;
            if (g_superscalar_window[i].anti_child_count != '\0') {
              for (k = '\0'; k < ' '; k = k + '\x01') {
                if (((*(uint *)(&g_window_entry_bit_masks + k * 4) &
                     g_superscalar_window[i].anti_children) != 0) &&
                   (anti_height < g_superscalar_window[k].path_length)) {
                  anti_height = g_superscalar_window[k].path_length;
                }
              }
            }
            if (anti_height + 1 < flow_height) {
              g_superscalar_window[i].path_length = flow_height;
            }
            else {
              g_superscalar_window[i].path_length = anti_height + 1;
            }
          }
          if ((g_current_request->flags_13c & 8) != 0) {
            dump_superscalar_window('\0');
          }
          return;
        }
        if (g_superscalar_window[i].write_count != '\0') {
          for (write_no = '\0'; j = i, write_no < g_superscalar_window[i].write_count;
              write_no = write_no + '\x01') {
            while (j = j + -1, -1 < j) {
              for (k = '\0'; k < g_superscalar_window[j].read_count; k = k + '\x01') {
                if (*(char *)(write_no + SD(0x0044bce8) + i * 0xe0) == *(char *)(k + SD(0x0044bcd0) + j * 0xe0))
                {
                  g_superscalar_window[j].anti_children =
                       g_superscalar_window[j].anti_children |
                       *(uint *)(&g_window_entry_bit_masks + i * 4);
                  g_superscalar_window[j].anti_child_count =
                       g_superscalar_window[j].anti_child_count + '\x01';
                  g_superscalar_window[i].anti_parents =
                       g_superscalar_window[i].anti_parents |
                       *(uint *)(&g_window_entry_bit_masks + j * 4);
                  g_superscalar_window[i].anti_parent_count =
                       g_superscalar_window[i].anti_parent_count + '\x01';
                  break;
                }
              }
              for (k = '\0'; k < g_superscalar_window[j].write_count; k = k + '\x01') {
                if (*(char *)(k + SD(0x0044bce8) + j * 0xe0) == *(char *)(write_no + SD(0x0044bce8) + i * 0xe0))
                goto LAB_0040545a;
              }
            }
LAB_0040545a: ;
          }
        }
        i = i + -1;
      } while( true );
    }
    if (g_superscalar_window[i].write_count != '\0') {
      for (write_no = '\0'; j = i, write_no < g_superscalar_window[i].write_count;
          write_no = write_no + '\x01') {
        while (j = j + '\x01', j <= g_pipeline_window_last_index) {
          for (k = '\0'; k < g_superscalar_window[j].read_count; k = k + '\x01') {
            if (*(char *)(write_no + SD(0x0044bce8) + i * 0xe0) == *(char *)(k + SD(0x0044bcd0) + j * 0xe0)) {
              g_superscalar_window[i].flow_children =
                   g_superscalar_window[i].flow_children |
                   *(uint *)(&g_window_entry_bit_masks + j * 4);
              g_superscalar_window[i].flow_child_count =
                   g_superscalar_window[i].flow_child_count + '\x01';
              g_superscalar_window[j].flow_parents =
                   g_superscalar_window[j].flow_parents |
                   *(uint *)(&g_window_entry_bit_masks + i * 4);
              g_superscalar_window[j].flow_parent_count =
                   g_superscalar_window[j].flow_parent_count + '\x01';
            }
          }
          for (k = '\0'; k < g_superscalar_window[j].write_count; k = k + '\x01') {
            if (*(char *)(k + SD(0x0044bce8) + j * 0xe0) == *(char *)(write_no + SD(0x0044bce8) + i * 0xe0)) {
              g_superscalar_window[i].ambi_children =
                   g_superscalar_window[i].ambi_children |
                   *(uint *)(&g_window_entry_bit_masks + j * 4);
              g_superscalar_window[i].ambi_child_count =
                   g_superscalar_window[i].ambi_child_count + '\x01';
              g_superscalar_window[j].ambi_parents =
                   g_superscalar_window[j].ambi_parents |
                   *(uint *)(&g_window_entry_bit_masks + i * 4);
              g_superscalar_window[j].ambi_parent_count =
                   g_superscalar_window[j].ambi_parent_count + '\x01';
              goto LAB_00405213;
            }
          }
        }
LAB_00405213: ;
      }
    }
    i = i + '\x01';
  } while( true );
}
