/* GEN_MEM_INDEX: in each of these the address of the last read is the sum of a pointer still in memory (a row of
   a table of pointers, a pointer kept in a global) and an index in a register. Release 26 loads the pointer into
   r0 and reads through @(R0,Rn); with the rule the pointer goes to a scratch register and is added (ADD R2,R6 and
   MOV.L @R6,R3 in set_script; MOV.L @R2,R3, ADD R3,R5 and MOV.L @R5,R1 in set_word). script_word returns the value,
   which is wanted in r0, so its row lands in r0 and the read stays indexed either way. */
typedef struct {
    short pad[112];
    short kind;
    short index;
    unsigned long *table[12];
    unsigned long *script;
} WORK;

extern unsigned long *words;

void set_script(WORK *wk, short kind, short index)
{
    wk->script = (unsigned long *)wk->table[kind][index];
}

void reset_script(WORK *wk)
{
    wk->script = (unsigned long *)wk->table[wk->kind][wk->index];
}

unsigned long script_word(WORK *wk, short kind, short index)
{
    return wk->table[kind][index];
}

void set_word(WORK *wk, short index)
{
    wk->script = (unsigned long *)words[index];
}
