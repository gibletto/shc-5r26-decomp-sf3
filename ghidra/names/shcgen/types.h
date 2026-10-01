/* shcgen's records, applied to the Ghidra project by ApplyStageTables.java and compiled into the C rebuild as
   include/stage_types.h (tools/gen-stage-types.py adds a typedef for each struct and the enum constants).
   shcgen has no debug dumps; the pseudo-code records (psd, ea, label_ref) and the request record are the ones
   shcpep reads back (shcgen writes the .sua stream shcpep loads, and every stage loads the same request file), so
   they keep shcpep's names, the [bracketed] ones from shcpep's own dumps. Every field sits at its natural
   alignment, so the layout is the same under Ghidra's packing and Visual C++'s. */

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

/* a node of the .ilb tree (00433720 read_ilb_node switches on the op byte and calls the per-shape readers
   00433b20 / 00433c20 / 00433d00 / 00433e00 / 00433e90 / 00433f40 / 00434160 / 004341f0 / 004342b0 / 00434360 /
   004343f0 / 004344b0 / 00434590 / 00434640 / 004346e0, which mirror shcmdl write_il_node 00404ae0 field for
   field). Size 0x2c: 00415cd0 calls the pool constructor 00433280(0x2c, 0x800), which stores 0x2c in
   g_gen_node_size (0045e634) and callocs 0x800 nodes chained through +0x14; 00433580 takes one (writes op),
   00433500 clears one (bytes 0..0x27 field by field, then g_gen_node_size - 0x28 more bytes, i.e. the desc
   pointer) and appends it to the free list through +0x14.
   NOT the same layout as shcmdl's il_node (0x68): the .ilb record is re-packed (type at +05 here, +03 there). */
struct gen_node {
    il_op op;                    /* +00 the IL operator (first .ilb byte; 00433580 stores it) */
    unsigned char bit_offset;    /* +01 IL_B_QUALIFY: bit position of the field counted from the top of its unit
                                    (004342b0 reads it from the .ilb = shcmdl il_node +01; 004034e0 copies it to
                                    desc +04; 0041c200 cases 6..12 shift by 8/16/32 - offset - width) */
    short symx;                  /* +02 symbol number of IL_ID / IL_FUNC / IL_BLOCK / IL_SWITCH / labels (00433f40
                                    = shcmdl il_node.symx +04); < 0 a compiler temporary (0041b070 looks it up in
                                    g_lreg_table), else index - 0xb6 into g_symbol_table (0041b070, 0040ff00) */
    unsigned char bit_width;     /* +04 IL_B_QUALIFY: field width in bits (004342b0 = shcmdl il_node +02 byte;
                                    004034e0 copies it to desc +05) */
    unsigned char type;          /* +05 the type byte (= shcmdl il_node.type +03): 1 const, 2 volatile (0041b070
                                    sets desc flags2 0x40), 4 unsigned (0041d1a0 picks unsigned routines), 0x18
                                    size, 0xe0 kind; see enums il_type_kind / il_type_size / il_type_class.
                                    Read for every typed operator by 00433720 ((type & 0xe0) == 0x60/0x80 selects
                                    the readers with an aggregate size) */
    short call_06;               /* +06 IL_CALL: one byte the .ilb gives after the type (00433e00 / 00433e90 store
                                    it as a short; shcmdl writes il_node +06); use not established */
    short filn;                  /* +08 source file (every reader; 0041abe0 copies it to g_msg_filn 0045fee8 for
                                    messages; 0040ff00 passes it to message 0x7e4) */
    unsigned short line;         /* +0a source line (every reader; 0041abe0 -> g_msg_line 0045f9ea) */
    struct gen_node *parent;     /* +0c (004335c0 sets it when adding an operand; 004347a0 walks it for the depth;
                                    0041b070 reads the parent's op) */
    struct gen_node *child;      /* +10 first operand (004335c0 prepends, 00433640 counts, 004335f0 finds the
                                    n-th, 00433660 the last) */
    struct gen_node *next;       /* +14 next operand of the same parent; also the free-list link (00433500,
                                    00433580, 00433280) */
    int val;                     /* +18 IL_CONST value (00434360; first word of 8/12-byte constants 004343f0 /
                                    004344b0; 4-byte pointer constant 00434590); aggregate size of struct/array
                                    typed nodes (00433d00, 00433e90, 004341f0, 0041b070 from the symbol); IL_ASM
                                    asmno (004346e0); IL_PRI/PRD/POI/POD step size (00434640; 0041c200 cases
                                    0xc/0xd); IL_BLOCK/E_BLOCK blkflg byte (00433f40 / 00433b20; bit 0 tested
                                    at 00407af0) */
    int val2;                    /* +1c IL_QUALIFY member offset (00434160 / 004341f0; 0041c200 imm case 1 and
                                    disp cases 4..6 add the parent's); IL_B_QUALIFY unit offset (004342b0);
                                    second word of a double constant (004343f0 / 004344b0); IL_ASM asmsize */
    int val3;                    /* +20 third word of a long double constant (004344b0); as a byte: IL_CALL flags
                                    (00433e00, shcmdl il_node +09 [tail]: bit 4 tested in 004053a0), FR0set of
                                    IL_ID / assignments / A_ops (00433c20, 00433d00, 00433f40 when
                                    request->stage == 2; bit 1 tested in 00421890) */
    short lreg;                  /* +24 IL_ID: the optimizer's lreg (00433f40; 0041b070 / 0042f830 use its absolute
                                    value, 0x8000 special); pointer constants: the 2-byte word shcmdl writes
                                    before the value (00434590) */
    short listno;                /* +26 listing line (every reader; 0041abe0 -> 0045fa20 for messages) */
    struct node_desc *desc;      /* +28 storage descriptor (0041b070 allocates 0x84 bytes; 0041be70 frees) */
};
// @size gen_node 0x2c

/* the storage descriptor of a gen_node (0041b070 initialize_node_descriptor_and_operand_slots: FUN_00406830(0x84),
   register slot bytes +2c..+30, +34..+37, +38..+3c, +3d..+3e, +41..+43, +44..+45, +46, +47 set to 0xff;
   0041be70 frees the ea records at +54..+64 and the label lists of +68/+74/+50, then the 0x84 bytes).
   Register masks come in pairs: general registers (bit n = Rn) at +12..+1c, floating registers (bit n = FRn)
   at +20..+2a, same order. */
struct node_desc {
    char usage;                  /* +00 how the parent uses the value (enum desc_usage), set by 0041b070 from the
                                    parent's op and operand position; 0040ceb0 skips the template when 0 and the
                                    node has no side effect (flags2 0x40); 1 sends it to 004289f0 (condition) */
    char opnd_class;             /* +01 where the value is (enum operand_class): 00401c90 0 (scratch register) /
                                    1 (target register from +14); 0040ba90 2 (both operands constant, folded);
                                    004031a0 / 00402200 3 (memory, @(R0,Rn) or stacked). 00423410 indexes the
                                    template matrix rows by it (0..3); 004289f0 takes +69 as the register for 0/1 */
    unsigned char flags2;        /* +02 bit 0x01 (0041b070: aggregates of int/long elements, 2nd argument of
                                    strcpy/strcmp); 0x02 (propagated to the parent in 0040ceb0; a child with it and
                                    usage 3 invalidates r0..r3 / fr0..fr3 contents, 0042fdb0(0xf000f)); 0x04 value
                                    goes to the stack as an 8-byte push (0040ceb0 op 0x60 to @-R15; 00431950 from
                                    tmpl +30); 0x08 value is pushed on the stack and its consumer pops it (0040ceb0
                                    moves to @-R15, operand readers then use 004497e0 @R15+); 0x10 (004034e0); 0x20
                                    (00424c80 from tmpl flags 4, 00401f30; tested by 004289f0 for IL_B_AND); 0x40
                                    side effect / volatile in the subtree (0041b070: type & 2, assignments, calls,
                                    PRI..POD; propagated to the parent); 0x80 (0041f8d0; 0041d1a0 picks the
                                    compare-routine variant) */
    unsigned char flags3;        /* +03 bit 0x01 subtree has conditional flow (0040ceb0 for IL_COND / AND / OR,
                                    propagated up; IL_SWITCH in 0041b070); 0x04 the address is in the register of
                                    +58 (00422180); 0x08 (004031a0, 004034e0, 004037e0 ...); 0x10 the saved value
                                    +60 is on the stack (0041ec90 sets; 0041c200 pops @R15+ instead of +60);
                                    0x20 the value is in memory addressed through +46 / +5c (0041b070 struct
                                    return, 00402200, 0040ceb0 builds +58/+5c for it); 0x80 IL_ID handled in
                                    place (0041b070 sets for every IL_ID, 004042e0 clears; 0040ceb0 / 00404b90
                                    test) */
    char bit_offset;             /* +04 IL_B_QUALIFY bit position (004034e0 from node +01; 0041c200 imm cases
                                    4/6..9/0x12..0x14, disp cases 6/10..12; 00431f90 / 00431fe0 / 00430890) */
    char bit_width;              /* +05 IL_B_QUALIFY width (004034e0 from node +04; 0041c200 case 5 mask
                                    (1 << width) - 1; 00412390 template entry flag 0x20 skips when width == 32) */
    char builtin;                /* +06 built-in function of an IL_CALL (enum builtin_fn): 0041b070 matches the
                                    callee's name after "__builtin_" against the table at 00458320 and stores the
                                    byte from 004583e8; 0040ff00 / 0041c200 / 0041db10 / 00429f90 switch on it;
                                    0 = ordinary call (0041b070 then marks r4..r7 in need_regs) */
    unsigned char flags7;        /* +07 bit 0x02 (00422180 on two narrowing casts of equal type; 004037e0); 0x04 /
                                    0x08 (0041c200: GBR / pool constant already in r0); 0x10 subtree contains a
                                    call (0041b070, propagated up); 0x20 needs a runtime routine (0041aed0: calls,
                                    div/mod, float ops without FPU, mul without mul.l, variable shifts below
                                    SH-3); 0x40 (inherited from the parent with +16/+24/+48: 00422180, 0040ff00;
                                    tested 00404830); 0x80 float multiply-add pair (0041b070 marks an IL_ADD /
                                    IL_A_ADD of float and its IL_MUL operand when an FPU is present; 0040ceb0 then
                                    calls 00421890 instead of the template) */
    unsigned char fpu_mode_flags; /* +08 SH-4 FPSCR.PR switching: bit 0x01 a mode switch was emitted for the node
                                    (00424c80, 0040f320, 00421890; tested 00425f60, 0042a180, 0040f610); 0x02
                                    (004289f0 second condition register) */
    char fpscr_pr;               /* +09 SH-4 only (request cpu 4, request +0x157 == 0): the tracked FPSCR.PR state
                                    g_fpscr_pr (0045f9f8) when the node was finished (0040ceb0 start and end) */
    unsigned char unknown_0a[2]; /* +0a */
    short true_label;            /* +0c usage 1: label to jump to when the condition holds (0041abe0 param 2;
                                    00404b90 places the left operand's +0c after an IL_OR) */
    short false_label;           /* +0e usage 1: label to jump to when it fails (0041abe0 param 3; 00404b90 places
                                    the left operand's +0e after an IL_AND; 0041d1a0 picks the eq/ne compare
                                    routine by whether it is set) */
    unsigned short saved_regs;   /* +10 general registers saved around the node's template: 0040ff00 collects
                                    them from regs_2c; 00414400 pushes them (MOV Rn,@-R15) before
                                    emit_template_record_sequence_for_node and pops them after */
    unsigned short pref_regs;    /* +12 general registers the result should go to: the chooser's preference
                                    mask (00401c90, 0040ceb0, 00425f60 pass it as 0041fa30's 2nd argument);
                                    0041b070 sets 1 (r0) for IL_SWITCH / IL_RETURN values; 00431950 copies
                                    template +2c / +2e into the operands' */
    unsigned short target_regs;  /* +14 the general register the result must end in: 0040ceb0 moves +68 there
                                    (00430f00 turns the mask into the register); 0040ff00 sets 1 */
    unsigned short busy_regs;    /* +16 general registers not available at this node: 0041abe0 seeds the root with
                                    g_var_gpr_mask (0045f9fa), parents copy theirs into each operand before it is
                                    generated (00422180, 0040ff00, 00401f30 ...), registers chosen for the node are
                                    added; passed as the chooser's excluded mask (0040ceb0) and ORed into
                                    g_used_gpr_mask (0045ff60) */
    unsigned short temp_regs;    /* +18 general registers the subtree used as temporaries (004289f0, 00425f60,
                                    00426fb0, 0040ceb0; template +31 clobbers in 00424c80); ORed into the parent
                                    (0040ceb0) and at the root into 0045fed0 (0041abe0) */
    unsigned short cached_regs;  /* +1a general registers whose content record the subtree set (0042f830 /
                                    0042faf0 r0..r3); ORed up (0040ceb0); 0041f8d0 tests */
    unsigned short reused_regs;  /* +1c general registers whose cached content (address / constant) the subtree
                                    reused instead of loading (00422180 after 0042ff60 hit; 0041c200 r0); ORed up
                                    (0040ceb0); 0041e740 / 0041e9e0 / 0041ec90 / 0041eef0 test it for spills */
    unsigned char unknown_1e[2]; /* +1e no access found (the general masks are +12..+1c, the floating ones
                                    +20..+2a) */
    unsigned short fpref_regs;   /* +20 floating counterpart of +12 (0041b070 sets fr0/fr1 for a double RETURN;
                                    00431950 from template +3c / +3e) */
    unsigned short ftarget_regs; /* +22 floating counterpart of +14 (0040ceb0 via 00430f30) */
    unsigned short fbusy_regs;   /* +24 floating counterpart of +16 (0041abe0 seeds from 0045fee4; ORed into
                                    g_used_fpr_mask 0045f9ac) */
    unsigned short ftemp_regs;   /* +26 floating counterpart of +18 (004289f0 condition pair, 00425f60) */
    unsigned short fcached_regs; /* +28 floating counterpart of +1a (0042f830 / 0042faf0) */
    unsigned short freused_regs; /* +2a floating counterpart of +1c (ORed up in 0040ceb0; 0041e9e0) */
    char regs_2c[5];             /* +2c registers chosen for the template's slots, slot kind 0x10 (00425f60 fills
                                    them per template reg_spec; 0041c200 source 4 reads slot (spec >> 14) & 0x3f;
                                    0040ceb0 puts the register of a side-effect-only result in [0]); 0xff = none */
    unsigned char unknown_31;    /* +31 never read (the reads at "+0x31" are the template header's) */
    unsigned short need_regs;    /* +32 hard registers the subtree needs (0041b070: the variable register of an
                                    IL_ID from g_lreg_table or its symbol's ea, 0xf0 = r4..r7 for calls, 0x8000 for
                                    lreg 0x8000; ORed from the operands); 00422180 tests it for IL_ID operands */
    char regs_34[4];             /* +34 slot kind 0x20 (00425f60; 0041c200 source 5; 00426fb0 second phase) */
    char cond_regs[5];           /* +38 004289f0 condition value registers: [0] general register for the value,
                                    [1] 0xff, [2]/[3] floating pair halves, [4] the second general register of an
                                    SH-4 PR switch; 0041c200 source 6 */
    char regs_3d[2];             /* +3d slot kind 0x60 (00425f60; 00413930 case 2) */
    unsigned char unknown_3f[2]; /* +3f not initialised to 0xff; +40 read as a byte by 0041e280 next to +41 */
    char regs_41[3];             /* +41 slot kind 0x30 (00425f60, 00426fb0, 00413930 case 1, 00431a30) */
    char regs_44[2];             /* +44 slot kind 0x40 (00425f60, 00426fb0, 0041e190) */
    char addr_reg;               /* +46 slot kind 0x50; 0040ceb0 stores here the register it loads the address of
                                    a memory result into (flags3 0x20); 0040d7d0 / 0040fca0 */
    char reg_47;                 /* +47 slot kind 0x70 (00425f60, 0041e190, 0040d7d0) */
    int frame_top;               /* +48 next free temporary frame offset (grows down): 0041abe0 seeds the root
                                    with the frame end 0045ee94, parents copy it to operands, 00420140 allocates
                                    a temporary by lowering it and returns @(disp, frame) */
    int frame_low;               /* +4c lowest temporary offset the subtree used (00420140 keeps the minimum,
                                    0040ceb0 propagates it to the parent); 0041e740 / 0041e9e0 / 0041ec90 compare
                                    it with a sibling's frame_top */
    struct label_ref *template_labels; /* +50 labels made for the template's LABEL (0x18) entries, two per 8-byte
                                    cell (00432030 builds it from tmpl flag 2; 004320a0 reads; 0041be70 frees
                                    with 004182c0) */
    struct ea *ea_54;            /* +54 operand source 7 of 0041c200; 004042e0 stores a copy of the IL_ID's
                                    operand when it substitutes template 004552f8 */
    struct ea *addr_reg_ea;      /* +58 register operand holding the address of the value (0040ceb0, 00422180) */
    struct ea *mem_ea;           /* +5c @(0,Rn) through +58 (0040ceb0 / 00422180: copy of +58 with the type set to
                                    EADISP); when set, operand readers (0041c200 source 1, 00425f60, 00422180)
                                    use it before +74 / +68 */
    struct ea *saved_ea;         /* +60 a copy of the value operand +68 kept for a later use (004034e0); 0041c200
                                    source 3 reads it when +64 is not set and flags3 0x10 is clear */
    struct ea *saved_reg_ea;     /* +64 register copy of it (0041ec90 loads it into a chosen register); 0041c200
                                    source 3 prefers it */
    struct ea value;             /* +68 where the node's value is (operand readers' default; 0040ceb0 type bit
                                    0x80 = volatile; 004289f0 base = register) */
    struct ea dest;              /* +74 where the value must go (0040ceb0 moves +68 there when they differ;
                                    0041b070 sets r0 / fr0 / frame for IL_SWITCH and IL_RETURN; 0041c200 source 2) */
    struct tmpl_header *tmpl;    /* +80 the code template chosen for the node (00422180 via 00423410; 0040ff00
                                    via 00410890; 004042e0 &004552f8); 00414400 runs its entries */
};
// @size node_desc 0x84

/* the content of a scratch register, for reuse (g_gpr_contents 0045ff00 = r0..r3, g_fpr_contents 0045fe70 =
   fr0..fr3; exactly 4 each: 0042fcb0 / 0042fdb0 / 0042fa50 / 00430220 loop 0..3, 0045ff60 follows the general
   array). The chooser 0041fa30 reads them through 0041ffd0 to rank r0..r3 (empty 2, holding something 4,
   +1 if just chosen). */
struct reg_content {
    int value;                   /* +00 0 = empty; the IL_ID's symx (0042f830) or, with flags 0x40, the constant /
                                    address disp of an EAIMM operand (0042faf0) */
    union {
        short lreg;              /* +04 the IL_ID's |lreg| (0042f830; matched by 0042fe80 / 004300d0) */
        struct label_ref *labels; /* +04 with flags 0x40: copy of the constant's label list (0042faf0 via
                                    0042b770; freed by 0042fcb0 with 004182c0) */
    } u;
    unsigned char type;          /* +08 the variable's type byte (0042f830); array kind (0x80) is not invalidated
                                    by 0042fdb0 */
    unsigned char flags;         /* +09 0x40 holds a constant/address (0042faf0) rather than a variable; 0x20 r0 holds
                                    g_r0_variable (0042f830); 0x80 already counted for this statement (00422180,
                                    0041c200; 0041abe0 clears it per statement) */
    unsigned char unknown_0a[2]; /* +0a */
    unsigned int stamp;          /* +0c g_stmt_serial (0045fedc) when loaded; the chooser and 0042fa50 prefer the
                                    oldest */
    struct reg_range *ranges;    /* +10 serial ranges over which the content is valid (0041bae0 / 0041bc70 /
                                    0041bda0; only when request +4 != 0 and 0045f940 == 0) */
    struct reg_range *ranges_tail; /* +14 last range */
};
// @size reg_content 0x18

/* a validity range of a reg_content (0041bc70 / 0041bae0 allocate 0xc) */
struct reg_range {
    struct reg_range *next;      /* +00 */
    unsigned int start;          /* +04 first statement serial */
    unsigned int end;            /* +08 last serial, 0 = open */
};
// @size reg_range 0xc

/* a saved copy of the four reg_content heads (00430220 pushes, 00430320 restores; FUN_00406830(0x44)) on
   g_gpr_contents_stack (0045fef0) / g_fpr_contents_stack (0045f998) */
struct reg_contents_save {
    struct reg_contents_save *next; /* +00 */
    unsigned int words[4][4];    /* +04 +00..+0f of each of the 4 reg_content records (0042b220(dst, src, 4)) */
};
// @size reg_contents_save 0x44

/* one entry of a template's code sequence (tmpl_header +38; 12 bytes, ends with op 0xff00): walked by 00412390
   emit_template_record_sequence_for_node, 00426fb0, 00425f60, 00432030 */
struct tmpl_entry {
    unsigned short op;           /* +00 < 0x100: a psd_op (0x18 LABEL, 0x23 CALL, 0x24..0x26 JUMP/JUMPT/JUMPF,
                                    0x2a MOVI, 0x40 MOV, 0x60 ADD, 0x63 SUB, ...: 00426dd0 reads 004586c0 /
                                    004588a8 per psd op); else a template macro (op >> 8) 1..0x44 (00426dd0 reads
                                    004589a8[(op >> 8) - 1]; 00412390 dispatches 0x100, 0x200..0x800, 0xc00,
                                    0xd00, 0xe00, 0xf00, 0x1600, 0x1700, 0x1b00, 0x1c00, 0x2300, 0x2700, 0x2800,
                                    0x2b00, 0x2f00..0x3700, 0x4200..0x4400); 0x3800 / 0x3900 are skipped by
                                    00425f60's slot count; 0xff00 ends the list */
    unsigned short flags;        /* +02 0x01 conditional on operand types (00412390: ops 0x300, 0x1600, 0x1700,
                                    0x4200); 0x02 swap the operands when the first is r0 based; 0x08 after the op
                                    00420d10(1, operand disp); 0x10 only for unsigned / pointer / array values;
                                    0x20 only when desc bit_width != 32; 0x40 only when usage 2, 0x80 only when
                                    usage 3, both = 2 or 3 */
    unsigned short opnd[3];      /* +04 +06 +08 operand codes: indexes into g_operand_desc_table (00449968);
                                    0xfa = none (all templates' padding); for op 0x23 CALL, opnd[0] 0xfe..0x105
                                    selects a computed runtime routine (00412390) */
    unsigned short unknown_0a;   /* +0a 0 in all 2481 entries of the 597 templates */
};
// @size tmpl_entry 0xc

/* a code template [the a* families: acast001.., aassgn.., apush025]; 0x48 bytes, the entries usually just before it.
   g_template_names (0045a378) lists 597 {tmpl_header *, char *name} pairs ending with a null pointer (no code
   reads that table). Read through desc +80 and as param_2 of 00424c80 / 00425f60 / 00426fb0 */
struct tmpl_header {
    unsigned char flags;         /* +00 0x02 make labels for its LABEL entries (00424c80 -> 00432030); 0x04 sets
                                    desc flags2 0x20 (00424c80); 0x08 second-pass slot swap (00425f60); 0x01
                                    (00414400 with flags3 bit 1 clear: marks the value register in 0045fa02) */
    unsigned char result;        /* +01 where the result is (00424c80 switch: 0, 1..: which reg_spec / slot; 00425f60
                                    3, 4, 8, 10 take the target register) */
    unsigned char flags2;        /* +02 0x02 / 0x04 SH-4 PR mode wanted (00424c80 with g_fpscr_pr); 0x06 counted
                                    slot use (00425f60); 0x08 (00424c80); 0x80 sets desc flags3 0x01 (00424c80) */
    unsigned char unknown_03;    /* +03 0 in all templates */
    unsigned int reg_spec[5];    /* +04 per slot of the node's register array (00425f60, 0 ends): bits 0..3
                                    registers r0..r3 not to use, 0x10/0x20/0x40/0x80 avoid the registers of operand
                                    4/3/2/1, 0x100/0x200 of the extra operands, 0x2000 take a fixed register via
                                    00425c60, 0x4000..0x20000 avoid slots 0..3, 0x40000 enables those, 0x380000 kind
                                    (0x80000 fixed register = low 4 bits, 0x100000 the register of operand
                                    n = low 4 bits, 0x180000 no r0 preference), 0x1000000 a floating register,
                                    0x2000000 a floating pair */
    unsigned int reg_spec2[4];   /* +18 second-phase slots (00426fb0 for slot kinds 0x20 / 0x40) */
    char spec2_entry[4];         /* +28 entry index paired with each reg_spec2 (00426fb0); 0xff none */
    unsigned short pref_left;    /* +2c general preference for the first operand (00431950 -> its desc +12;
                                    00422180 chooser preference) */
    unsigned short pref_right;   /* +2e same for the second operand */
    unsigned char push_mode;     /* +30 operands passed on the stack (00431950: 1 both, 2 left 8-byte + right,
                                    3 left, 4 left 8-byte, 5 right); 00414400 */
    unsigned char clobbers;      /* +31 general registers the template destroys (00424c80 ORs into desc +18 and
                                    0045ff60; 00422180 / 0040ff00 remove them from the operand's busy_regs) */
    unsigned char opnd_spec_left; /* +32 00424c80 -> 004258c0 */
    unsigned char opnd_spec_right; /* +33 00424c80 -> 004258c0 */
    unsigned char excluded;      /* +34 general registers the address register must avoid (00422180) */
    unsigned char spill_mask;    /* +35 mask passed to 0041e740 (00422180) */
    unsigned char unknown_36[2]; /* +36 0 in all templates */
    struct tmpl_entry *entries;  /* +38 the code sequence */
    unsigned short fpref_left;   /* +3c floating preference for the first operand (00431950 -> desc +20) */
    unsigned short fpref_right;  /* +3e same for the second */
    unsigned char unknown_40[2]; /* +40 */
    unsigned char fclobbers;     /* +42 floating registers destroyed (00424c80 -> desc +26, 0045f9ac) */
    unsigned char unknown_43[5]; /* +43 one template has 0x77 0x62 at +44 */
};
// @size tmpl_header 0x48

/* one choice of a tmpl_select */
struct tmpl_choice {
    unsigned char index;         /* +00 index into targets (0xff = none: error 0x1228) */
    unsigned char how;           /* +01 1 a tmpl_header; 3 a nested selector (004293c0); else a tmpl_matrix */
};
// @size tmpl_choice 0x2

/* a late-handler selection record (g_late_handler_table entries of kind 1/2, 00423410): picks a tmpl_header by
   the operand type classes (004236b0: 0 char/short, 1 int/long, 2 pointer/array/function, 3 float, 4 double).
   Variable length: 5 choice pairs for a unary node, 25 (left * 5 + right) for a binary one */
struct tmpl_select {
    void **targets;              /* +00 array the choices index */
    struct tmpl_choice choice[25];                /* +04 [left * 5 + right] for a binary node; a unary node's record has only the
                                    first 5 (indexed by its operand's class) */
};
// @size tmpl_select 0x38

/* a matrix of templates indexed by the operands' opnd_class (00423410) */
struct tmpl_matrix {
    struct tmpl_header **cells;  /* +00 */
    int row_stride;              /* +04 bytes per left-operand row */
    int param_08;                /* +08 passed to 00423800 */
    signed char left[4][2];      /* +0c by left operand class 0..3 (3 = default): column, 00423800 arg when -1 */
    signed char right[4][2];     /* +14 by right operand class */
};
// @size tmpl_matrix 0x1c

/* an entry of g_symbol_table (0045f9b0: (request +0xb0) + 0xb7 entries of 0x30, allocated and zeroed by 00401000,
   which reads the .sym file; index = symbol number + 0xb6, the first 0xb6 for runtime routines). Filled from the
   .sym file in shcmdl write_symbol_file's order; same content as shcmdl's 0x3c-byte symbol, re-packed. */
struct sym_entry {
    unsigned char flags;         /* +00 0x80 present in .sym (00401000); 0x20 a parameter / scope member with a
                                    flag byte (00401500 / 004019a0); 0x10 built-in function (00401000 when
                                    00401c00 finds the name); 0x08 referenced by another symbol's extension
                                    (00401780) */
    char sclass;                 /* +01 storage class (= shcmdl symbol.sclass: 1..4 static/extern, 5/6 local,
                                    7/8 parameter, 9, 10 block scope, 11 label); 0041b070 tests 5 and 9 */
    unsigned char type;          /* +02 type byte (0041b070 copies it into IL_ID nodes) */
    unsigned char byte_03;       /* +03 shcmdl symbol +06 */
    unsigned char sym_flags;     /* +04 shcmdl symbol.flags +07 (0x10 extension follows: 00401780); tested 0x40,
                                    0x04, 0x10 in 004053a0 / 0040a3f0 / 0040ad10 / 00408180 */
    unsigned char attr;          /* +05 shcmdl symbol.attr +2e; 00409610 bits 1 / 2 pick the frame offset, 00422180
                                    / 0041c200 test & 3, 0040d9e0 & 0x18 */
    short short_06;              /* +06 shcmdl symbol +16 (00408970 reads it) */
    char *name;                  /* +08 (00401b20; 0041b070 compares "__builtin_") */
    int size;                    /* +0c aggregate size; for class 1/3 functions the parameter list (struct
                                    param_block *, 00401500); other functions: built-in id (00401c00); class 10: the
                                    nested blocks (struct scope_children *, 00401870) */
    void *list_10;               /* +10 class 1/3 functions: the scope list (struct scope_pair_block *, 00401670);
                                    class 10: the locals (struct scope_locals *, 004019a0); class 9: an int
                                    (00401000) */
    struct sym_extension *ext;   /* +14 extension record (00401780) when sym_flags 0x10 */
    unsigned char ret_type;      /* +18 functions: return type byte (00401470; 0042a5b0) */
    unsigned char ret_19;        /* +19 functions: one byte (00401470) */
    unsigned char unknown_1a[2]; /* +1a */
    short func_index;            /* +1c functions: index into g_aux_records (0045f9bc, 0x44 each = shcpep
                                    aux_record; 00401470 numbers them, 00408180 writes them) */
    char reg;                    /* +1e register the optimizer gave the variable, -1 none (00401000; = shcmdl
                                    symbol +38) */
    unsigned char unknown_1f;    /* +1f */
    struct ea storage;           /* +20 where the symbol lives: EAREGD reg, or EAABS with a label_ref of the
                                    symbol (00401000); 0041b070 / 0042cb60 read +20 / +21 / +23 */
    int frame_offset;            /* +2c frame offset (00409610; 00410890 / 00414900 / 00415030 add disp) */
};
// @size sym_entry 0x30

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

struct alloc_class_table {
    short count;                 /* +00 classes used */
    unsigned char unknown_02[2]; /* +02 */
    struct alloc_class_table *next; /* +04 */
    struct alloc_size_class cls[32]; /* +08 */
};
// @size alloc_class_table 0x108

/* the per-function aux record (g_aux_records, 0x44 each, indexed by sym_entry +1c; g_current_aux 0045f950 points
   at the current one). Same layout as shcpep's aux_record (names kept from shcpep ghidra/names/shcpep types):
   shcgen fills it and writes it to the .asa (write_asa_global_symbol_record 00408180, tag 0xc), shcpep reads it
   back field for field (load_symbol_aux_record_stream case 0xc). Would type g_current_aux and g_aux_records. */
struct aux_record {
    int frame_size;              /* +00 end_function_code 0040ad10: g_max_temp_frame + g_local_frame_size;
                                    written 1st by 00408180 */
    unsigned short saved_regs;   /* +04 general registers saved (0040ad10 from g_used_gpr_mask) */
    unsigned short saved_regs2;  /* +06 float registers saved (0040ad10 from g_used_fpr_mask) */
    unsigned char saved_sys;     /* +08 system registers saved (0040ad10 from g_saved_sys_mask) */
    unsigned char unknown_09;    /* +09 */
    unsigned short flags;        /* +0a 0x8000 (begin_function_code 0040a3f0 for sym_flags 0x04, 0040ad10 when
                                    g_function_no_saves; 00408180 writes it as a 0/1 byte); +0b bit 0x40 (0040a3f0 for
                                    sym_flags 0x10); 0040ad10 stores 0xff into the low byte +0a first */
    int max_stack;               /* +0c 0040ad10: g_max_push_depth + g_max_temp_frame + g_local_frame_size */
    int stack_value;             /* +10 */
    unsigned short range_count;  /* +14 remap ranges (remap_register_variables_to_scratch_registers 0040b0d0
                                    increments it as a short; 00408180 writes its low byte) */
    unsigned char unknown_byte;  /* +16 */
    unsigned char saved_mac;     /* +17 0040ad10 from g_saved_mac_mask */
    struct aux_reg_range *ranges; /* +18 0040b0d0 appends 0x10-byte {next, before reg, after reg, start, end} */
    int unknown_1c;              /* +1c */
    int asb_word;                /* +20 0040ad10: g_stmt_serial at the end of the function */
    int sp_adjust;               /* +24 written by 00408180 */
    char reg28;                  /* +28 0040b0d0: register variable moved to r0 when its lreg entry has flag 0x40 */
    unsigned char unknown_29[3]; /* +29 */
    unsigned char asb_bytes[0x17]; /* +2c runtime routines used by the function, one bit per routine label
                                    (0040ad10 ORs them into g_used_routine_bits) */
    unsigned char unknown_43;    /* +43 */
};
// @size aux_record 0x44

/* a register remap range of an aux_record (FUN_00406830(0x10) in 0040b0d0); = shcpep aux_reg_range */
struct aux_reg_range {
    struct aux_reg_range *next;  /* +00 0 for the new record, appended at the tail */
    char before_reg;             /* +04 the variable's register */
    char after_reg;              /* +05 r0..r3, or 0x10 + n for fr0..fr3 */
    unsigned char unknown_06[2]; /* +06 */
    unsigned int start_expno;    /* +08 first statement serial of the live range */
    unsigned int end_expno;      /* +0c last serial */
};
// @size aux_reg_range 0x10

/* the per-function lreg table (g_lreg_table, 0x24-byte entries read from the .reg file by 004164f0; ends with
   lreg 0) */
struct lreg_entry {
    short lreg;                  /* +00 the lreg number (004164f0 reads 2 bytes; 0 ends the table; 0041ade0 /
                                    0041ae20 / 0041b070 / 0042f830 compare it with |node lreg|) */
    short reg;                   /* +02 register given by the optimizer (004164f0); find_lreg_register 0041ade0
                                    returns it; >= 0 a register (00417aa0 makes an EAREGD ea, 004160f0 adds it to the
                                    used masks); < 0 a frame slot id shared by the entries with the same value
                                    (00417aa0); 0040b0d0 renames it to the scratch register it moves to */
    unsigned char type;          /* +04 type byte (004164f0; 0041b070 copies it into IL_ID nodes; 00417aa0: doubles
                                    get 8 bytes and SH-4 register pairs) */
    unsigned char flags;         /* +05 0x40 holds a register parameter (00416480; 0040b0d0 copies the register to
                                    aux +0x28 when it moves to r0); 0x80 r0 was only ever kept for it (0041ae20 sets,
                                    clears when g_r0_used; 0040b4f0 / 0040b0d0 clear it) */
    unsigned short count;        /* +06 number of symbol numbers at +08 (004164f0) */
    short *symbols;              /* +08 symbol numbers (- 0xb6) the lreg stands for (004164f0; 00416480) */
    int live_length;             /* +0c sum of end - start + 1 over ranges (0040b4f0; its sort key) */
    struct reg_range *ranges;    /* +10 live ranges, start-sorted (read_reg_file_range_list 00416890; merged by
                                    0040b7c0; 0040b0d0 compares them with the scratch registers' free ranges) */
    struct serial_block *r0_serials; /* +14 statements where r0 was kept for it (0041ae20 appends; 0040b8e0 merges;
                                    0041ba90 marks r0 busy at each; 004164f0 frees) */
    struct ea storage;           /* +18 where the lreg lives (00417aa0: EAREGD reg, or @(disp, frame 0x6c);
                                    0042b7e0 copies another entry's) */
};
// @size lreg_entry 0x24

/* a block of statement serials (lreg_entry.r0_serials: 0041ae20 / 0040b8e0 allocate 0x14; 0041ba90 walks it) */
struct serial_block {
    struct serial_block *next;   /* +00 */
    unsigned int serial[4];      /* +04 g_stmt_serial values, sorted; 0 = unused, ends the list */
};
// @size serial_block 0x14

/* a block of a function symbol's parameter list (sym_entry.size of a class 1/3 function): read_function_params
   00401500 reads ((n + 3) >> 2) blocks of 4 parameters from the .sym, linked through +00 */
struct param_block {
    struct param_block *next;    /* +00 (00401500 links the blocks; 004169b0 / 00416410 / 0040a580 walk them) */
    unsigned char sym_flag[4];   /* +04 one .sym byte per parameter (00401500: nonzero sets sym_entry flags 0x20);
                                    00417000 gives a home only when it is 0 */
    short symno[4];              /* +08 symbol index (+0xb6 already added by 00401500), -1 ends */
    unsigned char state[4];      /* +10 0x01 arrived in a register (004169b0, tested by 00416410 / 00417000); 0x02
                                    must be moved to its home (0040a580); 0x04 the home is a register (00417000) */
    int home[4];                 /* +14 home of the parameter: frame offset (00417000) or, low byte, the register */
};
// @size param_block 0x24

/* a block of a function symbol's scope list (sym_entry.list_10 of a class 1/3 function: 00401670 reads
   ((n + 1) / 2) blocks) */
struct scope_pair_block {
    struct scope_pair_block *next; /* +00 */
    short symno[2];              /* +04 block-scope symbol index (+0xb6), -1 ends */
};
// @size scope_pair_block 0x8

/* the nested blocks of a block-scope symbol (sym_entry.size of class 10: 00401870 reads ((n + 5) / 6) blocks;
   assign_block_local_storage 004176b0 recurses into each) */
struct scope_children {
    struct scope_children *next; /* +00 */
    short symno[6];              /* +04 nested block symbols (+0xb6), -1 ends */
};
// @size scope_children 0x10

/* the locals of a block-scope symbol (sym_entry.list_10 of class 10: 004019a0 reads ((n + 3) / 4) blocks) */
struct scope_locals {
    struct scope_locals *next;   /* +00 */
    unsigned char sym_flag[4];   /* +04 one .sym byte per local (nonzero sets sym_entry flags 0x20); 004176b0 gives
                                    a register only when it is 0 */
    short symno[4];              /* +08 symbol index (+0xb6), -1 ends */
};
// @size scope_locals 0x10

/* sym_entry +14: the extension record read_symbol_extension 00401780 reads when sym_flags & 0x10 (malloc 0xc,
   zeroed). = shcmdl symbol +0x2d / +0x30 / +0x34 (read_symbol_extension 0040aed0) */
struct sym_extension {
    unsigned char flags;         /* +00 2: value present (4 = it is a symbol number); 1: value2 present */
    unsigned char unknown_01[3]; /* +01 */
    int value;                   /* +04 4 bytes, or with flags 4 a short symbol number + 0xb6 (that symbol's flags |= 0x08) */
    int value2;                  /* +08 */
};
// @size sym_extension 0xc

/* a use count of a variable as a base/index of an indexed address (@(R0,Rn) candidate), 8 bytes: g_deref_counts
   0045fa50 up to g_deref_count_cursor 0045fa18; g_r0_variable 0045f9a8 points at the one with the highest count.
   No allocation (fixed array); the 8-byte step is find_deref_count 0041bfb0 (short pointer + 4) and count_deref_use
   0041c000 (cursor + 4 shorts). find_deref_count would return deref_count *; g_r0_variable / g_deref_count_cursor
   would be deref_count * */
struct deref_count {
    short symx;                  /* +00 the IL_ID's symx (0041c000 writes; 0041bfb0, 00417c50 compare) */
    short lreg;                  /* +02 |lreg| of the IL_ID (0041c000 writes the absolute value; 0041bfb0 compares;
                                    generate_statement 0041abe0 looks it up in g_lreg_table via 0041ade0) */
    unsigned char count;         /* +04 uses (0041c000: 1 on creation, ++; 0041abe0 compares with g_deref_total) */
    unsigned char unknown_05[3]; /* +05 never accessed */
};
// @size deref_count 0x8

/* one case of the switch being generated: g_switch_cases 0045fee0, allocated by read_switch_case_table 00420600
   with 0043a550(count << 3) */
struct switch_case {
    int value;                   /* +00 case value (00420600 reads 4 bytes from .swi; 004208f0 compares, 00420b40
                                    fills the table gaps) */
    short label;                 /* +04 label number (.swi value + request +0xb0 + 0xb6; JUMPT target in 004208f0,
                                    CENT entry in 00420b40) */
    unsigned char unknown_06[2]; /* +06 */
};
// @size switch_case 0x8

/* one entry of g_builtin_info (00449e48, 0x32 entries indexed by enum builtin_fn = desc +06 of an IL_CALL and,
   after 0040ff00 copies it, of its IL_ARG node). Size 8: 0040faa0 / 0040ff00 index it as (&DAT_00449e48)[id * 8],
   00410890 reads the pointer as *(DAT_00449e4c + id * 8). Values read from shcgen_r26.exe: e.g. GBR_READ_BYTE 7
   flags 0xa1, GBR_WRITE_BYTE 0xa flags 0xe2, TRAPA_SVC 0x1c flags 0xa7, ASM 0x1d templates 0 */
struct builtin_info {
    unsigned char flags;         /* +00 0x07 which argument must be an immediate (7 = the last one) and 0x80 check it,
                                    0x20 range 0..0xff, 0x10 0..0x1fe even, neither 0..0x3fc multiple of 4 (0040faa0);
                                    0x40 select the template again after the arguments are generated (0040ff00 ->
                                    00410890(0, args)) */
    unsigned char unknown_01[3]; /* +01 */
    struct tmpl_header **templates; /* +04 candidate templates (the ainlin* family): 00410890 returns [0], [1] or [2] */
};
// @size builtin_info 0x8

/* a saved FPSCR.PR state (g_fpscr_pr_stack 0045f984): 004220a0 allocates it with 00406830(8) and fills +0 / +4,
   004220d0 reads +4, 004220e0 frees it with 00406a70(rec, 8) */
struct fpscr_pr_save {
    struct fpscr_pr_save *next;  /* +00 the previous head (004220a0 stores g_fpscr_pr_stack; 004220e0 restores it) */
    char pr;                     /* +04 g_fpscr_pr (0045f9f8) when pushed (004220a0 writes, 004220d0 reads, byte) */
    unsigned char unknown_05[3]; /* +05 never accessed */
};
// @size fpscr_pr_save 0x8

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
   the strings and lists that follow in the file. The names are shcpep's (its tables, ghidra/names/shcpep); the
   paths are named by the request file's own string order (.msg .ila .ilb .sym .swi .int .db1 .db2 .reg .sua .sub
   .sud .ofa .ofb .asa .asb .asl .lit). Fields neither stage is known to use are unknown_ */
struct request {
    char *source_name;                   /* +000 the source file, for messages */
    unsigned char unknown_004[0x14];     /* +004 */
    short cpu;                           /* +018 nonzero: JUMPT/JUMPF take part in the branch passes */
    short pic;                           /* +01a nonzero: call/jump target literals become label differences */
    unsigned char unknown_01c[4];        /* +01c */
    short switch_density_rule;           /* +020 the switch table rule of generate_switch_statement 00420220: nonzero
                                            count >= 10 and range < 3 * count, zero count >= 8 and range <=
                                            (11 * count - 81) / 4 */
    unsigned char unknown_022[2];        /* +022 */
    struct request_section *sections;    /* +024 */
    unsigned char unknown_028[3];        /* +028 */
    char div_routine_variant;            /* +02b 0 _divls/_modls, 1 _divlsp/_modlsp, 2 _divlspnm/_modlspnm
                                            (select_arithmetic_routine 0041d1a0) */
    unsigned char unknown_02c[0xa];      /* +02c */
    char macsave;                        /* +036 0: calls clobber MACH/MACL */
    unsigned char fpu_mode;              /* +037 FPU flags: 3 with cpu 2 (or cpu 4) = an FPU is present (0041aed0,
                                            0041b070, 0041e280, 0041abe0); bits 1 / 2 steer the float/double
                                            packing and rounding (unpack_float .. round_double_mantissa, as
                                            shcmdl's fpu_mode) */
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
    char *ila_path;                      /* +064 .ila (the paths follow the request file's string order) */
    char *ilb_path;                      /* +068 .ilb input, the IL tree */
    char *sym_path;                      /* +06c .sym input */
    char *swi_path;                      /* +070 .swi input */
    char *int_path;                      /* +074 .int input */
    char *db1_path;                      /* +078 .db1 */
    char *db2_path;                      /* +07c .db2 */
    char *reg_path;                      /* +080 .reg */
    char *sua_path;                      /* +084 .sua output */
    char *sub_path;                      /* +088 .sub */
    char *sud_path;                      /* +08c .sud */
    char *ofa_path;                      /* +090 .ofa output */
    char *ofb_path;                      /* +094 .ofb */
    char *asa_path;                      /* +098 .asa output */
    char *asb_path;                      /* +09c .asb */
    char *asl_path;                      /* +0a0 .asl */
    char *lit_path;                      /* +0a4 .lit */
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
    short id;                            /* +00 section number (004201e0 finds a section by it) */
    short name_len;                      /* +02 */
    char *name;                          /* +04 */
    int location;                        /* +08 code location counter (0042ab90 passes it to write_ofa_record) */
    unsigned int const_loc;              /* +0c location counter of initialised const data (00408ce0, 00409610,
                                            0040a370, 00408040 kind 7) */
    unsigned int data_loc;               /* +10 initialised data and every GBR-relative symbol (attr & 3): 00408ce0,
                                            00409610, 0040a370, 00415460 */
    unsigned int bss_loc;                /* +14 uninitialised data (00415460, 00408040 kind 9) */
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
