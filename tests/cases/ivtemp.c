/* an expression derived from the loop variable and used more than once: a scaled index used on both sides of
   an assignment (the rule steps a new temporary and copies it on each pass; Release 26 steps the first), the
   address of an element used by two statements (the same), the address of an element used twice in one
   statement (stepped as it is with and without the rule), and the index of two char arrays (the rule extends it
   on each pass; Release 26 steps a second counter) */
typedef struct { char pad[36]; short now[8]; short old[8]; } work;
typedef struct { char pad[94]; char status; char pad2[16]; char flags; char pad3[4]; } voice;
typedef struct { long ofs; long cell; } cell;
extern voice voices[16];
extern const cell cells[8];
extern void put();
void keep_old(work *wk)
{
    short i;
    for (i = 0; i < 8; i++) {
        wk->old[i] = wk->now[i];
    }
}
void stop_all(void)
{
    unsigned char i;
    for (i = 0; i < 16; i++) {
        voices[i].status = 192;
        voices[i].flags = 0;
    }
}
void put_all(void)
{
    short i;
    for (i = 0; i < 8; i++) {
        put(0, cells[i].ofs, cells[i].cell, 0);
    }
}
extern char faces[3][7];
extern const char cursor[3][7];
void copy_faces(void)
{
    short i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 7; j++) {
            faces[i][j] = cursor[i][j];
        }
    }
}
