#include "decls.h"
#include "imports.h"

#if SHC_REBUILD_UPDATED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* SHC_ALIGN_FILE (unset = Release 26 layout): a text file of "<function> <bytes>" lines. The named
   function's entry label is moved <bytes> (even, 2..30) further on, as if the code before it were that much longer:
   the first layout pass takes the bytes off its running shrink (g_layout_shrink_pass0) just before the label's position is
   corrected, so the label, everything after it in the section and the section size move together, the second pass
   aligns pools at the moved positions, the scheduler seeds its phase from the moved label, and the emitter fills
   the gap before the label with nops (the fill path emit_label_record already takes when a label lies past the location
   counter; the listing shows it as .ALIGN). */
static struct align_pad { char name[128]; int bytes; } *align_pads;
static int align_npads = -1;
static int align_pad_for(const char *name) {
    int i;
    if (align_npads < 0) {
        char *p = getenv("SHC_ALIGN_FILE"), line[256];
        FILE *fp;
        align_npads = 0;
        if (p && *p && (fp = fopen(p, "r")) != 0) {
            int cap = 0;
            while (fgets(line, sizeof line, fp)) {
                char nm[128]; int b;
                if (line[0] == '#' || sscanf(line, "%127s %i", nm, &b) != 2 || b <= 0 || b > 30 || (b & 1)) continue;
                if (align_npads == cap) {
                    cap = cap ? cap * 2 : 64;
                    align_pads = (struct align_pad *)realloc(align_pads, cap * sizeof *align_pads);
                }
                strcpy(align_pads[align_npads].name, nm);
                align_pads[align_npads++].bytes = b;
            }
            fclose(fp);
        }
    }
    if (!name) return 0;
    if (*name == '_') name++;
    for (i = 0; i < align_npads; i++)
        if (strcmp(align_pads[i].name, name) == 0 || (align_pads[i].name[0] == '_' && strcmp(align_pads[i].name + 1, name) == 0))
            return align_pads[i].bytes;
    return 0;
}
#define ALIGN_PAD(sym) ((((sym)->kind & 0x1f) == 1) ? align_pad_for((sym)->name) : 0)
#else
#define ALIGN_PAD(sym) 0
#endif
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_layout_pending_records
#define g_layout_pending_records (*(layout_record * *)(g_sd + 0xcca8))
#undef g_layout_record_tail
#define g_layout_record_tail (*(layout_record * *)(g_sd + 0x13158))
#undef g_layout_section_pass0
#define g_layout_section_pass0 (*(request_section * *)(g_sd + 0xcc9c))
#undef g_layout_section_pass1
#define g_layout_section_pass1 (*(request_section * *)(g_sd + 0xcca4))
#undef g_layout_symbol_pass0
#define g_layout_symbol_pass0 (*(symbol * *)(g_sd + 0xccf8))
#undef g_layout_symbol_pass1
#define g_layout_symbol_pass1 (*(symbol * *)(g_sd + 0xccac))


// entry: 00429060
// name : run_layout_passes
// size : 525
// sig  : void run_layout_passes(void)


int __cdecl run_layout_passes(void)

{
  char ofb_tag;
  section_layout *new_layout;
  request_section *cur_section;
  
  for (cur_section = g_current_request->sections; cur_section != (request_section *)0x0;
      cur_section = cur_section->next) {
    new_layout = pool_alloc(0x30);
    cur_section->layout = new_layout;
  }
  begin_layout_passes();
  if (g_ofb_at_end == 0) {
    for (; (g_layout_symbol_pass0->kind & 0x1f) < 6;
        g_layout_symbol_pass0 = g_layout_symbol_pass0 + 1) {
      g_layout_symbol_pass0->layout_records = (layout_record *)0x0;
      if ((g_layout_symbol_pass0->kind & 0x1f) != 0) {
        if (g_layout_symbol_pass0->section_id != g_layout_section_pass0->id) {
          g_layout_section_pass0->layout->shrink_pass0 = g_layout_shrink_pass0;
          g_layout_section_pass0 =
               find_section_by_id(g_current_request,g_layout_symbol_pass0->section_id);
          g_layout_shrink_pass0 = g_layout_section_pass0->layout->shrink_pass0;
        }
        g_layout_shrink_pass0 = g_layout_shrink_pass0 - ALIGN_PAD(g_layout_symbol_pass0);
        g_layout_symbol_pass0->value = g_layout_symbol_pass0->value - g_layout_shrink_pass0;
        if ((g_ofb_at_end == 0) && (g_layout_symbol_pass0->number == g_ofb_current_label)) {
          g_layout_record_tail = (layout_record *)0x0;
          while (((g_ofb_at_end == 0 && (ofb_tag = layout_next_ofb_record(), ofb_tag != '\x18')) &&
                 (ofb_tag != '\x19'))) {
            if ((ofb_tag == '\x1a') || (ofb_tag == '\x1b')) break;
          }
        }
      }
    }
    while (g_layout_pending_records != (layout_record *)0x0) {
      resolve_next_pending_layout_record();
    }
    g_layout_symbol_pass0 = g_layout_symbol_pass0 + -1;
    while (g_layout_symbol_pass1 <= g_layout_symbol_pass0) {
      resolve_next_pending_layout_record();
    }
  }
  while (g_layout_pending_records != (layout_record *)0x0) {
    resolve_next_pending_layout_record();
  }
  g_layout_section_pass0->layout->shrink_pass0 = g_layout_shrink_pass0;
  g_layout_section_pass1->layout->shrink_pass1 = g_layout_shrink_pass1;
  finish_layout_passes();
  return;
}
