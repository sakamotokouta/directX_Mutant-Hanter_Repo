# DirectX Portfolio — Codex Refactoring Harness

This repository package is a **refactoring harness**, not a replacement for the original game. It was generated after a full inventory and static analysis of the submitted DirectX project (622 files, 178 first-party C/C++ files, 20,350 C/C++ lines in the source folder).

## Purpose

The portfolio story should be:

1. **Original implementation:** a self-built DirectX 11 game demonstrating rendering, animation, collision, combat, UI, audio, and scene/gameplay systems.
2. **Engineering analysis:** identify reproducibility, ownership, maintainability, and legacy-API risks without hiding the original code.
3. **Behavior-preserving refactor:** use Codex in small, reviewable phases governed by this harness.
4. **Evidence:** show before/after diffs, build/run checks, architecture notes, and decisions.

## Important naming note

Codex uses **`AGENTS.md`** (plural) as the repository instruction file. `AGENTS.ja.md` is the Japanese human-readable mirror. The English `AGENTS.md` is the canonical agent instruction source to avoid conflicting duplicated instructions.

## Start here

- Agent entry point: [`AGENTS.md`](AGENTS.md)
- Japanese guide: [`README.ja.md`](README.ja.md)
- Architecture: [`ARCHITECTURE.md`](ARCHITECTURE.md)
- Full analysis: [`docs/analysis/PROJECT_ANALYSIS.md`](docs/analysis/PROJECT_ANALYSIS.md)
- Refactor plan: [`docs/refactor/REFACTOR_PLAN.md`](docs/refactor/REFACTOR_PLAN.md)
- Acceptance gates: [`docs/refactor/ACCEPTANCE_CRITERIA.md`](docs/refactor/ACCEPTANCE_CRITERIA.md)
- Codex prompts: [`docs/prompts/CODEX_TASK_PROMPTS.md`](docs/prompts/CODEX_TASK_PROMPTS.md)
- Hiring reviewer guide: [`docs/portfolio/REVIEWER_GUIDE.md`](docs/portfolio/REVIEWER_GUIDE.md)
- All 622 files: [`docs/analysis/FULL_FILE_INVENTORY.csv`](docs/analysis/FULL_FILE_INVENTORY.csv)

## Recommended portfolio repository layout

```text
portfolio-directx/
├─ AGENTS.md
├─ AGENTS.ja.md
├─ ARCHITECTURE.md
├─ README.md
├─ README.ja.md
├─ archive/
│  └─ original/              # immutable snapshot of the submitted source/project
├─ src/                      # refactored first-party code
├─ shaders/                  # HLSL source
├─ assets/                   # distributable assets only after license review
├─ third_party/
│  ├─ assimp/
│  └─ imgui/
├─ docs/
└─ scripts/
```

Prefer a Git tag such as `original-submission` in addition to `archive/original/`. This gives reviewers both a simple side-by-side comparison and trustworthy history.

## Harness design basis

OpenAI's current Codex guidance treats `AGENTS.md` as persistent repository context, and OpenAI's harness-engineering guidance recommends keeping it short and using it as a table of contents into structured documentation. This package follows that pattern.

References:
- https://openai.com/index/harness-engineering/
- https://openai.com/index/unrolling-the-codex-agent-loop/
- https://openai.com/academy/skills/
