---
name: build-reproducibility
description: Workflow for making the DirectX portfolio build reproducible on a clean Windows/Visual Studio environment without changing gameplay logic.
---

# Build Reproducibility

## Workflow
1. Inspect `.sln`, `.vcxproj`, source/runtime directory layout, relative includes, library paths, working directory, shaders, and runtime DLLs.
2. Compare project-listed files with files on disk.
3. Move/copy dependencies only into explicit `third_party/` or documented package locations; do not edit game logic.
4. Establish one canonical target first: Visual Studio 2022 v143 x64 Debug.
5. Document D3DX/DirectX prerequisites rather than silently assuming the author's machine state.
6. Verify the runtime working directory resolves `asset/` and `shader/` paths.
7. Record exact clean-build steps and any unresolved external prerequisite.

## Output
- Build prerequisites
- Repository layout changes
- Exact build command/IDE steps
- Success/failure evidence
- Runtime working-directory requirement
- Remaining blockers

## Prohibited
- C++ architecture refactor
- broad symbol rename
- encoding conversion
- D3DX-to-DirectXMath migration
- gameplay changes
