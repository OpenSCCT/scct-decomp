"""Rebuild every Campaign /O2 /Gy and /O2 /Gy /EHa source file under alternative switches
and count the units that still link byte-identical to retail.

Usage: python pc/evidence/flag_experiments.py PATH_TO_CL_13.10.3052 PATH_TO_splintercell3.exe
"""
import sys,json,subprocess,tempfile,collections,concurrent.futures as cf
from pathlib import Path
repo=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(repo/'tools'))
from manifests import load_target
from progress import built_unit_bytes,span,verify
VC71=sys.argv[1]
pc=repo/'pc';t=load_target(pc/'config/steam-252084-campaign.json')
original=verify(t,Path(sys.argv[2]))
files=collections.defaultdict(list)
for u in t['units']:
    if 'match' not in u or '13.10.3052' not in u['toolchain']:continue
    fl=frozenset(x for x in u['build_command'].split() if x.startswith('/') and not x.startswith(('/Fo','/c','/nologo')))
    if fl==frozenset({'/O2','/Gy'}):files['O2',u['inputs'][0]].append(u)
    elif fl==frozenset({'/O2','/Gy','/EHa'}):files['EHa',u['inputs'][0]].append(u)
V={'O2':[('/O2','/Gy'),('/Ox','/Gy'),('/O2','/G6','/Gy'),('/O2','/G5','/Gy'),('/O2','/GB','/Gy'),('/O1','/Gy'),('/Od','/Gy'),('/O2','/Oy-','/Gy')],
   'EHa':[('/O2','/Gy','/EHa'),('/O2','/Gy','/GX'),('/O2','/Gy','/EHs'),('/O1','/Gy','/EHa'),('/Ox','/Gy','/EHa')]}
tmp=Path(tempfile.mkdtemp())
def run(job):
    (kind,src),units,flags=job
    o=tmp/f'{abs(hash((src,flags)))}.obj'
    r=subprocess.run([VC71,'/nologo',*flags,'/c','/Fo'+str(o),src],cwd=pc,capture_output=True,text=True)
    if r.returncode:return kind,flags,len(units),0,sum(u['size'] for u in units),0
    obj=o.read_bytes();ok=okb=0
    for u in units:
        try:
            a,b=span(u['offset'],u['size'],len(original))
            if built_unit_bytes(t,u,obj,original)==original[a:b]:ok+=1;okb+=u['size']
        except Exception:pass
    o.unlink()
    return kind,flags,len(units),ok,sum(u['size'] for u in units),okb
jobs=[(k,us,f) for k,us in files.items() for f in V[k[0]]]
tot=collections.defaultdict(lambda:[0,0,0,0,0])
with cf.ThreadPoolExecutor(12) as ex:
    for kind,flags,n,ok,nb,okb in ex.map(run,jobs):
        x=tot[kind,flags];x[0]+=n;x[1]+=ok;x[2]+=nb;x[3]+=okb;x[4]+=1
res=[dict(group=k,flags=' '.join(f),files=v[4],units=v[0],identical_units=v[1],bytes=v[2],identical_bytes=v[3]) for (k,f),v in sorted(tot.items())]
for r in res:print(r)
