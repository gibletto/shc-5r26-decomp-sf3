#include "decls.h"
#include "imports.h"

// entry: 0040b055
// name : add_superscalar_entry_written_register
// size : 745
// sig  : void __cdecl add_superscalar_entry_written_register(char regno)


int __cdecl add_superscalar_entry_written_register(char regno)

{
  char i;
  char reg_no;
  char first_slot;
  
  first_slot = g_superscalar_window[g_superscalar_current_entry].write_count;
  if ((regno < '\x10') || ('\x1f' < regno)) {
    if ((regno < ' ') || ('.' < regno)) {
      if ((regno < 'P') || ('^' < regno)) {
        if ((regno < '0') || ('<' < regno)) {
          if (regno == '`') {
            reg_no = '\x10';
            for (i = '\0'; i < '\x10'; i = i + '\x01') {
              *(char *)((int)first_slot + (int)i + SD(0x0044bce8) + g_superscalar_current_entry * 0xe0) =
                   reg_no;
              g_superscalar_window[g_superscalar_current_entry].write_count =
                   g_superscalar_window[g_superscalar_current_entry].write_count + '\x01';
              reg_no = reg_no + '\x01';
            }
          }
          else {
            *(char *)(g_superscalar_current_entry * 0xe0 + SD(0x0044bce8) + (int)first_slot) = regno;
            g_superscalar_window[g_superscalar_current_entry].write_count =
                 g_superscalar_window[g_superscalar_current_entry].write_count + '\x01';
          }
        }
        else {
          reg_no = regno + -0x20;
          for (i = '\0'; i < '\x04'; i = i + '\x01') {
            *(char *)((int)first_slot + (int)i + SD(0x0044bce8) + g_superscalar_current_entry * 0xe0) =
                 reg_no;
            g_superscalar_window[g_superscalar_current_entry].write_count =
                 g_superscalar_window[g_superscalar_current_entry].write_count + '\x01';
            reg_no = reg_no + '\x01';
          }
        }
      }
      else {
        *(char *)(g_superscalar_current_entry * 0xe0 + SD(0x0044bce8) + (int)first_slot) = regno + -0x40;
        *(char *)(first_slot + SD(0x0044bce9) + g_superscalar_current_entry * 0xe0) = regno + -0x3f;
        g_superscalar_window[g_superscalar_current_entry].write_count =
             g_superscalar_window[g_superscalar_current_entry].write_count + '\x02';
      }
    }
    else {
      *(char *)(g_superscalar_current_entry * 0xe0 + SD(0x0044bce8) + (int)first_slot) = regno + -0x10;
      *(char *)(first_slot + SD(0x0044bce9) + g_superscalar_current_entry * 0xe0) = regno + -0xf;
      g_superscalar_window[g_superscalar_current_entry].write_count =
           g_superscalar_window[g_superscalar_current_entry].write_count + '\x02';
    }
  }
  else {
    *(char *)(g_superscalar_current_entry * 0xe0 + SD(0x0044bce8) + (int)first_slot) = regno;
    g_superscalar_window[g_superscalar_current_entry].write_count =
         g_superscalar_window[g_superscalar_current_entry].write_count + '\x01';
  }
  return;
}
