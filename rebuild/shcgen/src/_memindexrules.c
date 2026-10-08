/* GEN_MEM_INDEX (only with SHC_REBUILD_UPDATED=1): a pointer that is still in memory is not loaded into r0 to index.

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

   Not changed, for want of a place in the game that decides it: both operands in memory (Release 26 loads one
   into r0 and the other into a register), which only Setup_PL_Color reaches with a scalar access. The game's
   unoptimized files have no such sum either, so the rule is not measured there.

   GEN_MEM_INDEX=1 (unset: 1, the arcade rule; 0: Release 26). GEN_MEM_INDEX_LOG=<file> (a diagnostic, off unless
   set; a %d in the name is replaced by the process id) logs each sum the rule leaves to the add template. */
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

int gen_mem_index_plain(gen_node *node, gen_node *left, gen_node *right)
{
    static int mode = -1;
    FILE *f;
    if (mode < 0) {
        const char *p = getenv("GEN_MEM_INDEX");
        mode = (p && *p) ? atoi(p) : 1;
    }
    if (mode == 0) {
        return 0;
    }
    f = mem_index_log_file();
    if (f) {
        gen_node *parent = node->parent;
        fprintf(f, "%s line %d left op %02x right op %02x access type %02x usage %d\n",
                gen_function_name ? gen_function_name : "?", node->line, (unsigned char)left->op,
                (unsigned char)right->op, parent->type, parent->desc ? parent->desc->usage : -1);
        fflush(f);
    }
    return 1;
}
#endif
