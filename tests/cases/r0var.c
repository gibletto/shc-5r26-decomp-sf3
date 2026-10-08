/* GEN_R0VAR: i is the index of three arrays in the loop. Release 26 makes it the r0 variable of each statement: it
   is extended into r0 once and every array is a base (EXTS.W R14,R0, MOV.B @(R0,R8),R3, MOV.B R3,@(R0,R9),
   MOV.B R13,@(R0,R11)). With the rule there is none: the index stays in a scratch register, the array read
   takes its address into r0 (MOV R8,R0, MOV.B @(R0,R4),R3) and the stores add (ADD R4,R2, MOV.B R3,@R2). */
extern char record[];
extern char stock[];
extern char seen[];
extern void show();

void keep_all(short n)
{
    short i;

    for (i = 0; i < n; i++) {
        show(i);
        stock[i] = record[i];
        seen[i] = 0;
    }
}
