#ifndef XORTEST_H
#define XORTEST_H
extern void pep_fold_dead_xor_tests(void);
extern int pep_dead_xor_candidate(flow_block *block, psd *xor_rec, psd *test_rec);
#endif
