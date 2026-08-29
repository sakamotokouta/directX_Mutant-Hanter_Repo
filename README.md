# DirectX Portfolio — Claude Code Refactoring Harness

This package is a **Claude Code refactoring harness**, not a replacement for the original game. It is based on a full inventory/static analysis of the submitted DirectX project: 622 files, 178 first-party C/C++ files, and roughly 20,350 C/C++ lines in the source folder.

## Portfolio story

1. **Original implementation:** a self-built DirectX 11 game demonstrating rendering, animation, collision, combat, UI, audio, and scene/gameplay systems.
2. **Engineering analysis:** identify reproducibility, ownership, maintainability, and legacy-API risks without hiding the original code.
3. **Behavior-preserving refactor:** use Claude Code in small, reviewable phases governed by this harness.
4. **Evidence:** show before/after diffs, build/run checks, architecture notes, and design decisions.

## Why `CLAUDE.md`

Claude Code reads `CLAUDE.md` as project memory/instructions. Repeatable procedures belong in `.claude/skills/`, path-specific instructions belong in `.claude/rules/`, and deterministic enforcement belongs in hooks/settings.

The English files are canonical for Claude Code. Japanese mirrors are provided for human review without duplicating automatically loaded instructions.

## Start here

- Claude Code entry point: [`CLAUDE.md`](CLAUDE.md)
- Japanese mirror: [`CLAUDE.ja.md`](CLAUDE.ja.md)
- Claude Code usage: [`docs/claude/USAGE.md`](docs/claude/USAGE.md)
- Architecture: [`ARCHITECTURE.md`](ARCHITECTURE.md)
- Full analysis: [`docs/analysis/PROJECT_ANALYSIS.md`](docs/analysis/PROJECT_ANALYSIS.md)
- Refactor plan: [`docs/refactor/REFACTOR_PLAN.md`](docs/refactor/REFACTOR_PLAN.md)
- Acceptance gates: [`docs/refactor/ACCEPTANCE_CRITERIA.md`](docs/refactor/ACCEPTANCE_CRITERIA.md)
- Task prompts: [`docs/prompts/CLAUDE_TASK_PROMPTS.md`](docs/prompts/CLAUDE_TASK_PROMPTS.md)
- Hiring reviewer guide: [`docs/portfolio/REVIEWER_GUIDE.md`](docs/portfolio/REVIEWER_GUIDE.md)
- All 622 files: [`docs/analysis/FULL_FILE_INVENTORY.csv`](docs/analysis/FULL_FILE_INVENTORY.csv)

## Claude Code extensions included

```text
.claude/
├─ settings.json
├─ hooks/
│  └─ protect-original.ps1
├─ skills/
│  ├─ build-reproducibility/
│  ├─ directx-safe-refactor/
│  └─ portfolio-review/
├─ rules/
│  ├─ cpp-safety.md
│  ├─ shader-safety.md
│  └─ visual-studio-project.md
└─ agents/
   └─ refactor-reviewer.md
```

The `protect-original.ps1` PreToolUse hook denies direct Claude Code file writes to `archive/original/**` and blocks common shell mutation commands that target the original snapshot. It supplements, rather than replaces, the instruction in `CLAUDE.md`.

## Recommended portfolio repository layout

```text
portfolio-directx/
├─ CLAUDE.md
├─ CLAUDE.ja.md
├─ .claude/
├─ ARCHITECTURE.md
├─ README.md
├─ README.ja.md
├─ archive/
│  └─ original/              # immutable snapshot
├─ src/                      # refactored first-party code
├─ shaders/
├─ assets/                   # distributable assets only after license review
├─ third_party/
├─ docs/
└─ scripts/
```

Prefer a Git tag such as `original-submission` in addition to `archive/original/`.

## Recommended first session

1. Put this harness at the project root.
2. Start Claude Code from the repository root.
3. Run `/memory` and verify `CLAUDE.md` is loaded.
4. Run `/skills` and verify the three project skills are visible.
5. Run `/hooks` or `/doctor` to verify the project hook/configuration.
6. Invoke `/build-reproducibility` for Phase 0; do not start architectural refactoring first.

## Official Claude Code references

- Project memory / CLAUDE.md: https://code.claude.com/docs/en/memory
- Skills: https://code.claude.com/docs/en/skills
- Rules / extension model: https://code.claude.com/docs/en/features-overview
- Hooks: https://code.claude.com/docs/en/hooks-guide
- Subagents: https://code.claude.com/docs/en/sub-agents
