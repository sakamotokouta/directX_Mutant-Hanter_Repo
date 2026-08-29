# Claude Code Harness Usage

## 1. Verify project memory

Start Claude Code at the repository root, then use `/memory`. Confirm that root `CLAUDE.md` is loaded. `CLAUDE.ja.md` is intentionally not an automatic instruction file.

## 2. Verify skills

Use `/skills`. The project should expose:

- `/build-reproducibility`
- `/directx-safe-refactor`
- `/portfolio-review`

Skills live under `.claude/skills/<name>/SKILL.md`. Invoke them explicitly when you want the exact workflow; Claude may also select them automatically when the description matches the task.

## 3. Verify rules

Rules in `.claude/rules/` are path-scoped. Claude Code loads them when relevant files are read:

- C/C++ lifetime and behavior-preservation rules
- HLSL shader invariants
- Visual Studio project/build-file rules

Japanese mirrors are stored under `docs/claude/rules-ja/` so they do not duplicate active instructions.

## 4. Verify original-snapshot protection

Project `.claude/settings.json` registers a PreToolUse hook implemented by `.claude/hooks/protect-original.ps1`.

On Windows, run `/hooks` or `/doctor` to verify it is active. The hook blocks Claude Code `Write`/`Edit` operations under `archive/original/**` and common shell mutation commands targeting that path.

Do not deliberately bypass the hook. If the original snapshot genuinely must change, create a new baseline intentionally and update the portfolio history rather than mutating the old snapshot.

## 5. Use the read-only reviewer

For a risky multi-file refactor, ask Claude to use the `refactor-reviewer` subagent after implementation. It is intentionally limited to read-oriented tools and should return findings, not edit the code.

You can inspect available agents with `/agents`.

## 6. Recommended phase workflow

1. `/build-reproducibility`
2. Phase 1 mechanical hygiene
3. `/directx-safe-refactor` for one ownership/refactor objective at a time
4. independent `refactor-reviewer` check for risky changes
5. validation/build/smoke tests
6. update `BEFORE_AFTER_LOG.md`
7. `/portfolio-review` before submission

## 7. Useful diagnostics

- `/memory` — loaded CLAUDE.md/rules/memory
- `/skills` — available skills
- `/agents` — custom/built-in subagents
- `/hooks` — active hooks
- `/doctor` — configuration diagnostics

## 8. Local-only preferences

Put personal paths or machine-specific preferences in `CLAUDE.local.md` or `.claude/settings.local.json`; both should remain out of Git. Do not place author-machine absolute paths into the shared `CLAUDE.md`.
