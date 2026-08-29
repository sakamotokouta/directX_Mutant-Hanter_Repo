# Claude Code Task Prompts

Use these as starting prompts. `CLAUDE.md` remains the persistent project instruction source. Prefer invoking the matching skill when available.

## 0. First task — baseline only

```text
Use /build-reproducibility.
Perform Phase 0 only: establish an immutable original snapshot and make the repository/build layout reproducible for Visual Studio 2022 v143 x64 Debug without changing gameplay or C++ logic.

Inspect the .sln/.vcxproj, ImGui/Assimp locations, shader/runtime working-directory assumptions, and D3DX prerequisites. Create an exec plan before risky multi-file edits.
Do not modernize C++, rename classes, convert encoding, or migrate D3DX in this task.
After changes, report exact build commands attempted, whether they succeeded, unresolved blockers, and files changed.
```

## 1. Encoding normalization

```text
Perform only the encoding/line-ending part of Phase 1. Convert first-party C/C++ text to UTF-8 consistently according to .editorconfig. Do not rename symbols, reformat code broadly, or change logic/string contents. Run the encoding checker before and after and summarize any file that cannot be converted losslessly.
```

## 2. Resolve conflict copies

```text
Analyze every *-DESKTOP-2FSCGV3.* conflict copy against its base file. Use vcxproj membership, includes/references, behavior/build evidence, and Git history if available to decide canonical status. Do not delete materially different copies without evidence. Produce an exec plan and decision table first; then make only conflict-copy cleanup changes.
```

## 3. Remove delete-this ownership

```text
Use /directx-safe-refactor.
Refactor only the Scene/GameObject destruction path so GameObject never self-deletes. Preserve object update order and the public SetDestroy intent. Introduce the smallest safe owner-managed deletion design, add required virtual destructors, and do not refactor gameplay classes in the same task. Run applicable verification, then request the refactor-reviewer subagent for an independent read-only review.
```

## 4. Convert Scene object ownership

```text
Use /directx-safe-refactor.
After delete-this is removed, migrate Scene's owned GameObject collection to explicit unique ownership. Keep GetGameObject/GetGameObjects observer APIs behavior-compatible unless a small signature change is required and propagated safely. Do not convert unrelated observer pointers to shared_ptr. Validate scene transitions and destruction, then use refactor-reviewer.
```

## 5. Refactor Player in slices

```text
Use /directx-safe-refactor.
Characterize Player behavior first. Create a map of Player states, input conditions, animation names/frame counters, spawned effects, and collision side effects. Then extract exactly one responsibility from Player without changing constants, state transition order, or animation timing. One responsibility per task. Request refactor-reviewer after each risky slice.
```

## 6. Portfolio evidence review

```text
Use /portfolio-review.
Compare the original snapshot and current refactored code plus docs/portfolio/BEFORE_AFTER_LOG.md. Identify the five strongest reviewer-facing improvements supported by concrete diffs and validation evidence. Update the reviewer guide to clearly separate original author work, third-party dependencies/assets, and Claude Code-assisted refactoring work. Do not exaggerate.
```
