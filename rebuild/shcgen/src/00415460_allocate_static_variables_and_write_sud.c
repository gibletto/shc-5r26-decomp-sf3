#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_section
#define g_current_section (*(request_section * *)(g_sd + 0x1f9b8))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_sud_buffer_cursor
#define g_sud_buffer_cursor (*(char * *)(g_sd + 0x1f9f4))
#undef g_sud_buffer_start
#define g_sud_buffer_start (*(char * *)(g_sd + 0x1fe64))
#undef g_sud_file
#define g_sud_file (*(FILE * *)(g_sd + 0x1f9f0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00415460
// name : allocate_static_variables_and_write_sud
// size : 989
// sig  : void allocate_static_variables_and_write_sud(void)


int __cdecl allocate_static_variables_and_write_sud(void)

{
  unsigned char _frec_14[20];
#define rec_tags (*(char (*)[2])(_frec_14 + 0))
#define sym_no (*(ushort *)(_frec_14 + 2))
#define sect_kind (*(char *)(_frec_14 + 4))
#define unit_class (*(char *)(_frec_14 + 5))
#define uStack_e (*(undefined2 *)(_frec_14 + 6))
#define elem_count (*(uint *)(_frec_14 + 8))
#define sym_type (*(byte *)(_frec_14 + 12))
#define zero_bytes (*(char (*)[4])(_frec_14 + 16))
  byte bVar1;
  uint uVar2;
  uint obj_size;
  sym_entry *sym;
  uint *offset;
  uint old_offset;
  char sclass;
  int shift;
  
  g_sud_buffer_cursor = &g_sud_buffer;
  g_sud_buffer_start = &g_sud_buffer;
  builtin_strncpy(zero_bytes,"tTA",4);
  write_sud_initialized_data();
  rec_tags[0] = '\x0f';
  rec_tags[1] = 0x18;
  zero_bytes[0] = '\0';
  zero_bytes[1] = '\0';
  zero_bytes[2] = '\0';
  zero_bytes[3] = '\0';
  g_current_section = (request_section *)0x0;
  sect_kind = '\n';
  sym_no = 0xb7;
  if (0xb6 < *(int *)g_request->unknown_0b0 + 0xb6) {
    obj_size = CONCAT22(uStack_e,CONCAT11(unit_class,10));
    do {
      uVar2 = CONCAT12(sect_kind,sym_no) & 0xffff;
      sym = g_symbol_table + uVar2;
      sclass = sym->sclass;
      if ((((((sym->flags & 0x80) != 0) && ((sym->flags & 0x40) == 0)) && (sym->byte_03 == '\0')) &&
          (((sclass == '\x03' || (sclass == '\x01')) || (sclass == '\x04')))) &&
         ((bVar1 = g_symbol_table[uVar2].type & 0xf8, bVar1 != 0x48 && (bVar1 != 0x50)))) {
        if ((g_current_section == (request_section *)0x0) ||
           (sym->short_06 != g_current_section->id)) {
          write_bytes_or_fail(rec_tags,1,g_sud_file);
          g_current_section =
               find_section_record(g_request,
                                   g_symbol_table[CONCAT12(sect_kind,sym_no) & 0xffff].short_06);
          write_bytes_or_fail((char *)g_current_section,2,g_sud_file);
        }
        uVar2 = (uint)sym_no;
        if (g_symbol_table[uVar2].reg == -1) {
          sym_type = g_symbol_table[uVar2].type;
          switch(sym_type & 0xf8) {
          case 0:
            obj_size = 1;
            unit_class = '\0';
            elem_count = 1;
            break;
          case 8:
            unit_class = '\x01';
            elem_count = 1;
            obj_size = 2;
            break;
          case 0x10:
          case 0x18:
          case 0x28:
          case 0x40:
            unit_class = '\x02';
            elem_count = 1;
            obj_size = 4;
            break;
          default:
            report_codegen_message(0x1235,1,0,0,(char *)0x0);
            break;
          case 0x30:
          case 0x38:
            unit_class = '\x02';
            elem_count = 2;
            obj_size = 8;
            break;
          case 0x60:
          case 0x68:
          case 0x70:
          case 0x80:
          case 0x88:
          case 0x90:
            obj_size = g_symbol_table[uVar2].size;
            if ((sym_type & 0x18) == 0) {
              unit_class = '\0';
              elem_count = obj_size;
            }
            else {
              if ((sym_type & 0x18) == 8) {
                unit_class = '\x01';
                shift = 1;
              }
              else {
                if ((sym_type & 0x18) != 0x10) {
                  report_codegen_message(0x1234,1,0,0,(char *)0x0);
                  break;
                }
                unit_class = '\x02';
                shift = 2;
              }
              elem_count = obj_size >> shift;
            }
          }
          bVar1 = g_symbol_table[sym_no].attr;
          if ((bVar1 & 1) == 0) {
            if ((bVar1 & 2) == 0) {
              sect_kind = '\n';
              offset = &g_current_section->bss_loc;
            }
            else {
              sect_kind = '\t';
              offset = &g_current_section->data_loc;
            }
          }
          else {
            sect_kind = '\t';
            offset = &g_current_section->data_loc;
          }
          if (((unit_class == '\x01') || (unit_class == '\x02')) ||
             (((g_symbol_table[sym_no].attr & 0x40) != 0 && (unit_class == '\0')))) {
            write_sud_alignment_padding((int)unit_class,offset,(uint)sym_no);
          }
          g_symbol_table[CONCAT12(sect_kind,sym_no) & 0xffff].frame_offset = *offset;
          write_asa_record(9,sym_no);
          write_bytes_or_fail(rec_tags + 1,1,g_sud_file);
          write_bytes_or_fail((char *)&sym_no,2,g_sud_file);
          write_bytes_or_fail(zero_bytes,4,g_sud_file);
          old_offset = *offset;
          uVar2 = old_offset + obj_size;
          *offset = uVar2;
          if (uVar2 < old_offset) {
            report_codegen_message(0xc81,1,0,0,(char *)0x0);
          }
          write_bytes_or_fail(&sect_kind,2,g_sud_file);
          write_bytes_or_fail((char *)&elem_count,4,g_sud_file);
        }
        else {
          write_asa_record(9,sym_no);
        }
        g_symbol_table[CONCAT12(sect_kind,sym_no) & 0xffff].flags =
             g_symbol_table[CONCAT12(sect_kind,sym_no) & 0xffff].flags | 0x40;
      }
      sym_no = sym_no + 1;
    } while ((int)(CONCAT12(sect_kind,sym_no) & 0xffff) <= *(int *)g_request->unknown_0b0 + 0xb6);
  }
  return;
#undef rec_tags
#undef sym_no
#undef sect_kind
#undef unit_class
#undef uStack_e
#undef elem_count
#undef sym_type
#undef zero_bytes
}



