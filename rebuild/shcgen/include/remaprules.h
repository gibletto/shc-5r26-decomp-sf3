/* GEN_CHAIN_JUMP and the GEN_REMAP_LOG diagnostic (src/_remaprules.c), compiled in with SHC_REBUILD_UPDATED=1;
   otherwise Release 26's. */
#ifndef REMAPRULES_H
#define REMAPRULES_H
#if SHC_REBUILD_UPDATED
extern void gen_remap_log(void);
extern void gen_remap_log_mark(const char *what, unsigned int mask, unsigned int serial);
extern unsigned int gen_chain_jump_regs(unsigned int mask);
#define REMAP_LOG() gen_remap_log()
#define REMAP_MARK(what, mask, serial) gen_remap_log_mark(what, mask, serial)
#define CHAIN_JUMP_REGS(mask) gen_chain_jump_regs(mask)
#else
#define REMAP_LOG()
#define REMAP_MARK(what, mask, serial)
#define CHAIN_JUMP_REGS(mask) (mask)
#endif
#endif
