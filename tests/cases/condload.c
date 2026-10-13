/* a global that the right operand of && tests and both a later arm and a later statement read: the block that holds
   the condition does not read it on every path, so one load after the first test serves the later reads, and the
   comparison loads it again */
extern char two_coin;
extern char request[2];
extern char credit;
extern void more(int n);
extern void insert(int n);

int credit_state(void)
{
    char status;
    if (two_coin != 0 && request[0] == 0 && credit < 2) {
        status = 99;
    } else {
        status = request[0] | credit;
    }
    switch (status) {
    case 0:
        insert(0);
        break;
    case 99:
        if (credit) {
            more(1);
        } else {
            insert(1);
        }
        break;
    default:
        more(2);
        break;
    }
    return status;
}
