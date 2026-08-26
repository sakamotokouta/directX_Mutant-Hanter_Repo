# AGENTS.md — DirectX Portfolio Refactoring Rules

## Mission

Preserve the behavior and authorship evidence of the original DirectX 11 game while improving build reproducibility, maintainability, safety, and reviewer readability through small, auditable changes.

This is a portfolio refactor. **Do not rewrite the game from scratch.** The value is the traceable transformation from original code to improved code.

## Source of truth map

Read only what is relevant to the task, in this order:

1. `docs/analysis/PROJECT_ANALYSIS.md` — observed repository facts and risks.
2. `ARCHITECTURE.md` — current system map and boundaries.
3. `docs/refactor/REFACTOR_PLAN.md` — required phase order.
4. `docs/refactor/ACCEPTANCE_CRITERIA.md` — validation gates.
5. `docs/design-docs/core-beliefs.md` — design constraints.
6. `docs/exec-plans/` — active task plan and decision log.
7. Relevant skill under `.codex/skills/` for repeatable workflows.

Japanese mirrors (`*.ja.md`) are for human review. Treat the English documents as canonical for agent execution unless the user explicitly says otherwise.

## Non-negotiable guardrails

- Never modify `archive/original/**` after the baseline snapshot is created.
- Never combine gameplay changes with refactoring in the same task.
- Never perform a broad rename, encoding conversion, ownership rewrite, and directory move in one patch.
- Keep one primary refactoring theme per task.
- Do not delete an asset, shader, library, or duplicate-looking file until its build/runtime usage is proven.
- Do not claim a build or runtime test passed unless it was actually run.
- If Windows/DirectX execution is unavailable, perform static checks and explicitly report the limitation.
- Preserve visible game behavior unless the task explicitly authorizes a behavior change.
- Preserve original credits and third-party notices. Do not publish assets until licensing is reviewed.
- Do not replace first-party code with a new engine/framework merely to reduce line count.

## Baseline first

Before structural refactoring:

1. Create/verify the immutable original snapshot.
2. Run `scripts/analyze_repository.py` and store the report.
3. Run `scripts/snapshot_tree.py` on the original source.
4. Establish the Windows x64 Debug build command or record why the provided project is not yet reproducible.
5. Capture a manual smoke-test checklist and screenshots/video externally if possible.

## Build target

Primary target: Windows + Visual Studio 2022 toolset (`v143`), x64 Debug first.

The analyzed project uses Direct3D 11 plus legacy D3DX headers/libraries, Assimp, Dear ImGui, XAudio2, and WinMM. Do not modernize all of these at once.

## Change protocol

For every task:

1. Inspect the relevant files and dependency edges.
2. Write/update a focused exec plan under `docs/exec-plans/` when the change spans multiple files or risks behavior.
3. State invariants that must remain true.
4. Make the smallest coherent change.
5. Run the required static/build/manual checks.
6. Update docs only when the code or known facts changed.
7. Report: changed files, behavior impact, validation evidence, remaining risk, and recommended next task.

## Refactoring order

Follow the phase order in `docs/refactor/REFACTOR_PLAN.md`. In particular:

- Fix packaging/build reproducibility before architectural modernization.
- Convert text encoding in a dedicated mechanical commit.
- Resolve conflict-copy files before relying on file names for architecture.
- Introduce RAII/ownership changes before large feature decomposition.
- Split `player.cpp`, UI state logic, animation code, and renderer initialization incrementally.
- Treat D3DX-to-DirectXMath migration as a later, isolated modernization phase.

## C++ rules for touched code

- Prefer explicit ownership: `std::unique_ptr` for sole ownership, references/non-owning pointers for observation.
- Prefer `Microsoft::WRL::ComPtr` for COM ownership when that migration phase is active.
- Add virtual destructors to polymorphic ownership bases before deleting through base pointers.
- Do not introduce new `delete this` patterns.
- Avoid new raw owning `new/delete`.
- Prefer `enum class` for newly introduced state enums.
- Prefer `constexpr` constants over new macros when practical.
- Use `const` correctness and references where it improves intent without broad churn.
- Keep gameplay constants unchanged during mechanical refactors.
- Do not silently change frame timing, collision tolerances, animation frame numbers, or shader constants.

## Naming and file moves

Existing misspellings are known (`collition`, `bace`, `sprit`, `flame`, etc.). Rename only in dedicated tasks with a mapping recorded in `docs/refactor/RENAME_MAP.md`. Keep behavior-only and rename-only diffs separate whenever possible.

## Verification

At minimum run applicable checks from `docs/refactor/ACCEPTANCE_CRITERIA.md`, including:

- harness self-check,
- encoding report,
- duplicate/conflict-copy report,
- source inventory diff,
- Windows build when available,
- manual smoke test for scene transitions, combat, UI, audio, collision, animation, and rendering.

## Portfolio evidence rule

Every meaningful refactor should produce reviewer-friendly evidence. Update `docs/portfolio/BEFORE_AFTER_LOG.md` with:

- problem,
- original code location,
- design decision,
- changed code location,
- measurable or explainable improvement,
- validation evidence,
- what was intentionally not changed.

## Stop conditions

Stop and report instead of guessing when:

- the original baseline cannot be located,
- two conflict-copy files differ materially and there is no evidence which one is canonical,
- an asset/license origin is unknown and publication is requested,
- a dependency path is missing and a build fix would require inventing a version,
- behavior preservation cannot be checked for a high-risk change.
