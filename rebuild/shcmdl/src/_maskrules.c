/* The arcade's rule for a mask by 0xff, MDL_MASK_AND (only with SHC_REBUILD_UPDATED=1).

   Release 26's expression simplifier turns a bit-and with 0xff or 0xffff into a pair of casts: `x & 0xff` is
   (T)(unsigned char)x (simplify_bitand_bitor), and `v &= 0xff` on a variable is v = (T)(unsigned char)v
   (simplify_and_or_assign; an and-assignment to memory is left alone). shcgen then extends (extu.b r5,r5), or
   loads only the low byte of a short it has not loaded yet. The arcade's compiler leaves the 0xff mask an and:
   and #255,r0 where the value is in r0 (Check_Store_Lever: extu.w r5,r0 / and #255,r0 for `Tech_Number & 0xFF`),
   and a load of H'00FF and and r1,r5 where it is not (Setup_Char_Index: `xx &= 0xFF`). Its extu.b come from
   casts and unsigned char objects.

   MDL_MASK_AND=<bits> (unset: 3; 0: Release 26)
     1  `x & 0xff` stays a bit-and
     2  `v &= 0xff` stays an and-assignment
   0xffff is converted under every setting: the arcade program has no and with a register holding H'0000FFFF,
   and sound_note_to_pitch (`v &= 0xFFFF` on an int, extu.w in the arcade) matches with the conversion.
   The evidence over the Street Fighter III build is in tools/public/SF3.md and notes/shcmdl.md.
   MDL_MASK_LOG=<file> (a diagnostic, off unless set) lists each mask by 0xff the simplifier meets: function,
   bit, the and's type, source line and whether it was kept. The process id is appended to the name. */
#include "decls.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>

#define MASK_AND_DEFAULT 3

/* 1: make the casts (Release 26); 0: leave the and. mask is the constant operand, bit the asker (1 `&`, 2 `&=`) */
int mdl_mask_to_cast(il_node *node, il_node *mask, int bit)
{
    static FILE *log = (FILE *)1;
    static int bits = -1;
    if (is_const_value(mask, 0xff, node->type) == 0)
        return 1;
    if (bits < 0) {
        const char *v = getenv("MDL_MASK_AND");
        bits = (v && *v) ? atoi(v) : MASK_AND_DEFAULT;
    }
    if (log == (FILE *)1) {
        const char *p = getenv("MDL_MASK_LOG");
        char name[600];
        log = 0;
        if (p && *p && strlen(p) < 500) {
            sprintf(name, "%s.%d", p, (int)_getpid());
            log = fopen(name, "a");
        }
    }
    if (log) {
        fprintf(log, "%s\tbit=%d\tty=%02x\tline=%d\tkept=%d\n",
                g_func_node && g_func_node->symx > 0 ? g_symtab[g_func_node->symx].name : "?", bit, node->type,
                (int)node->line, (bits & bit) != 0);
        fflush(log);
    }
    return (bits & bit) == 0;
}
