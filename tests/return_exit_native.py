"""Execute the actual terminal literal finder, stock bypass and structural controls."""
from pathlib import Path
import argparse,hashlib,importlib.util,json,os,subprocess
ROOT=Path(__file__).resolve().parent.parent

def main():
 ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--work',type=Path,required=True);a=ap.parse_args()
 c=ROOT
 spec=importlib.util.spec_from_file_location('build_native',ROOT/'build.py');b=importlib.util.module_from_spec(spec);spec.loader.exec_module(b)
 tc=b.toolchain('msvc');env,cc,cf,ld,lf=tc
 out=a.work.resolve();assert not out.exists(),'use a fresh --work';out.mkdir(parents=True);inc=c/'rebuild/shcpep/include';source=(c/'rebuild/shcpep/src/_pep_rules.c').read_text()
 def function(needle):
  a=source.index(needle);z=source.index('{',a);depth=1;e=z+1
  while depth:
   depth+=(source[e]=='{')-(source[e]=='}');e+=1
  return source[a:e]+'\n'
 body=function('static int env_int(')+'\n'+function('int pep_terminal_literal_exit(')
 helper=out/'helper.c';helper.write_bytes(('#include "decls.h"\n#include <stdlib.h>\n'+body).encode());bindings={'verbatim_helper_sha256':hashlib.sha256(body.encode()).hexdigest()}
 for mode in [0,1]:
  folder=out/('mode'+str(mode));folder.mkdir(exist_ok=True);objects=[]
  for s in [c/'tests/return_exit_native.c',helper,*[c/'rebuild/shcpep/src'/n for n in ['004175b0_find_slot_candidate_after_label.c','004095e0_find_next_psd_record.c','00409ad0_is_movi_feeding_stack_add.c']]]:
   obj=folder/(s.stem+'.obj');name,rc,msg=b.compile_one(tc,s,obj,inc,mode);assert rc==0,msg;objects.append(obj)
  exe=folder/'cases.exe';p=subprocess.run(cc+['/nologo',*map(str,objects),'/Fe'+str(exe)],cwd=folder,env=env,capture_output=True,text=True);assert p.returncode==0,p.stdout+p.stderr
  for flag in [None,'0','1']:
   runenv={k:v for k,v in os.environ.items()if k!='PEP_RETURN_EXIT'}
   if flag is not None:runenv['PEP_RETURN_EXIT']=flag
   expected=int(mode==1 and flag=='1');p=subprocess.run([str(exe),str(expected)],env=runenv,capture_output=True,text=True);(folder/(('unset'if flag is None else flag)+'.log')).write_bytes((p.stdout+p.stderr).encode());assert p.returncode==0,p.stdout+p.stderr
   print('PASS actual finder, mode',mode,'setting',flag,':',p.stdout.splitlines()[-1],flush=True)
 (out/'bindings.json').write_text(json.dumps(bindings,indent=2)+'\n')

if __name__=="__main__":main()
