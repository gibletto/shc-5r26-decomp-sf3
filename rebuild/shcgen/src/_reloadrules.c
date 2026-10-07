/* GEN_RELOAD (only with SHC_REBUILD_UPDATED=1): a variable's last reference does not take a register copy.

   After `v = expr` generate_assign_node records the scratch register that held the value as holding v
   (record_variable_in_register), and a load of v does the same; the next reference to v asks
   find_register_holding_variable, and on a hit uses the register in place of v's frame slot. For a short or char
   that is `exts.w r0,r7` where the slot would be read again; for a long the read becomes a register copy.

   The optimizer numbers each reference with its logical register (lreg) and writes the number negated on the
   reference that ends the logical register's life (write_lreg_numbers / set_node_lreg_number in shcmdl).
   Release 26 looks a reference up by the absolute value of that number. The arcade's compiler finds nothing for a
   negated number: the last reference to a variable kept in memory reads the frame slot again, even straight after
   the store (`mov.w r0,@(12,r15)`, `mov.w @(12,r15),r0`, `mov r0,r7`), while a reference that is not the last, or a
   variable with no logical register (a global, a local whose address is taken), still takes the register. The
   record itself stays, so the choice of scratch registers around it does not change.

   Measured on the game (Street Fighter III 3rd Strike, every C routine): of the short variables our build forwards
   from the register an assignment left them in and whose store exists in the arcade's code, the arcade reads the
   slot again at 72 sites, all 72 with a negated number, and forwards at 21, none negated (19 with no logical
   register, 2 not the last reference). Not recording shorts at all, or refusing every short hit, loses the 21.
   The same holds for the char sites that can be read off the code and for the pointer temporaries the peephole
   stage does not turn back into a register copy (test_menu_select).

   GEN_RELOAD=1 (unset: 1, the arcade rule; 0: Release 26). GEN_RELOAD_LOG=<file> (a diagnostic, off unless set; a
   %d in the name is replaced by the process id) logs each reference the rule sends back to its slot. */
#if SHC_REBUILD_UPDATED
#include <stdlib.h>
#include <stdio.h>
#include <process.h>
#include "decls.h"
#include "imports.h"
#include "reloadrules.h"

extern char *gen_function_name;

static FILE *reload_log_file(void)
{
    static FILE *f;
    static int opened;
    if (!opened) {
        const char *p = getenv("GEN_RELOAD_LOG");
        char path[512];
        opened = 1;
        if (p && *p) {
            _snprintf(path, sizeof path, p, _getpid());
            f = fopen(path, "a");
        }
    }
    return f;
}

int gen_reload_last_use(gen_node *node)
{
    static int mode = -1;
    FILE *f;
    if (mode < 0) {
        const char *p = getenv("GEN_RELOAD");
        mode = (p && *p) ? atoi(p) : 1;
    }
    /* 0x8000 is not a negated number: it marks the frame pointer's own node (prepare_identifier_node) */
    if (mode == 0 || node->lreg >= 0 || (unsigned short)node->lreg == 0x8000) {
        return 0;
    }
    f = reload_log_file();
    if (f) {
        int r;
        for (r = 0; r < 4; r++) {
            reg_content *c = &g_gpr_contents[r];
            if (c->u.lreg == -node->lreg && (c->flags & 0x40) == 0 && c->value == (int)node->symx
                && c->type == node->type) {
                fprintf(f, "%s line %d type %02x symx %d lreg %d r%d\n", gen_function_name ? gen_function_name : "?",
                        node->line, node->type, node->symx, node->lreg, r);
                fflush(f);
                break;
            }
        }
    }
    return 1;
}
#endif
