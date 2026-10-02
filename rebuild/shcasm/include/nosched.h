/* the ASM_NOSCHED diagnostic (src/_nosched.c), compiled in with SHC_REBUILD_UPDATED=1; otherwise Release 26's issue
   test. */
#ifndef NOSCHED_H
#define NOSCHED_H
#if SHC_REBUILD_UPDATED
extern int asm_sched_can_issue(int index);
#define SCHED_CAN_ISSUE(i) asm_sched_can_issue(i)
#else
#define SCHED_CAN_ISSUE(i) can_schedule_pipeline_entry_now(i)
#endif
#endif
