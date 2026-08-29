# Codex Task Prompts

Use these as starting prompts. `AGENTS.md` remains the persistent source of rules.

## 0. First task — baseline only

```text
Read AGENTS.md, docs/analysis/PROJECT_ANALYSIS.md, docs/refactor/REFACTOR_PLAN.md, and docs/refactor/ACCEPTANCE_CRITERIA.md.
Perform Phase 0 only: establish an immutable original snapshot and make the repository/build layout reproducible for Visual Studio 2022 v143 x64 Debug without changing gameplay or C++ logic.

First inspect the .sln/.vcxproj, ImGui/Assimp locations, shader/runtime working-directory assumptions, and D3DX prerequisites. Create an exec plan before edits.
Do not modernize C++, rename classes, convert encoding, or migrate D3DX in this task.
After changes, report exact build commands attempted, whether they succeeded, unresolved blockers, and files changed.
```

## 1. Encoding normalization

```text
Perform only the encoding/line-ending part of Phase 1. Convert first-party C/C++ text to UTF-8 consistently according to .editorconfig. Do not rename symbols, reformat code broadly, or change logic/string contents. Run the encoding checker before and after and summarize any file that cannot be converted losslessly.
```

## 2. Resolve conflict copies

```text
Analyze every *-DESKTOP-2FSCGV3.* conflict copy against its base file. Use vcxproj membership, includes/references, behavior/build evidence, and Git history if available to decide canonical status. Do not delete materially different copies without evidence. Produce an exec plan and a decision table first; then make only conflict-copy cleanup changes.
```

## 3. Remove delete-this ownership

```text
Refactor only the Scene/GameObject destruction path so GameObject never self-deletes. Preserve object update order and the public SetDestroy intent. Introduce the smallest safe owner-managed deletion design, add required virtual destructors, and do not refactor gameplay classes in the same task. Add/update focused tests or static verification where practical and run the manual smoke-test subset that can be executed.
```

## 4. Convert Scene object ownership

```text
After delete-this is removed, migrate Scene's owned GameObject collection to explicit unique ownership. Keep GetGameObject/GetGameObjects observer APIs behavior-compatible unless a small signature change is required and propagated safely. Do not convert unrelated observer pointers to shared_ptr. Validate scene transitions and destruction.
```

## 5. Refactor Player in slices

```text
Characterize Player behavior first. Create a map of Player states, input conditions, animation names/frame counters, spawned effects, and collision side effects. Then extract exactly one responsibility from Player (for example input collection or one state update) without changing constants, state transition order, or animation timing. One responsibility per task.
```

## 6. Portfolio evidence review

```text
Read the original snapshot and current refactored code plus docs/portfolio/BEFORE_AFTER_LOG.md. Identify the five strongest reviewer-facing improvements that are supported by concrete diffs and validation evidence. Do not exaggerate. Update the reviewer guide to clearly separate original author work, third-party dependencies, and AI-assisted refactoring work.
```
