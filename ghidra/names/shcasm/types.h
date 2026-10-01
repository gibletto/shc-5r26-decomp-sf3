/* shcasm's records, applied to the Ghidra project by ApplyStageTables.java and compiled into the C rebuild as
   include/stage_types.h (tools/gen-stage-types.py adds a typedef for each struct and the enum constants).
   The backend records shcasm reads (.sub, from shcpep) are shcpep's psd records with their ea operands and
   label_ref lists (ghidra/names/shcpep/types.h has the stage's own field names in [brackets]). Every field sits
   at its natural alignment, so the layout is the same under Ghidra's packing and Visual C++'s. */

/* an operand [eatbl] of a backend record */
struct ea {
    unsigned char type;          /* +00 [eatype] low 5 bits: the kind (1 Rn, 2 @Rn, 3 @-Rn, 4 @Rn+, 5 control
                                    register, 6 system register, 7 #imm, 8 @(disp,Rn), 9 @(R0,Rn), 10 @(disp,PC),
                                    11 @(disp,GBR), 12 @(R0,GBR), 13 absolute; 0xf and 0x10 are register kinds
                                    too: the scheduler treats them as no memory access, like 1, 5 and 6) */
    reg base;                    /* +01 [eabase] register */
    reg index;                   /* +02 [eaindex] index register of @(R0,Rn) and @(R0,GBR) */
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

/* a backend record [psdtbl]: one instruction or directive, as shcpep writes it to .sub */
struct psd {
    psd_op op;                   /* +00 [psdop] */
    unsigned char flg;           /* +01 [psdflg] operand size and other flags */
    char misc;                   /* +02 [psdmisc] */
    char tmp;                    /* +03 [psdtmp] */
    int sptravel;                /* +04 [psdsptravel] stack pointer offset at this record */
    int expno;                   /* +08 [psdexpno] expression number */
    short filno;                 /* +0c [psdfilno] source file */
    unsigned short linno;        /* +0e [psdlinno] source line */
    struct ea *ea1;              /* +10 source operand */
    struct ea *ea2;              /* +14 destination operand */
};
// @size psd 0x18

/* an entry of the list scheduler's window [pipetbl] (g_pipeline_window, up to 32 records; pipeline() prints them
   as "tbl[%d]:%s :refreg=%08x %08x, setreg=%08x %08x" / "flags=%04x, count=%d, next=%d" / "depend =") */
struct pipeline_entry {
    struct psd rec;              /* +00 the backend record */
    unsigned int setreg[2];      /* +18 [setreg] registers the record sets (bit masks of the register numbering:
                                    [0] registers 0..0x1f, [1] the rest) */
    unsigned int refreg[2];      /* +20 [refreg] registers the record reads */
    unsigned short flags;        /* +28 [flags] 0x8000: reads memory (not a PC-relative load or MOVA); 0x4000:
                                    writes memory or is an ordering barrier (a tail branch, writing R15,
                                    SLEEP/TAS/PREF, LDC to SR/VBR) */
    short depend;                /* +2a [depend] first of the entries that must follow it (an index into
                                    g_pipeline_edges), -1 none */
    short count;                 /* +2c [count] entries it must follow that are not scheduled yet */
    short next;                  /* +2e [next] the entry scheduled after it; -1 not scheduled, -2 the last */
};
// @size pipeline_entry 0x30

/* a dependency of the scheduler's window (g_pipeline_edges, at most 0x3e0): a list per pipeline_entry.depend */
struct pipeline_edge {
    short entry;                 /* +00 the window entry that must follow */
    short next;                  /* +02 the next edge of the list, -1 the last */
};
// @size pipeline_edge 0x4

/* an entry of the SH-4 (request->cpu == 4) superscalar scheduler's window (g_superscalar_window, 32 entries;
   read_next_superscalar_scheduled_record copies the record in, clear_superscalar_window_analysis clears the rest,
   record_superscalar_entry_operands / describe_superscalar_window_entry fill it). Dependency names follow the
   stage's dump (dump_superscalar_window: "FlowChild AntiChild AmbiChild Kind Latency" / "FlowParent AntiParent
   AmbiParent Path"): flow = read after write, anti = write after read, ambi = write after write and memory
   ordering. Masks hold one bit per window entry, g_window_entry_bit_masks[i] = 0x80000000 >> i. issue_group:
   1 EX, 2 FE, 3 MT, 4 CO, 6 BR, 7..0x15 LS (0xc..0x10 loads, 0x11..0x15 stores), named by the table at
   0043f298 */
struct superscalar_entry {
    struct psd rec;              /* +00 the backend record */
    unsigned char order;         /* +18 issue position chosen by schedule_superscalar_window; 0xff not yet */
    char scheduled;              /* +19 1: issued */
    reg src_reg;                 /* +1a rec.ea1->base */
    reg dst_reg;                 /* +1b rec.ea2->base */
    char src_kind;               /* +1c rec.ea1->type & 0x1f */
    char dst_kind;               /* +1d rec.ea2->type & 0x1f */
    char read_count;             /* +1e registers in read_regs */
    char write_count;            /* +1f registers in write_regs */
    char read_regs[24];          /* +20 registers the instruction reads (DR/FV/XD pairs expanded) */
    char write_regs[24];         /* +38 registers it writes */
    char latency;                /* +50 cycles until a flow child may issue */
    char issue_group;            /* +51 */
    char expr_rewritten;         /* +52 set by rewrite_entry_expression_with_earlier_definitions */
    unsigned char unknown_53[1]; /* +53 */
    int path_length;             /* +54 longest latency path to the end of the window (the sort key) */
    char defs_text[64];          /* +58 definitions "lhs=rhs" separated by ':' */
    char expr_text[32];          /* +98 the value/memory expression "Rn=@(Rm)"; set_superscalar_entry_timing copies
                                    0x40 bytes here and clear_superscalar_window_analysis clears 0x40, running into
                                    the dependency fields after it, which are rebuilt afterwards */
    char flow_child_count;       /* +b8 */
    char flow_parent_count;      /* +b9 */
    unsigned char unknown_ba[2]; /* +ba */
    unsigned int flow_children;  /* +bc later entries reading a register this one writes */
    unsigned int flow_parents;   /* +c0 earlier entries writing a register this one reads */
    char anti_child_count;       /* +c4 */
    char anti_parent_count;      /* +c5 */
    unsigned char unknown_c6[2]; /* +c6 */
    unsigned int anti_children;  /* +c8 later entries writing a register this one reads */
    unsigned int anti_parents;   /* +cc */
    char ambi_child_count;       /* +d0 */
    char ambi_parent_count;      /* +d1 */
    unsigned char unknown_d2[2]; /* +d2 */
    unsigned int ambi_children;  /* +d4 later entries writing the same register; memory operations after a store */
    unsigned int ambi_parents;   /* +d8 */
    char *expr;                  /* +dc the current (rewritten) expression: expr_text or a malloc'd rewrite */
};
// @size superscalar_entry 0xe0

/* g_superscalar_order: the window sorted by path length for schedule_superscalar_window */
struct superscalar_order_slot {
    char issued;                 /* +00 */
    unsigned char entry;         /* +01 window index */
    unsigned char unknown_02[2]; /* +02 */
    int path_length;             /* +04 copy of superscalar_entry.path_length (sorted descending) */
    int cycle;                   /* +08 issue cycle */
};
// @size superscalar_order_slot 0xc

/* sort_array's argument block for quicksort_range */
struct sort_context {
    void *base;                  /* +00 */
    int size;                    /* +04 element size */
    int compare;                 /* +08 the comparison function, int compare(void *a, void *b) (an address: the
                                    decompiler calls it through code *) */
};
// @size sort_context 0xc

/* a row of g_instruction_format_table (0043da90, 182 rows): how assemble_instruction encodes an instruction */
struct instruction_format {
    unsigned short opcode;       /* +00 base instruction word */
    unsigned char unknown_02[2]; /* +02 */
    int encode1;                 /* +04 ea1 encoder function (emit_register_operand, emit_memory_operand, ...; an
                                    address: the decompiler calls it through code *) */
    int encode2;                 /* +08 ea2 encoder function */
    char shift1a;                /* +0c ea1 first field shift (register / value), -1 none */
    char shift1b;                /* +0d ea1 second field shift (displacement), -1 none */
    char shift2a;                /* +0e ea2 first field shift */
    char shift2b;                /* +0f ea2 second field shift */
    char *mnemonic;              /* +10 "MOV", "MOV.W", ... */
};
// @size instruction_format 0x14

/* the size-class allocator (pool_alloc, pool_try_alloc, pool_free; the same code and records as shcpep's
   alloc_zeroed): a chunk of one size class (new_pool_chunk allocates 0x414 bytes) */
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
    short size;                  /* +00 block size (a multiple of 4, at most 0x400) */
    unsigned char unknown_02[2]; /* +02 */
    struct alloc_chunk *chunks;  /* +04 */
};
// @size alloc_size_class 0x8

/* a block of up to 32 size classes (0x108 bytes); the list head is g_pool_size_classes */
struct alloc_class_table {
    short count;                 /* +00 classes used */
    unsigned char unknown_02[2]; /* +02 */
    struct alloc_class_table *next; /* +04 */
    struct alloc_size_class cls[32]; /* +08 */
};
// @size alloc_class_table 0x108

/* a literal of the pool tables (pool_alloc(0x10)); shcpep's struct */
struct literal_entry {
    struct literal_entry *next;  /* +00 insertion order */
    struct literal_entry *hash_next; /* +04 bucket chain */
    int value;                   /* +08 */
    struct label_ref *labels;    /* +0c the symbols added to the value (a copied list), 0 for a plain number */
};
// @size literal_entry 0x10

/* g_word_literal_table / g_long_literal_table (layout pass 0 and the final emission) and their pass-1 copies */
struct literal_table {
    struct literal_entry *head;  /* +000 */
    struct literal_entry *tail;  /* +004 */
    int count;                   /* +008 */
    struct literal_entry *buckets[0x7f]; /* +00c hash = (value + the label numbers) % 0x7f */
};
// @size literal_table 0x208

/* one of the four buffered output channels (g_output_channels): 0 the layout pass decision spool ("wb+",
   0x1000, spilled to a temp file when full), 1 the object file ("wb", 0xff: one object record), 2 the assembler
   source text ("w", 0x100), 3 the listing ("a", line width + 2) */
struct output_channel {
    char *buffer;                /* +00 */
    char *end;                   /* +04 buffer + size, less the bytes kept for the line end / record checksum */
    char *cursor;                /* +08 next free byte */
    short opened;                /* +0c 1 once opened (channel 0: once its temp file exists and holds data) */
    short unknown_0e;            /* +0e set 0 when opened */
    short size;                  /* +10 buffer size */
    unsigned char unknown_12[2]; /* +12 */
    FILE *file;                  /* +14 */
    char *mode;                  /* +18 fopen mode */
};
// @size output_channel 0x1c

/* the per-function aux record (.asa/.asb tag 0xc; g_aux_record_table, request->aux_count of them, indexed by the
   function symbol's aux_index). shcpep's layout; the comments add what shcasm's code shows */
struct aux_reg_range {
    struct aux_reg_range *next;  /* +00 */
    char before_reg;             /* +04 */
    char after_reg;              /* +05 */
    unsigned char unknown_06[2]; /* +06 */
    int start_expno;             /* +08 */
    int end_expno;               /* +0c */
};
// @size aux_reg_range 0x10

struct aux_record {
    int frame_size;              /* +00 local frame (add #-frame_size,r15 in the prologue) */
    short saved_regs;            /* +04 bit n: Rn saved */
    short saved_regs2;           /* +06 bit n: FRn (register 0x10+n) saved */
    unsigned char saved_sys;     /* +08 bit 0: FPUL, bit 1: FPSCR saved */
    unsigned char unknown_09;    /* +09 */
    unsigned short flags;        /* +0a 0x8000: PR not saved (leaf); 0x4000: interrupt function (returns with RTE);
                                    0x2000 with 0x4000: returns with TRAPA #trap_number; 0x0800/0x1000/0x1800:
                                    the kind of stack_value of a stack switch (constant, variable, symbol address) */
    int max_stack;               /* +0c maximum stack depth */
    int stack_value;             /* +10 the new stack of a stack switch (a constant or a symbol number) */
    unsigned short range_count;  /* +14 */
    unsigned char trap_number;   /* +16 TRAPA immediate of the 0x2000 return */
    unsigned char saved_mac;     /* +17 bit 0: MACL, bit 1: MACH saved */
    struct aux_reg_range *ranges; /* +18 */
    int stack_offset_count;      /* +1c (address, stack offset) records of the function in g_stack_offset_temp */
    int expno_count;             /* +20 highest expression number (the size of the register/variable map) */
    int sp_adjust;               /* +24 added to frame_size by the epilogue (shcpep: fold_add_immediates) */
    char reg28;                  /* +28 a register number */
    unsigned char unknown_29[3]; /* +29 */
    unsigned char runtime_routines_used[0x17]; /* +2c bit map of the runtime routines it calls (8 per byte, names at
                                    0043cb24, "; used runtime library name:") */
    unsigned char unknown_43;    /* +43 */
};
// @size aux_record 0x44

/* a node of g_stack_adjust_list: a stack pointer change not visible as an immediate */
struct stack_adjust_node {
    struct stack_adjust_node *next; /* +00 */
    int amount;                  /* +04 */
};
// @size stack_adjust_node 0x8

/* a symbol or label record [the .asa/.asb symbols]: load_intermediate_record_stream reads them into one array of
   request->label_count (g_symbol_table), create_symbol_entry makes more in blocks of 32; hashed by number % 0x3fd
   in g_symbol_hash */
struct symbol {
    unsigned char kind;          /* +00 low 5 bits: 1 function, 2 internal label, 3 case label, 4 default label,
                                    5 named label, 7..9 static data, 0xa/0xb others, 0xc function aux (merged into
                                    the kind-1 record), 0xf literal pool label; the layout passes walk kinds <= 5 */
    unsigned char flags;         /* +01 the tag bits 0xc0; 0x80: printed as _name, not Lnnn */
    unsigned char attr;          /* +02 attribute bits 0x01..0x20 (& 3, 0x20 abs16 address) */
    unsigned char attr2;         /* +03 second attribute byte (kinds > 6): a register number, 0xff none */
    unsigned char unknown_04[2]; /* +04 */
    short number;                /* +06 symbol/label number (label_ref.labno1; the hash key) */
    int value;                   /* +08 position in its section: shcpep's estimate, corrected by the layout passes'
                                    running shrink */
    char *name;                  /* +0c (kinds > 4) */
    short aux_index;             /* +10 functions: index into g_aux_record_table */
    unsigned char unknown_12[2]; /* +12 */
    struct symbol *hash_next;    /* +14 next in its g_symbol_hash bucket */
    short section_id;            /* +18 id of the request_section it is in */
    short section_number;        /* +1a its object section number */
    int sequence;                /* +1c load order */
    unsigned char unknown_20[4]; /* +20 */
    struct layout_record *layout_records; /* +24 labels: the layout records that follow it in .ofb. A literal pool
                                    label (kind 0xf) holds an int here instead (the position of the pool's long
                                    part) */
    short external_index;        /* +28 import/export number of an external symbol */
    unsigned char unknown_2a[2]; /* +2a */
};
// @size symbol 0x2c

/* a .ofb record kept for the layout passes (alloc_layout_record: calloc(1, 0x20)), filled as shcpep's write_ofb_*
   writers wrote it; on a label's layout_records list or g_layout_pending_records; the relax_* handlers resize it
   (pass 0) and resolve_layout_record frees it (pass 1) */
struct layout_record {
    struct layout_record *next;  /* +00 */
    psd_op op;                   /* +04 */
    char size;                   /* +05 current size in bytes; a handler stores the new size and adds old - new
                                    to the pass's shrink */
    unsigned char misc;          /* +06 the record's psd misc (JUMPT/JUMPF; 0x80 delayed branch, 2: no literal
                                    pool may follow) */
    unsigned char flg;           /* +07 the record's psd flg: low 2 bits the operand size (0 B, 1 W, 2 L) */
    int location;                /* +08 location in the section; the running shrink is subtracted */
    char part_size[4];           /* +0c sizes of the instructions the record expands to (MOVI / JUMP parts) */
    int value;                   /* +10 immediate / displacement / frame offset; B_ASM and CTBL: size in bytes */
    struct label_ref *labels;    /* +14 the operand's label terms (freed by resolve_layout_record); MV_LOC, MVA_LC,
                                    C_JMP and CTBL hold a plain int here */
    short pool_size;             /* +18 bytes of literal pool placed after the record; C_JMP: the table label */
    short label;                 /* +1a C_JMP: the default label */
    int pool_before_table;       /* +1c C_JMP: literal pool bytes (with alignment) placed before the case table */
};
// @size layout_record 0x20

/* the per-section layout state (pool_alloc(0x30) for every section in run_layout_passes, request_section.layout) */
struct section_layout {
    short section_number[4];     /* +00 object section number per kind (program, const, data, bss), swapped with
                                    g_section_numbers by switch_section */
    int location[4];             /* +08 location counters per kind */
    int object_offset[4];        /* +18 swapped with g_section_object_offsets */
    int shrink_pass0;            /* +28 g_layout_shrink_pass0 while the section is not current */
    int shrink_pass1;            /* +2c g_layout_shrink_pass1 while the section is not current */
};
// @size section_layout 0x30

/* a debug scope (pool_alloc(0x10); g_scope_stack holds pointers to the open ones) */
struct debug_scope {
    int start;                   /* +00 start address */
    int end;                     /* +04 end address (emit_debug_information stores the current location) */
    struct debug_scope *next;    /* +08 next sibling */
    struct debug_scope *child;   /* +0c first / next child still to emit */
};
// @size debug_scope 0x10

/* a debug symbol of the current function, hashed by id % 0x7f in g_debug_symbol_hash (pool_alloc(0x20)) */
struct debug_symbol {
    struct debug_symbol *next;   /* +00 hash chain */
    short id;                    /* +04 debug id (symbol number - 0xb6) */
    unsigned char kind;          /* +06 kind << 1 | 1 */
    unsigned char loc_kind;      /* +07 0 none, 1 register, 6 stack offset */
    short value;                 /* +08 record word - 1 */
    unsigned char word_0a[2];    /* +0a copied as a word into the 0x34 records */
    short scope_depth;           /* +0c the scope depth when defined */
    unsigned char unknown_0e[2]; /* +0e */
    int word_10;                 /* +10 copied into the 0x34 records after the location kind */
    int loc;                     /* +14 register number (low byte) or stack offset */
    char *name;                  /* +18 */
    struct debug_type_ext *type_ext; /* +1c kind 0xe only (pool_alloc(8)) */
};
// @size debug_symbol 0x20

/* the kind-0xe extension of a debug_symbol */
struct debug_type_ext {
    unsigned char byte0;         /* +00 */
    unsigned char flags;         /* +01 0x80: a value follows; 0x40: the value is a register (byte at +4) */
    unsigned char unknown_02[2]; /* +02 */
    int value;                   /* +04 */
};
// @size debug_type_ext 0x8

/* a location of the current function's debug data, hashed by id % 0x7f in g_debug_location_hash */
struct debug_location {
    struct debug_location *next; /* +00 hash chain */
    short id;                    /* +04 */
    unsigned char kind;          /* +06 6 stack offset, else register */
    unsigned char unknown_07;    /* +07 */
    int value;                   /* +08 stack offset (rebased by the frame when negative) or register (low byte) */
};
// @size debug_location 0xc

/* a call site of a source line range (pool_alloc(8)) */
struct line_call_site {
    struct line_call_site *next; /* +00 */
    int address;                 /* +04 address of the JSR/BSR/BSRF */
};
// @size line_call_site 0x8

/* a source line's address range (record_source_line_range: pool_alloc(0x18)); the .LINE path fills only
   next/filno/linno */
struct source_line_range {
    struct source_line_range *next; /* +00 */
    short filno;                 /* +04 */
    unsigned short linno;        /* +06 */
    short section;               /* +08 */
    short call_count;            /* +0a */
    int start;                   /* +0c */
    int end;                     /* +10 */
    struct line_call_site *calls; /* +14 */
};
// @size source_line_range 0x18

/* a register holding a variable (load_function_register_variable_map, update_register_variable_map) */
struct register_variable {
    struct register_variable *next; /* +00 */
    short reg;                   /* +04 register (as read from the .reg file) */
    short variable;              /* +06 variable number */
};
// @size register_variable 0x8

/* a candidate of update_register_variable_map (pool_alloc(0x10)) */
struct register_candidate {
    struct register_candidate *next; /* +00 next register */
    short reg;                   /* +04 */
    short variable;              /* +06 */
    short weight;                /* +08 summed expression use counts */
    unsigned char unknown_0a[2]; /* +0a */
    struct register_candidate *alternative; /* +0c the same register, another variable */
};
// @size register_candidate 0x10

/* an expression number seen in the current range (update_debug_info_for_record: pool_alloc(0xc)) */
struct expno_use {
    struct expno_use *next;      /* +00 */
    int expno;                   /* +04 */
    short count;                 /* +08 */
    unsigned char unknown_0a[2]; /* +0a */
};
// @size expno_use 0xc

/* The request record every SHC stage loads from its counted request file (load_request_record_file) and
   stores back (store_request_record_file), as shcasm sees it. shcasm keeps it in g_current_request and
   g_loaded_request (same pointer; DAT_0044d9a8 is a third alias).

   File: a short giving the size of the fixed part, the fixed part read raw, then a short 0x1e and the
   variable part (strings and lists that replace the pointer fields; FUN_00432c10 in shcasm, FUN_00407390
   in shcprm).

   SIZE: shcprm writes the size word from the constant 0x16c at 0x4110dc, clears 0x16c bytes of
   g_current_record (00401512..0040151d) and stores options at +0x168/+0x169. shcasm allocates whatever
   the size word says. The fixed part is therefore 0x16c bytes, not 0x164 (shcpep's size line).

   Names come from shcpep's types.h where its evidence holds, from shcprm's option table (keyword ->
   action entry {kind, size<<16|value, handler, alias slot} at 0x4114b0..0x4119b0; alias slot ->
   record offset in bind_current_record_aliases 00404cb0), from shcprm normalize_record_options
   (00402070) and allocate_intermediate_file_names (004026a0), and from shctil's statistics table
   (0x4124b4..0x4126d0). Options with a "=" value are -option=value on the shc command line; extra=
   subkeys are -extra=<key>=<n>. Natural alignment; offsets in the comments are hex. */

struct request {
    char *source_name;                   /* +000 the source file, for messages (shcpep) */
    short optimize;                      /* +004 -optimize=0|1 (numeric 0..1). shcasm: 'h' instead of 'H' object
                                            header, picks .sua(+084)/.asa(+098) when 0, .sub/.asb when 1; one byte
                                            read of its low half (0040f97b, 0041013c: DAT_00448131 = byte +004) */
    unsigned short show;                 /* +006 -show= bits: source 0x1, object 0x2, statistics 0x4, include 0x8,
                                            expansion 0x10 (shcprm table 0x413fe0, "no" keywords clear); cleared
                                            when nolistfile. shcasm tests & 2 (object listing) and & 0x11 */
    int list_width;                      /* +008 -show=width=n. shcasm 004348a0: page header width (0 -> 0x80) */
    int list_length;                     /* +00c -show=length=n (lines per listing page) */
    short listfile;                      /* +010 1 = -listfile, 0 = -nolistfile */
    short code;                          /* +012 -code=: 1 machinecode, 2 asmcode (0 never set by an option).
                                            shcasm: == 2 selects the .src (asm source) output path */
    short word_014;                      /* +014 shcprm binds an alias slot here but no option writes it; shcasm
                                            does not read it */
    short debug;                         /* +016 1 = -debug, 0 = -nodebug; cleared (and +034 set) for asmcode */
    short cpu;                           /* +018 -cpu=: 0 sh1/7000, 1 sh2/7600, 2 sh3, 3 sh3e (normalised to 2 +
                                            fpu_mode bits), 4 sh4. 0x7fff from SHCPU when absent (shcpep: nonzero
                                            -> JUMPT/JUMPF take part in the branch passes) */
    short pic;                           /* +01a -pic=0|1, forced 0 for sh1 (shcpep: label-difference literals) */
    short string_section;                /* +01c -string=const (0) | data (1) */
    short comment_nest;                  /* +01e -comment=nonest (0) | nest (1) */
    short speed;                         /* +020 -nospeed 0, -speed 1, -size 2 (2 becomes 0 + optimize_size) */
    unsigned char unknown_022[2];        /* +022 */
    struct request_section *sections;   /* +024 section records (program/const/data/bss sizes, object ids) */
    short input_code;                    /* +028 -euc (0) | -sjis (1): source character code; outcode default */
    char endian;                         /* +02a -endian=big (0) | little (1) */
    char division;                       /* +02b -division=cpu (0) | peripheral (1) | nomask (2) */
    int aggressive;                      /* +02c -aggressive=n (numeric 0..0xffff) */
    char inline_mode;                    /* +030 -inline 1, -noinline 2 */
    unsigned char unknown_031[1];        /* +031 */
    short inline_size;                   /* +032 -inline=n; cleared by -noinline, or unless speed and optimize */
    char asm_debug;                      /* +034 set to 1 by shcprm when debug (or C++ browser) is asked for with
                                            -code=asmcode: debug info goes into the .src output. shcasm tests == 1
                                            in run_assembler_passes and emit_final_asm_record_stream */
    char optimize_size;                  /* +035 set to 1 by shcprm for -size (speed 2 -> 0) */
    char macsave;                        /* +036 -macsave=0|1 (shcpep: 0 -> calls clobber MACH/MACL) */
    unsigned char fpu_mode;              /* +037 bit 1: denormalize off (sh3e, or sh4 -denormalize=off), bit 2:
                                            round to zero (sh3e, or sh4 -round=zero) */
    char *temp_list_path;                /* +038 temp listing file (.lst/.lpp suffix), only when listfile.
                                            shcasm FUN_00413626: file kind 3 */
    char *object_path;                   /* +03c -objectfile=name. shcasm: module name in the machine-code header
                                            (FUN_004130d6), file kinds 1-2 (FUN_00413626) */
    struct request_string *defines;      /* +040 -define= list (shcpep string_list_040) */
    unsigned char unknown_044[4];        /* +044 */
    struct request_string12 *include_dirs; /* +048 -include= list (shcprm handler 0x405ff0) */
    struct request_sized_string *preincludes; /* +04c -preinclude= list */
    char *section_program;               /* +050 -section=program=name (shcpep path_050). shcasm 00427d94 */
    char *section_const;                 /* +054 -section=const=name */
    char *section_data;                  /* +058 -section=data=name */
    char *section_bss;                   /* +05c -section=bss=name */
    char *message_path;                  /* +060 .msg, the message record file */
    char *ila_path;                      /* +064 .ila */
    char *ilb_path;                      /* +068 .ilb */
    char *sym_path;                      /* +06c .sym */
    char *swi_path;                      /* +070 .swi */
    char *int_path;                      /* +074 .int */
    char *db1_path;                      /* +078 .db1: emit_debug_information reads its debug records ("rb") */
    char *db2_path;                      /* +07c .db2 (shcgen opens it when debug): emit_debug_information reads the
                                            functions' debug symbol and location tables from it ("rb") */
    char *reg_path;                      /* +080 .reg. shcasm FUN_0041e360 opens it when optimize */
    char *sua_path;                      /* +084 .sua input (optimize 0) */
    char *sub_path;                      /* +088 .sub (optimize 1) */
    char *sud_path;                      /* +08c .sud. shcasm read_next_backend_record reopens it at EOF */
    char *ofa_path;                      /* +090 .ofa. shcasm FUN_0042926d when optimize 0 */
    char *ofb_path;                      /* +094 .ofb. shcasm FUN_0042926d when optimize 1 */
    char *asa_path;                      /* +098 .asa input (shcasm main: optimize 0, or back flags 0x2000) */
    char *asb_path;                      /* +09c .asb input (optimize 1, or back flags 0x40) */
    char *asl_path;                      /* +0a0 .asl. shcasm opens it when code == 2 (asmcode) */
    char *lit_path;                      /* +0a4 .lit */
    char *log_path;                      /* +0a8 -log=name */
    int label_count;                     /* +0ac symbols/labels in the .asa stream (shcpep); shcasm sizes its
                                            symbol array from it and stores DAT_0044a6dc back; shctil adds it into
                                            NUMBER OF INTERNAL/EXTERNAL SYMBOLS */
    int int_0b0;                         /* +0b0 label-number bound: shcgen faults above 0x7f49 and adds it + 0xb6
                                            to label_count; shcasm FUN_0041013c skips symbol ids in (+0b4, +0b0] */
    int int_0b4;                         /* +0b4 lower end of that skipped id range */
    struct request_entry *entry11_list_0b8; /* +0b8 */
    struct request_entry *entry11_list_0bc; /* +0bc */
    struct request_entry *entry12_list_0c0; /* +0c0 */
    unsigned char unknown_0c4[4];        /* +0c4 */
    int warning_count;                   /* +0c8 shctil NUMBER OF WARNINGS */
    int error_count;                     /* +0cc shctil NUMBER OF ERRORS */
    int source_line_count;               /* +0d0 shctil COMPILED SOURCE LINE */
    int result_0d4;                      /* +0d4 (shcpep) */
    unsigned char unknown_0d8[0xc];      /* +0d8 */
    int extern_ref_count;                /* +0e4 written by shcasm (DAT_0044bc5c: type 10/11 undefined symbols +
                                            runtime helpers used); shctil NUMBER OF EXTERNAL REFERENCE SYMBOLS */
    int extern_def_count;                /* +0e8 written by shcasm (DAT_0044a8ea, from the .asa trailer record 0x0e);
                                            shctil NUMBER OF EXTERNAL DEFINITION SYMBOLS */
    struct request_source_file *source_files; /* +0ec file number -> name, for messages; shcasm counts it for
                                            the object header file table */
    char compile_date[0x20];             /* +0f0 "dd-Mon-yyyy hh:mm:ss" built by shcprm FUN_004044b0 from ctime():
                                            dd +0f0, Mon +0f3, yyyy +0f7 (yy +0f9), hh +0fc, mm +0ff, ss +102,
                                            NUL +104. shcasm: listing page header (whole string, 004348a0) and the
                                            object header date YYMMDDhhmmss (bytes +0f9.. ; month name mapped to
                                            digits by FUN_00412f3f) in 0040f483 and 00412995 */
    int aux_count;                       /* +110 aux (function) records in the .asa stream (shcpep) */
    char *list_path;                     /* +114 -listfile=name, else derived from the source (shcpep string_114) */
    int stage;                           /* +118 the stage that loaded it (4 = shcasm, 3 = shcpep) */
    char *compiler_version;              /* +11c */
    char *copyright;                     /* +120 */
    unsigned char message_flags;         /* +124 low byte of -extra=cnt=n (shcprm stores an int). shcasm
                                            report_message_by_code tests & 8; shcprm & 4 = name intermediates
                                            after the source instead of temp names */
    unsigned char unknown_125[3];        /* +125 rest of the extra=cnt int */
    unsigned int frt_flags;              /* +128 -extra=frt=n */
    unsigned int mdl_flags;              /* +12c -extra=mdl=n */
    unsigned int back_flags;             /* +130 -extra=back=n. shcasm main: & 0x2040 == 0x40 -> .asb, == 0x2000
                                            -> .asa; also read as a byte at +131 (& 4 = bit 0x400: signal handler
                                            mode; & 0x40 = bit 0x4000 in 00426a8d) */
    unsigned int gen_flags;              /* +134 -extra=gen=n */
    unsigned int stage_flags;            /* +138 -extra=pep=n (shcpep debug-trace flags, g_stage_flags) */
    unsigned char flags_13c;             /* +13c low byte of -extra=asm=n (int store). & 1, & 2, & 4, & 8 =
                                            "pipetbl dump after pipeline()" */
    unsigned char flags_13d;             /* +13d second byte of extra=asm: & 4 (scheduling, 0041a982/004222bd),
                                            & 8 (alignment, with align16) */
    unsigned char unknown_13e[2];        /* +13e rest of the extra=asm int */
    char *extra_temp;                    /* +140 -extra=temp=string (shcpep string_140) */
    struct request_cpp_block *cpp_block; /* +144 nonzero: C++ (shcasm: CPP_SH language tag, C++ banner) */
    char double_float;                   /* +148 -double=float; cleared (fpu single) for sh4 */
    char scratch_bank_reg_count;         /* +149 -extra=reg=n (shcpep: registers 0x14.. and 0x24.. clobbered) */
    char message_all;                    /* +14a -message (1) | -nomessage (0) */
    char align16;                        /* +14b -align16 (1) | -noalign16 (0) (shcpep pool_flag_14b). shcasm
                                            00412cda, 00425fbc, 004262e0, 00428aa3: 16-byte alignment */
    char nestinline;                     /* +14c -nestinline=n */
    char outcode;                        /* +14d -outcode=euc (0) | sjis (1); 2 = default -> input_code */
    unsigned char unknown_14e[2];        /* +14e */
    unsigned int reg_mask_150;           /* +150 one bit per register number (shcpep) */
    unsigned char abs16;                 /* +154 -abs16=run (1) | all (3). shcasm 0042805a: == 3, & 1 */
    char loop;                           /* +155 -loop (1) | -noloop (0); 0 when optimize 0 */
    char rtnext;                         /* +156 -rtnext (1) | -nortnext (0) */
    char fpu;                            /* +157 -fpu=single (1) | double (2); 0 unless sh4 */
    char denormalize;                    /* +158 -denormalize=off (0) | on (1) */
    char round;                          /* +159 -round=zero (0) | nearest (1) */
    unsigned char unknown_15a[2];        /* +15a */
    char *obl_path;                      /* +15c .obl, made only when listfile (shcpep string_15c). shcasm
                                            run_assembler_passes opens it with show object + source/expansion */
    int info_count;                      /* +160 shctil NUMBER OF INFORMATIONS; shcasm report_message_by_code
                                            increments it */
    unsigned char unknown_164[4];        /* +164 */
    char chgincpath;                     /* +168 -chgincpath */
    char errorpath;                      /* +169 -errorpath */
    unsigned char unknown_16a[2];        /* +16a */
};
// @size request 0x16c

/* a section record of request->sections (shcasm walks it per section kind 0..3) */
struct request_section {
    short id;                            /* +00 section number */
    short name_len;                      /* +02 */
    char *name;                          /* +04 */
    int size[4];                         /* +08 program, const, data, bss sizes (shctil SECTION SIZE INFORMATION
                                            sums +08..+14; shcasm emits a header entry per nonzero size) */
    struct section_layout *layout;       /* +18 shcasm's layout state of the section (run_layout_passes allocates
                                            it; its first words are the object section number per kind); freed and
                                            zeroed by store_request_record_updates */
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
    short filno;                         /* +04 file number (shcasm object header: 1..count) */
    short name_len;                      /* +06 shcasm writes its low byte as the name length */
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
    char preprocessor;                   /* +00 -preprocessor (shcprm alias cpp+0) */
    char browser;                        /* +01 -browser (cpp+1); with asmcode it becomes request asm_debug */
    char ecpp;                           /* +02 -ecpp (cpp+2) */
    unsigned char unknown_03[1];         /* +03 */
    char *strings[5];                    /* +04 [0] .tkn, [1] .id, [2] source-derived name (normalize),
                                            [3] .dtb (debug), [4] unknown */
};
// @size request_cpp_block 0x18

/* a row of g_opcode_format_index, per psd_op (assemble_instruction) */
struct opcode_format {
    unsigned char format;        /* +00 the g_instruction_format_table row, 0xff none */
    unsigned char unknown_01[3]; /* +01 */
    void *alternatives;          /* +04 a list of 8-byte rows {format row, operand size, ea1 kind, ea2 kind, ...}
                                    chosen by the operands */
};
// @size opcode_format 0x8

/* an entry of the C++ demangler's tables (g_demangle_tokens, g_demangle_placeholder_types, g_demangle_type_pieces,
   g_demangle_back_references; 256 each) */
struct demangle_entry {
    short kind;                  /* +00 tokens: 1 'F', 2 '_' return separator, 3 complete type, 0 consumed; type
                                    pieces: 2 type/name, 7 member pointer; placeholders/back references: 1 used */
    unsigned char unknown_02[2]; /* +02 */
    char *text;                  /* +04 */
};
// @size demangle_entry 0x8

/* a temporary file of g_temp_files (open_temp_file, close_and_delete_temp_files) */
struct temp_file {
    char *path;                  /* +00 */
    FILE *file;                  /* +04 */
};
// @size temp_file 0x8
