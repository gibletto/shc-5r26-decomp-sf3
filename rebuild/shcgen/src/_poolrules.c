/* GEN_POOL_MOVLOC (only with SHC_REBUILD_UPDATED=1): the size of a frame-slot load or store in the literal pool
   window of an unoptimized unit.

   With -optimize=0 this stage places the literal pools itself (decide_literal_pool_placement): it adds up an
   estimate of each record's code and literals and puts a pool after an unconditional branch once the total passes
   the reach of a pc-relative load. compute_record_code_size estimates a MOV_LOC record (a load or store of a frame
   slot) as 6 bytes, the longest form (displacement through r0 with r0 saved in a temporary). The arcade's compiler
   counts 4: its pools in the unoptimized units come later than Release 26's by 2 bytes for each frame-slot access
   since the last pool. Only the window changes here; the size written for the assembler stays 6 (counting 4 there
   as well gives the same code for the whole game).

   Measured on the game's 16 unoptimized units: of 492 pool decisions in routines whose instructions already match,
   461 are the same either way, 23 fit only 4, 2 fit only 6 (memtest_pattern_masked_word, config_bytes_equal) and
   6 fit neither (simm_quick_checksum, scsi_read_10). Counting 5 or 3, or 6 only when the record has a temporary
   register, each matches fewer routines. No flag of the record explains the 2: memtest_pattern_stride_8 has the same
   frame-slot records, a longer window, and no pool.

   GEN_POOL_MOVLOC=<n> (unset: 4; 0 = Release 26): count a MOV_LOC record as n bytes. */
#if SHC_REBUILD_UPDATED
#include <stdlib.h>
#include "decls.h"
#include "imports.h"
#include "poolrules.h"

int gen_pool_record_size(psd *rec, int size)
{
  static int n = -1;
  if (n < 0) {
    const char *p = getenv("GEN_POOL_MOVLOC");
    n = (p && *p) ? atoi(p) : 4;
  }
  if (rec->op == OP_MOV_LOC && n != 0) {
    return n;
  }
  return size;
}
#endif
