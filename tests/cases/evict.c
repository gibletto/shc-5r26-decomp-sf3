/* GEN_EVICT_ORDER: wins[loser] loads the address of loser into r3 and the address of wins into r2, and r2, noted as
   holding that constant, is then noted as holding the array. Release 26 forgets r2's own note first, so r3's
   survives and the next address goes to r1. Forgetting the older of the two first drops r3's (both are of the same
   statement and r3 is the higher register), so the next address goes to r3. */
extern short wins[2];
extern signed char loser, winner, versus;
extern signed char streak[2];
unsigned long bonus(void)
{
    if (versus == 1) {
        if (wins[loser]) {
            return 0;
        }
        return 30000;
    }
    if (wins[loser]) {
        return streak[winner] = 0;
    }
    streak[winner]++;
    return streak[winner];
}
