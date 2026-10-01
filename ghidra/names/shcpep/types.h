/* shcpep's records, applied to the Ghidra project by ApplyStageTables.java and compiled into the C rebuild as
   include/stage_types.h (tools/gen-stage-types.py adds a typedef for each struct and the enum constants).
   The names in [brackets] are the stage's own, from its debug dumps (dump_node_list_debug and friends print
   "psdtbl->psdop", "eabase", "labtbl->labno1", ...). Every field sits at its natural alignment, so the layout is
   the same under Ghidra's packing and Visual C++'s. */

/* an operand [eatbl]: the effective address of a psd record's source or destination */
struct ea {
    unsigned char type;          /* +00 [eatype] low 5 bits: EANON 0, EAREGD 1 (Rn), EAIDREG 2 (@Rn), EAPRDEC 3 (@-Rn),
                                    EAPOINC 4 (@Rn+), EACREGD 5 (control reg), EASREGD 6 (system reg), EAIMM 7 (#imm),
                                    EADISP 8 (@(disp,Rn)), EAINDEX 9 (@(R0,Rn)), EAIDPC 10 (@(disp,PC)),
                                    EADSPGBR 11 (@(disp,GBR)), EAIDXGBR 12 (@(R0,GBR)), EAABS 13 */
    char base;                   /* +01 [eabase] base register (0x0f = r15 the stack pointer, 0x6c = the frame) */
    char index;                  /* +02 [eaindex] index register */
    char misc;                   /* +03 [eamisc] */
    int disp;                    /* +04 [eadisp] displacement or immediate value */
    struct label_ref *labels;    /* +08 the labels/symbols the value refers to */
};
// @size ea 0xc

/* a symbol reference of an operand [labtbl], a list */
struct label_ref {
    struct label_ref *next;      /* +00 */
    short labno1;                /* +04 [labno1] label (or symbol) number */
    short labno2;                /* +06 [labno2] second label of a difference (labno1 - labno2), 0 = none */
};
// @size label_ref 0x8

/* a pseudo-code record [psdtbl]: one instruction or directive of the function being compiled */
struct psd {
    psd_op op;                   /* +00 [psdop] */
    char flg;                    /* +01 [psdflg] operand size and other flags */
    char misc;                   /* +02 [psdmisc] */
    char tmp;                    /* +03 [psdtmp] */
    int sptravel;                /* +04 [psdsptravel] stack pointer offset at this record */
    int expno;                   /* +08 [psdexpno] expression number */
    short filno;                 /* +0c [psdfilno] source file */
    unsigned short linno;        /* +0e [psdlinno] source line */
    struct ea *ea1;              /* +10 source operand; a LABEL's [psdlabno] in the low half */
    struct ea *ea2;              /* +14 destination operand */
};
// @size psd 0x18

/* a node of a code block [nodetbl]: up to 15 psd records. The first node of each block links the blocks
   ("Base Next Block"), every node the rest of its block ("Base Next Node") */
struct code_node {
    unsigned char flags;         /* +00 1: the block does not fall through to a label of its own; 2: needs the
                                    after-load clean-up passes again */
    unsigned char psd_count;     /* +01 records used in the block's last node */
    unsigned char unknown_02[2]; /* +02 */
    short labno;                 /* +04 the label the block starts with, 0 = none */
    short target_labno;          /* +06 the label its final branch goes to, 0 = none */
    struct code_node *next_block; /* +08 */
    struct code_node *next;      /* +0c the next node of this block */
    struct psd psd[15];          /* +10 */
};
// @size code_node 0x178

/* one entry of a flow block's predecessor list */
struct flow_edge {
    struct flow_edge *next;      /* +00 */
    struct flow_block *block;    /* +04 */
};
// @size flow_edge 0x8

/* a basic block of the flow graph the final passes (from FUN_00401000) build over the code blocks */
struct flow_block {
    struct code_node *code;      /* +00 the block's first node */
    struct flow_block *next;     /* +04 next in code order */
    struct flow_block *target;   /* +08 the block its final branch goes to */
    struct flow_block *prev;     /* +0c previous in code order */
    struct flow_edge *preds;     /* +10 the blocks that branch here */
    unsigned int live_in[2];     /* +14 registers used before they are set in the block */
    unsigned int defs[2];        /* +1c registers the block sets */
    unsigned char flags;         /* +24 1: ends in an unconditional transfer (RETURN/JUMP/BRA/JMP); 2: EXIT;
                                    4: has a CALL; 8: has an end record (op 0x10); 0x10: only labels so far;
                                    0x20: has a CASEJMP; 0x40: has a volatile operand */
    unsigned char flags2;        /* +25 */
    unsigned char unknown_26[2]; /* +26 */
};
// @size flow_block 0x28

/* a label or other symbol [labtbl entry of the symbol table]: the .asa symbols (load_symbol_aux_record_stream,
   an array of request->label_count) and labels made later (create_symbol_record, blocks of 32), hashed by
   number % 0x3fd into g_symbol_hash */
struct symbol {
    unsigned char type;          /* +00 low 5 bits: the .asa tag 1..0xc (2..5 label kinds whose references are
                                    counted; 0xc function) */
    unsigned char flags;         /* +01 0xc0: high bits of the .asa tag byte; 0x20: referenced */
    unsigned char attr;          /* +02 attribute bits 0..5 from the stream */
    unsigned char attr2;         /* +03 */
    unsigned char unknown_04[2]; /* +04 */
    short number;                /* +06 label/symbol number (the hash key) */
    int value;                   /* +08 */
    char *name;                  /* +0c */
    short aux_index;             /* +10 index into g_aux_record_table (functions) */
    short savelab;               /* +12 [savelab] the label a branch to this one is redirected to (br_brchg) */
    struct symbol *hash_next;    /* +14 next in the hash bucket */
    short header_word;           /* +18 */
    unsigned char unknown_1a[2]; /* +1a */
    int sequence;                /* +1c load order */
    struct label_block_ref *ref_blocks; /* +20 [LISTTBL] the blocks whose final branch goes here */
    int ref_count;               /* +24 reference count (dellab: 0 = dead) */
    struct psd *label_psd;       /* +28 the LABEL record of the label */
};
// @size symbol 0x2c

/* one entry of a symbol's list of referencing blocks [LISTTBL] */
struct label_block_ref {
    struct label_block_ref *next; /* +00 */
    struct code_node *block;      /* +04 0 once unlinked */
};
// @size label_block_ref 0x8

/* a register renaming range of a function (start expno / end expno / before reg / after reg in the
   advance_sua_record_stream debug output) */
struct aux_reg_range {
    struct aux_reg_range *next;  /* +00 */
    char before_reg;             /* +04 */
    char after_reg;              /* +05 */
    unsigned char unknown_06[2]; /* +06 */
    int start_expno;             /* +08 */
    int end_expno;               /* +0c */
};
// @size aux_reg_range 0x10

/* the per-function aux record (.asa tag 0xc), an array of request->aux_count */
struct aux_record {
    int frame_size;              /* +00 local frame */
    short saved_regs;            /* +04 bit n: Rn saved */
    short saved_regs2;           /* +06 bit n: register 0x10+n saved */
    unsigned char saved_sys;     /* +08 bit 0: register 0x67, bit 1: register 0x68 saved */
    unsigned char unknown_09;    /* +09 */
    unsigned short flags;        /* +0a 0x8000: PR not saved (leaf); 0x4000; 0x0800/0x1000/0x1800: the kind of
                                    stack_value; 0x2000: unknown_byte present */
    int max_stack;               /* +0c maximum stack depth */
    int stack_value;             /* +10 */
    unsigned short range_count;  /* +14 */
    unsigned char unknown_byte;  /* +16 */
    unsigned char saved_mac;     /* +17 bit 0: MACL, bit 1: MACH saved */
    struct aux_reg_range *ranges; /* +18 */
    int unknown_1c;              /* +1c */
    int asb_word;                /* +20 written to .asb */
    int sp_adjust;               /* +24 stack adjustment folded in by fold_add_immediates */
    char reg28;                  /* +28 a register number, written to .asb */
    unsigned char unknown_29[3]; /* +29 */
    unsigned char asb_bytes[0x17]; /* +2c copied from the stream to .asb */
    unsigned char unknown_43;    /* +43 */
};
// @size aux_record 0x44

/* the size-class allocator (alloc_zeroed, try_alloc_zeroed, pool_free): a chunk of one size class */
struct alloc_chunk {
    struct alloc_chunk *next;    /* +00 */
    char *cursor;                /* +04 next never-used byte */
    char *end;                   /* +08 end of data */
    void *free_list;             /* +0c freed blocks, linked through their first word */
    int free_count;              /* +10 */
    unsigned char data[0x400];   /* +14 */
};
// @size alloc_chunk 0x414

struct alloc_size_class {
    short size;                  /* +00 block size */
    unsigned char unknown_02[2]; /* +02 */
    struct alloc_chunk *chunks;  /* +04 */
};
// @size alloc_size_class 0x8

/* a block of up to 32 size classes; the list head is g_alloc_size_classes */
struct alloc_class_table {
    short count;                 /* +00 classes used */
    unsigned char unknown_02[2]; /* +02 */
    struct alloc_class_table *next; /* +04 */
    struct alloc_size_class cls[32]; /* +08 */
};
// @size alloc_class_table 0x108

/* a literal of the pool tables (g_word_literal_table, g_long_literal_table, g_frame_offset_literal_table) */
struct literal_entry {
    struct literal_entry *next;  /* +00 insertion order */
    struct literal_entry *hash_next; /* +04 bucket chain */
    int value;                   /* +08 */
    struct label_ref *labels;    /* +0c */
};
// @size literal_entry 0x10

struct literal_table {
    struct literal_entry *head;  /* +000 */
    struct literal_entry *tail;  /* +004 */
    int count;                   /* +008 */
    struct literal_entry *buckets[0x7f]; /* +00c hash = (value + the label numbers) % 0x7f */
};
// @size literal_table 0x208

/* the request record every SHC stage loads from its counted request file (load_request_record_file) and stores
   back: the file's first short is the size of this fixed part, read raw; the pointer fields are then replaced by
   the strings and lists that follow in the file (read_request_variable_part). Fields shcpep does not use are
   unknown_ */
struct request {
    char *source_name;                   /* +000 the source file, for messages */
    unsigned char unknown_004[0x14];     /* +004 */
    short cpu;                           /* +018 nonzero: JUMPT/JUMPF take part in the branch passes */
    short pic;                           /* +01a nonzero: call/jump target literals become label differences */
    unsigned char unknown_01c[8];        /* +01c */
    struct request_section *sections;    /* +024 */
    unsigned char unknown_028[0xe];      /* +028 */
    char macsave;                        /* +036 0: calls clobber MACH/MACL */
    unsigned char unknown_037[1];        /* +037 */
    char *string_038;                    /* +038 */
    char *string_03c;                    /* +03c */
    struct request_string *string_list_040; /* +040 */
    unsigned char unknown_044[4];        /* +044 */
    struct request_string12 *string_list_048; /* +048 */
    struct request_sized_string *sized_string_list_04c; /* +04c */
    char *path_050;                      /* +050 */
    char *path_054;                      /* +054 */
    char *path_058;                      /* +058 */
    char *path_05c;                      /* +05c */
    char *message_path;                  /* +060 the message record file */
    char *path_064;                      /* +064 */
    char *path_068;                      /* +068 */
    char *path_06c;                      /* +06c */
    char *path_070;                      /* +070 */
    char *path_074;                      /* +074 */
    char *path_078;                      /* +078 */
    char *path_07c;                      /* +07c */
    char *path_080;                      /* +080 */
    char *sua_path;                      /* +084 .sua input */
    char *sub_path;                      /* +088 .sub output */
    char *sud_path;                      /* +08c .sud */
    char *path_090;                      /* +090 */
    char *ofb_path;                      /* +094 .ofb output */
    char *asa_path;                      /* +098 .asa input */
    char *asb_path;                      /* +09c .asb output */
    char *path_0a0;                      /* +0a0 */
    char *lit_path;                      /* +0a4 .lit output */
    char *path_0a8;                      /* +0a8 */
    int label_count;                     /* +0ac symbols in the .asa stream; the label counter is stored back */
    unsigned char unknown_0b0[8];        /* +0b0 */
    struct request_entry *entry11_list_0b8; /* +0b8 */
    struct request_entry *entry11_list_0bc; /* +0bc */
    struct request_entry *entry12_list_0c0; /* +0c0 */
    unsigned char unknown_0c4[4];        /* +0c4 */
    int warning_count;                   /* +0c8 */
    int error_count;                     /* +0cc */
    unsigned char unknown_0d0[4];        /* +0d0 */
    int result_0d4;                      /* +0d4 */
    unsigned char unknown_0d8[0x14];     /* +0d8 */
    struct request_source_file *source_files; /* +0ec file number -> name, for messages */
    unsigned char unknown_0f0[0x20];     /* +0f0 */
    int aux_count;                       /* +110 aux (function) records in the .asa stream */
    char *string_114;                    /* +114 */
    int stage;                           /* +118 the stage that loaded it (3 = shcpep) */
    char *compiler_version;              /* +11c */
    char *copyright;                     /* +120 */
    unsigned char message_flags;         /* +124 */
    unsigned char unknown_125[0x13];     /* +125 */
    unsigned int stage_flags;            /* +138 debug-trace flags (g_stage_flags) */
    unsigned char flags_13c;             /* +13c */
    unsigned char flags_13d;             /* +13d */
    unsigned char unknown_13e[2];        /* +13e */
    char *string_140;                    /* +140 */
    struct request_cpp_block *cpp_block; /* +144 nonzero: C++ */
    unsigned char unknown_148[1];        /* +148 */
    char scratch_bank_reg_count;         /* +149 registers 0x14.. and 0x24.. treated as call-clobbered */
    char message_all;                    /* +14a */
    char pool_flag_14b;                  /* +14b */
    unsigned char unknown_14c[4];        /* +14c */
    unsigned int reg_mask_150;           /* +150 one bit per register number */
    unsigned char abs16;                 /* +154 */
    unsigned char unknown_155[7];        /* +155 */
    char *string_15c;                    /* +15c */
    int info_count;                      /* +160 */
};
// @size request 0x164

/* a section record of request->sections */
struct request_section {
    short id;                            /* +00 section number */
    short name_len;                      /* +02 */
    char *name;                          /* +04 */
    int unknown_08;                      /* +08 */
    unsigned char unknown_0c[0xc];       /* +0c */
    int unknown_18;                      /* +18 */
    struct request_section *next;        /* +1c */
};
// @size request_section 0x20

struct request_string {
    struct request_string *next;         /* +00 */
    char *str;                           /* +04 */
};
// @size request_string 0x8

struct request_string12 {
    struct request_string12 *next;       /* +00 */
    char *str;                           /* +04 */
    unsigned char unknown_08[4];         /* +08 */
};
// @size request_string12 0xc

struct request_sized_string {
    struct request_sized_string *next;   /* +00 */
    char *str;                           /* +04 */
    short len;                           /* +08 */
    unsigned char unknown_0a[2];         /* +0a */
};
// @size request_sized_string 0xc

struct request_source_file {
    struct request_source_file *next;    /* +00 */
    short filno;                         /* +04 */
    short name_len;                      /* +06 */
    char *name;                          /* +08 */
};
// @size request_source_file 0xc

/* node of the request's 11- and 12-byte entry lists (16 bytes in memory) */
struct request_entry {
    struct request_entry *next;          /* +00 */
    unsigned char a[4];                  /* +04 */
    unsigned char b[4];                  /* +08 */
    unsigned char c[4];                  /* +0c */
};
// @size request_entry 0x10

struct request_cpp_block {
    unsigned char unknown_00[4];         /* +00 */
    char *strings[5];                    /* +04 */
};
// @size request_cpp_block 0x18

/* a temporary file of g_temp_files (open_temp_file, close_and_delete_temp_files) */
struct temp_file {
    char *path;                  /* +00 */
    FILE *file;                  /* +04 */
};
// @size temp_file 0x8
