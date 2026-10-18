#!/usr/bin/env python3
"""Bounded single-field native ASM probes disambiguate repeated SUB instructions.

No policy/source edits or raw-object patches. Only a one-instruction register
nibble delta, with every other native section/relocation/symbol unchanged, can
bind a direct record. A final composed native suffix and full oracle are required.
"""
from pathlib import Path
import argparse, ast, collections, csv, hashlib, math, pprint, re, subprocess, sys, time
import stage_reg_edit as p


def only(folder,pattern):
    found=list(folder.glob(pattern));p.require(len(found)==1,f'expected one {pattern} in {folder}')
    return found[0]


def native_metadata_equal(old,new,oracle):
    return ([(s.name,s.address,s.lenght,s.align) for s in old.sections]==[(s.name,s.address,s.lenght,s.align) for s in new.sections]
        and old.loc_syms==new.loc_syms and old.endian==new.endian and old.ext_syms==new.ext_syms
        and [s for s in old.sections if s.name!='P']==[s for s in new.sections if s.name!='P']
        and next(s.relocs for s in old.sections if s.name=='P')==next(s.relocs for s in new.sections if s.name=='P'))


def clean_probe(before,after,start,end,word,shift,oldreg,newreg,known_offsets):
    """Return relative occurrence only for exactly one predicted nibble rewrite."""
    p.require(len(before)==len(after),'native P length changed')
    changed=[off for off in range(0,len(before),2) if before[off:off+2]!=after[off:off+2]]
    p.require(len(changed)==1,'probe changes zero/multiple native instruction words')
    absolute=changed[0];relative=absolute-start
    p.require(start<=absolute<end and relative in known_offsets,'probe changes outside expected instruction group')
    a=int.from_bytes(before[absolute:absolute+2],'big');b=int.from_bytes(after[absolute:absolute+2],'big')
    p.require(a==word and ((a>>shift)&15)==oldreg,'probe original operand mismatch')
    expected=(word&~(15<<shift))|(newreg<<shift)
    p.require(b==expected and not ((a^b)&~p.reg_mask(a)),'probe changes opcode/control/displacement or unexpected register')
    return relative


def run(args):
    args.out.mkdir(parents=True,exist_ok=False)
    started=time.monotonic();deadline=started+args.seconds
    sys.path.insert(0,str(args.codec_dir))
    sub=p.load_module('stage_sub',args.codec_dir/'stage_sub.py')
    asa=p.load_module('stage_asa',args.codec_dir/'stage_asa.py')
    native=p.load_module('probe_oracle',args.oracle);oracle=native.Oracle()
    files=args.capture/'before_shcasm/files'
    original=only(files,'*.sub');asa_path=only(files,'*.asa');sua=only(files,'*.sua')
    original_obj=args.capture/'work/out'/(Path(args.module).stem+'.obj')
    listing=only(args.capture/'work','*.lst')
    baseline,details=oracle.compare(original_obj,args.module,args.target)
    p.require(baseline['native_sections_and_symbols_equal_baseline'],'capture differs from frozen native baseline')
    old,bases,content,relocs,starts,base=oracle.baseline(args.module)
    start=starts[args.target];end=min((v for v in starts.values() if v>start),default=len(content))
    raw=next(s.content for s in old.sections if s.name=='P')
    words=p.listing_instructions(listing,raw,start,end)
    records=sub.decode(original.read_bytes());names=p.asa_names(asa,asa_path)
    labels=[(i,names.get({f.name:f.value for f in r.fields}.get('raw_ea1'))) for i,r in enumerate(records) if r.name=='FLABEL']
    firsts=[i for i,name in labels if name==args.target];p.require(len(firsts)==1,'ambiguous target FLABEL')
    first=firsts[0];last=next((i for i,_ in labels if i>first),len(records))
    direct=collections.defaultdict(list)
    for record in records[first:last]:
        encoded=p.direct_encoding(record)
        if encoded:direct[encoded[0]].append((record,encoded[1]))
    frozen_paths=[Path(__file__),Path(p.__file__),args.driver,args.oracle,args.capture/'manifest.txt',original,original_obj,asa_path,sua,listing,
                  args.codec_dir/'stage_sub.py',args.codec_dir/'stage_asa.py']
    frozen_paths.extend(path for path in files.iterdir() if path.is_file())
    frozen={str(path.resolve()):p.sha(path) for path in frozen_paths}
    (args.out/'FREEZE.txt').write_text(pprint.pformat(frozen)+'\n')
    observations={};probe_rows=[];maps=[];count=0
    plan_args=argparse.Namespace(sub=original,asa=asa_path,object=original_obj,listing=listing,module=args.module,
        target=args.target,oracle=args.oracle,codec_dir=args.codec_dir,out=args.out/'plan')

    def save():
        p.write_tsv(args.out/'PROBES.tsv',probe_rows,['probe','record','field','old','new','word','status','native_offset','reason','object','sha256'])
        p.write_tsv(args.out/'OBSERVED.tsv',maps,['record','native_offset','word','field','probe','object_sha256'])

    def suffix(folder,replacement):
        nonlocal count
        p.require(count<args.max_probes,'suffix probe cap reached')
        remaining=deadline-time.monotonic();p.require(remaining>=2,'routine time cap reached')
        count+=1
        cmd=[sys.executable,str(args.driver),'replay','--capture',str(args.capture),'--from-stage','shcasm',
             '--out',str(folder),'--replace','sub='+str(replacement),'--timeout',str(max(1,math.floor(remaining)-1))]
        result=subprocess.run(cmd,capture_output=True,text=True,timeout=remaining+1)
        folder.parent.joinpath(folder.name+'.log').write_text(result.stdout+result.stderr)
        p.require(result.returncode==0,'native suffix failed')
        return folder/'work/out'/original_obj.name

    status='unresolved';reason='';result=None;final_object=None;outside_result=None
    try:
        while True:
            p.require(time.monotonic()<deadline,'routine time cap reached')
            try:
                plan_result=p.plan(plan_args,observations)
                break
            except p.Ineligible as exc:
                match=re.fullmatch(r'repeated instruction has different arcade operands: ([0-9a-f]{4})',str(exc))
                if not match:raise
                word=int(match[1],16);items=direct[word];known={o for o,w in words.items() if w==word}
                p.require(len(items)==len(known),'probe group cardinality differs')
                for record,bindings in items:
                    if record.index in observations:continue
                    success=False
                    for field,nshift,fshift in bindings:
                        d={f.name:f.value for f in record.fields};types={f.name:f.kind for f in record.fields}
                        oldreg=(d[field]>>fshift)&15;newreg=oldreg^1
                        new=(d[field]&~(15<<fshift))|(newreg<<fshift)
                        folder=args.out/f'probe{count+1:03d}';folder.mkdir()
                        patch=dict(record=record.index,field=field,type=types[field],old=d[field],new=new,opcode=record.name,mechanism='single-field-occurrence-probe',native_offsets='')
                        p.write_tsv(folder/'PATCH.tsv',[patch],list(patch));(folder/'PATCH_BINDING.txt').write_text(p.sha(original)+'\n')
                        edited=folder/'edited.sub';p.apply(original,folder/'PATCH.tsv',edited,args.codec_dir)
                        row=dict(probe=count+1,record=record.index,field=field,old=d[field],new=new,word=f'{word:04x}',status='rejected',native_offset='',reason='',object='',sha256='')
                        try:
                            objpath=suffix(folder/'run',edited);row.update(object=str(objpath),sha256=p.sha(objpath))
                            obj=native.Sysrof.from_bytes(objpath.read_bytes())
                            p.require(native_metadata_equal(old,obj,native),'native layout/symbols/relocations/non-P section changed')
                            candidate=next(s.content for s in obj.sections if s.name=='P')
                            off=clean_probe(raw,candidate,start,end,word,nshift,oldreg,newreg,known)
                            p.require(off not in observations.values(),'observed occurrence already owned by another record')
                            observations[record.index]=off;row.update(status='mapped',native_offset=off)
                            maps.append(dict(record=record.index,native_offset=off,word=f'{word:04x}',field=field,probe=count,object_sha256=row['sha256']))
                            success=True
                        except (p.Ineligible,ValueError,AssertionError,subprocess.TimeoutExpired) as exc:row['reason']=str(exc)
                        probe_rows.append(row);save()
                        if success:break
                    p.require(success,f'no clean one-field mapping for record {record.index}; coupled/nonlinear/unknown effect')
        final_object=suffix(args.out/'final_run',args.out/'plan/edited.sub')
        result,details=oracle.compare(final_object,args.module,args.target);oracle.write(args.out/'oracle',result,details)
        new=native.Sysrof.from_bytes(final_object.read_bytes());newraw=next(s.content for s in new.sections if s.name=='P')
        outside=native_metadata_equal(old,new,native) and raw[:start]==newraw[:start] and raw[end:]==newraw[end:]
        outside_result=dict(outside_unchanged=outside,native_metadata_equal=native_metadata_equal(old,new,native),start=start,end=end,
                            raw_P_outside_equal=raw[:start]==newraw[:start] and raw[end:]==newraw[end:])
        (args.out/'OUTSIDE.txt').write_text(pprint.pformat(outside_result)+'\n')
        p.require(outside,'composed edit changed outside target or native metadata')
        p.require(result['strict_relocation_identity_exact'],'composed full target not exact')
        p.require(time.monotonic()<=deadline,'routine time cap reached during final validation')
        status='validated_hit'
    except (p.Ineligible,ValueError,AssertionError,subprocess.TimeoutExpired) as exc:reason=str(exc)
    save()
    unchanged={path:p.sha(path)==digest for path,digest in frozen.items()}
    p.require(all(unchanged.values()),'frozen input changed during probes')
    answer=dict(target=args.target,module=args.module,status=status,reason=reason,suffix_calls=count,seconds_cap=args.seconds,elapsed_seconds=time.monotonic()-started,
                observed_records=len(observations),capture=str(args.capture),original_sub=str(original),original_sua=str(sua),original_asa=str(asa_path),
                edited_sub=str(args.out/'plan/edited.sub') if (args.out/'plan/edited.sub').is_file() else '',
                native_object=str(final_object) if final_object else '',full_object_sha256=p.sha(final_object) if final_object else '',
                oracle_result=str(args.out/'oracle/result.txt') if result else '',outside_result=str(args.out/'OUTSIDE.txt') if result else '',
                strict_raw=result['strict_raw_byte_exact'] if result else False,strict_identity=result['strict_relocation_identity_exact'] if result else False,
                outside_unchanged=outside_result['outside_unchanged'] if outside_result is not None else 'not_run',fields=plan_result['fields'] if 'plan_result' in locals() else '',
                all_inputs_unchanged=True,qualification='single-field diagnostic mapping plus full composed suffix proof; boundary sufficiency, not historical cause')
    (args.out/'RESULT.txt').write_text(pprint.pformat(answer,sort_dicts=False)+'\n')
    return answer


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    for key in ('capture','oracle','driver','codec-dir','out'):parser.add_argument('--'+key,type=Path,required=True)
    for key in ('module','target'):parser.add_argument('--'+key,required=True)
    parser.add_argument('--max-probes',type=int,default=256);parser.add_argument('--seconds',type=float,default=120)
    args=parser.parse_args();p.require(1<=args.max_probes<=256 and 1<=args.seconds<=120,'caps exceed authorized limits')
    print(pprint.pformat(run(args)))

if __name__=='__main__':main()
