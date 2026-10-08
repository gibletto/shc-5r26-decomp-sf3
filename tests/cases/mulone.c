/* MDL_MUL_ONE: the index of a char array is (long)x * 1, and with -extra=m=8 the product stays in the tree, so
   Release 26 takes (long)x and (long)x * 1 for two values. The rule folds the product when x is read from memory.
   keep: the element is and-assigned. Release 26 copies the index out of r0 (MOV R0,R3), loads the table's
   address, reads through it, and loads the address a second time for the store (ADD R3,R1). With the rule the
   index stays in r0, the address is loaded once, read indexed (MOV.B @(R0,R1),R2) and copied for the store
   (MOV R1,R3, ADD R0,R3).
   next: one byte member indexes two byte tables. Release 26 extends the second read into another register and
   loads the table's address into r0 (EXTU.B R0,R4, MOV.L cols,R0, MOV.B @(R0,R4),R4); with the rule the index
   stays in r0 and the address is in a scratch register (EXTU.B R0,R0, MOV.B @(R0,R2),R4). */
struct work {
    char pad[8];
    short id;
    unsigned char type;
    unsigned char op;
};
extern char flags[];
extern const unsigned char times[];
extern const unsigned char cols[];
extern void load(short c);

int keep(struct work *w)
{
    return flags[w->id] &= 0x80;
}

void next(struct work *w)
{
    w->type = times[w->op];
    load(cols[w->op]);
}

/* not the rule's case: the index is a variable, MDL_CAST_MUL's subject, and its product by 1 is left alone */
int plain(short ix)
{
    return flags[ix] &= 0x80;
}
