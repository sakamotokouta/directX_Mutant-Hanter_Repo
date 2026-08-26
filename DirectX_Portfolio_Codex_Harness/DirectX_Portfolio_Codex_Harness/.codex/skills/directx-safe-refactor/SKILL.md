---
name: directx-safe-refactor
description: Behavior-preserving refactoring workflow for the legacy DirectX 11 C++ portfolio project. Use for ownership, decomposition, naming, or architecture refactors while protecting original behavior.
---

# DirectX Safe Refactor

## Inputs
- Target refactoring objective
- Relevant source files
- Current exec plan if one exists

## Workflow
1. Read root `AGENTS.md` and relevant analysis/refactor docs.
2. Identify owners, observers, global dependencies, asset/shader paths, state transitions, and timing constants touched by the target.
3. Write behavior invariants before editing.
4. Limit the patch to one primary concern.
5. Prefer extraction and ownership clarification over rewrites.
6. Do not change gameplay constants, animation frame values, collision thresholds, render order, shader constants, or asset paths unless explicitly required.
7. Run applicable static checks/build/smoke tests.
8. Update `BEFORE_AFTER_LOG.md` if the change is portfolio-significant.

## Required final report
- Files changed
- Why each change was necessary
- Behavior invariants
- Validation actually run
- Remaining risk
- Next smallest recommended refactor

## Final checks
- Original snapshot unchanged
- No new unexplained owning raw pointer
- No new `delete this`
- No unrelated rename/formatting churn
- No claimed test that was not run
