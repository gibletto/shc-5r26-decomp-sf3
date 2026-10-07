/* MDL_CAST_MUL: ix indexes a short array (scaled by 2) and then a char array (scaled by 1) in three blocks. The
   common-expression pass leaves (long)ix alone because its first use is the operand of a multiplication; Release 26
   then keeps (long)ix * 1, the char array's index, in a register for the three blocks (exts.w r5,r4 once, r12
   saved for it). With the rule that product takes no temporary and each use extends ix again (exts.w r5,r0). */
extern unsigned short pad_now, pad_old;
extern short timer[4];
extern signed char count[4];
signed char repeat(unsigned short sw, short ix)
{
    if (~pad_old & pad_now & sw) {
        return 1;
    }
    if (pad_now & sw) {
        timer[ix]++;
        if (timer[ix] > 10) {
            count[ix]++;
            if (count[ix] > 8) {
                count[ix] = 0;
                return 1;
            }
        }
    } else {
        timer[ix] = 0;
        count[ix] = 0;
    }
    return 0;
}

/* not the rule's case: ix only indexes char arrays, so the first (long)ix is scaled by 1 and the product keeps its
   temporary under both settings, as the arcade does */
extern signed char other[4];
signed char both(short ix)
{
    if (pad_now) {
        other[ix] = 1;
        if (pad_old) {
            count[ix] = 1;
        }
    } else {
        count[ix] = 0;
    }
    return 0;
}
