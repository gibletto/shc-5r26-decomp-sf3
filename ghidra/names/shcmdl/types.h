/* shcmdl's records, applied to the Ghidra project by ApplyStageTables.java and compiled into the C rebuild as
   include/stage_types.h (tools/gen-stage-types.py adds a typedef for each struct and the enum constants).
   The names in [brackets] are the stage's own, from its debug dumps: the tree dump (004086b0: "symx", "lreg",
   "listno", "cmnexp", "refchn", "c:%08x s:%08x f:%08x n:%08x", ...), the DAG chain dump (00410ff0: "node val_no
   cmnexp refchn refcnt duptr operater"), the basic block dumps (00409070, 00405e30: "tcount", "ilnode", "prelst",
   "suclst", "domlst", "d_in", "l_in", "_out", "bn_next", "startpp", "usepreg", ...), the data flow dumps
   (0040c750, 0040c910: "Current Basic Block Gen/Kill/Out/Use/Def"), the loop table dumps (00405c90, 00408fa0:
   "fath", "child", "front", "next", "start", "exit", "pre", "lstep", "repet", "nestcnt", "BRC No."), the leaf table
   dump (00408d60: "symno", "flag", "gen", "use", "lastnd", LF_*) and the logical register dump (00414820: "lregno",
   "pregno", "set", "priori", "profit", "life area", "exp area", "clashed lregs", "bind at", "bakbind at",
   "chained nodes", "contents", "value", "dominator type", "dominator block No.").
   Every field sits at its natural alignment, so the layout is the same under Ghidra's packing and Visual C++'s. */

/* a node of the IL tree [ilnode]: an operator with its operands as children. Allocated 0x68 bytes from a pool
   (allocate_il_node_block, free nodes chained through next) */
struct il_node {
    il_op op;                    /* +00 the operator (name table at 00434668) */
    unsigned char boff;          /* +01 [boff] a bit-field reference's bit offset (IL_B_QUALIFY) */
    unsigned char bsiz;          /* +02 [bsiz] its width in bits */
    unsigned char type;          /* +03 [type] the value's type: 1 const, 2 volatile, 4 unsigned, 0x18 size class
                                    (char, short, int, long / float, double, long double), 0xe0 kind (0 integer,
                                    0x20 floating, 0x40 pointer, 0x60 struct, 0x80 array) */
    short symx;                  /* +04 [symx] symbol number (an index into the symbol table), or a label number */
    unsigned char unknown_06[2]; /* +06 */
    unsigned char unknown_08;    /* +08 */
    unsigned char call_flags;    /* +09 a call's flags from the .ila: 4 [tail] */
    short filn;                  /* +0a [filn] source file */
    unsigned short line;         /* +0c [line] source line */
    unsigned char unknown_0e[2]; /* +0e */
    struct il_node *parent;      /* +10 [f] the node this one is an operand of */
    struct il_node *child;       /* +14 [s] the first operand */
    struct il_node *next;        /* +18 [n] the next operand of the same parent */
    unsigned char unknown_1c[4]; /* +1c */
    int val;                     /* +20 [val] a constant's value; [asmno] of an asm, [size] of a pri/prd/poi/pod,
                                    [blkflg] (bit 0) of a block/e_block */
    int val2;                    /* +24 [asmsize] of an asm; the second word of an 8- or 12-byte constant */
    int val3;                    /* +28 the third word of a 12-byte (long double) constant; on a web's definition
                                    node the register allocator keeps its lreg here (new_register_candidate) */
    unsigned char unknown_2c[4]; /* +2c */
    short lreg;                  /* +30 [lreg] */
    short listno;                /* +32 [listno] */
    unsigned char unknown_34[4]; /* +34 */
    struct dutbl *duptr;         /* +38 [duptr] the node's def-use record */
    struct il_node *cmnexp;      /* +3c [cmnexp] */
    struct il_node *refchn;      /* +40 [refchn] */
    unsigned short pp;           /* +44 [pp] program point; the DAG and CSE passes keep the value number here
                                    ([val_no] in the DAG chain dump) */
    unsigned char unknown_46[2]; /* +46 */
    struct il_node *cse_head;    /* +48 the first node of its class of equal expressions (itself for the head) */
    struct il_node *cse_next;    /* +4c the next node of the class */
    struct bblock *cse_block;    /* +50 the block the expression was numbered in */
    unsigned short expp;         /* +54 [expp] */
    short ivno;                  /* +56 [ivno] */
    short nleaf;                 /* +58 [nleaf] the leaf table entry of a variable */
    char invno;                  /* +5a [invno] */
    unsigned char nodes;         /* +5b the number of nodes in the subtree */
    unsigned short refcnt;       /* +5c [refcnt]; on a CSE class head the number of members */
    unsigned short flag;         /* +5e [flag] 2 side effect, 4 in an allocatable web, 0x20 value used, 0x40
                                    volatile, 0x80 end of a chain in its block, 0x100 [LASTUSE], 0x200 statement
                                    root, 0x400 (IL_FUNC) the function makes calls, 0x800 contains a call, 0x1000
                                    assignment of an assignment chain, 0x4000 induction variable update */
    unsigned short flag2;        /* +60 [flag2] 2 skipped by the CSE pass, 8 memory dependent, 0x10 comma made by
                                    the CSE pass, 0x20 compiler temporary, 0x40 inline warning given */
    char fr0set;                 /* +62 [FR0set] */
    unsigned char unknown_63[5]; /* +63 */
};
// @size il_node 0x68

/* a list of IL nodes (a block's statements [ilnode], a block's local static data) */
struct node_list {
    struct il_node *node;        /* +00 */
    struct node_list *next;      /* +04 */
};
// @size node_list 0x8

/* a list cell with the link first (the CSE and DAG hash buckets) */
struct node_cell {
    struct node_cell *next;      /* +00 */
    struct il_node *node;        /* +04 */
};
// @size node_cell 0x8

/* a list of basic blocks (predecessors [prelst], successors [suclst]) */
struct block_list {
    struct bblock *block;        /* +00 */
    struct block_list *next;     /* +04 */
};
// @size block_list 0x8

/* the data flow bit sets of a basic block, a bit per definition or leaf (new_bblock allocates 0x20, 0x20, 0x20,
   0x40, 0x40 bytes) */
struct bblock_sets {
    unsigned int *gen;           /* +00 [Gen] definitions made */
    unsigned int *kill;          /* +04 [Kill] definitions killed */
    unsigned int *reach_out;     /* +08 [Out] reaching definitions at the end */
    unsigned int *use;           /* +0c [Use] leaves used before a definition */
    unsigned int *def;           /* +10 [Def] leaves defined */
};
// @size bblock_sets 0x14

/* a basic block of the control flow graph [B%d], 0x68 bytes (new_bblock) */
struct bblock {
    short number;                /* +00 [B%d] */
    short tcount;                /* +02 [tcount] */
    struct node_list *ilnode;    /* +04 [ilnode] [b_trelst] its statements */
    struct block_list *prelst;   /* +08 [prelst] predecessors */
    struct block_list *suclst;   /* +0c [suclst] successors */
    unsigned int *d_in;          /* +10 [d_in] reaching definitions in, 0x20 bytes */
    unsigned int *out;           /* +14 [_out] live variables out, 0x40 bytes */
    unsigned int *l_in;          /* +18 [l_in] live variables in, 0x40 bytes */
    struct bblock_sets *sets;    /* +1c */
    struct bblock *f_next;       /* +20 [f_chain] */
    struct bblock *b_next;       /* +24 [b_chain] */
    struct bblock *bn_next;      /* +28 [bn_next] the block list in creation order */
    struct bblock *merge_next;   /* +2c the next block with the same code (common code merging) */
    struct loop *lptbl;          /* +30 [lptbl] [lpnumber] the innermost loop it is in */
    struct node_list *statics;   /* +34 [local static datas]; the register candidate list during register
                                    allocation */
    unsigned int domlst[8];      /* +38 [domlst] dominators, a bit per block number - 1 */
    unsigned short startpp;      /* +58 [startpp] */
    unsigned short endpp;        /* +5a [endpp] */
    unsigned int usepreg;        /* +5c [usepreg] general registers used (1 << pregno); before register allocation
                                    [startexpp] (low half) and [endexpp] (high half) */
    unsigned int usefreg;        /* +60 [usefreg] floating registers used */
    short flag;                  /* +64 [flag] 1 visited (depth-first order), 2 contains a call, 4 may not take
                                    argument registers, 8 in the current lreg's life area, 0x10 holds a node of the
                                    current web, 0x40 visited, 0x80 kills found (CSE path search), 0x200 visited
                                    (constant life areas), 0x400 visited (path search in the current loop) */
    unsigned char unknown_66[2]; /* +66 */
};
// @size bblock 0x68

/* a loop [LP%d] of the loop table [lptbl], 0x3c bytes (new_loop, at most 0x80) */
struct loop {
    short lpnumber;              /* +00 [lpnumber] */
    short nestcnt;               /* +02 [nestcnt] */
    unsigned int flag;           /* +04 [lp_flag] 1: [ENTER] (else [EXIT]), 0x20 skipped, 0x80 too many induction
                                    variables, 0x200 test replaced */
    struct il_node *node;        /* +08 the loop statement */
    struct il_node *init_def;    /* +0c the induction variable's initial assignment */
    struct il_node *step_def;    /* +10 the induction variable's increment */
    struct loop *fath;           /* +14 [fath] the enclosing loop */
    struct loop *child;          /* +18 [child] the first inner loop */
    struct loop *front;          /* +1c [front] the previous loop at this level */
    struct loop *next;           /* +20 [next] the next loop at this level */
    struct bblock *start;        /* +24 [start] [startcfg] */
    struct bblock *exit;         /* +28 [exit] [exitcfg] */
    struct bblock *pre;          /* +2c [pre] [precfg] */
    int lstep;                   /* +30 [lstep] */
    int repet;                   /* +34 [repet] */
    short brc;                   /* +38 [BRC No.] */
    unsigned char unknown_3a[2]; /* +3a */
};
// @size loop 0x3c

/* an entry of the leaf table [LEAF TABLE] (g_leaf_table, 0x801 entries, entry 0 unused) */
struct leaf {
    unsigned int *gen;           /* +00 [gen] bit set */
    unsigned int *use;           /* +04 [use] bit set */
    struct il_node *lastnd;      /* +08 [lastnd] */
    short symno;                 /* +0c [symno] the symbol, <= 0 a temporary ([TEMP]) */
    unsigned char flag;          /* +0e [flag] LF_STATIC 1, LF_CNDASS 2, LF_IMPVOL 4, LF_EXPVOL 8, LF_INDVAR 0x10,
                                    LF_NODEF 0x20 */
    unsigned char unknown_0f;    /* +0f */
};
// @size leaf 0x10

/* an entry of the symbol table (0x3c bytes, indexed by il_node.symx), read from the .sym file (read_symbol_table) */
struct symbol {
    char sclass;                 /* +00 storage class: 1..4 static/extern, 5/6 local, 7/8 parameter, 9, 10 block
                                    scope, 11 label */
    unsigned char type;          /* +01 the type byte, as il_node.type (0x48 a function) */
    unsigned char name_len;      /* +02 the length of name */
    unsigned char impvol;        /* +03 non-zero: implicitly volatile (LF_IMPVOL) */
    short unknown_04;            /* +04 (classes 3, 4, 9, 11; a label's number for class 11) */
    unsigned char unknown_06;    /* +06 */
    unsigned char flags;         /* +07 2 the first parameter is hidden, 0x10 the extension (+2d..) follows */
    int size;                    /* +08 the size of a struct/union/array */
    char *name;                  /* +0c */
    void *info;                  /* +10 a function's func_info, a block scope's scope_info */
    short ms_leaf;               /* +14 [ms_leaf] */
    short unknown_16;            /* +16 */
    int unknown_18;              /* +18 (class 9) */
    struct inline_body *inline_body; /* +1c the body for inline expansion */
    void *new_info;              /* +20 the updated copy of info (a block's scope record while inlining) */
    int inline_symbols;          /* +24 the symbols one inline expansion needs */
    int inline_labels;           /* +28 the labels one inline expansion needs */
    unsigned char inline_flags;  /* +2c 1: no warning */
    unsigned char ext_flags;     /* +2d */
    unsigned char attr;          /* +2e function attributes (0x10 no tail calls, 0x80 not referenced) */
    unsigned char no_inline;     /* +2f the body could not be loaded */
    int ext_30;                  /* +30 */
    int ext_34;                  /* +34 */
    char unknown_38;             /* +38 != -1 keeps a variable out of the register candidates */
    unsigned char unknown_39[3]; /* +39 */
};
// @size symbol 0x3c

/* symbol.info of a function: 0x14 bytes (read_function_info) */
struct func_info {
    int ret_size;                /* +00 the size of the return type */
    unsigned char ret_type;      /* +04 */
    unsigned char unknown_05;    /* +05 */
    char nparams;                /* +06 */
    unsigned char unknown_07;    /* +07 */
    short nscopes;               /* +08 */
    unsigned char unknown_0a[2]; /* +0a */
    short *params;               /* +0c the parameters' symbol numbers */
    short *scopes;               /* +10 the block scopes' symbol numbers */
};
// @size func_info 0x14

/* symbol.info of a block scope (class 10): 0x14 bytes allocated, 0xc used (read_scope_info) */
struct scope_info {
    short nscopes;               /* +00 */
    short nmembers;              /* +02 */
    short *scopes;               /* +04 nested scopes */
    short *members;              /* +08 variables */
    unsigned char unknown_0c[8]; /* +0c */
};
// @size scope_info 0x14

/* a def-use record [dutbl] (il_node.duptr), 0x20 bytes (new_dutbl 0040a810; " free dutbl %x"); a web of the
   register allocator is a chain of them */
struct dutbl {
    int kind;                    /* +00 1 a use (links: its reaching definitions), 2 a definition (links: its uses) */
    struct node_list *links;     /* +04 */
    struct dutbl *next;          /* +08 the next record of the same web */
    struct bblock *block;        /* +0c the block of node */
    struct il_node *node;        /* +10 the node whose duptr this is */
    struct dutbl *all_next;      /* +14 every record (g_du_tables) */
    struct lreg *lreg;           /* +18 */
    short count;                 /* +1c the number of links */
    unsigned char unknown_1e[2]; /* +1e */
};
// @size dutbl 0x20

/* a logical register [lregno], 0x2c bytes (new_register_candidate), chained from g_lreg_list */
struct lreg {
    short pregno;                /* +00 [pregno] physical register, < 0 a memory id, 0 none */
    short set;                   /* +02 [set] 0 CONST DATA, 1 WEB CHAIN, 2 MEMORY ALLOCATED, 3 DELETE(WEB) */
    int priori;                  /* +04 [priori] */
    int profit;                  /* +08 [profit] */
    void *life;                  /* +0c [life area] a list of {next, lifetbl *} */
    void *clashed;               /* +10 [clashed lregs] a list of {next, lreg *} */
    struct lreg *next;           /* +14 */
    struct lreg *bind;           /* +18 [bind at] the lreg this one is coalesced into */
    void *exp_area;              /* +1c [exp area] a list of {next, int, int} */
    void *chain;                 /* +20 [chained nodes] set 1/3: the web (dutbl *), set 0/2: const_data * */
    struct lreg *bakbind;        /* +24 [bakbind at] the next lreg bound to the same register */
    short lregno;                /* +28 [lregno] the number written to the .reg file */
    unsigned char unknown_2a[2]; /* +2a */
};
// @size lreg 0x2c

/* a pp range of a life area [lifetbl {st, en}], shared by every lreg live over it, 0xc bytes */
struct lifetbl {
    struct lifetbl *next;        /* +00 the next range with the same start */
    void *lregs;                 /* +04 a list of {next, lreg *} */
    unsigned short st;           /* +08 */
    unsigned short en;           /* +0a */
};
// @size lifetbl 0xc

/* a constant (or variable) a register may hold [CONST DATA], 0x1c bytes, in the 128-bucket hashes */
struct const_data {
    short contents;              /* +00 [contents] 1 ADDRESS CONST, else NUMBER CONST (0 a constant, 4 a
                                    static/extern variable, 8 an expression) */
    short dom_type;              /* +02 [dominator type] 0 NO_DOM, 1 EX_DOM, 2 SELF_DOM */
    int value;                   /* +04 [value] the constant, or the leaf number */
    struct const_use *uses;      /* +08 [chained nodes] */
    struct const_data *hash_next; /* +0c the next in its bucket */
    struct const_data *next;     /* +10 every record (g_const_data_list) */
    struct bblock *dom_block;    /* +14 [dominator block No.] */
    struct il_node *dom_node;    /* +18 the node in dom_block the range starts at */
};
// @size const_data 0x1c

/* a use of a const_data, 0x14 bytes */
struct const_use {
    struct const_use *next;      /* +00 */
    struct bblock *block;        /* +04 */
    struct il_node *node;        /* +08 */
    struct il_node *latest;      /* +0c the latest use in the block (compute_const_life_area) */
    unsigned char flag;          /* +10 1, 2: reached on a path to the dominator */
    unsigned char unknown_11[3]; /* +11 */
};
// @size const_use 0x14

/* a memory frequency record, 0x1c bytes (g_mem_freq_list) */
struct mem_freq {
    int freq;                    /* +00 */
    int mem_number;              /* +04 */
    short pregno;                /* +08 the memory id */
    unsigned char unknown_0a[2]; /* +0a */
    struct mem_freq *next;       /* +0c */
    struct lreg *lreg;           /* +10 */
    int merge_next;              /* +14 (reflect_register_numbers) */
    int merge_prev;              /* +18 */
};
// @size mem_freq 0x1c

/* an entry of the induction variable table (g_iv_table, entries 1..3) */
struct iv_entry {
    struct iv_use *uses;         /* +00 */
    struct il_node *update;      /* +04 the update statement x++ / x += c / x = x + c */
    struct il_node *step;        /* +08 the step expression */
    struct bblock *block;        /* +0c the update statement's block */
};
// @size iv_entry 0x10

/* a use of an induction variable, 0x24 bytes (record_induction_use) */
struct iv_use {
    struct iv_use *next;         /* +00 */
    struct il_node *expr;        /* +04 the (derived) expression in the statement */
    struct il_node *id;          /* +08 the induction variable reference it started from */
    struct node_list *factors;   /* +0c */
    struct il_node *incr;        /* +10 */
    struct bblock *block;        /* +14 */
    struct il_node *copy;        /* +18 the expression in the statement copy */
    struct il_node *copy_id;     /* +1c */
    int test_adjust;             /* +20 added to the relational operator of the loop test */
};
// @size iv_use 0x24

/* a cell of the term list (g_term_list), 0xc bytes */
struct term {
    char op;                     /* +00 '@' added, 'A' subtracted, 'D' multiplied, or the collecting operator */
    unsigned char unknown_01[3]; /* +01 */
    struct il_node *node;        /* +04 */
    struct term *next;           /* +08 */
};
// @size term 0xc

/* a size class of the pool allocator, 0xc bytes (g_pool_classes) */
struct pool_class {
    short size;                  /* +00 the block size */
    unsigned char unknown_02[2]; /* +02 */
    void *free_list;             /* +04 free blocks, linked through their first word */
    struct pool_class *next;     /* +08 by size */
};
// @size pool_class 0xc

/* a label of the CFG builder, 0x10 bytes (g_label_hash) */
struct label_rec {
    short labno;                 /* +00 */
    unsigned char unknown_02[2]; /* +02 */
    struct bblock *block;        /* +04 the labelled block */
    struct block_list *gotos;    /* +08 the blocks jumping here */
    struct label_rec *next;      /* +0c */
};
// @size label_rec 0x10

/* a function body available for inline expansion (symbol.inline_body), 0xc bytes */
struct inline_body {
    struct il_node *tree;        /* +00 */
    short *params;               /* +04 the parameters' symbol numbers */
    unsigned char unknown_08[4]; /* +08 */
};
// @size inline_body 0xc

/* a call chosen for inline expansion, 0x10 bytes */
struct inline_call {
    struct inline_call *next;    /* +00 */
    struct il_node *call;        /* +04 the IL_CALL */
    short callee;                /* +08 the callee's symbol number */
    short result;                /* +0a the symbol of the result variable, 0 for void */
    short return_label;          /* +0c */
    unsigned char unknown_0e[2]; /* +0e */
};
// @size inline_call 0x10

/* the inline calls of one expression, 0xc bytes */
struct inline_group {
    struct inline_group *prev;   /* +00 */
    struct inline_group *next;   /* +04 */
    struct inline_call *calls;   /* +08 */
};
// @size inline_group 0xc

/* old -> new number while copying an inline body, 8 bytes */
struct inline_map_entry {
    struct inline_map_entry *next; /* +00 */
    short old_number;            /* +04 */
    short new_number;            /* +06 */
};
// @size inline_map_entry 0x8

/* a case of a switch table, 8 bytes */
struct switch_case {
    int value;                   /* +00 */
    short label;                 /* +04 */
    unsigned char unknown_06[2]; /* +06 */
};
// @size switch_case 0x8

/* a switch table read from the .swi file for an inline body, 0x10 bytes */
struct switch_table {
    struct switch_table *next;   /* +00 */
    short number;                /* +04 the table number (IL_SWITCH symx) */
    char has_default;            /* +06 */
    unsigned char unknown_07;    /* +07 */
    short default_label;         /* +08 */
    short count;                 /* +0a */
    struct switch_case *cases;   /* +0c */
};
// @size switch_table 0x10

/* the compiler option record the driver passes in the .int file (read_intermediate_file: a 2-byte size, then the
   record, then its strings and lists); only the fields this stage uses are named. Every stage reads the same record */
struct option_record {
    char *source_name;           /* +00 the main source file name */
    short optimize;              /* +04 */
    unsigned char unknown_06[18];        /* +06 */
    short cpu;                   /* +18 2, or 4 (SH-4); 2 with fpu_mode 3 has the single-precision FPU */
    unsigned char unknown_1a[6];        /* +1a */
    short unknown_20;            /* +20 non-zero: every loop is inverted */
    unsigned char unknown_22[10];       /* +22 */
    unsigned int option_bits;    /* +2c bit 0 loop test replacement, bit 1 float division by a constant as a multiply */
    unsigned char unknown_30[5];        /* +30 */
    char unknown_35;             /* +35 */
    unsigned char unknown_36[1];        /* +36 */
    unsigned char fpu_mode;      /* +37 bit 0 flush denormals, bit 1 chop rounding; 3 with cpu 2 */
    unsigned char unknown_38[12];       /* +38 */
    int unknown_44;              /* +44 */
    unsigned char unknown_48[24];       /* +48 */
    char *error_file;            /* +60 the error file name */
    char *work_file_64;          /* +64 work file names */
    char *work_file_68;          /* +68 */
    char *sym_file;              /* +6c the symbol file name */
    char *work_file_70;          /* +70 */
    unsigned char unknown_74[12];       /* +74 */
    char *work_file_80;          /* +80 */
    unsigned char unknown_84[40];       /* +84 */
    int label_count;             /* +ac */
    int symbol_count;            /* +b0 */
    int unknown_b4;              /* +b4 */
    void *inline_records;        /* +b8 the inline function records */
    unsigned char unknown_bc[4];        /* +bc */
    void *keyed_offsets;         /* +c0 the keyed offset list (find_keyed_offset) */
    unsigned char unknown_c4[4];        /* +c4 */
    int message_count_c8;        /* +c8 message counters */
    int message_count_cc;        /* +cc */
    unsigned char unknown_d0[28];       /* +d0 */
    void *file_list;             /* +ec the source files ({next, short filn, char *name}) */
    unsigned char unknown_f0[40];       /* +f0 */
    int phase;                   /* +118 the stage number (read_intermediate_file) */
    unsigned char unknown_11c[8];       /* +11c */
    unsigned char unknown_124;   /* +124 bit 3 tested by the error reporter */
    unsigned char unknown_125[31];      /* +125 */
    int use_shcpp_env;           /* +144 non-zero: the SHCPP_ environment names */
    unsigned char unknown_148[1];       /* +148 */
    char unknown_149;            /* +149 */
    char warnings;               /* +14a the warnings switch */
    unsigned char unknown_14b[1];       /* +14b */
    char inline_passes;          /* +14c */
    unsigned char unknown_14d[1];       /* +14d */
    short next_switch_table;     /* +14e the switch table counter */
    unsigned char unknown_150[5];       /* +150 */
    char unroll;                 /* +155 loop unrolling */
    unsigned char unknown_156[10];      /* +156 */
    int message_count_160;       /* +160 */
    unsigned int node_pool_size; /* +164 */
};
// @size option_record 0x168
