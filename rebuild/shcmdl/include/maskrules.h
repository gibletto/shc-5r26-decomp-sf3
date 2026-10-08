/* MDL_MASK_AND (src/_maskrules.c), compiled in with SHC_REBUILD_UPDATED=1; otherwise a mask by 0xff becomes a cast
   as in Release 26. */
#ifndef MASKRULES_H
#define MASKRULES_H
#if SHC_REBUILD_UPDATED
extern int mdl_mask_to_cast(il_node *node, il_node *mask, int bit);
#define MASK_TO_CAST(node, mask, bit) mdl_mask_to_cast(node, mask, bit)
#else
#define MASK_TO_CAST(node, mask, bit) 1
#endif
#endif
