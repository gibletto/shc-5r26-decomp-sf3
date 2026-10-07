/* MDL_MUL_CONST.
   round_item: 16 is in r12 for the test and the two divisions, and `cur *= 16` is a char multiply. Release 26
   leaves the constant in the multiply, which shcgen turns into two shll2; with the rule the multiply reads the
   register (muls.w r12 and sts macl, and the routine saves MACL).
   level: the same with 100, where Release 26 copies r12 to a scratch register for the multiply.
   percent: four int multiplies of a short by 100. Release 26 sets the constant aside for a 16-bit multiply and
   loads it at each one; with the rule 100 is a register candidate like any int multiply's constant and is kept
   in r7. */
extern signed char cur, old, keep, step;
extern unsigned short pad;
extern void show(int now, int before);

void round_item(void)
{
    step = 0;
    if (pad & 16) {
        step = 1;
    }
    if (step) {
        old /= 16;
        old &= 3;
        cur /= 16;
        cur &= 3;
        cur += step;
        show(cur, old);
        cur *= 16;
        cur &= 0x30;
        keep |= cur;
    }
}

extern short gauge, rest, rate;

void level(void)
{
    if (pad & 1) {
        gauge /= 100;
        rest /= 100;
        rate %= 100;
        show(gauge, rest);
        gauge *= 100;
        rest += gauge;
    }
}

struct totals { short offence, defence, tech, extra; };
extern struct totals total[2];

int percent(short side, short kind)
{
    int n;
    switch (kind) {
    case 0:
        n = total[side].offence * 100;
        n /= 500;
        break;
    case 1:
        n = total[side].defence * 100;
        n /= 500;
        break;
    case 2:
        n = total[side].tech * 100;
        n /= 500;
        break;
    case 3:
        n = total[side].extra * 100;
        n /= 500;
        break;
    }
    if (n > 120) {
        n = 120;
    }
    return n;
}
