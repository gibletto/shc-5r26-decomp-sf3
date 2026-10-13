/* the instruction after a multiply: a register move waiting beside a literal load is issued first in either half
   of the long word (cases 1 and 3 start at 0 mod 4, where the alignment rule would take the literal load) */
typedef struct { short offence; short defence; short tech; short extra; short pad[2]; } JUDGE;
extern JUDGE judge_tbl[2];

int point_percentage(short ix, short kind)
{
    int n;
    switch (kind) {
    case 0:
        n = judge_tbl[ix].offence * 100;
        n /= 500;
        break;
    case 1:
        n = judge_tbl[ix].defence * 100;
        n /= 500;
        break;
    case 2:
        n = judge_tbl[ix].tech * 100;
        n /= 500;
        break;
    case 3:
        n = judge_tbl[ix].extra * 100;
        n /= 500;
        break;
    }
    if (n > 120) {
        n = 120;
    }
    return (short)n;
}
