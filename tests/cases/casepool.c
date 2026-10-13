/* a word constant loaded just before a switch jump table, and enough cases with long literals behind the table
   that the next literal pool falls at a different case under the word reach than under the long reach */
extern int a0;
extern int a1;
extern int a2;
extern int a3;
extern int a4;
extern int a5;
extern int a6;
extern int a7;
extern int a8;
extern int a9;
extern int a10;
extern int a11;
extern int a12;
extern int a13;
extern int a14;
extern int a15;
extern int a16;
extern int a17;
extern int a18;
extern int a19;
extern int a20;
extern int a21;
extern int a22;
extern int a23;
extern int a24;
extern int a25;
extern int a26;
extern int a27;
extern int a28;
extern int a29;
extern int a30;
extern int a31;
extern int a32;
extern int a33;
extern int a34;
extern int a35;
extern int a36;
extern int a37;
extern int a38;
extern int a39;
extern void put(int *, int);

void sel(int n, short *p)
{
    *p = 1000;
    switch (n) {
    case 0:
        put(&a0, 74565);
        break;
    case 1:
        put(&a1, 78934);
        break;
    case 2:
        put(&a2, 83303);
        break;
    case 3:
        put(&a3, 87672);
        break;
    case 4:
        put(&a4, 92041);
        break;
    case 5:
        put(&a5, 96410);
        break;
    case 6:
        put(&a6, 100779);
        break;
    case 7:
        put(&a7, 105148);
        break;
    case 8:
        put(&a8, 109517);
        break;
    case 9:
        put(&a9, 113886);
        break;
    case 10:
        put(&a10, 118255);
        break;
    case 11:
        put(&a11, 122624);
        break;
    case 12:
        put(&a12, 126993);
        break;
    case 13:
        put(&a13, 131362);
        break;
    case 14:
        put(&a14, 135731);
        break;
    case 15:
        put(&a15, 140100);
        break;
    case 16:
        put(&a16, 144469);
        break;
    case 17:
        put(&a17, 148838);
        break;
    case 18:
        put(&a18, 153207);
        break;
    case 19:
        put(&a19, 157576);
        break;
    case 20:
        put(&a20, 161945);
        break;
    case 21:
        put(&a21, 166314);
        break;
    case 22:
        put(&a22, 170683);
        break;
    case 23:
        put(&a23, 175052);
        break;
    case 24:
        put(&a24, 179421);
        break;
    case 25:
        put(&a25, 183790);
        break;
    case 26:
        put(&a26, 188159);
        break;
    case 27:
        put(&a27, 192528);
        break;
    case 28:
        put(&a28, 196897);
        break;
    case 29:
        put(&a29, 201266);
        break;
    case 30:
        put(&a30, 205635);
        break;
    case 31:
        put(&a31, 210004);
        break;
    case 32:
        put(&a32, 214373);
        break;
    case 33:
        put(&a33, 218742);
        break;
    case 34:
        put(&a34, 223111);
        break;
    case 35:
        put(&a35, 227480);
        break;
    case 36:
        put(&a36, 231849);
        break;
    case 37:
        put(&a37, 236218);
        break;
    case 38:
        put(&a38, 240587);
        break;
    case 39:
        put(&a39, 244956);
        break;
    }
}
