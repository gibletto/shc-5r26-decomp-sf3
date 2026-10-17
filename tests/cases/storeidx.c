/* a store through `base + index`, both in registers, of a quotient (the division routine returns it in r0): the
   address is made after the value, base first (mov r14,r2 / add r6,r2 / ... / mov.w r0,@r2); Release 26 makes
   it before the value with the add template (mov r6,r3 / add r14,r3 / ... / mov.w r0,@r3) */
extern unsigned long digit_table[];
extern void put_digits(short *d, short *r);

void split_digits(unsigned long v)
{
    short i;
    short rest[6];
    short digit[6];
    for (i = 5; i > 0; i--) {
        digit[i] = v / digit_table[i];
        rest[i] = v = v % digit_table[i];
    }
    digit[i] = v;
    put_digits(digit, rest);
}

/* the value is made in r0 by an operation with a constant (or #1,r0): no change, the add template as in
   Release 26 */
extern short lever_buff[];
extern short lever_pool[];
extern int unit_busy(short id);

void lever_set(short id, int up)
{
    if (unit_busy(id)) {
        lever_buff[id] = 0;
    } else if (lever_buff[id] & 2) {
        lever_buff[id] |= lever_pool[id];
    } else if (up) {
        lever_buff[id] = lever_pool[id] | 1;
    }
    lever_buff[id] |= lever_pool[id];
}
