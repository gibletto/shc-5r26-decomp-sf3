/* Exercise the actual candidate finder and its real block-local scanner. */
#include "decls.h"
#include "pep_rules.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
unsigned char g_sd[0x20000];
int _printf() { return 0; }
static code_node join_block, exit_block, continuation, intervening;
static ea immediate, destination, add_source, add_destination;
static int count, enabled;
static void setup(void) {
    memset(&join_block,0,sizeof join_block);
    memset(&exit_block,0,sizeof exit_block);
    memset(&continuation,0,sizeof continuation);
    memset(&intervening,0,sizeof intervening);
    memset(&immediate,0,sizeof immediate);
    memset(&destination,0,sizeof destination);
    memset(&add_source,0,sizeof add_source);
    memset(&add_destination,0,sizeof add_destination);
    join_block.psd[0].op=OP_LABEL;
    join_block.psd[1].op=OP_MOVI;
    join_block.psd[1].flg=2;
    join_block.psd[1].ea1=&immediate;
    join_block.psd[1].ea2=&destination;
    immediate.type=7; immediate.disp=1;
    destination.type=1; destination.base=0;
    join_block.next_block=&exit_block;
    exit_block.psd[0].op=OP_LABEL;
    exit_block.psd[1].op=OP_EXIT;
    exit_block.flags=1;
}
static void check(const char* name,int eligible) {
    psd* result=find_slot_candidate_after_label(&join_block,&join_block.psd[0]);
    assert(result==(eligible ? &join_block.psd[1] : (psd*)0));
    printf("PASS %s %s\n",name,eligible?"accept":"reject"); ++count;
}
#define NEG(name,change) do {setup();change;check(name,0);} while(0)
int main(int argc,char** argv) {
    int i,j;
    const int values[3]={0,-7,42};
    const int registers[3]={0,2,13};
    enabled=argc>1?atoi(argv[1]):0;
    for(i=0;i<3;i++)for(j=0;j<3;j++) {
        setup(); immediate.disp=values[i]; destination.base=(char)registers[j];
        check("generic-literal-and-destination",enabled);
    }
    setup();
    for(i=1;i<15;i++)exit_block.psd[i].op=OP_LINE;
    exit_block.next=&continuation;
    continuation.psd[14].op=OP_EXIT;
    check("exit-crosses-record-chunk",enabled);
    NEG("candidate-outgoing-target",join_block.target_labno=7);
    NEG("candidate-no-fallthrough",join_block.flags=1);
    NEG("missing-successor",join_block.next_block=0);
    NEG("intervening-block",join_block.next_block=&intervening;intervening.next_block=&exit_block);
    NEG("successor-outgoing-target",exit_block.target_labno=7);
    NEG("successor-not-exit",exit_block.psd[1].op=OP_MOV);
    NEG("missing-exit",exit_block.psd[1].op=OP_DUMMY);
    NEG("second-exit",exit_block.psd[2].op=OP_EXIT);
    NEG("late-second-exit",exit_block.next=&continuation;continuation.psd[14].op=OP_EXIT);
    NEG("late-real-record",exit_block.next=&continuation;continuation.psd[14].op=OP_MOV);
    NEG("label-after-exit",exit_block.next=&continuation;continuation.psd[14].op=OP_LABEL);
    NEG("second-label",exit_block.psd[1].op=OP_LABEL;exit_block.psd[2].op=OP_EXIT);
    NEG("non-immediate-source",immediate.type=2);
    NEG("memory-destination",destination.type=8);
    NEG("special-register-destination",destination.base=16);
    NEG("negative-register-destination",destination.base=-1);
    NEG("stack-add-consumer",join_block.psd[2].op=OP_ADD;
        add_source.type=1;add_source.base=0;add_destination.type=1;add_destination.base=15;
        join_block.psd[2].ea1=&add_source;join_block.psd[2].ea2=&add_destination);
    printf("PASS %d actual-finder cases\n",count);
    return 0;
}
