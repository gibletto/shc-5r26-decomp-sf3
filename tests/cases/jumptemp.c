/* GEN_JUMP_TEMP: a loop body that ends in continue, and a switch in a loop whose cases leave by break. In age
   the copy of the stepped index that the second assignment reads lives through the statement in front of the
   continue; in tick the scaled index lives through the statements in front of the cases' breaks. Release 26
   charges the jump's scratch register to that statement, so the value keeps a saved register; with the rule it
   moves to the scratch register and one register less is saved. */
typedef struct { short x; short y; short z; short n; short r; short h; char f; char c; short k; } ghost;
typedef struct { short nx; short ny; short col; unsigned short chr; } mark;
typedef struct { char pad[1024]; mark m[108]; } board;
extern ghost *trail[2];
extern short marks;
extern const short waits[];
void age(void)
{
    short i;
    for (i = 47; i > 0; i--) {
        trail[0][i] = trail[0][i - 1];
        trail[1][i] = trail[1][i - 1];
        continue;
    }
}
void tick(board *bd)
{
    short i;
    for (i = 0; i < marks; i++) {
        switch (bd->m[i + 20].ny) {
        default:
            if (--bd->m[i + 20].col > 0) {
                break;
            }
        case 0:
            bd->m[i + 20].col = waits[bd->m[i + 20].ny];
            bd->m[i + 20].ny++;
            bd->m[i].chr++;
            break;
        case 4:
            break;
        }
        continue;
    }
}
