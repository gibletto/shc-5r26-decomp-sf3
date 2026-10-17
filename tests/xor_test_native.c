#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decls.h"
#include "xortest.h"
#include "pep_rules.h"
extern void _stockdata_relocate(void);

static request req;
static aux_record aux[1];
static symbol sym;
static flow_block blocks[6];
static code_node nodes[7];
static ea eas[96];
static label_ref labels[16];
static int ne,nl,checks;
#define CHECK(x) do { ++checks;if(!(x)){printf("FAIL %d %s\n",__LINE__,#x);exit(1);} }while(0)
static ea *reg(int r) {ea *e=&eas[ne++];e->type=1;e->base=(char)r;return e;}
static ea *imm(int v) {ea *e=&eas[ne++];e->type=7;e->disp=v;return e;}
static psd *ins(int b,int slot,psd_op op,int a,int d)
{
 psd *r=&nodes[b].psd[slot];r->op=op;r->flg=2;r->tmp=-1;
 if(a>=0)r->ea1=reg(a);if(d>=0)r->ea2=reg(d);return r;
}
static void movi(int b,int slot,int value,int dest)
{
 psd *r=ins(b,slot,OP_MOVI,-1,dest);r->ea1=imm(value);
}
static void branch(int b,int slot,psd_op op,int target,int tmp)
{
 psd *r=&nodes[b].psd[slot];label_ref *l=&labels[nl++];
 r->op=op;r->flg=0;r->tmp=(char)tmp;r->ea1=imm(0);r->ea1->labels=l;
 l->labno1=(short)(2000+target);nodes[b].target_labno=l->labno1;
 nodes[target].labno=l->labno1;blocks[b].target=&blocks[target];
}
static void ex(int b,int slot) {psd*r=&nodes[b].psd[slot];r->op=OP_EXIT;r->tmp=-1;}
static void reset(void)
{
 int i;
 memset(&req,0,sizeof req);memset(aux,0,sizeof aux);memset(&sym,0,sizeof sym);
 memset(blocks,0,sizeof blocks);memset(nodes,0,sizeof nodes);memset(eas,0,sizeof eas);memset(labels,0,sizeof labels);
 memset(g_symbol_hash,0,sizeof g_symbol_hash);ne=nl=0;
 req.aux_count=1;g_current_request=&req;g_aux_record_table=aux;g_current_aux_index=0;
 g_current_node_list=&nodes[0];g_flow_blocks=&blocks[0];nodes[0].labno=2000;
 sym.number=2000;sym.name="fixture";sym.aux_index=0;g_symbol_hash[2000%1021]=&sym;
 for(i=0;i<6;++i)blocks[i].code=&nodes[i];
 for(i=0;i<2;++i){blocks[i].next=&blocks[i+1];blocks[i+1].prev=&blocks[i];nodes[i].next_block=&nodes[i+1];}
 nodes[0].psd[0].op=OP_FLABEL;nodes[0].psd[1].op=OP_ENTER;
 ins(0,2,OP_XOR,4,3);ins(0,3,OP_TST,3,3);branch(0,4,OP_JUMPF,2,1);
 ins(1,0,OP_MOV,14,4);ins(1,1,OP_ADD,13,4);movi(1,2,28,3);
 nodes[2].psd[0].op=OP_LABEL;ex(2,1);
}
static int candidate(void) {return pep_dead_xor_candidate(&blocks[0],&nodes[0].psd[2],&nodes[0].psd[3]);}
static void masks(psd*r,uint *uses,uint *defs) {CHECK(compute_record_register_use_def(r,uses,defs)==0);}
int main(void)
{
 uint uses[2],defs[2];psd x,t,j;unsigned seed=0x12345678,a,b;int k;
 _stockdata_relocate();
 _putenv("PEP_XOR_TEST=");CHECK(pep_xor_test()==1);
 _putenv("PEP_XOR_TEST=0");CHECK(pep_xor_test()==0);
 _putenv("PEP_XOR_TEST=1");CHECK(pep_xor_test()==1);
 reset();CHECK(candidate());
 reset();nodes[1].psd[2].op=OP_MOV;nodes[1].psd[2].ea1=reg(3);nodes[1].psd[2].ea2=reg(4);CHECK(!candidate());
 reset();ins(2,1,OP_MOV,3,4);ex(2,2);CHECK(!candidate());
 reset();blocks[2].next=&blocks[3];nodes[2].psd[1].op=OP_DUMMY;ins(3,0,OP_MOV,3,4);ex(3,1);CHECK(!candidate());
 reset();ins(1,0,OP_ADD,4,3);masks(&nodes[1].psd[0],uses,defs);CHECK(uses[0]&g_reg_mask_table[3]);CHECK(defs[0]&g_reg_mask_table[3]);CHECK(!candidate());
 reset();ins(1,0,OP_MOV,3,3);masks(&nodes[1].psd[0],uses,defs);CHECK(uses[0]&g_reg_mask_table[3]);CHECK(!candidate());
 reset();nodes[0].psd[4].tmp=3;ins(2,1,OP_MOV,3,4);ex(2,2);
 masks(&nodes[0].psd[4],uses,defs);CHECK(defs[0]&g_reg_mask_table[3]);CHECK(!candidate()); /* MAYdef is not kill. */
 reset();nodes[0].psd[2].ea2->base=0;nodes[0].psd[3].ea1->base=nodes[0].psd[3].ea2->base=0;
 masks(&nodes[2].psd[1],uses,defs);CHECK(!(uses[0]&g_reg_mask_table[0]));CHECK(!candidate()); /* Returned R0 requires explicit ABI exclusion. */
 reset();nodes[0].psd[2].ea2->base=10;nodes[0].psd[3].ea1->base=nodes[0].psd[3].ea2->base=10;CHECK(!candidate());
 reset();nodes[0].psd[2].ea2->base=15;nodes[0].psd[3].ea1->base=nodes[0].psd[3].ea2->base=15;CHECK(!candidate());
 reset();req.reg_mask_150=1u<<3;CHECK(!candidate());
 reset();aux[0].flags=0x4000;CHECK(!candidate());
 reset();aux[0].flags=0x2000;CHECK(!candidate());
 reset();sym.attr=8;CHECK(!candidate());
 reset();sym.aux_index=1;CHECK(!candidate());
 reset();g_current_aux_index=1;CHECK(!candidate());
 reset();nodes[0].psd[1].op=OP_DUMMY;CHECK(!candidate());
 reset();nodes[1].psd[0].op=OP_NON_43;nodes[1].psd[0].ea1=nodes[1].psd[0].ea2=0;
 masks(&nodes[1].psd[0],uses,defs);CHECK(!candidate()); /* Barrier0 does not certify this opcode. */
 reset();blocks[0].target=0;CHECK(!candidate());
 reset();blocks[0].target=(flow_block*)1;CHECK(!candidate());
 reset();nodes[2].labno=2222;CHECK(!candidate());
 reset();memset(nodes[1].psd,0,sizeof nodes[1].psd);branch(1,0,OP_JUMP,1,1);CHECK(!candidate());
 reset();nodes[0].psd[2].flg=1;CHECK(!candidate());
 reset();nodes[0].psd[3].flg=1;CHECK(!candidate());
 reset();nodes[0].psd[2].flg=0x42;CHECK(!candidate());
 reset();nodes[0].psd[3].flg=0x82;CHECK(!candidate());
 reset();nodes[0].psd[2].misc=0x80;CHECK(!candidate());
 reset();nodes[0].psd[4].flg=2;CHECK(!candidate());
 reset();nodes[2].psd[1].flg=2;CHECK(!candidate());
 reset();nodes[0].psd[2].ea1->type=7;CHECK(!candidate());
 reset();nodes[0].psd[3].ea1->base=2;CHECK(!candidate());
 reset();nodes[1].psd[0].op=OP_CALL;CHECK(!candidate());
 reset();nodes[1].psd[0].op=OP_MOV_LOC;CHECK(!candidate());
 reset();labels[nl].labno1=2000;nodes[1].psd[2].ea1->labels=&labels[nl++];CHECK(!candidate());
 reset();blocks[2].next=0;nodes[2].psd[1].op=OP_DUMMY;CHECK(!candidate());
 reset();nodes[0].psd[2].ea1->base=3;CHECK(candidate()); /* Same-register identity valid, result dead. */
 reset();x=nodes[0].psd[2];t=nodes[0].psd[3];j=nodes[0].psd[4];nodes[0].psd[2].op=nodes[0].psd[3].op=nodes[0].psd[4].op=OP_DUMMY;
 nodes[0].psd[14]=x;nodes[0].next=&nodes[3];nodes[3].psd[0]=t;nodes[3].psd[1]=j;
 CHECK(pep_dead_xor_candidate(&blocks[0],&nodes[0].psd[14],&nodes[3].psd[0]));
 reset();t=nodes[0].psd[3];nodes[0].psd[3].op=OP_LINE;nodes[0].psd[4]=t;CHECK(!pep_dead_xor_candidate(&blocks[0],&nodes[0].psd[2],&nodes[0].psd[4]));
 reset();x=nodes[0].psd[2];memset(&nodes[0].psd[2],0,13*sizeof(psd));nodes[0].psd[14]=x;nodes[0].next=&nodes[3];nodes[3].next=&nodes[3];
 CHECK(!pep_dead_xor_candidate(&blocks[0],&nodes[0].psd[14],&nodes[0].psd[3]));
 pep_fold_dead_xor_tests();CHECK(nodes[0].psd[14].op==OP_XOR); /* Bounded malformed node cycle. */
 for(k=0;k<2000;++k) {seed=seed*1664525u+1013904223u;a=seed;seed=seed*1664525u+1013904223u;b=seed;CHECK(((a^b)==0)==(a==b));CHECK(((a^a)==0)==(a==a));}
 printf("PASS %d checks, actual production helper objects; ABI/RMW/branch/flags/cycle counterexamples\n",checks);
 return 0;
}
