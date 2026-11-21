"""Rebuild every Versus 13.10.3052 source file with another compiler, using each unit's own
switches, and count units that still link byte-identical to retail.
Usage: python pc/evidence/versus_compiler_experiments.py CL_PATH LABEL STEAM/Versus/System/SCCT_Versus.exe"""
import sys,json,subprocess,tempfile,collections,concurrent.futures as cf
from pathlib import Path
repo=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(repo/'tools'))
from manifests import load_target
from progress import built_unit_bytes,span,verify
CL=sys.argv[1]
pc=repo/'pc';t=load_target(pc/'config/steam-252084-versus.json')
original=verify(t,Path(sys.argv[-1]))
groups=collections.defaultdict(list)
for u in t['units']:
    if 'match' not in u or '13.10.3052' not in u['toolchain']:continue
    toks=u['build_command'].split()
    flags=tuple(x for x in toks if x.startswith('/') and not x.startswith(('/Fo','/c','/nologo')))
    groups[flags,toks[-1]].append(u)
tmp=Path(tempfile.mkdtemp())
def run(item):
    (flags,src),units=item
    o=tmp/f'{abs(hash((src,flags)))}.obj'
    r=subprocess.run([CL,'/nologo',*flags,'/c','/Fo'+str(o),src],cwd=pc,capture_output=True,text=True)
    res=collections.Counter(units=len(units),bytes=sum(u['size'] for u in units))
    if r.returncode:res['compile_fail']=len(units);return flags,res,[]
    obj=o.read_bytes();o.unlink();ok=[]
    for u in units:
        try:
            a,b=span(u['offset'],u['size'],len(original))
            if built_unit_bytes(t,u,obj,original)==original[a:b]:res['ok']+=1;res['ok_bytes']+=u['size'];ok.append(u['id'])
        except Exception:pass
    return flags,res,ok
tot=collections.defaultdict(collections.Counter);allok=[]
with cf.ThreadPoolExecutor(12) as ex:
    for flags,res,ok in ex.map(run,groups.items()):tot[' '.join(flags)].update(res);allok+=ok
for k,v in sorted(tot.items(),key=lambda kv:-kv[1]['bytes']):print(f'{k:20s} {dict(v)}')
s=collections.Counter();[s.update(v) for v in tot.values()];print('TOTAL',dict(s))
print('reproduced:',json.dumps(sorted(allok)))
