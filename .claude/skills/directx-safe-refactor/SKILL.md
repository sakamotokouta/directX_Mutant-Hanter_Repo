---
name: directx-safe-refactor
description: Behavior-preserving refactoring workflow for the legacy DirectX 11 C++ portfolio project. Use for ownership, RAII, decomposition, naming, state cleanup, or architecture refactors where preserving original gameplay/rendering behavior matters.
---

# DirectX Safe Refactor

## Inputs
- One target refactoring objective
- Relevant source files
- Current exec plan if the change is non-trivial

## Workflow
1. Read root `CLAUDE.md` and only the relevant analysis/refactor documents.
2. Identify owners, observers, global dependencies, asset/shader paths, state transitions, update/draw order, and timing constants touched by the target.
3. Write behavior invariants before editing.
4. If the task spans multiple risky files, create/update one focused exec plan.
5. Limit the patch to one primary concern.
6. Prefer extraction, RAII, and ownership clarification over rewrites.
7. Do not change gameplay constants, animation frame values, collision thresholds, render order, shader constants, or asset paths unless explicitly required.
8. Run applicable static checks, build, and smoke tests.
9. For risky multi-file changes, request the `refactor-reviewer` subagent after implementation.
10. Update `docs/portfolio/BEFORE_AFTER_LOG.md` if the change is portfolio-significant.

## Required final report
- Files changed
- Why each change was necessary
- Behavior invariants
- Validation actually run
- Remaining risk
- Next smallest recommended refactor

## Final checks
- `archive/original/**` unchanged
- No new unexplained owning raw pointer
- No new `delete this`
- No unrelated rename/formatting churn
- No claimed test that was not run
