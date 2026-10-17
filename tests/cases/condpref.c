/* an assignment to a register from a conditional: the test takes no preference from the destination (msg, r7),
   so the tested value goes where the chooser puts it (mov.b @r2,r3 / cmp/ge r1,r3); Release 26 hands r7 to the
   test (mov.b @r3,r7 / cmp/ge r2,r7) */
extern signed char credit;
extern const signed char msg_one[];
extern const signed char msg_many[];
extern void print_at(int x, int y, int attr, const signed char *s);

void credit_line(int x)
{
    const signed char *msg;
    msg = (credit < 2) ? msg_one : msg_many;
    print_at(x + 6, 23, 18, msg);
}
