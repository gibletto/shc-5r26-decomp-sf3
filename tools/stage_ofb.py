#!/usr/bin/env python3
"""Lossless typed SHC OFB layout sidecar codec; no compiler execution.

Schema: shcasm read_ofb_layout_record (00429c0d), layout_next_ofb_record
(004298b6), begin_layout_passes (0042926d); shcpep write_ofb_* producers.
OFB must stay coherent with SUB when record forms, labels or sizes change.
Unknown records preserve the entire remaining stream, without guessed sync.
"""
import argparse, csv, io, struct, hashlib
from pathlib import Path
from stage_sub import Reader, Record, Field, FORMATS, HEADER
MAGIC='# stage-ofb-v1'

def decode(data):
    r=Reader(data);records=[]
    while r.pos < len(data):
        r.start=r.pos;r.fields=[];warning=''
        try:
            op=r.read('opcode','u8')
            if op in (0x18,0x19,0x1a,0x1b):r.read('label','u16')
            elif op==0x10:
                r.read('location','i32');r.read('value','i32')
            elif op==0x11:
                r.read('size','u8');r.read('location','i32');r.read('pool_size','u16');r.read('label','u16');r.read('value','i32');r.read('labels_raw','u32')
            elif op==0x14:
                r.read('value','i32');r.read('location','i32')
            elif op==0x20:r.read('size','u8')
            elif op==0x21:
                r.read('size','u8');r.read('location','i32');r.read('pool_size','u16')
            elif op in (0x22,0x24,0x23,0x25,0x26,0x29,0x2b):
                r.read('size','u8')
                if op in (0x25,0x26):r.read('misc_raw','u8')
                r.read('location','i32');r.read('value','i32');r.refs('labels')
                if op in (0x22,0x24):r.read('pool_size','u16')
            elif op in (0x27,0x28):
                r.read('size','u8');r.read('flags_raw','u8')
                if op==0x27:r.read('misc_raw','u8')
                r.read('value','i32');r.read('labels_raw','u32')
            elif op in (0x2a,0x2c):
                r.read('size','u8');r.read('flags_raw','u8');r.read('value','i32');r.refs('labels')
            elif op==0x2e:
                r.read('size','u8');r.read('flags_raw','u8')
            elif op in (0x8e,0x92,0x94,0x96):
                r.read('size','u8');r.read('location','i32');r.read('pool_size','u16');r.read('misc_raw','u8')
            else:raise ValueError(f'unknown OFB opcode 0x{op:02x}')
        except ValueError as e:
            r.fields=[Field(0,'opaque_remainder','hex',data[r.start:])];r.pos=len(data);warning=str(e)
        records.append(Record(len(records),r.start,f'ofb_{op:02x}',op,r.fields,warning))
    return records

def dumps(data):
    out=io.StringIO(newline='');out.write(MAGIC+'\n')
    out.write(f'# original_bytes={len(data)} sha256={hashlib.sha256(data).hexdigest()}\n')
    w=csv.writer(out,delimiter='\t',lineterminator='\n');w.writerow(HEADER)
    for r in decode(data):
        out.write(f'# record={r.index} original_offset=0x{r.offset:x} {r.name}\n')
        if r.warning:out.write('# WARNING '+r.warning+'\n')
        for f in r.fields:w.writerow([r.index,hex(f.offset),f.name,f.kind,f.value.hex() if f.kind=='hex' else str(f.value)])
    return out.getvalue()

def encode(text):
    if text.splitlines()[:1]!=[MAGIC]:raise ValueError('missing stage-ofb-v1 signature')
    rows=csv.DictReader((x for x in text.splitlines() if not x.startswith('#')),delimiter='\t')
    if rows.fieldnames!=HEADER:raise ValueError('unexpected TSV columns')
    data=bytearray();shapes=[];seen=set();prev=None;names=set();offset=0
    for x in rows:
        if None in x or any(v is None for v in x.values()):raise ValueError('malformed TSV row')
        if x['record']!=prev:
            prev=x['record']
            if prev in seen:raise ValueError('noncontiguous record group')
            seen.add(prev);shapes.append([]);names=set();offset=0
        if x['field'] in names or int(x['offset'],0)!=offset:raise ValueError('duplicate/noncontiguous field')
        names.add(x['field']);kind=x['type']
        if kind=='hex':raw=bytes.fromhex(x['value'])
        elif kind in FORMATS:raw=struct.pack('<'+FORMATS[kind],int(x['value'],0))
        else:raise ValueError('unsupported atom type')
        shapes[-1].append((offset,x['field'],kind,len(raw)));data.extend(raw);offset+=len(raw)
    actual=[[(f.offset,f.name,f.kind,len(f.value) if f.kind=='hex' else struct.calcsize('<'+FORMATS[f.kind])) for f in r.fields] for r in decode(bytes(data))]
    if shapes!=actual:raise ValueError('encoded grammar differs from typed OFB fields')
    return bytes(data)

def main():
    p=argparse.ArgumentParser(description=__doc__);sub=p.add_subparsers(dest='verb',required=True)
    for verb in ('dump','encode','check'):
        a=sub.add_parser(verb);a.add_argument('input',type=Path)
        if verb!='check':a.add_argument('output',type=Path)
        if verb!='encode':a.add_argument('--require-complete',action='store_true')
    a=p.parse_args()
    if a.verb!='check' and (a.input.resolve()==a.output.resolve() or a.output.exists()):raise ValueError('output must be a fresh distinct path')
    if a.verb=='encode':a.output.write_bytes(encode(a.input.read_text()));return
    data=a.input.read_bytes();text=dumps(data);assert encode(text)==data
    records=decode(data);unknown=sum(bool(x.warning) for x in records)
    if a.require_complete and unknown:raise ValueError('undecoded OFB remainder')
    if a.verb=='dump':a.output.write_text(text)
    print(f'roundtrip=identical bytes={len(data)} records={len(records)} opaque_remainders={unknown}')
if __name__=='__main__':
    try:main()
    except (ValueError,OSError,struct.error) as e:raise SystemExit(f'stage_ofb: {e}')
