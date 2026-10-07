/* GEN_R0VAR (src/_r0varrules.c), compiled in with SHC_REBUILD_UPDATED=1; otherwise Release 26's. */
#ifndef R0VARRULES_H
#define R0VARRULES_H
#if SHC_REBUILD_UPDATED
extern int gen_r0var(void);
extern int gen_r0var_statement(int count, int symx);
extern int gen_r0var_reserved;
/* count_deref_use: does a candidate counted later replace the current one? */
#define R0VAR_REPLACES(cur, cand) (gen_r0var() == 1 ? (cur) <= (cand) : (cur) < (cand))
/* generate_statement_expression: drop the statement's r0 variable (count = its indexed uses, -1 for none; symx < 0 a temporary) */
#define R0VAR_DROP(count, symx) gen_r0var_statement(count, symx)
/* choose_general_register: is r0 held for the statement's indexed addresses */
#define R0VAR_HELD(var) ((var) != 0 || gen_r0var_reserved)
/* ... and is r0 kept out of the choice (avoided, its preference dropped) */
#define R0VAR_AVOIDS(var) ((var) != 0 || gen_r0var_reserved == 2)
/* assign_template_slot_registers: the registers a template slot prefers */
extern unsigned short gen_r0var_slot_pref(gen_node *node, unsigned short pref);
#define R0VAR_SLOT_PREF(node, pref) gen_r0var_slot_pref(node, pref)
#else
#define R0VAR_REPLACES(cur, cand) ((cur) < (cand))
#define R0VAR_DROP(count, symx) 0
#define R0VAR_HELD(var) ((var) != 0)
#define R0VAR_AVOIDS(var) ((var) != 0)
#define R0VAR_SLOT_PREF(node, pref) (pref)
#endif
#endif
