"""Rebuild every Versus /O2-family and /O2 /GX source file under alternative switches with
13.10.3052 and count units that still link byte-identical to retail.
Usage: python pc/evidence/versus_flag_experiments.py CL_13.10.3052 STEAM/Versus/System/SCCT_Versus.exe"""
import sys,json,subprocess,tempfile,collections,concurrent.futures as cf
from pathlib import Path
repo=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(repo/'tools'))
from manifests import load_target
from progress import built_unit_bytes,span,verify
CL=sys.argv[1]
pc=repo/'pc';t=load_target(pc/'config/steam-252084-versus.json')
original=verify(t,Path(sys.argv[-1]))
O2={frozenset({'/O2','/Gy'}),frozenset({'/O2','/G6','/Gy'}),frozenset({'/O2','/G5','/Gy'})}
files=collections.defaultdict(list)
for u in t['units']:
    if 'match' not in u or '13.10.3052' not in u['toolchain']:continue
    toks=u['build_command'].split();fl=frozenset(x for x in toks if x.startswith('/') and not x.startswith(('/Fo','/c','/nologo')))
    if fl in O2:files['O2',toks[-1]].append(u)
    elif fl==frozenset({'/O2','/Gy','/GX'}):files['GX',toks[-1]].append(u)
V={'O2':[('/O2','/Gy'),('/O2','/G6','/Gy'),('/O2','/G5','/Gy'),('/O2','/GB','/Gy'),('/Ox','/Gy'),('/O2','/Oy-','/Gy'),('/O1','/Gy'),('/Od','/Gy')],
   'GX':[('/O2','/Gy','/GX'),('/O2','/Gy','/EHsc'),('/O2','/Gy','/EHa'),('/O2','/Gy'),('/O1','/Gy','/GX'),('/Ox','/Gy','/GX')]}
tmp=Path(tempfile.mkdtemp())
def run(job):
    (kind,src),units,flags=job
    o=tmp/f'{abs(hash((src,flags)))}.obj'
    r=subprocess.run([CL,'/nologo',*flags,'/c','/Fo'+str(o),src],cwd=pc,capture_output=True,text=True)
    n=len(units);nb=sum(u['size'] for u in units)
    if r.returncode:return kind,flags,n,0,nb,0
    obj=o.read_bytes();o.unlink();ok=okb=0
    for u in units:
        try:
            a,b=span(u['offset'],u['size'],len(original))
            if built_unit_bytes(t,u,obj,original)==original[a:b]:ok+=1;okb+=u['size']
        except Exception:pass
    return kind,flags,n,ok,nb,okb
jobs=[(k,us,f) for k,us in files.items() for f in V[k[0]]]
tot=collections.defaultdict(lambda:[0,0,0,0])
with cf.ThreadPoolExecutor(12) as ex:
    for kind,flags,n,ok,nb,okb in ex.map(run,jobs):
        x=tot[kind,flags];x[0]+=n;x[1]+=ok;x[2]+=nb;x[3]+=okb
for (k,f),v in sorted(tot.items()):print(k,' '.join(f),v)
