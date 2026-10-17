#include "ghidra_stubs.h"
#include "stage_types.h"
#include "narrow_normalize_proof.h"
#include "gen_rules.h"
#include <assert.h>

unsigned char g_sd[0x20000];
int copy_ea_into(ea *dest,ea *source) { *dest=*source;return 0; }
static gen_node n,c,l,r,p,k;
static node_desc nd,cd,ld,pd,kd;
static sym_entry syms[256],fn;
static lreg_entry rows[3];
static short represented;
static tmpl_header cast,compare;
static tmpl_entry ext[2],cmp[2];
static unsigned int reserved;
static int tests;

static void setup(void)
{
    memset(&n,0,sizeof n);memset(&c,0,sizeof c);memset(&l,0,sizeof l);
    memset(&r,0,sizeof r);memset(&p,0,sizeof p);memset(&k,0,sizeof k);
    memset(&nd,0,sizeof nd);memset(&cd,0,sizeof cd);memset(&ld,0,sizeof ld);
    memset(&pd,0,sizeof pd);memset(&kd,0,sizeof kd);
    memset(syms,0,sizeof syms);memset(rows,0,sizeof rows);memset(&fn,0,sizeof fn);
    memset(&cast,0,sizeof cast);memset(&compare,0,sizeof compare);
    memset(ext,0,sizeof ext);memset(cmp,0,sizeof cmp);
    reserved=0;
    n.op=IL_CAST;n.type=16;n.desc=&nd;n.child=&c;n.parent=&p;
    c.op=IL_A_ADD;c.type=12;c.desc=&cd;c.child=&l;
    l.op=IL_ID;l.type=12;l.symx=1;l.lreg=1;l.desc=&ld;l.next=&r;
    p.op=IL_GT;p.type=16;p.desc=&pd;p.child=&n;n.next=&k;
    k.op=IL_CONST;k.type=17;k.desc=&kd;
    cd.opnd_class=ld.opnd_class=1;
    cd.value.type=ld.value.type=1;cd.value.base=ld.value.base=6;
    cd.value.index=ld.value.index=-1;
    nd.tmpl=&cast;cast.result=3;cast.reg_spec[0]=0x180000;cast.entries=ext;
    ext[0].op=0x300;ext[0].opnd[0]=0xa9;ext[0].opnd[1]=0x5e;ext[0].opnd[2]=0xfa;
    ext[1].op=0xff00;
    pd.usage=1;pd.tmpl=&compare;compare.flags=4;compare.entries=cmp;
    cmp[0].op=0x600;cmp[1].op=0xff00;
    syms[183].flags=128;syms[183].sclass=5;syms[183].type=12;syms[183].reg=-1;
    represented=1;rows[0].lreg=1;rows[0].reg=6;rows[0].type=12;
    rows[0].count=1;rows[0].symbols=&represented;rows[0].storage=ld.value;
    fn.sym_flags=4;
}
static void check(const char *name,int want)
{
    gen_node saved_n=n;node_desc saved=nd;
    const ea *got=nn_owned_home(&n,syms,256,rows,reserved,&fn);
    assert(!!got==want);assert(!memcmp(&saved,&nd,sizeof nd));
    assert(!memcmp(&saved_n,&n,sizeof n));
    printf("PASS %s %s\n",name,want?"accept":"reject");++tests;
}
#define NEG(name,change) do {setup();change;check(name,0);} while(0)
int main(int argc,char **argv)
{
    int type,op,home;
    setup();check("ordinary",1);
    for(type=0;type<=12;type+=4)for(op=IL_A_ADD;op<=IL_A_SUB;++op) {
        setup();c.type=l.type=syms[183].type=rows[0].type=(unsigned char)type;
        c.op=(unsigned char)op;check("integer-narrow-compound",1);
    }
    for(op=IL_LT;op<=IL_GE;++op){setup();p.op=(unsigned char)op;check("relational-family",1);}
    for(home=1;home<15;++home){setup();cd.value.base=ld.value.base=rows[0].storage.base=rows[0].reg=(char)home;check("generic-home",1);}
    NEG("parameter",syms[183].sclass=7);
    NEG("address-observable",syms[183].flags|=0x20);
    NEG("symbol-extension",syms[183].ext=(sym_extension*)1);
    NEG("local-qualified",l.type|=1);
    NEG("volatile",l.type|=2);
    NEG("wide-result",c.type=l.type=20);
    NEG("pointer",c.type=l.type=64);
    NEG("memory-left",l.op=IL_ASTER);
    NEG("postincrement",c.op=IL_POI);
    NEG("negative-lreg",l.lreg=-1);
    NEG("special-lreg",l.lreg=(short)0x8000);
    NEG("hidden-symbol",l.symx=-1);
    NEG("frame-home",rows[0].reg=-1);
    NEG("coalesced-symbols",rows[0].count=2);
    NEG("wide-canonical",rows[0].type=20);
    NEG("mixed-symbol",syms[183].type=20);
    NEG("wrong-owner",represented=2);
    NEG("parameter-flag",rows[0].flags=0x40);
    NEG("special-r0",rows[0].flags=0x80);
    NEG("same-home-other-web",rows[1]=rows[0];rows[1].lreg=2);
    NEG("fixed-global",syms[200].flags=128;syms[200].sclass=1;syms[200].reg=6);
    NEG("direct-alias",syms[200].flags=128;syms[200].storage=ld.value);
    NEG("reserved-home",reserved=1u<<6);
    NEG("raw-r0",ld.value.base=cd.value.base=0);
    NEG("stack-pointer",ld.value.base=cd.value.base=15);
    NEG("memory-result",cd.mem_ea=&ld.value);
    NEG("popped-result",cd.flags2=8);
    NEG("different-result",cd.value.base=5);
    NEG("temporary-result",cd.opnd_class=0);
    NEG("required-dest",nd.dest=ld.value);
    NEG("required-target",nd.target_regs=64);
    NEG("preferred-result",nd.pref_regs=64);
    NEG("conversion-clobber",cast.clobbers=1);
    NEG("extra-slot",cast.reg_spec[1]=0x180000);
    NEG("conversion-runtime",ext[0].op=0x2300);
    NEG("conversion-source",ext[0].opnd[0]=0xaa);
    NEG("arithmetic-consumer",p.op=IL_ADD);
    NEG("equality-unreviewed",p.op=IL_EQ);
    NEG("floating-consumer",k.type=32);
    NEG("pointer-consumer",k.type=64);
    NEG("value-consumer",pd.usage=2);
    NEG("consumer-destination",pd.dest=ld.value);
    NEG("destructive-consumer",cmp[0].op=0x100);
    NEG("special-function",fn.attr=0x10);
    NEG("interrupt-function",fn.sym_flags=0x10);
    NEG("assembly-function",fn.sym_flags=0x40);
    NEG("fixed-symbol",syms[183].reg=6);
    printf("PASS %d actual-helper cases\n",tests);
    {
        request request_value;
        int want=argc>1?atoi(argv[1]):1;
        memset(&request_value,0,sizeof request_value);
        setup();syms[0]=fn;
        *(request **)(g_sd+0x1eea0)=&request_value;
        *(sym_entry **)(g_sd+0x1f9b0)=syms;
        *(lreg_entry **)(g_sd+0x1fa10)=rows;
        *(short *)(g_sd+0x1eea8)=0;
        *(unsigned int *)((unsigned char *)&request_value+0xb0)=256-0xb7;
#if SHC_REBUILD_UPDATED
        assert(gen_narrow_normalize_mode()==want);
#else
        want=0;
#endif
        NARROW_NORMALIZE(&n);
        assert(!!nd.dest.type==want);
        if(want)assert(!memcmp(&nd.dest,&ld.value,sizeof(ea)));
        printf("PASS actual setting reader+late destination: %d\n",want);
    }
    return 0;
}
