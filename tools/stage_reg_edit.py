#!/usr/bin/env python3
"""Plan scalar SUB register edits from a native/arcade register-only delta.

Planning never invokes a compiler and never claims a match. The emitted patch
requires a native suffix replay and full-extent byte/relocation oracle check.
Unsupported encodings, ambiguous occurrences and non-register differences fail
closed. No target names, candidate register numbers or accepted patches occur
in the planner. ASA binds FLABEL identities; complete native modules are required.
"""
from __future__ import annotations

import argparse
import collections
import csv
import hashlib
import importlib.util
from pathlib import Path
import pprint
import re
import struct
import sys


class Ineligible(ValueError):
    pass


def require(test, reason):
    if not test:
        raise Ineligible(reason)


def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def load_module(name, path):
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


def write_tsv(path, rows, fields):
    with Path(path).open('w', newline='', encoding='utf8') as stream:
        writer = csv.DictWriter(stream, fieldnames=fields, delimiter='\t')
        writer.writeheader()
        writer.writerows(rows)


def reg_mask(word):
    """Only actual SH-2 general-register fields, never displacement bits."""
    top, low = word >> 12, word & 15
    if top == 0:
        if low in (4, 5, 6, 7, 12, 13, 14, 15):
            return 0x0ff0
        if word & 0xf0ff in (0x0002, 0x0012, 0x0022, 0x000a, 0x001a, 0x002a, 0x0029):
            return 0x0f00
        return 0
    if top in (1, 2, 3, 5, 6):
        return 0x0ff0
    if top == 4:
        return 0x0ff0 if low == 15 else 0x0f00
    if top in (7, 9, 13, 14):
        return 0x0f00
    if word & 0xff00 in (0x8000, 0x8100, 0x8400, 0x8500):
        return 0x00f0
    return 0


def call_scan_barrier(word, temporary):
    """Conservative callee-address lifetime guard, including implicit R0 writes.

    Any mention of the temporary is rejected, even a read. This also covers
    post-increment sources/MAC operands that write an m field, not just n.
    """
    if word in (0x000b,0x002b,0x001b) or word&0xff00==0xc300:
        return True
    if word&0xf0ff in (0x400b,0x402b,0x0003,0x0023):
        return True
    if temporary==0 and word&0xff00 in (0xc700,0x8400,0x8500,0xc400,0xc500,0xc600):
        return True
    mask=reg_mask(word)
    return bool((mask&0x0f00 and (word>>8)&15==temporary) or
                (mask&0x00f0 and (word>>4)&15==temporary))


def align_register_schedule(words, arcade_words):
    """Unique, bounded pure-register permutation; no load/branch displacement moves.

    This only derives a candidate operand mapping. No record order is edited;
    the native suffix must independently reproduce the required schedule.
    """
    offsets=sorted(words);mapping={off:off for off in offsets};i=0
    key=lambda word:word & ~reg_mask(word)
    pure={0x6003,0x600c,0x600d,0x600e,0x600f,0x300c,0x3008,
          0x2009,0x200a,0x200b,0x4000,0x4001,0x4008,0x4009,
          0x4018,0x4019,0x4028,0x4029,0x4020,0x4021}
    while i<len(offsets):
        off=offsets[i]
        if key(words[off])==key(arcade_words[off]):i+=1;continue
        found=False
        for end in range(i+2,min(i+8,len(offsets))+1):
            window=offsets[i:end]
            if window!=list(range(window[0],window[-1]+2,2)):break
            left=[key(words[x]) for x in window];right=[key(arcade_words[x]) for x in window]
            if any(k not in pure for k in left+right):break
            if collections.Counter(left)!=collections.Counter(right):continue
            require(len(set(left))==len(left),'ambiguous repeated opcode in local schedule permutation')
            for at,k in zip(window,left):mapping[at]=window[right.index(k)]
            found=True;i=end;break
        require(found,f'opcode/structure mismatch at {off:#x}; no unique pure-register permutation')
    return mapping


def listing_instructions(path, raw, start, end):
    """Bind existing raw-ASM listing instruction cells to native P bytes.

    This does not pretend a partial listing has a TIL completion footer. Only
    explicit instruction rows with exact native words are accepted; the caller
    also requires the arcade control-flow/pool classification to agree.
    """
    result = {}
    section = None
    for line in Path(path).read_text(errors='replace').splitlines():
        m = re.match(r'^\s*(?:(\w+)\s+)?([0-9A-F]{8})\s+([0-9A-F]{4})(?:\s{2,})(\S+)\s*(.*)$', line)
        if not m:
            sm = re.match(r'^(\w+)\s+[0-9A-F]{8}\s+', line)
            if sm:
                section = sm[1]
            continue
        if m[1]:
            section = m[1]
        at, word, mnemonic = int(m[2], 16), int(m[3], 16), m[4]
        if section != 'P' or not start <= at < end or mnemonic.startswith('.'):
            continue
        require(at + 2 <= len(raw), 'listing instruction outside P section')
        require(int.from_bytes(raw[at:at+2], 'big') == word, f'listing/native word mismatch at {at:#x}')
        require(at not in result, f'duplicate listing instruction {at:#x}')
        result[at-start] = word
    require(result, 'no bound target instruction rows')
    return result


def asa_names(codec, path):
    records = collections.defaultdict(dict)
    for atom in codec.parse(Path(path).read_bytes()):
        records[atom.record][atom.field] = atom.value
    names = {}
    for fields in records.values():
        if 'symbol' in fields and fields.get('name'):
            name = fields['name'].decode('latin1').lstrip('_')
            key = fields['symbol']
            require(key not in names or names[key] == name, f'ambiguous ASA symbol {key}')
            names[key] = name
    return names


def runtime_names(codec_dir):
    """Original ASM runtime-symbol table; constants are schema, not targets."""
    source = (codec_dir.parent/'rebuild/shcasm/src/_stockdata.c').read_text()
    decls = (codec_dir.parent/'rebuild/shcasm/include/decls.h').read_text()
    base = int(re.search(r'stock data image (0x[0-9a-fA-F]+)', source)[1], 16)
    body = re.search(r'unsigned char g_sd\[[^]]+\] = \{(.*?)\};', source, re.S)[1]
    data = bytes(int(x, 16) for x in re.findall(r'0x([0-9a-fA-F]{2})\b', body))
    offset = int(re.search(r'#define g_runtime_routine_names .*g_sd \+ (0x[0-9a-fA-F]+)', decls)[1], 16)
    def name(index):
        # IDs below182 are the fixed runtime namespace; ordinary symbols are ASA-bound.
        if not 0 <= index < 182:
            return None
        pointer = struct.unpack_from('<I', data, offset+4*index)[0]
        if not base <= pointer < base+len(data):
            return None
        raw = data[pointer-base:].split(b'\0', 1)[0]
        if not raw or len(raw)>100:
            return None
        text = raw.decode('ascii', errors='replace')
        return text.lstrip('_') if re.fullmatch(r'[_a-zA-Z][_a-zA-Z0-9]*', text) else None
    return name


def direct_encoding(record):
    """Return one exact instruction word and serialized-field/nibble bindings.

    Each binding is (field, native nibble shift, serialized nibble shift).
    Unsupported forms return None. Size/immediate/displacement remain exact.
    """
    d = {f.name:f.value for f in record.fields}
    size = d.get('flags_raw', 0) & 3
    k1, k2 = d.get('ea1.type_raw', 0) & 31, d.get('ea2.type_raw', 0) & 31
    a, b = d.get('ea1.base'), d.get('ea2.base')
    def link(field, shift, packed=0):
        return field, shift, packed
    def rr(code):
        return code | b << 8 | a << 4, [link('ea1.base',4),link('ea2.base',8)]
    if record.name == 'MOV' and size <= 2:
        if k1 == k2 == 1:
            return rr(0x6003)
        if k1 == 8 and k2 == 1:
            disp = d['ea1.displacement']
            if disp == 0:
                return (0x6000|size|b<<8|a<<4), [link('ea1.base',4),link('ea2.base',8)]
            if size == 2 and 0 <= disp <= 60 and disp % 4 == 0:
                return (0x5000|b<<8|a<<4|disp//4), [link('ea1.base',4),link('ea2.base',8)]
            if size < 2 and b == 0 and 0 <= disp <= 15*(1<<size) and disp % (1<<size)==0:
                return (0x8400|size<<8|a<<4|disp//(1<<size)), [link('ea1.base',4)]
        if k1 == 1 and k2 == 8:
            disp = d['ea2.displacement']
            if disp == 0:
                return (0x2000|size|b<<8|a<<4), [link('ea1.base',4),link('ea2.base',8)]
            if size == 2 and 0 <= disp <= 60 and disp % 4 == 0:
                return (0x1000|b<<8|a<<4|disp//4), [link('ea1.base',4),link('ea2.base',8)]
            if size < 2 and a == 0 and 0 <= disp <= 15*(1<<size) and disp % (1<<size)==0:
                return (0x8000|size<<8|b<<4|disp//(1<<size)), [link('ea2.base',4)]
        if k1 == 9 and k2 == 1:
            packed = d['ea1.base_index_packed']
            if packed & 15 == 0:
                return (0x000c|size|b<<8|(packed>>4)<<4), [link('ea1.base_index_packed',4,4),link('ea2.base',8)]
        if k1 == 1 and k2 == 9:
            packed = d['ea2.base_index_packed']
            if packed & 15 == 0:
                return (0x0004|size|(packed>>4)<<8|a<<4), [link('ea1.base',4),link('ea2.base_index_packed',8,4)]
    pairs = {'ADD':0x300c,'ADDC':0x300e,'SUB':0x3008,'SUBC':0x300a,
             'TST':0x2008,'AND':0x2009,'OR':0x200b,'XOR':0x200a,
             'CMP_EQ':0x3000,'CMP_GE':0x3003,'CMP_GT':0x3007,'CMP_HS':0x3002,'CMP_HI':0x3006}
    if record.name in pairs and k1 == k2 == 1:
        return rr(pairs[record.name])
    if record.name in ('EXTS','EXTU') and k1 == k2 == 1 and size < 2:
        return rr((0x600e if record.name == 'EXTS' else 0x600c)+size)
    unary = {'SHLL':0x4000,'SHLL2':0x4008,'SHLL8':0x4018,'SHLL16':0x4028,
             'SHLR':0x4001,'SHLR2':0x4009,'SHLR8':0x4019,'SHLR16':0x4029,
             'SHAL':0x4020,'SHAR':0x4021,'ROTL':0x4004,'ROTR':0x4005,'CMP_PL':0x4015,'CMP_PZ':0x4011}
    if record.name in unary and k1 == 1:
        return unary[record.name]|a<<8, [link('ea1.base',8)]
    if record.name == 'ADD' and k1 == 7 and k2 == 1 and d.get('ea1.labels.count') == 0:
        immediate = d['ea1.immediate']
        if -128 <= immediate <= 127:
            return 0x7000|b<<8|(immediate&255), [link('ea2.base',8)]
    return None


def direct_occurrences(word, items, offsets, desired, observed_records=None):
    """Resolve direct records; optional observations must form a full bijection.

    Observations are diagnostic input from single-field native suffix probes.
    They do not establish final correctness; a composed suffix/oracle is required.
    """
    require(len(items)==len(offsets),f'direct expansion/cardinality ambiguity for {word:04x}: {len(items)} records/{len(offsets)} words')
    if len({desired[off] for off in offsets})==1:
        return [(record,bindings,offsets) for record,bindings in items]
    require(observed_records is not None and all(record.index in observed_records for record,_ in items),
            f'repeated instruction has different arcade operands: {word:04x}')
    selected=[observed_records[record.index] for record,_ in items]
    require(len(set(selected))==len(selected) and set(selected)==set(offsets),
            f'observed direct occurrence map is not bijective: {word:04x}')
    return [(record,bindings,[observed_records[record.index]]) for record,bindings in items]


def plan(args, observed_records=None):
    sys.path.insert(0,str(args.codec_dir))
    sub = load_module('stage_sub',args.codec_dir/'stage_sub.py')
    asa = load_module('stage_asa',args.codec_dir/'stage_asa.py')
    oracle_module = load_module('stage_reg_oracle',args.oracle)
    oracle = oracle_module.Oracle()
    native_result, native_details = oracle.compare(args.object,args.module,args.target)
    require(native_result.get('native_sections_and_symbols_equal_baseline'), 'input native module is not the frozen current baseline')
    require(native_result['extent_equal'], 'extent differs')
    require(native_result['relocation_identity_equal'] and not native_result['unresolved_module_relocations'], 'unresolved/mismatched relocation')
    require(native_result['actual_load_identities_equal'] and native_result['branch_identities_equal'], 'load/branch identity mismatch')
    obj,bases,content,relocs,starts,base = oracle.baseline(args.module)
    ordered=sorted(starts.items(),key=lambda p:p[1]);target=args.target.lstrip('_')
    index=[n for n,_ in ordered].index(target);start=ordered[index][1]
    end=ordered[index+1][1] if index+1<len(ordered) else len(content)
    aa,extent=oracle.arc_functions[target]
    require(end-start==extent,'native target needs padding/relink or extent correction')
    psection=next(s for s in obj.sections if s.name=='P')
    words=listing_instructions(args.listing,psection.content,start,end)
    arcade_offsets=oracle_module.MS.arcade_insns(oracle.arcade,aa,extent,oracle.arc_pool)
    require(set(words)==set(arcade_offsets),'listing/arcade code-data structure differs')
    arcade_words={off:int.from_bytes(oracle.arcade[aa-oracle_module.BASE+off:aa-oracle_module.BASE+off+2],'big') for off in words}
    alignment=align_register_schedule(words,arcade_words)
    desired={off:arcade_words[alignment[off]] for off in words}
    # Validate entire target, including explicit non-instruction data.
    masks={i for off in relocs if start<=off<end for i in range(off-start,off-start+4)}
    codebytes={b for off in words for b in (off,off+1)}
    arcade=oracle.arcade[aa-oracle_module.BASE:aa-oracle_module.BASE+extent]
    require(all(content[start+i]==arcade[i] for i in range(extent) if i not in masks|codebytes),'non-instruction constant/data mismatch')
    deltas={off for off,w in words.items() if w!=desired[off]}
    for off in deltas:
        require(not ((words[off]^desired[off]) & ~reg_mask(words[off])),f'opcode/immediate/displacement difference at {off:#x}')
    records=sub.decode(args.sub.read_bytes());names=asa_names(asa,args.asa)
    labels=[(i,names.get({f.name:f.value for f in r.fields}.get('raw_ea1'))) for i,r in enumerate(records) if r.name=='FLABEL']
    hits=[i for i,name in labels if name==target]
    require(len(hits)==1,'ASA/FLABEL target identity missing or ambiguous')
    first=hits[0];last=next((i for i,_ in labels if i>first),len(records));selected=records[first:last]
    direct=collections.defaultdict(list)
    for record in selected:
        encoding=direct_encoding(record)
        if encoding:
            direct[encoding[0]].append((record,encoding[1]))
    word_offsets=collections.defaultdict(list)
    for off,w in words.items():word_offsets[w].append(off)
    proposals={};covered=collections.defaultdict(int);provenance=collections.defaultdict(set)
    def assign(record,bindings,offsets,kind):
        values={f.name:f.value for f in record.fields};types={f.name:f.kind for f in record.fields}
        for field,nshift,fshift in bindings:
            wanted={((desired[off]>>nshift)&15) for off in offsets}
            require(len(wanted)==1,f'ambiguous repeated operands: record {record.index} {field}')
            old=values[field];new=(old & ~(15<<fshift))|(next(iter(wanted))<<fshift)
            if old==new:continue
            key=record.index,field
            require(key not in proposals or proposals[key]['new']==new,f'conflicting field requirements {key}')
            proposals[key]=dict(record=record.index,field=field,type=types[field],old=old,new=new,opcode=record.name,mechanism=kind)
            provenance[key].update(offsets)
        for off in offsets:
            covered[off] |= sum(15<<shift for _,shift,_ in bindings)
    for word,items in direct.items():
        offsets=word_offsets.get(word,[])
        if not any(off in deltas for off in offsets):continue
        for record,bindings,bound in direct_occurrences(word,items,offsets,desired,observed_records):
            assign(record,bindings,bound,'direct-observed' if len(bound)==1 and len(offsets)>1 else 'direct')
    runtime=runtime_names(args.codec_dir)
    loads=native_details['loads']
    def symbol_value(label):
        name=names.get(label) or runtime(label)
        return oracle.symbols.get(name) if name else None
    def movi_value(d):
        count=d['labels.count'];value=d['immediate']
        if count==1:
            address=symbol_value(d['labels[0]'])
            return None if address is None else (address+value)&0xffffffff
        return value&0xffffffff if count==0 else None
    movi_counts=collections.Counter();frame_counts=collections.Counter();call_counts=collections.Counter()
    for record in selected:
        fields={f.name:f.value for f in record.fields}
        if record.name=='MOVI':movi_counts[movi_value(fields),fields['destination']]+=1
        elif record.name=='MVA_LC':frame_counts[fields['destination']]+=1
        elif record.name=='CALL':call_counts[symbol_value(fields['branch_label']),fields['tmp']]+=1
    for record in selected:
        d={f.name:f.value for f in record.fields}
        if record.name=='MOVI':
            count=d['labels.count'];value=movi_value(d)
            if value is None:continue
            reg=d['destination']
            candidates=[r['offset'] for r in loads if r.get('ours_value')==(value & ((1<<(8*r['width']))-1)) and (r['ours_word']>>8)&15==reg]
            if count==0 and -128<=d['immediate']<=127:candidates+=word_offsets.get(0xe000|reg<<8|(value&255),[])
            if any(off in deltas for off in candidates):
                require(len(candidates)==movi_counts[value,reg],'MOVI expansion/cardinality ambiguity')
                assign(record,[('destination',8,0)],candidates,'literal')
        elif record.name=='MVA_LC':
            offsets=word_offsets.get(0x60f3|d['destination']<<8,[])
            if any(off in deltas for off in offsets):
                require(len(offsets)==frame_counts[d['destination']]==1,'MVA_LC MOV-SP occurrence ambiguous')
                assign(record,[('destination',8,0)],offsets,'frame-base-copy')
        elif record.name=='CALL':
            address=symbol_value(d['branch_label']);reg=d['tmp']
            if address is None:continue
            candidates=[r for r in loads if r.get('ours_value')==address and (r['ours_word']>>8)&15==reg]
            if any(r['offset'] in deltas for r in candidates):
                require(len(candidates)==call_counts[address,reg],'CALL literal/record cardinality ambiguity')
            for load in candidates:
                tail=[off for off in sorted(words) if load['offset']<off<=load['offset']+96]
                call=None
                for off in tail:
                    w=words[off]
                    if w==0x400b|reg<<8:call=off;break
                    # Conservatively reject crossing branches/calls or a possible write to the temporary.
                    if oracle_module.branch_target(w,base+start+off) is not None or call_scan_barrier(w,reg):break
                if call is not None and (call in deltas or load['offset'] in deltas):
                    require(len(candidates)==call_counts[address,reg],'CALL literal/record cardinality ambiguity')
                    assign(record,[('tmp',8,0)],[load['offset'],call],'callee-address-and-jsr')
    missing=[off for off in deltas if (words[off]^desired[off]) & ~covered.get(off,0)]
    require(not missing,f'unmapped changed instruction bits at offsets: {missing}')
    for key,row in proposals.items():row['native_offsets']=','.join(f'{off:x}' for off in sorted(provenance[key]))
    rows=sorted(proposals.values(),key=lambda r:(r['record'],r['field']))
    args.out.mkdir(parents=True,exist_ok=False)
    write_tsv(args.out/'PATCH.tsv',rows,['record','field','type','old','new','opcode','mechanism','native_offsets'])
    write_tsv(args.out/'ALIGNMENT.tsv',[dict(native_offset=off,arcade_offset=alignment[off],old_word=f'{words[off]:04x}',arcade_word=f'{desired[off]:04x}') for off in words],['native_offset','arcade_offset','old_word','arcade_word'])
    inputs=[args.sub,args.asa,args.object,args.listing,args.oracle,Path(__file__),args.codec_dir/'stage_sub.py',args.codec_dir/'stage_asa.py',
            args.codec_dir.parent/'rebuild/shcasm/src/_stockdata.c',args.codec_dir.parent/'rebuild/shcasm/include/decls.h']
    inputs+=list(oracle.inputs)
    write_tsv(args.out/'INPUTS.tsv',[dict(path=str(p.resolve()),sha256=sha(p)) for p in inputs],['path','sha256'])
    status=dict(status='candidate_requires_suffix_oracle',target=target,module=args.module,fields=len(rows),changed_native_words=len(deltas),extent=extent,
                register_only=True,full_extent_native_match_claim=False,source_cause_claim=False)
    (args.out/'PLAN.txt').write_text(pprint.pformat(status)+'\n')
    (args.out/'PATCH_BINDING.txt').write_text(sha(args.sub)+'\n')
    apply(args.sub,args.out/'PATCH.tsv',args.out/'edited.sub',args.codec_dir)
    return status


def apply(source,patch,output,codec_dir):
    require(not output.exists(),'output already exists')
    codec=load_module('stage_sub',codec_dir/'stage_sub.py')
    data=Path(source).read_bytes();records=codec.decode(data)
    binding=Path(patch).parent/'PATCH_BINDING.txt'
    require(binding.is_file() and binding.read_text().strip()==hashlib.sha256(data).hexdigest(),'patch/source hash binding mismatch')
    lookup={(r.index,f.name):f for r in records for f in r.fields}
    with Path(patch).open(encoding='utf8') as stream:rows=list(csv.DictReader(stream,delimiter='\t'))
    seen=set()
    for row in rows:
        key=int(row['record']),row['field'];require(key in lookup and key not in seen,f'invalid/duplicate patch field {key}');seen.add(key)
        field=lookup[key];require(field.kind==row['type'] and field.value==int(row['old']),f'old value/type mismatch {key}')
        require(row['field'] in ('destination','tmp') or row['field'].endswith(('.base','.base_index_packed')),f'non-register edit {key}')
        new=int(row['new']);require(0<=new<=(255 if row['field'].endswith('_packed') else 15),'register outside supported range')
        if row['field'].endswith('_packed'):
            require((new&15)==(field.value&15)==0,'unsupported indexed register change')
        else:require(0<=field.value<=15,'original field is not a general register')
    edits={(int(r['record']),r['field']):r['new'] for r in rows};lines=[]
    for line in codec.dumps(data).splitlines():
        cells=line.split('\t')
        if cells[0].isdigit() and (int(cells[0]),cells[2]) in edits:cells[4]=edits[int(cells[0]),cells[2]];line='\t'.join(cells)
        lines.append(line)
    text='\n'.join(lines)+'\n';encoded=codec.encode(text)
    require(len(encoded)==len(data),'scalar patch changed serialized size')
    output.write_bytes(encoded);output.with_suffix(output.suffix+'.tsv').write_text(text,encoding='utf8')


def main():
    p=argparse.ArgumentParser(description=__doc__);commands=p.add_subparsers(dest='command',required=True)
    q=commands.add_parser('plan')
    for name in ('sub','asa','object','listing','oracle','codec-dir','out'):q.add_argument('--'+name,type=Path,required=True)
    q.add_argument('--module',required=True);q.add_argument('--target',required=True)
    q=commands.add_parser('apply')
    for name in ('sub','patch','out','codec-dir'):q.add_argument('--'+name,type=Path,required=True)
    args=p.parse_args()
    try:
        if args.command=='plan':print(pprint.pformat(plan(args)))
        else:apply(args.sub,args.patch,args.out,args.codec_dir)
    except (Ineligible,ValueError,KeyError,AssertionError) as exc:p.exit(2,f'ineligible: {exc}\n')


if __name__=='__main__':main()
