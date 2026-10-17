/* Full-width XOR/self-test fold. Deadness is proved
   from current records on every modeled successor; unknown paths reject. */
#include "decls.h"
#include "xortest.h"
#include "pep_rules.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 256
#define MAX_RECORDS 16384
typedef struct cursor { code_node *node; int slot; } cursor;
typedef struct proof {
    flow_block *blocks[MAX_BLOCKS];
    unsigned char state[MAX_BLOCKS];
    int count, reg, budget;
    const char *why;
} proof;

static int enabled(void)
{
    return pep_xor_test()!=0;
}

static void report(const char *event, psd *rec, const char *why)
{
    const char *p=getenv("PEP_XOR_TEST_LOG");
    FILE *f;
    symbol *s;
    if (!p || !*p || !(f=fopen(p,"a"))) return;
    s=g_current_node_list ? find_label_symbol(g_current_node_list->labno) : 0;
    fprintf(f,"%s function=%s line=%u exp=%d reason=%s\n",event,
            s && s->name ? s->name : "?",rec ? (unsigned)rec->linno : 0,
            rec ? rec->expno : 0,why ? why : "?");
    fclose(f);
}

static int fail(proof *p, const char *why) { p->why=why; return 0; }
static int gp(ea *e)
{
    return e && e->type==1 && e->base>=0 && e->base<16 &&
           e->disp==0 && !e->labels;
}
static int immediate(ea *e)
{
    return e && e->type==7 && !e->labels && e->disp>=-128 && e->disp<=127;
}
static int plain(psd *r)
{
    return r && r->flg==2 && r->misc==0 && r->tmp==-1;
}
static int note(psd *r)
{
    return r->op==OP_DUMMY || r->op==OP_LINE ||
           r->op==OP_BBGN || r->op==OP_BEND;
}
static void advance(cursor *c)
{
    if (++c->slot==15) { c->slot=0; c->node=c->node->next; }
}
static psd *next_test(cursor *c)
{
    int budget=MAX_RECORDS;
    while(c->node && c->node->psd[c->slot].op==OP_DUMMY) {
        if(--budget<0)return 0;
        advance(c);
    }
    return c->node?&c->node->psd[c->slot]:0;
}
static int locate(flow_block *b,psd *r,cursor *out)
{
    code_node *n;int i,budget=MAX_RECORDS;
    for(n=b->code;n && budget>0;n=n->next) for(i=0;i<15 && budget>0;++i,--budget)
        if(&n->psd[i]==r) {out->node=n;out->slot=i;return 1;}
    return 0;
}
static int ordinary_function(int reg)
{
    symbol *s;aux_record *aux;cursor entry;psd *r;int entered=0,limit=64;
    if (!g_current_request || !g_aux_record_table || !g_current_node_list ||
        !g_current_node_list->labno ||
        g_current_node_list->psd[0].op!=OP_FLABEL ||
        g_current_aux_index<0 || g_current_aux_index>=g_current_request->aux_count)
        return 0;
    s=find_label_symbol(g_current_node_list->labno);
    if(!s || s->aux_index!=g_current_aux_index || s->attr!=0) return 0;
    aux=&g_aux_record_table[g_current_aux_index];
    if(aux->flags & 0x7fff) return 0;
    /* GEN suppresses ENTER for a distinct special function flag that is not
       fully represented by ordinary attrs. Require a real ordinary entry. */
    entry.node=g_current_node_list;entry.slot=0;advance(&entry);
    while(entry.node && --limit>0) {
        r=&entry.node->psd[entry.slot];advance(&entry);
        if(note(r))continue;
        entered=r->op==OP_ENTER && !r->misc && !(r->flg & 0xc0);
        break;
    }
    if(!entered)return 0;
    /* Ordinary GP scratch class, excluding the architectural GP result and
       every request-reserved register. SP and callee-saved GPs are outside it. */
    return reg>0 && reg<8 && !(g_current_request->reg_mask_150 & (1u<<reg));
}
static int block_index(proof *p,flow_block *b)
{
    int i;for(i=0;i<p->count;++i)if(p->blocks[i]==b)return i;return -1;
}
static int setup(proof *p,int reg)
{
    flow_block *b;int i;
    p->count=0;p->reg=reg;p->budget=MAX_RECORDS;p->why="unknown";
    for(b=g_flow_blocks;b;b=b->next) {
        if(p->count==MAX_BLOCKS || block_index(p,b)>=0)return fail(p,"bad-block-list");
        if(!b->code)return fail(p,"missing-code");
        i=p->count++;p->blocks[i]=b;p->state[i]=0;
    }
    return p->count>0;
}
static int masks(proof *p,psd *r,uint *uses,uint *defs)
{
    if(compute_record_register_use_def(r,uses,defs)!=0)return fail(p,"mask-barrier");
    return 1;
}
static int has(uint *m,int reg) { return (m[0] & g_reg_mask_table[reg])!=0; }
static int tail_notes(proof *p,cursor c)
{
    while(c.node) {
        if(--p->budget<0)return fail(p,"budget");
        if(!note(&c.node->psd[c.slot]))return fail(p,"record-after-control");
        advance(&c);
    }
    return 1;
}
static int prove_block(proof *p,flow_block *b);
static int prove_stream(proof *p,flow_block *b,cursor c,int entry)
{
    psd *r;uint uses[2],defs[2];label_ref *lab;int is_branch;
    while(c.node) {
        if(--p->budget<0)return fail(p,"budget");
        r=&c.node->psd[c.slot];advance(&c);
        if(note(r))continue;
        if(r->op==OP_LABEL || r->op==OP_DLABEL || r->op==OP_CLABEL) {
            if(!entry)return fail(p,"internal-label");
            continue;
        }
        entry=0;
        if(r->op==OP_EXIT) {
            if(r->misc || r->flg!=0 || r->tmp!=-1 || r->ea1 || r->ea2 || !tail_notes(p,c))
                return fail(p,"abnormal-exit");
            if(!masks(p,r,uses,defs))return 0;
            if(has(uses,p->reg))return fail(p,"exit-use");
            return 1; /* Ordinary ABI result/reserved class was excluded. */
        }
        is_branch=r->op==OP_JUMP || r->op==OP_JUMPT || r->op==OP_JUMPF || r->op==OP_RETURN;
        if(is_branch) {
            if(r->misc || r->flg!=0 || r->tmp<0 || r->tmp>=16 || r->ea2 || !r->ea1 ||
               r->ea1->type!=7 || !(lab=r->ea1->labels) || lab->next ||
               !lab->labno1 || lab->labno2 || block_index(p,b->target)<0 ||
               b->code->target_labno!=lab->labno1 ||
               b->target->code->labno!=lab->labno1 || !tail_notes(p,c))
                return fail(p,"unknown-target-or-slot");
            if(!masks(p,r,uses,defs))return 0;
            if(has(uses,p->reg))return fail(p,"branch-use");
            /* GP tmp defs on pseudo branches are MAY clobbers. NEVER kills. */
            if(!prove_block(p,b->target))return 0;
            if(r->op==OP_JUMPT || r->op==OP_JUMPF) {
                if(!b->next)return fail(p,"missing-fallthrough");
                return prove_block(p,b->next);
            }
            return 1;
        }
        if(!plain(r))return fail(p,"uncertified-flags");
        switch(r->op) {
        case OP_MOVI:
            if(!immediate(r->ea1) || !gp(r->ea2))return fail(p,"uncertified-movi");
            break;
        case OP_MOV:
            if(!gp(r->ea1) || !gp(r->ea2))return fail(p,"uncertified-mov");
            break;
        case OP_ADD:
        case OP_SUB:
        case OP_AND:
        case OP_OR:
        case OP_XOR:
            if(!gp(r->ea2) || !(gp(r->ea1) || (r->op==OP_ADD && immediate(r->ea1))))
                return fail(p,"uncertified-arithmetic");
            /* Explicit RMW check supplements (never weakens) helper uses. */
            if(r->ea2->base==p->reg)return fail(p,"rmw-use");
            break;
        default:return fail(p,"uncertified-opcode");
        }
        if(!masks(p,r,uses,defs))return 0;
        if(has(uses,p->reg))return fail(p,"register-use");
        /* Only certified unconditional full-width direct destinations kill. */
        if(r->ea2->base==p->reg && has(defs,p->reg))return 1;
    }
    if(b->code->target_labno || b->target || (b->flags & (1|2|8|0x20)))
        return fail(p,"missing-control");
    if(!b->next)return fail(p,"unknown-end");
    return prove_block(p,b->next);
}
static int prove_block(proof *p,flow_block *b)
{
    int i=block_index(p,b);cursor c;int ok;
    if(i<0)return fail(p,"foreign-block");
    if(p->state[i]==1)return fail(p,"cycle");
    if(p->state[i]==2)return 1;
    if(p->state[i]==3)return 0;
    p->state[i]=1;c.node=b->code;c.slot=0;
    ok=prove_stream(p,b,c,1);p->state[i]=ok?2:3;return ok;
}
int pep_dead_xor_candidate(flow_block *b,psd *x,psd *t)
{
    proof p;cursor c;psd *next;int rd;
    if(!x || !t || x->op!=OP_XOR || t->op!=OP_TST || !plain(x) || !plain(t) ||
       !gp(x->ea1) || !gp(x->ea2) || !gp(t->ea1) || !gp(t->ea2) ||
       x->ea2->base!=t->ea1->base || x->ea2->base!=t->ea2->base) return 0;
    rd=x->ea2->base;
    if(!ordinary_function(rd)) {report("reject",x,"abi-domain");return 0;}
    if(!b || !locate(b,x,&c))return 0;
    advance(&c);
    next=next_test(&c);
    if(next!=t)return 0;
    advance(&c);
    if(!setup(&p,rd) || block_index(&p,b)<0 || !prove_stream(&p,b,c,0)) {
        report("reject",x,p.why);return 0;
    }
    return 1;
}
void pep_fold_dead_xor_tests(void)
{
    flow_block *b;code_node *n;int i,bi,budget=MAX_RECORDS;cursor c;psd *x,*t;proof graph;
    if(!enabled())return;
    if(!setup(&graph,-1))return;
    for(bi=0;bi<graph.count;++bi) {
      b=graph.blocks[bi];
      for(n=b->code;n;n=n->next)for(i=0;i<15;++i) {
        if(--budget<0) {report("reject",0,"outer-node-budget");return;}
        x=&n->psd[i];if(x->op!=OP_XOR)continue;
        c.node=n;c.slot=i;advance(&c);
        t=next_test(&c);
        if(pep_dead_xor_candidate(b,x,t)) {
            report("fold",x,"all-successors-dead");
            x->op=OP_CMP_EQ;delete_psd_record(t);
        }
      }
    }
}
