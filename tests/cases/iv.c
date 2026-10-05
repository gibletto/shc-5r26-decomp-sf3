/* a loop over an array of 6-byte records: the address of record i is a char-cast product of the counter
   ((char)(i * 6)), which the rule strength-reduces like i * 6 */
typedef struct { char a, b, c, d; short e; } rec;
extern struct { short n; short m; rec r[3]; } w;
void clear(void)
{
    short i;
    for (i = 0; i < 3; i++) {
        w.r[i].a = 0;
        w.r[i].b = 0;
    }
}
