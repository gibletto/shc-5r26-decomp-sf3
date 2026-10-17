/* the add evaluates its right operand (coin[who]) first; the left operand's index work then takes r0, so the note
   that r0 holds &coin is forgotten. Release 26 forgets it when the order is decided: when score's base address is
   loaded for @(r0,Rn) only the note of &win survives, and the store to total takes r0. The arcade forgets it after
   the add's template: the base address's note counts it and pushes out the older &win note, so the store takes
   the register that held &win (GEN_RIGHT_FIRST_DROP). */
extern signed char who, player;
extern signed char flags[2][24];
extern unsigned char last, target;
extern unsigned short win;
extern unsigned short wins[2];
extern unsigned char coin[2];
extern unsigned long score[2][3];
extern unsigned long total;

void result_set(void)
{
    if (flags[player][0] == 0) {
        last = who;
        target = who;
        win = wins[who];
        total = coin[who] + score[who][0];
    }
}
