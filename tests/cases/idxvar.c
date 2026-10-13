/* a char or short variable that indexes byte tables: the index (long)v * 1 is used as the converted value, with no
   temporary of its own, unless the variable's first use as an index is the test of an if */
extern char table_a[8];
extern char table_b[8];
extern short wide[8];
extern char who;
extern void note(int n);

int pick(short id)
{
    table_a[id] = 2;
    table_b[id] = 3;
    wide[id] = table_a[id] + table_b[id];
    return table_b[id];
}

void test_first(void)
{
    if (table_a[who]) {
        if (table_b[who]) {
            note(1);
        }
    }
}
