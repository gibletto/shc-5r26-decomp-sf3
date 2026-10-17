"""Compile and execute the actual normalization proof/reader in fresh processes."""
from pathlib import Path
import argparse,importlib.util,os,subprocess
ROOT=Path(__file__).resolve().parent.parent
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--work',type=Path,required=True);a=ap.parse_args()
 work=a.work.resolve();assert not work.exists();work.mkdir(parents=True)
 spec=importlib.util.spec_from_file_location('native_build',ROOT/'build.py');m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
 env,cc,cf,ld,lf=m.toolchain('msvc');inc=ROOT/'rebuild/shcgen/include'
 count=0
 for mode in [0,1]:
  out=work/('mode'+str(mode));out.mkdir();objects=[]
  for src in [ROOT/'tests/narrow_normalize_native.c',ROOT/'rebuild/shcgen/src/_narrownormalize.c',ROOT/'rebuild/shcgen/src/_gen_rules.c']:
   obj=out/(src.stem+'.obj');name,rc,msg=m.compile_one((env,cc,cf,ld,lf),src,obj,inc,mode)
   assert rc==0,msg;objects.append(obj)
  exe=out/'cases.exe'
  r=subprocess.run(cc+['/nologo',*map(str,objects),'/Fe'+str(exe)],cwd=out,env=env,capture_output=True,text=True)
  assert r.returncode==0,r.stdout+r.stderr
  for setting,want in [(None,1),('0',0),('1',1)]:
   runenv={k:v for k,v in os.environ.items()if k not in ['GEN_NARROW_NORMALIZE','GEN_NARROW_NORMALIZE_TRACE']}
   if setting is not None:runenv['GEN_NARROW_NORMALIZE']=setting
   r=subprocess.run([str(exe),str(want)],env=runenv,capture_output=True,text=True)
   (out/('unset'if setting is None else setting)).with_suffix('.log').write_text(r.stdout+r.stderr)
   assert r.returncode==0,r.stdout+r.stderr
   assert 'PASS 74 actual-helper cases' in r.stdout
   actual=want if mode else 0
   assert 'PASS actual setting reader+late destination: '+str(actual) in r.stdout
   print('PASS SHC_REBUILD_UPDATED',mode,'setting',setting,'74 helpers + actual reader/destination',actual,flush=True);count+=1
 print('PASS',count,'native modes; predicates and stock bypass',flush=True)
if __name__=='__main__':main()
