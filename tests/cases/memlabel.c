/* GEN_MEM_INDEX, the bits after the first. In show_message the scaled index id * 2 is used twice and is kept in
   the frame; the second use adds it to the address of left[]. Release 26 loads that address into r0 and reads
   through @(R0,Rn) (MOV.L @R15,R2, MOV.W @(R0,R2),R1); with bit 2 the address goes to a scratch register and is
   added (MOV.L @R15,R1, ADD R2,R1, MOV.W @R1,R3). In take_word the index is in r0 and the pointer row is read
   from memory: Release 26 reads through @(R0,R2), with bit 8 the sum is an add (ADD R2,R0, MOV.W @R0,R1). */
extern short wide[];
extern short base[];
extern short left[];
extern short line;
extern void put();
extern unsigned long *rows;
extern unsigned long *row;
extern unsigned short word;
extern short pick;
extern short step;

void show_message(short id)
{
    put(base[wide[id]] + left[id], line, 18);
}

void take_word(void)
{
    row = (unsigned long *)rows[pick];
    word = ((unsigned short *)row)[step];
}
