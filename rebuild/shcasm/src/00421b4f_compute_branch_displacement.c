#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_layout_section_pass0
#define g_layout_section_pass0 (*(request_section * *)(g_sd + 0xcc9c))
#undef g_layout_section_pass1
#define g_layout_section_pass1 (*(request_section * *)(g_sd + 0xcca4))
#undef g_layout_symbol_pass0
#define g_layout_symbol_pass0 (*(symbol * *)(g_sd + 0xccf8))
#undef g_layout_symbol_pass1
#define g_layout_symbol_pass1 (*(symbol * *)(g_sd + 0xccac))


// entry: 00421b4f
// name : compute_branch_displacement
// size : 524
// sig  : int compute_branch_displacement(layout_record * item, int pass)


int __cdecl compute_branch_displacement(layout_record *item,int pass)

{
  symbol *target_sym;
  request_section *target_section;
  int shrink_total;
  int displacement;
  short cur_section_id;
  
  if (item->labels == (label_ref *)0x0) {
    displacement = item->value + -4;
  }
  else if ((item->labels->labno2 == 0) && (0xb6 < item->labels->labno1)) {
    target_sym = find_symbol_by_id(item->labels->labno1);
    if (('\0' < (char)target_sym->kind) && ((char)target_sym->kind < '\x06')) {
      if (pass == 0) {
        cur_section_id = g_layout_section_pass0->id;
      }
      else {
        cur_section_id = g_layout_section_pass1->id;
      }
      if (target_sym->section_id == cur_section_id) {
        displacement = target_sym->value - item->location;
        if (pass == 0) {
          if (displacement < 0) {
            if ((uint)target_sym->sequence <= (uint)g_layout_symbol_pass1->sequence) {
              if (target_sym->section_id == g_layout_section_pass1->id) {
                displacement = displacement + g_layout_shrink_pass1;
              }
              else {
                target_section = find_section_by_id(g_current_request,target_sym->section_id);
                displacement = target_section->layout->shrink_pass1 + displacement;
              }
            }
          }
          else {
            displacement = displacement - g_layout_shrink_pass0;
          }
        }
        else if (0 < displacement) {
          if ((uint)g_layout_symbol_pass0->sequence < (uint)target_sym->sequence) {
            if (target_sym->section_id == g_layout_section_pass0->id) {
              shrink_total = g_layout_shrink_pass1 + g_layout_shrink_pass0;
            }
            else {
              target_section = find_section_by_id(g_current_request,target_sym->section_id);
              shrink_total = target_section->layout->shrink_pass0 + g_layout_shrink_pass1;
            }
            displacement = displacement - shrink_total;
          }
          else {
            displacement = displacement - g_layout_shrink_pass1;
          }
        }
        return displacement + item->value + -4;
      }
    }
    displacement = 0x7fffffff;
  }
  else {
    displacement = 0x7fffffff;
  }
  return displacement;
}



