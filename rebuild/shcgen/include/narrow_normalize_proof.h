/* Owned narrow-value representation normalization. No target-specific keys. */
#ifndef NARROW_NORMALIZE_PROOF_H
#define NARROW_NORMALIZE_PROOF_H

static int nn_plain_gp(const ea *e)
{
    return e && e->type == 1 && e->base > 0 && e->base < 15 &&
           e->index == -1 && e->misc == 0 && e->disp == 0 && e->labels == 0;
}

static int nn_unary_extension(const tmpl_header *t)
{
    unsigned int i;
    const tmpl_entry *e;
    if (!t || t->flags || t->flags2 || t->result != 3 ||
        t->reg_spec[0] != 0x180000 || t->clobbers || t->fclobbers ||
        t->excluded || t->spill_mask || t->push_mode ||
        t->opnd_spec_left || t->opnd_spec_right ||
        t->pref_left || t->pref_right || t->fpref_left || t->fpref_right)
        return 0;
    for (i = 1; i < 5; ++i) if (t->reg_spec[i]) return 0;
    for (i = 0; i < 4; ++i) if (t->reg_spec2[i]) return 0;
    e = t->entries;
    return e && e[0].op == 0x300 && e[0].flags == 0 &&
        e[0].opnd[0] == 0xa9 && e[0].opnd[1] == 0x5e &&
        e[0].opnd[2] == 0xfa && e[1].op == 0xff00;
}

/* Every integer relational matrix cell is materialization(s), compare, END.
   Class 0 and class 1 map to the same rows/columns in this selector family. */
static int nn_readonly_relational(const gen_node *p)
{
    const tmpl_header *t;
    const tmpl_entry *e;
    int i, compares = 0;
    if (!p || !p->desc || p->op < IL_LT || p->op > IL_GE ||
        p->desc->usage != 1 || (p->type & ~4) != 0x10 ||
        !p->child || !p->child->next || p->child->next->next ||
        (p->child->type & ~5) != 0x10 ||
        (p->child->next->type & ~5) != 0x10 ||
        p->desc->dest.type || p->desc->mem_ea ||
        p->desc->target_regs || p->desc->ftarget_regs)
        return 0;
    t = p->desc->tmpl;
    if (!t || t->result || (t->flags & ~4) || t->flags2 || t->clobbers ||
        t->fclobbers || t->push_mode || !t->entries) return 0;
    for (i = 0; i < 4; ++i) {
        e = t->entries + i;
        if (e->op == 0xff00) return compares == 1;
        if (e->flags) return 0;
        if (e->op == 0xc00 && !compares) {
            /* An operand copy into a template slot, never into an input. */
            if ((e->opnd[0] != 0xa9 && e->opnd[0] != 0xaa) ||
                e->opnd[1] < 0x5e || e->opnd[1] > 0x62 ||
                e->opnd[2] < 0x63 || e->opnd[2] > 0x67) return 0;
        } else if ((e->op == 0x600 || e->op == 0x700 || e->op == 0x800) && !compares) {
            compares = 1;
        } else return 0;
    }
    return 0;
}

/* Return a borrowed, read-only home EA. Caller copies it only after all children
   have been evaluated and before applying this cast's existing template. */
static const ea *nn_owned_home(gen_node *n, sym_entry *syms, unsigned int count,
                             lreg_entry *rows, unsigned int reserved,
                             const sym_entry *fn)
{
    int nn_trace = getenv("GEN_NARROW_NORMALIZE_TRACE") && n && n->op == IL_CAST && n->child && (n->child->op == IL_A_ADD || n->child->op == IL_A_SUB);
    gen_node *c, *l;
    node_desc *d, *cd, *ld;
    lreg_entry *r, *owner = 0;
    sym_entry *s;
    unsigned int i, si, home;
    if (!n || n->op != IL_CAST || (n->type & ~4) != 0x10 ||
        !n->desc || !n->child || n->child->next || !syms || !rows ||
        !fn || fn->attr || (fn->sym_flags & ~4) || fn->ext) { if(nn_trace) fprintf(stderr,"NN_REJECT source=%u guard=%u\n",n->line,__LINE__); return 0; }
    c = n->child; l = c->child; d = n->desc; cd = c->desc;
    if ((c->op != IL_A_ADD && c->op != IL_A_SUB) ||
        (c->type != 0 && c->type != 4 && c->type != 8 && c->type != 12) ||
        !l || !l->next || l->next->next || l->op != IL_ID ||
        l->type != c->type || l->symx < 0 || l->lreg <= 0 ||
        !cd || !l->desc || !nn_readonly_relational(n->parent) ||
        !nn_unary_extension(d->tmpl)) { if(nn_trace) fprintf(stderr,"NN_REJECT source=%u guard=%u\n",n->line,__LINE__); return 0; }
    ld = l->desc;
    if (d->dest.type || d->mem_ea || d->target_regs || d->ftarget_regs ||
        d->pref_regs || d->fpref_regs || (d->flags2 & 8) ||
        cd->mem_ea || ld->mem_ea || (cd->flags2 & 8) ||
        (ld->flags2 & (8|0x40)) || cd->opnd_class != 1 || ld->opnd_class != 1 ||
        !nn_plain_gp(&cd->value) || !nn_plain_gp(&ld->value) ||
        cd->value.base != ld->value.base) { if(nn_trace) fprintf(stderr,"NN_REJECT source=%u guard=%u\n",n->line,__LINE__); return 0; }
    home = (unsigned char)ld->value.base;
    if (reserved & (1u << home)) { if(nn_trace) fprintf(stderr,"NN_REJECT source=%u guard=%u\n",n->line,__LINE__); return 0; }
    si = (unsigned int)l->symx + 0xb6;
    if (si >= count) { if(nn_trace) fprintf(stderr,"NN_REJECT source=%u guard=%u\n",n->line,__LINE__); return 0; }
    s = syms + si;
    if (s->flags != 0x80 || s->sclass != 5 || s->type != c->type ||
        s->byte_03 || s->sym_flags || s->attr || s->ext || s->reg != -1)
        { if(nn_trace) fprintf(stderr,"NN_REJECT source=%u guard=%u\n",n->line,__LINE__); return 0; }
    for (r = rows; r->lreg; ++r) {
        if (r->lreg == l->lreg) {
            if (owner) { if(nn_trace) fprintf(stderr,"NN_REJECT source=%u guard=%u\n",n->line,__LINE__); return 0; }
            owner = r;
        } else if ((r->storage.type & 31) == 1 && r->storage.base == home) { if(nn_trace) fprintf(stderr,"NN_REJECT source=%u guard=%u\n",n->line,__LINE__); return 0; }
    }
    if (!owner || owner->flags || owner->count != 1 || !owner->symbols ||
        owner->symbols[0] != l->symx || owner->type != c->type ||
        owner->reg != home || !nn_plain_gp(&owner->storage) ||
        owner->storage.base != home) { if(nn_trace) fprintf(stderr,"NN_REJECT source=%u guard=%u\n",n->line,__LINE__); return 0; }
    /* Declared fixed/global bindings need not appear in the lreg table. */
    for (i = 0; i < count; ++i) {
        s = syms + i;
        if (!(s->flags & 0x80)) continue;
        if (((s->storage.type & 31) == 1 && s->storage.base == home) || s->reg == home)
            { if(nn_trace) fprintf(stderr,"NN_REJECT source=%u guard=%u\n",n->line,__LINE__); return 0; }
    }
    return &ld->value;
}
#endif
