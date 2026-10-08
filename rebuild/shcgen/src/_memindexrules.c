/* GEN_MEM_INDEX (only with SHC_REBUILD_UPDATED=1): a pointer or index that is still in memory is not made the operand
   of an indexed access.

   fold_address_add looks at the two operands of the address sum under a dereference, `*(a + b)`, and where it can
   turns the sum into an addressing mode. Its table has an entry for an operand that is still a memory operand (a
   pointer read through another pointer or from a structure, `table[a]` in `table[a][b]`; a pointer variable kept
   in the frame or in a global) beside one that is already in a register. When that register is not r0, Release 26
   loads the pointer into r0 and makes the access indexed:

       mov.l @(r0,r3),r0      ; table[a]
       mov.l @(r0,r2),r3      ; [b]

   The arcade's compiler has no such case: the sum goes to the add template like any other, which loads the
   pointer into the scratch register the chooser gives it and adds:

       mov.l @(r0,r3),r3
       add   r3,r2
       mov.l @r2,r1

   The access is still indexed when the pointer ends in r0 for another reason (the value is wanted in r0: a
   return value, a byte or word stored with a displacement), and nothing changes when the other operand is in r0
   (the pointer goes to another register and is the base) or is a constant (a displacement).

   Measured on the game (Street Fighter III 3rd Strike, every C routine): Release 26's case is taken at 71 places
   in 31 routines. In 13 of the routines (24 places) the arcade's code has exactly the sums and indexed loads the
   rule gives, and six of them become the arcade's instructions (comm_retmj, exset_char_move_init, char_move_cmms2,
   char_move_cmms3, test_menu_select, stun_mark_write). In no routine does the arcade have an indexed load at a
   place the rule changes. Counting, over all routines, the loads through a pointer that was just read from memory:
   the arcade has 132 indexed and 237 summed; Release 26's case on our source gives 169 and 178, of which 114 and
   165 are where the arcade has them; the rule gives 127 and 221, of which 114 and 197. So 32 places move to the
   arcade's form, none leaves it, and about 10 are places where the arcade has neither form: our source keeps the
   pointer in the frame there and the arcade has it in a register (Setup_PL_Color, check_super_arts_attack,
   check_special_attack, the setup_*_cells routines), so its code has no memory operand to decide by.

   The same holds beside the two other kinds of operand a memory operand can meet (bits 2 and 8):

   An address constant (bit 2). The memory operand is a scaled index that is used twice and kept in the frame,
   `id * 2` in `base[wide[id]] + left[id]`. Release 26 loads it into a register, the array's address into r0 and
   indexes (mov.l @r15,r2; mov.l left,r0; mov.w @(r0,r2),r1); the arcade loads the address into a scratch register
   and adds (mov.l left,r2; mov.l @r15,r1; add r2,r1; mov.w @r1,r3). Over every C routine of the game, counting a
   long read from memory that is then, unchanged, either the index of @(r0,Rn) with a literal address in r0 or
   added to a register holding a literal address and dereferenced: the arcade has 0 of the first and 33 of the
   second; Release 26's case on our source 12 and 26; with the bit 0 and 34. The 12 places are in 10 routines:
   effect_work_list_release, c3_new_damage and Disp_Personal_Count become the arcade's instructions, and
   Break_Into_08, Ck_Break_Into, Entry_01_Sub, Entry_Main_Sub (2), Setup_Next_Step, normal_ending (2) and
   win_mark_all_write have the arcade's add at the place. For 12, against 0.

   r0 (bit 8). The index is already in r0 and the pointer is read from memory (`rows[pick]` with rows a pointer
   variable, `((u16 *)row)[step]`). Release 26 loads the pointer into a scratch register and indexes; left to the
   add template the access is still indexed when the value goes on from the pointer's register (mov.l @(r0,r1),r1
   in Next_Talk_Message, which becomes the arcade's code) and an add where the index is not wanted again
   (debug_draw_hit_edit_info, whose four reads of dbg_edit_box[i] are adds in the arcade: mov.l @r1,r3; shll r2;
   add r3,r2; mov.w @r2,r0). 6 places in 5 routines: for 2 routines (5 places), against 0, and 3 routines whose
   instructions do not change (Rewrite_End_Message, Rewrite_Talk_Message, set_tenguiwa).

   Not changed, for want of a place in the game that decides it: both operands in memory (bit 4; Release 26 loads
   one into r0 and the other into a register). Only Setup_PL_Color reaches it, and there the arcade has no memory
   operand: it sets the two pointers later, in registers. A number beside a memory operand is a displacement and
   is not asked about. The game's unoptimized files have no such sum either, so the rule is not measured there.

   GEN_MEM_INDEX=<bits> (unset: 11, the arcade rule; 0: Release 26): the sum is left to the add template when the
   operand beside the memory operand is
     1  a register other than r0
     2  an address constant
     4  a memory operand too (off)
     8  r0
   GEN_MEM_INDEX_LOG=<file> (a diagnostic, off unless set; a %d in the name is replaced by the process id) logs
   each such sum with the class of the other operand and what was decided. */
#if SHC_REBUILD_UPDATED
#include <stdlib.h>
#include <stdio.h>
#include <process.h>
#include "decls.h"
#include "imports.h"
#include "memindexrules.h"

extern char *gen_function_name;

static FILE *mem_index_log_file(void)
{
    static FILE *f;
    static int opened;
    if (!opened) {
        const char *p = getenv("GEN_MEM_INDEX_LOG");
        char path[512];
        opened = 1;
        if (p && *p) {
            _snprintf(path, sizeof path, p, _getpid());
            f = fopen(path, "a");
        }
    }
    return f;
}

static int mem_index_mode(void)
{
    static int mode = -1;
    if (mode < 0) {
        const char *p = getenv("GEN_MEM_INDEX");
        mode = (p && *p) ? atoi(p) : 11;
    }
    return mode;
}

/* other: the class of the operand beside the memory operand (7 a register other than r0, 6 r0, 1 an address
   constant, 3 a number, 8 memory) */
int gen_mem_index_plain(gen_node *node, gen_node *left, gen_node *right, int other)
{
    int mode = mem_index_mode(), bit;
    FILE *f;
    bit = other == 7 ? 1 : other == 1 ? 2 : other == 8 ? 4 : other == 6 ? 8 : 0;
    f = mem_index_log_file();
    if (f) {
        gen_node *parent = node->parent;
        fprintf(f, "%s line %d other %d %s left op %02x right op %02x access type %02x usage %d\n",
                gen_function_name ? gen_function_name : "?", node->line, other, (mode & bit) ? "add" : "r26",
                (unsigned char)left->op, (unsigned char)right->op, parent->type,
                parent->desc ? parent->desc->usage : -1);
        fflush(f);
    }
    return (mode & bit) != 0;
}
#endif
