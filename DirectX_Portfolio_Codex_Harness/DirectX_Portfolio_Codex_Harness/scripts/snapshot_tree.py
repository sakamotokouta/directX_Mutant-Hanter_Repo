#!/usr/bin/env python3
"""Snapshot file SHA-256 hashes so archive/original can be proven unchanged."""
from pathlib import Path
import argparse, hashlib, json

def digest(p):
    h=hashlib.sha256()
    with p.open('rb') as f:
        for c in iter(lambda:f.read(1024*1024),b''):h.update(c)
    return h.hexdigest()

def main():
    ap=argparse.ArgumentParser();ap.add_argument('root',type=Path);ap.add_argument('-o','--output',type=Path,default=Path('snapshot.json'));a=ap.parse_args()
    data={p.relative_to(a.root).as_posix():digest(p) for p in sorted(a.root.rglob('*')) if p.is_file()}
    a.output.write_text(json.dumps(data,indent=2,ensure_ascii=False),encoding='utf-8')
    print(f'wrote {len(data)} hashes to {a.output}')
if __name__=='__main__':main()
