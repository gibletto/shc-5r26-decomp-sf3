"""Execute terminal-return scheduling controls with the companion SH2 interpreter.

No installed tools or game sources change. Supply complete production tools,
the candidate shcpep.exe, optional stage settings JSON, and a fresh --work.
"""
from pathlib import Path
import argparse,csv,hashlib,importlib.util,json,os,re,shutil,subprocess,sys
ROOT=Path(__file__).resolve().parent.parent
PREFIXES=('GEN_','PEP_','MDL_','ASM_','SWITCH_','XJUMP','SLOT_','SHCGEN_')
OPTIONS=['-cpu=sh2','-division=cpu','-endian=big','-pic=0','-extra=m=8,a=8','-nortnext','-optimize=1','-speed']

def function_body(module,name):
 start=module.starts[name]
 end=min([v for v in module.starts.values() if v>start]+[module.sizes['P']])
 relocs=tuple((offset-start,width,expr)for section,offset,width,expr in module.relocations if section=='P'and start<=offset<end)
 return end-start,module.words[name],relocs

class Driver:
 def __init__(self,profile):self.REVISION=profile
 def env_for(self,tree,tmp,sets=None):
  tmp.mkdir(parents=True,exist_ok=True)
  env={k:v for k,v in os.environ.items() if not k.startswith(PREFIXES)}
  env.update(self.REVISION,SHC_LIB=str(tree/'bin'),SHC_TMP=str(tmp),TMP=str(tmp),TEMP=str(tmp),PATH=str(tree/'bin')+';'+os.environ.get('PATH',''))
  env.update(sets or {});return env
 def compile_one(self,tree,src,obj,flags,tmp,listing=None,sets=None):
  obj.unlink(missing_ok=True)
  cmd=[str(tree/'bin/shc.exe'),str(src.relative_to(tree)),*OPTIONS,'-object='+str(obj.relative_to(tree)),'-listfile='+str(listing.relative_to(tree)),'-show=object']
  process=subprocess.run(cmd,cwd=tree,env=self.env_for(tree,tmp,sets),capture_output=True,text=True,timeout=120)
  msg=process.stdout+process.stderr
  return process.returncode==0 and obj.exists() and listing.exists() and '(E)'not in msg and '(F)'not in msg,msg

def main():
 ap=argparse.ArgumentParser(description=__doc__)
 ap.add_argument('--trial',type=Path);ap.add_argument('--production',type=Path)
 ap.add_argument('--matchlab',type=Path);ap.add_argument('--work',type=Path)
 ap.add_argument('--profile',type=Path,help='optional existing stage settings JSON; excludes PEP_RETURN_EXIT')
 a=ap.parse_args()
 if not(a.trial and a.production and a.matchlab):
  print('SKIP: needs --trial, --production and --matchlab (see tests/README.md)');return 0
 if not a.work:ap.error('--work is required')
 r=a.work.resolve();assert not r.exists(),'use a fresh --work';r.mkdir(parents=True)
 c=ROOT;sys.path.insert(0,str(a.matchlab.resolve()));sys.path.insert(0,str(ROOT/'tests'))
 import diff_exec as dx
 import msearch_module as mm
 import parity
 profile=json.loads(a.profile.read_text())if a.profile else {}
 assert 'PEP_RETURN_EXIT' not in profile
 buildng=Driver(profile)
 out=r/'semantic';out.mkdir();(out/'src').mkdir();(out/'bin').mkdir()
 for p in a.production.resolve().iterdir():
  if p.is_file():shutil.copy2(p,out/'bin'/p.name)
 shutil.copy2(a.trial.resolve(),out/'bin/shcpep.exe')
 stockbin=a.production.resolve()
 source=ROOT/'tests/return_exit.c';(out/'src/fixture.c').write_bytes(source.read_bytes())
 NAMES=re.findall(r'^int (\w+)\(SlotWork\*',source.read_text(),re.M);assert len(NAMES)==8
 fixed='          .CPU SH2\n'
 for name,address in [('ready',0x02001000),('choices',0x02002000),('observer',0x06008000)]:
  fixed+=f"          .EXPORT _{name}\n_{name} .EQU H'{address:08X}\n"
 fixed+='          .END\n';(out/'fixed.src').write_bytes(fixed.encode())
 env=buildng.env_for(out,r/'tmpsym')
 pr=subprocess.run([str(out/'bin/asmsh.exe'),'fixed.src','-object=fixed.obj'],cwd=out,env=env,capture_output=True,text=True)
 assert pr.returncode==0 and(out/'fixed.obj').exists(),pr.stdout+pr.stderr
 outputs={};images={};fns={};execrows=[]
 for label,flag,old in [('installed','0',True),('unset',None,False),('off','0',False),('on','1',False)]:
  folder=out/'build'/label;folder.mkdir(parents=True,exist_ok=True);obj=folder/'fixture.obj';lst=folder/'fixture.lst';sets={} if flag is None else {'PEP_RETURN_EXIT':flag}
  if old:sets.update(SHC_LIB=str(stockbin),PATH=str(stockbin)+';'+os.environ.get('PATH',''))
  sets['PEP_DUMP']=str(folder/'pep.txt')
  ok,msg=buildng.compile_one(out,out/'src/fixture.c',obj,'speed',r/('tmpfixture'+label),listing=lst,sets=sets);assert ok,msg[-2000:]
  outputs[label]=parity.normalize(obj.read_bytes());module=mm.parse_listing(lst);fns[label]={name:function_body(module,name) for name in NAMES}
  shutil.copy2(out/'fixed.obj',folder/'fixed.obj')
  sub=folder/'fixture.sub';sub.write_bytes(b'START P(06000000)\nINPUT fixture.obj\nINPUT fixed.obj\nOUTPUT fixture.abs\nPRINT fixture.map\nFORM A\nEXIT\n')
  runenv=buildng.env_for(out,r/('tmplink'+label))
  for cmd in [[str(out/'bin/lnk.exe'),'-SUBCOMMAND=fixture.sub'],[str(out/'bin/rof2bin.exe'),'-s=06000000','-e=06010000','-v=00','fixture.abs']]:
   pr=subprocess.run(cmd,cwd=folder,env=runenv,capture_output=True,text=True);assert pr.returncode==0,pr.stdout+pr.stderr
   (folder/('link.log'if'lnk.exe'in cmd[0] else'convert.log')).write_text(pr.stdout+pr.stderr)
  syms={n:int(a,16)for n,a in re.findall(r"^_(\w+)\s+H'([0-9A-F]+)",(folder/'fixture.map').read_text(),re.M)}
  image=dx.Image((folder/'fixture.bin').read_bytes());dx.G={};live=dx.LiveIn(image)
  class Machine(dx.Machine):
   def call(self,tgt,tail=False):
    assert tgt==0x06008000 and not tail
    self.flush();self.trace.append(('call',tgt,self.R[4]));self.ncall+=1
    for rr in range(8):self.R[rr]=(0xdead0000+rr*0x1111+self.ncall)&0xffffffff
    self.last_call_r0=self.R[0];self.base=list(self.R);self.T=1
  for name in fns[label]:
   for player in [0,1]:
    for state in [0,3,32767]:
     for ready in [0,1,-1,2]:
      for equal in [False,True]:
       work=0x02030000;initial=bytearray([0x5a]*868);initial[36:38]=(state&65535).to_bytes(2,'big');initial[818:820]=player.to_bytes(2,'big');initial[820:822]=(1 if equal else 2).to_bytes(2,'big');initial[822:824]=(9).to_bytes(2,'big')
       machine=Machine(image,syms[name],dx.BASE,dx.BASE+0x1000,0,[],live,lambda v:v);machine.R[4]=work
       for off,v in enumerate(initial):machine.wr(work+off,1,v)
       for k in [0,1]:machine.wr(0x02001000+2*k,2,ready);machine.wr(0x02002000+k,1,1)
       machine.trace=[];machine.seg=[];machine.run();context=(label,name,player,state,ready,equal)
       assert machine.trace and machine.trace[-1][0]=='ret',(context,machine.trace[-4:]);ret=0 if ready==0 else (-7 if name=='literal_negative' else 42 if name=='literal_positive' else 1)
       if name=='literal_zero':ret=0
       assert machine.trace[-1][1]==ret&0xffffffff,(context,'return',machine.trace[-1],ret)
       assert machine.trace[-1][2],(context,'callee-saved',machine.trace[-1])
       want=state
       skip=ready==0 or name=='extra_predecessor'and ready==2
       if not skip:want=(9 if name=='arm_dependency' else 4)if equal else(state+1)&65535
       assert machine.rd(work+36,2)==want,(context,'state',machine.rd(work+36,2),want)
       assert machine.ncall==int(name=='arm_call'and ready!=0 and equal),(context,'calls',machine.ncall)
       actual=bytes(machine.rd(work+i,1)for i in range(len(initial)));expected=initial[:];expected[36:38]=(want&65535).to_bytes(2,'big');assert actual==expected,(context,'other memory')
       execrows.append([*context,ret&0xffffffff,want,'PASS'])
  print('PASS execution',label,len(fns[label]),'functions',flush=True)
 assert outputs['installed']==outputs['unset']==outputs['off'],'off/default native object mismatch'
 changes={n:fns['off'][n]!=fns['on'][n]for n in fns['off']};print('changes',changes)
 for n in ['arm_dependency','arm_call','extra_predecessor']:assert not changes[n],('negative changed',n)
 for n in ['disjoint','literal_negative','literal_positive']:assert changes[n],('positive did not exercise policy',n)
 with(out/'results.tsv').open('w',newline='')as f:
  w=csv.writer(f,delimiter='\t',lineterminator='\n');w.writerow(['mode','function','player','initial_state','ready','equal','return','state','status']);w.writerows(execrows)
 (out/'summary.json').write_text(json.dumps({'executions':len(execrows),'changes':changes,'off_old_object_equal':True,'profile':buildng.REVISION},indent=2)+'\n');print('PASS',len(execrows),'SH2 executions, disabled/default parity')

 paths=[Path(__file__).resolve(),source,a.trial.resolve(),Path(dx.__file__).resolve()]
 bindings={str(p):hashlib.sha256(p.read_bytes()).hexdigest()for p in paths}
 (out/'bindings.json').write_text(json.dumps(bindings,indent=2)+'\n')
 return 0

if __name__=="__main__":raise SystemExit(main())
