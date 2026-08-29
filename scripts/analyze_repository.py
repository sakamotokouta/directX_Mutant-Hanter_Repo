#!/usr/bin/env python3
"""Create a deterministic repository inventory without external dependencies."""
from pathlib import Path
import argparse, csv, hashlib

def digest(path):
    h=hashlib.sha256()
    with path.open('rb') as f:
        for chunk in iter(lambda:f.read(1024*1024),b''): h.update(chunk)
    return h.hexdigest()

def detect_text(path):
    data=path.read_bytes()
    for enc in ('utf-8-sig','utf-8','cp932'):
        try: return enc, len(data.decode(enc).splitlines())
        except UnicodeDecodeError: pass
    return 'binary/unknown',''

def main():
    ap=argparse.ArgumentParser(); ap.add_argument('root',type=Path); ap.add_argument('-o','--output',type=Path,default=Path('inventory.csv')); a=ap.parse_args()
    rows=[]
    for p in sorted(a.root.rglob('*')):
        if not p.is_file(): continue
        enc,lines=detect_text(p) if p.suffix.lower() in {'.cpp','.h','.hpp','.hlsl','.md','.sln','.vcxproj','.filters','.ini'} else ('binary/unknown','')
        rows.append({'path':p.relative_to(a.root).as_posix(),'size_bytes':p.stat().st_size,'extension':p.suffix.lower(),'sha256':digest(p),'encoding':enc,'lines':lines})
    a.output.parent.mkdir(parents=True,exist_ok=True)
    with a.output.open('w',newline='',encoding='utf-8-sig') as f:
        w=csv.DictWriter(f,fieldnames=rows[0].keys());w.writeheader();w.writerows(rows)
    print(f'wrote {len(rows)} files to {a.output}')
if __name__=='__main__': main()
