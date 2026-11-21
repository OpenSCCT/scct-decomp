"""Rebuild every Versus unit built with VC7.0 13.00.9466 under alternative switches and count
units that still link byte-identical to retail. Link-time code generation units (/GL) are
linked again into their DLL with the LINK.EXE beside the compiler.
Usage: python pc/evidence/versus_vc70_flag_experiments.py CL_13.00.9466 STEAM/Versus/System/SCCT_Versus.exe"""
import sys, subprocess, tempfile, collections, concurrent.futures as cf
from pathlib import Path
repo = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(repo / 'tools'))
from manifests import load_target
from progress import built_unit_bytes, span, verify
from link_image import link_arguments, stub_object

CL = sys.argv[1]
LINK = str(Path(CL).with_name('LINK.EXE'))
pc = repo / 'pc'
t = load_target(pc / 'config/steam-252084-versus.json')
original = verify(t, Path(sys.argv[-1]))

FAMILIES = {
    'O2': ('/O2', '/Gy'), 'GX': ('/O2', '/Gy', '/GX'),
    'LTCG O2': ('/O2', '/Gy', '/GL'), 'LTCG GX': ('/O2', '/Gy', '/GX', '/GL'),
    'LTCG Ob1': ('/O2', '/Ob1', '/Gy', '/GL'), 'LTCG Ob1 GX': ('/O2', '/Ob1', '/Gy', '/GX', '/GL'),
}
VARIANTS = {
    'O2': [('/O2', '/Gy'), ('/O2', '/G6', '/Gy'), ('/O2', '/G5', '/Gy'), ('/Ox', '/Gy'), ('/O2', '/Oy-', '/Gy'),
           ('/O1', '/Gy'), ('/Od', '/Gy')],
    'GX': [('/O2', '/Gy', '/GX'), ('/O2', '/Gy', '/EHa'), ('/O2', '/Gy'), ('/O1', '/Gy', '/GX'), ('/Ox', '/Gy', '/GX'),
           ('/O2', '/Oy-', '/Gy', '/GX')],
    'LTCG O2': [('/O2', '/Gy', '/GL'), ('/O2', '/Gy'), ('/Ox', '/Gy', '/GL'), ('/O2', '/Oy-', '/Gy', '/GL'),
                ('/O1', '/Gy', '/GL'), ('/Od', '/Gy', '/GL')],
    'LTCG GX': [('/O2', '/Gy', '/GX', '/GL'), ('/O2', '/Gy', '/GX'), ('/O2', '/Gy', '/EHa', '/GL'), ('/O2', '/Gy', '/GL'),
                ('/Ox', '/Gy', '/GX', '/GL'), ('/O1', '/Gy', '/GX', '/GL')],
    'LTCG Ob1': [('/O2', '/Ob1', '/Gy', '/GL'), ('/O2', '/Gy', '/GL'), ('/O2', '/Ob0', '/Gy', '/GL'), ('/O2', '/Ob1', '/Gy'),
                 ('/O1', '/Ob1', '/Gy', '/GL'), ('/O2', '/Ob1', '/Oy-', '/Gy', '/GL')],
    'LTCG Ob1 GX': [('/O2', '/Ob1', '/Gy', '/GX', '/GL'), ('/O2', '/Gy', '/GX', '/GL'), ('/O2', '/Ob0', '/Gy', '/GX', '/GL'),
                    ('/O2', '/Ob1', '/Gy', '/GX'), ('/O2', '/Ob1', '/Gy', '/GL'), ('/O1', '/Ob1', '/Gy', '/GX', '/GL')],
}
groups = collections.defaultdict(list)
for u in t['units']:
    if 'match' not in u or '13.00.9466' not in u['toolchain']: continue
    toks = u['build_command'].split()
    fl = frozenset(x for x in toks if x.startswith('/') and not x.startswith(('/Fo', '/c', '/nologo')))
    kind = next((k for k, f in FAMILIES.items() if frozenset(f) == fl), None)
    if kind: groups[kind, toks[-1]].append(u)

tmp = Path(tempfile.mkdtemp())

def run(job):
    (kind, src), units, flags = job
    o = tmp / f'{abs(hash((src, flags)))}.obj'
    r = subprocess.run([CL, '/nologo', *flags, '/c', '/Fo' + str(o), src], cwd=pc, capture_output=True, text=True)
    n = len(units); nb = sum(u['size'] for u in units); ok = okb = 0
    if r.returncode: return kind, flags, n, 0, nb, 0
    obj = o.read_bytes()
    for i, u in enumerate(units):
        try:
            built = obj
            if 'ltcg_link' in u:
                stubs = o.with_name(f'{o.stem}_{i}_stubs.obj'); dll = o.with_name(f'{o.stem}_{i}.dll')
                stubs.write_bytes(stub_object(u['ltcg_link']['stubs']))
                subprocess.run([LINK, *link_arguments(u['ltcg_link']), '/OUT:' + str(dll), str(o), str(stubs)],
                               capture_output=True, check=True)
                built = dll.read_bytes()
            a, b = span(u['offset'], u['size'], len(original))
            if built_unit_bytes(t, u, built, original) == original[a:b]: ok += 1; okb += u['size']
        except Exception:
            pass
    return kind, flags, n, ok, nb, okb

jobs = [(k, us, f) for k, us in groups.items() for f in VARIANTS[k[0]]]
tot = collections.defaultdict(lambda: [0, 0, 0, 0])
with cf.ThreadPoolExecutor(12) as ex:
    for kind, flags, n, ok, nb, okb in ex.map(run, jobs):
        x = tot[kind, flags]; x[0] += n; x[1] += ok; x[2] += nb; x[3] += okb
for (k, f), v in sorted(tot.items()):
    print(f'{k:8} | {" ".join(f):24} | units {v[1]}/{v[0]} | bytes {v[3]}/{v[2]}')
