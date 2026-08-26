# Before / After Evidence Log

| ID | Problem | Original location | Decision | Refactored location/commit | Evidence | Behavior preserved? |
|---|---|---|---|---|---|---|
| 001 | Project would not build on a clean machine: `<d3dx9.h>`/`<d3dx11.h>` unresolved because the legacy DirectX SDK include/lib paths lived only in the original author's per-user global IDE settings, not in the checked-in `.vcxproj` | `GM31 23.04.18.vcxproj` (all 4 configs), `main.h:17-18` | Add `AdditionalIncludeDirectories`/`AdditionalLibraryDirectories`/`AdditionalDependencies` using the `$(DXSDK_DIR)` MSBuild macro (set automatically by the DirectX SDK installer) instead of a hardcoded machine path | `GM31 23.04.18.vcxproj` (Phase 0 commit, see `docs/exec-plans/2026-08-27-phase0-build-reproducibility.md`) | Full `MSBuild /t:Rebuild` for `Debug\|x64`: 0 errors before→after captured in exec plan; exe smoke-launched successfully | Yes — zero `.cpp`/`.h` changes, only build-configuration metadata |

For each entry, include a small diff/screenshot/link rather than a long essay.
