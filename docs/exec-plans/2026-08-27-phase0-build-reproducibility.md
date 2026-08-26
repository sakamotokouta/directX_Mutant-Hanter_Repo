# Phase 0 — Freeze and reproduce (baseline + Windows x64 Debug build)

## Goal

Make the original submission trustworthy and establish a reproducible Windows x64 Debug build without changing any C++ logic, gameplay behavior, or asset content.

## In scope

- Immutable original snapshot (git tag).
- Repository-level analysis/inventory/encoding/duplicate reports.
- Diagnosing and fixing the Visual Studio build so it reproduces on a machine other than the original author's, using project-relative MSBuild macros only.
- Documenting remaining reproducibility caveats (working directory, legacy SDK prerequisite).

## Out of scope

- Any C++ logic change, renaming, encoding conversion, or directory restructuring (Phases 1+).
- Migrating away from D3DX/legacy DirectX SDK (Phase 7).

## Observed files/dependencies

- `GM31 23.04.18.vcxproj`: `PlatformToolset v143`, four configurations (Debug/Release × Win32/x64), no `.sln` file present.
- `main.h` includes `<d3dx9.h>` and `<d3dx11.h>` (legacy DirectX SDK, June 2010) with **no** `AdditionalIncludeDirectories`/`AdditionalLibraryDirectories`/`AdditionalDependencies` entries in the vcxproj for these.
- This machine has the legacy DirectX SDK unpacked at a personal path with a machine-level `DXSDK_DIR` environment variable pointing to it (`...OneDrive\デスクトップ\directx\`, containing the standard `Include/`, `Lib/x86/`, `Lib/x64/` layout of the June 2010 SDK).
- `imgui/` and `assimp/` are vendored directly under the project root as loose source folders (quoted `#include "assimp/..."` resolves without extra include dirs because MSVC searches the including file's directory first). `assimp-vc143-mt.dll/.lib` sit at project root; no `pragma comment(lib, ...)` or `AdditionalDependencies` references them, so linking presumably relies on default library search plus manual project setup outside the checked-in file — **not exercised in this pass** since assimp usage did not block the Debug|x64 build (needs confirmation if a task later touches model loading).
- Assets are loaded with relative paths (e.g. `"asset/model/..."`, `"asset/texture/..."`) with no `SetCurrentDirectory`/`GetModuleFileName` call in `main.cpp`, so the process's working directory must be the project root, not `x64\Debug\`.

## Behavior invariants

- No gameplay constant, shader, asset path, or draw order changes.
- Only MSBuild project settings touched; zero `.cpp`/`.h` edits.

## Planned steps

1. Create `original-submission` git tag over the untouched submission (source, assets, project files) before any edits.
2. Add `AdditionalIncludeDirectories`/`AdditionalLibraryDirectories`/`AdditionalDependencies` referencing `$(DXSDK_DIR)` (an MSBuild macro backed by the environment variable the DirectX SDK installer sets) to all four vcxproj configurations. This is project-relative, not an author-machine absolute path, per `.claude/rules/visual-studio-project.md`.
3. Rebuild `Debug|x64` from clean and capture the log.
4. Smoke-launch the built executable with working directory = project root and confirm it does not crash immediately.
5. Run `scripts/analyze_repository.py`, `scripts/check_text_encoding.py`, `scripts/check_no_desktop_duplicates.py`, `scripts/snapshot_tree.py`, `scripts/verify_harness.py` against a clean `git archive HEAD` snapshot and store the reports under `docs/analysis/`.

## Validation commands/checks

```
MSBuild.exe "GM31 23.04.18.vcxproj" /p:Configuration=Debug /p:Platform=x64 /t:Rebuild
```
Result: **0 errors**, warnings only (pre-existing `C4244`/`C4305`/`X3206`/`X3578`, unrelated to this change).

```
python scripts/verify_harness.py
```
Result: `Claude Code harness structure OK`.

Executable smoke test: launched `x64\Debug\GM31 23.04.18.exe` with working directory = project root; process stayed alive for 5s (no immediate crash/exit). Full manual gameplay smoke test (scene transitions, combat, UI, audio, collision, animation) still needs a human pass with a visible display — not performed by the agent in this session.

## Risks and rollback

- Risk: `$(DXSDK_DIR)` is undefined on a machine without the legacy DirectX SDK installed — build will fail identically to before, but now with a clear missing-include error instead of silently depending on undocumented per-user IDE state. This is a pre-existing dependency, not a new one; it is now explicit instead of implicit.
- Rollback: revert the single vcxproj commit; no other files touched.

## Result

Windows x64 Debug build is reproducible via `MSBuild.exe` alone (no Visual Studio IDE session required first) on any machine with VS2022 v143 tools and the legacy DirectX SDK (June 2010) installed with `DXSDK_DIR` set — which is what the SDK's own installer does automatically. Previously the project relied on undocumented, per-user global IDE property-sheet state that is not checked into the repository and not reproducible from a fresh clone.

## Validation evidence

- Build log before fix: `main.h(17,10): error C1083: ... 'd3dx9.h': No such file or directory`.
- Build log after fix: `GM31 23.04.18.vcxproj -> ...\x64\Debug\GM31 23.04.18.exe`, exit code 0, full rebuild.
- `docs/analysis/FULL_FILE_INVENTORY.csv`, `docs/analysis/ORIGINAL_TREE_SNAPSHOT.csv`, `docs/analysis/ENCODING_REPORT_before.txt`, `docs/analysis/DUPLICATE_COPY_SCAN.txt` generated from `git archive HEAD` (661 files = 622 original + 39 harness files).

## Follow-up

- Phase 1 (this session, next): UTF-8 encoding conversion for first-party CP932 files, conflict-copy resolution, `.gitignore` finalization.
- Not yet addressed: assimp linking configuration is undocumented in the vcxproj; revisit if/when a task touches model loading.
- Not yet addressed: running the exe outside the VS debugger requires manually setting the working directory to the project root; consider documenting this in a reviewer-facing run guide rather than changing asset-loading code (would be a behavior-risk change, out of scope here).
