#!/usr/bin/env python3
from pathlib import Path
import sys
root=Path(__file__).resolve().parents[1]
required=[
 'AGENTS.md','AGENTS.ja.md','ARCHITECTURE.md','README.md','README.ja.md',
 'docs/analysis/PROJECT_ANALYSIS.md','docs/analysis/PROJECT_ANALYSIS.ja.md',
 'docs/analysis/FULL_FILE_INVENTORY.csv','docs/analysis/SOURCE_METRICS.csv',
 'docs/refactor/REFACTOR_PLAN.md','docs/refactor/ACCEPTANCE_CRITERIA.md',
 'docs/prompts/CODEX_TASK_PROMPTS.md',
 '.codex/skills/directx-safe-refactor/SKILL.md',
 '.codex/skills/build-reproducibility/SKILL.md',
 '.codex/skills/portfolio-review/SKILL.md']
missing=[x for x in required if not (root/x).exists()]
if missing:
 print('missing:');[print(' -',x) for x in missing];sys.exit(1)
print('harness structure OK')
