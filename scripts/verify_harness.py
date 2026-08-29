#!/usr/bin/env python3
from pathlib import Path
import json
import sys

root = Path(__file__).resolve().parents[1]
required = [
    'CLAUDE.md', 'CLAUDE.ja.md', 'ARCHITECTURE.md', 'README.md', 'README.ja.md',
    'docs/claude/USAGE.md', 'docs/claude/USAGE.ja.md',
    'docs/analysis/PROJECT_ANALYSIS.md', 'docs/analysis/PROJECT_ANALYSIS.ja.md',
    'docs/analysis/FULL_FILE_INVENTORY.csv', 'docs/analysis/SOURCE_METRICS.csv',
    'docs/refactor/REFACTOR_PLAN.md', 'docs/refactor/ACCEPTANCE_CRITERIA.md',
    'docs/prompts/CLAUDE_TASK_PROMPTS.md', 'docs/prompts/CLAUDE_TASK_PROMPTS.ja.md',
    '.claude/settings.json', '.claude/hooks/protect-original.ps1',
    '.claude/skills/directx-safe-refactor/SKILL.md',
    '.claude/skills/build-reproducibility/SKILL.md',
    '.claude/skills/portfolio-review/SKILL.md',
    '.claude/rules/cpp-safety.md', '.claude/rules/shader-safety.md',
    '.claude/rules/visual-studio-project.md',
    '.claude/agents/refactor-reviewer.md',
]

missing = [x for x in required if not (root / x).exists()]
if missing:
    print('missing:')
    for x in missing:
        print(' -', x)
    sys.exit(1)

try:
    json.loads((root / '.claude/settings.json').read_text(encoding='utf-8'))
except Exception as exc:
    print('invalid .claude/settings.json:', exc)
    sys.exit(1)

claude_lines = (root / 'CLAUDE.md').read_text(encoding='utf-8').splitlines()
if len(claude_lines) > 200:
    print(f'warning: CLAUDE.md has {len(claude_lines)} lines; keep always-on instructions concise')

if (root / '.codex').exists():
    print('unexpected Codex configuration directory remains: .codex')
    sys.exit(1)

print('Claude Code harness structure OK')
print('CLAUDE.md lines:', len(claude_lines))
