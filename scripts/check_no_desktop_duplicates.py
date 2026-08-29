#!/usr/bin/env python3
from pathlib import Path
import argparse,sys
ap=argparse.ArgumentParser();ap.add_argument('root',type=Path);a=ap.parse_args()
files=[p for p in a.root.rglob('*') if p.is_file() and '-DESKTOP-' in p.name]
for p in files:print(p)
if files:sys.exit(1)
print('no machine-name conflict copies found')
