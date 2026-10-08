/* an address derived from the loop variable and used again in the statement that first takes it, when that
   statement is an assignment: a record moved up one place while the variable counts down, and a member set
   from another member of the same element (the rule steps a new temporary and copies it on each pass, Release
   26 steps the first); a scaled index used by two statements while the variable counts down (the same); and
   the address of an element used by two statements while the variable counts down (stepped as it is with
   and without the rule) */
typedef struct { long name; long score; long wins; long grade; long stage; } rank;
typedef struct { char pad[70]; char flip; char pad2[5]; short dir; char pad3[122]; } part;
typedef struct { short x; short y; } pos;
extern rank ranks[20];
extern part parts[4];
extern char base_flip;
extern pos *trail[2];
short insert(short at)
{
    short j;
    for (j = 3; j >= at; j--) {
        ranks[j + 1] = ranks[j];
    }
    return at;
}
void flip_parts(void)
{
    short i;
    for (i = 0; i < 4; i++) {
        parts[i].flip = base_flip ^ (char)parts[i].dir;
    }
}
void age_trail(void)
{
    short i;
    for (i = 47; i > 0; i--) {
        trail[0][i] = trail[0][i - 1];
        trail[1][i] = trail[1][i - 1];
    }
}
void push_pos(pos *buf)
{
    short i;
    for (i = 16; i > 0; i--) {
        buf[i].x = buf[i - 1].x;
        buf[i].y = buf[i - 1].y;
    }
}
