"""Execute generic stable-frontier controls with a native SHC toolchain.

No installed tools change. The optional profile supplies existing stage flags;
ASM_READY_WAVES is controlled only by this runner. Missing native inputs skip.
"""
from pathlib import Path
import argparse,hashlib,json,os,re,shutil,subprocess,sys

ROOT=Path(__file__).resolve().parent.parent
MASK=0xffffffff
PREFIXES=('GEN_','PEP_','MDL_','ASM_','SWITCH_','XJUMP','SLOT_','SHCGEN_')
OPTIONS=['-cpu=sh2','-division=cpu','-endian=big','-pic=1','-extra=m=8,a=8',
         '-nortnext','-optimize=1','-speed']

def main():
 ap=argparse.ArgumentParser(description=__doc__)
 ap.add_argument('--trial',type=Path);ap.add_argument('--production',type=Path)
 ap.add_argument('--matchlab',type=Path);ap.add_argument('--work',type=Path)
 ap.add_argument('--profile',type=Path)
 a=ap.parse_args()
 if not(a.trial and a.production and a.matchlab):
  print('SKIP: needs --trial, --production and --matchlab');return 0
 if not a.work:ap.error('--work is required')
 r=a.work.resolve();assert not r.exists(),'use a fresh --work';r.mkdir(parents=True)
 profile=json.loads(a.profile.read_text()) if a.profile else {}
 assert 'ASM_READY_WAVES' not in profile
 sys.path[:0]=[str(ROOT/'tests'),str(a.matchlab.resolve())]
 import parity,diff_exec as dx,msearch_module as mm
 tree=r/'tree';tree.mkdir();shutil.copytree(a.production.resolve(),tree/'bin')
 (tree/'src').mkdir();(tree/'include').mkdir()
 source=ROOT/'tests/ready_wave.c';shutil.copyfile(source,tree/'src/controls.c')
 def environment(tmp,flag=None):
  tmp.mkdir(parents=True,exist_ok=True)
  e={k:v for k,v in os.environ.items() if not k.startswith(PREFIXES)}
  e.update(profile,SHC_LIB=str(tree/'bin'),SHC_TMP=str(tmp),TMP=str(tmp),TEMP=str(tmp),
           PATH=str(tree/'bin')+';'+os.environ.get('PATH',''))
  if flag is not None:e['ASM_READY_WAVES']=flag
  return e
 def link(folder,obj,env):
  (folder/'unit.sub').write_bytes(b'START P(06000000)\nINPUT '+obj.name.encode()+b'\nOUTPUT unit.abs\nPRINT unit.map\nFORM A\nEXIT\n')
  for command in [[str(tree/'bin/lnk.exe'),'-SUBCOMMAND=unit.sub'],
    [str(tree/'bin/rof2bin.exe'),'-s=06000000','-e=06010000','-v=00','unit.abs']]:
   p=subprocess.run(command,cwd=folder,env=env,capture_output=True,text=True)
   assert p.returncode==0,p.stdout+p.stderr
   (folder/('link.log' if 'lnk.exe' in command[0] else 'convert.log')).write_text(p.stdout+p.stderr)
  syms={n:int(v,16) for n,v in re.findall(r"^_(\w+)\s+H'([0-9A-F]+)",(folder/'unit.map').read_text(),re.M)}
  image=dx.Image((folder/'unit.bin').read_bytes());dx.G={};return image,syms,dx.LiveIn(image)
 rows=[];outputs={};functions={}
 def machine(image,syms,live,name,args):
  class Machine(dx.Machine):
   def call(self,target,tail=False):
    assert target==0x06008000 and not tail,('unexpected callback',target,tail)
    self.flush();arg=self.R[4];self.trace.append(('call',target,arg));self.ncall+=1
    for rr in range(8):self.R[rr]=(0xdead0000+rr*0x1111+self.ncall)&MASK
    self.R[0]=(arg*3+7)&MASK;self.last_call_r0=self.R[0];self.base=list(self.R);self.T=1
  m=Machine(image,syms[name],dx.BASE,dx.BASE+0x1000,0,[],live,lambda v:v)
  for i,value in enumerate(args):m.R[4+i]=value&MASK
  m.trace=[];m.seg=[];return m
 def finish(m,expected,context):
  m.run();assert m.trace[-1][0]=='ret' and m.trace[-1][2],(context,'return/callee-save')
  assert m.trace[-1][1]==expected&MASK,(context,m.trace[-1][1],expected&MASK)
  rows.append([*context,'PASS'])
 vectors=[0,1,0x7fffffff,0x80000000,0xffffffff,0x12345678]
 for mode,flag in [('installed',None),('unset',None),('off','0'),('on','1')]:
  folder=tree/mode;folder.mkdir();obj=folder/'controls.obj';lst=folder/'controls.lst'
  shutil.copyfile(a.production.resolve()/'shcasm.exe' if mode=='installed' else a.trial.resolve(),tree/'bin/shcasm.exe')
  command=[str(tree/'bin/shc.exe'),'src/controls.c',*OPTIONS,'-include=include',
           '-object='+str(obj.relative_to(tree)),'-listfile='+str(lst.relative_to(tree)),'-show=object']
  env=environment(folder/'tmp',flag)
  p=subprocess.run(command,cwd=tree,env=env,capture_output=True,text=True,timeout=120)
  (folder/'compile.log').write_text(p.stdout+p.stderr)
  assert p.returncode==0 and obj.exists() and '(E)' not in p.stdout+p.stderr and '(F)' not in p.stdout+p.stderr,p.stdout+p.stderr
  outputs[mode]=parity.normalize(obj.read_bytes());functions[mode]=mm.parse_listing(lst).words
  image,syms,live=link(folder,obj,environment(folder/'linktmp',flag))
  for x in vectors:
   for y in vectors:
    port=0x02010000;v=(x+1)&MASK;w=(y+3)&MASK;join=v^w;tail=((join<<2)+w)&MASK
    m=machine(image,syms,live,'graph',[port,x,y]);finish(m,((v>>3)^tail)+join,(mode,'graph',x,y))
    assert [m.rd(port+i*4,4) for i in range(4)]==[v,w,join,tail]
    m=machine(image,syms,live,'multiply',[x,y]);want=x*y+((((x+3)&MASK)*(y^7))<<1)+(x&255)
    finish(m,want,(mode,'multiply',x,y))
    v=(x+1)&MASK;w=(v*3+7)&MASK;m=machine(image,syms,live,'callsite',[port,0x06008000,x,y])
    finish(m,v^w^y,(mode,'callsite',x,y));assert m.ncall==1 and m.rd(port,4)==y and m.rd(port+4,4)==w
    for condition in [0,1]:
     m=machine(image,syms,live,'diamond',[condition,x,y]);want=(((x+3)&MASK)^y) if condition else (((y+7)&MASK)^x)
     finish(m,want,(mode,'diamond',condition,x,y))
   for offset in [0,4,16]:
    port=0x02010000;mem=[(x+i*0x1020304)&MASK for i in range(10)];want=mem[:];j=offset//4
    want[j]=(want[0]+x)&MASK;want[j+1]=want[1]^want[j];want[j+2]=(want[2]+want[j+1])&MASK
    m=machine(image,syms,live,'overlap',[port,port+offset,x])
    for i,v in enumerate(mem):m.wr(port+4*i,4,v)
    finish(m,want[j+2]+want[0],(mode,'overlap',x,offset))
    assert [m.rd(port+4*i,4) for i in range(10)]==want
   mem=[(x+i*0x1020304)&MASK for i in range(33)];want=mem[0]
   for i in range(1,33):want=(want+mem[i])&MASK if i&1 else want^mem[i]
   m=machine(image,syms,live,'window32',[0x02010000])
   for i,v in enumerate(mem):m.wr(0x02010000+4*i,4,v)
   finish(m,want,(mode,'window32',x))
   assert [m.rd(0x02010000+4*i,4) for i in range(33)]==mem
  print('PASS',mode,'generic execution',flush=True)
 assert outputs['installed']==outputs['unset']==outputs['off'],'complete generic off parity'
 changes={n:functions['off'][n]!=functions['on'][n] for n in functions['off']}
 assert any(changes.values()),'fixture did not exercise alternate scheduling'
 bindings={str(p):hashlib.sha256(p.read_bytes()).hexdigest() for p in [Path(__file__).resolve(),source,a.trial.resolve(),Path(dx.__file__).resolve()]}
 proof={'executions':len(rows),'complete_generic_off_parity':True,'profile':profile,
        'functions_changed':changes,'bindings':bindings,'cases':rows}
 (r/'proof.json').write_text(json.dumps(proof,indent=2)+'\n')
 print('PASS',len(rows),'SH2 executions',changes)
 return 0

if __name__=='__main__':raise SystemExit(main())
