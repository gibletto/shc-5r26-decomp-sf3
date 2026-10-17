/* a value masked as it is stored: ((*cell++ = *tbl++) & 0x100) >> 8 keeps the widening of the stored unsigned
   short before the and (extu.w), as a variable or memory read does; MDL_MASK_AND bit 4 alone, which drops the
   widening of a computed value, drops it. pack_bits masks a variable and keeps its code (only its schedule moves
   with copy_cells' size) */
void copy_cells(unsigned short *cell, unsigned short *tbl, short w)
{
    while (w > 0) {
        w--;
        *cell++ = *tbl++ | (((*cell++ = *tbl++) & 0x100) >> 8);
    }
}

void pack_bits(unsigned short *cell, unsigned short v)
{
    *cell = (v & 0x100) >> 8;
}
