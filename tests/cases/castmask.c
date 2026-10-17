/* a computed short masked by a constant inside 16 bits is not sign-extended first: `(short)-p->x & 0x3FF` is
   neg r5,r5 / and r14,r5 (Release 26: neg r5,r5 / exts.w r5,r5 / and r14,r5) */
typedef struct { short x; short y; } POS;
extern void set_pos(int n, int x, int y);

void put_pos(POS *p, int n)
{
    set_pos(n, (short)-p->x & 0x3FF, (768 - (p->y & 0x3FF)) & 0x3FF);
}

/* a memory operand keeps its cast (the load extends), as in Release 26 */
int low_bits(POS *p)
{
    return (short)p->y & 0x3FF;
}
