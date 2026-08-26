#!/usr/bin/env python3
from pathlib import Path
import argparse, hashlib, json, sys

def digest(p):
    h=hashlib.sha256()
    with p.open('rb') as f:
        for c in iter(lambda:f.read(1024*1024),b''):h.update(c)
    return h.hexdigest()

def main():
    ap=argparse.ArgumentParser();ap.add_argument('root',type=Path);ap.add_argument('snapshot',type=Path);a=ap.parse_args()
    old=json.loads(a.snapshot.read_text(encoding='utf-8'))
    now={p.relative_to(a.root).as_posix():digest(p) for p in sorted(a.root.rglob('*')) if p.is_file()}
    added=sorted(set(now)-set(old));removed=sorted(set(old)-set(now));changed=sorted(k for k in set(old)&set(now) if old[k]!=now[k])
    for label,items in [('ADDED',added),('REMOVED',removed),('CHANGED',changed)]:
        for x in items: print(label,x)
    if added or removed or changed: sys.exit(1)
    print('snapshot matches')
if __name__=='__main__':main()
