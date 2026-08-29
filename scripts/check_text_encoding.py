#!/usr/bin/env python3
from pathlib import Path
import argparse, sys

def main():
    ap=argparse.ArgumentParser();ap.add_argument('root',type=Path);a=ap.parse_args();bad=[];legacy=[]
    for p in sorted(a.root.rglob('*')):
        if p.suffix.lower() not in {'.cpp','.h','.hpp','.hlsl'}: continue
        b=p.read_bytes()
        try:b.decode('utf-8-sig');continue
        except UnicodeDecodeError:pass
        try:b.decode('cp932');legacy.append(p);continue
        except UnicodeDecodeError:bad.append(p)
    for p in legacy:print('CP932',p)
    for p in bad:print('UNKNOWN',p)
    if bad:sys.exit(2)
    if legacy:sys.exit(1)
    print('all target text is UTF-8 compatible')
if __name__=='__main__':main()
