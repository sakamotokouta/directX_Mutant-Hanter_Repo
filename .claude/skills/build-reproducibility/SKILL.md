---
name: build-reproducibility
description: Workflow for making the DirectX portfolio build reproducible on a clean Windows/Visual Studio environment without changing gameplay logic. Use for Phase 0, broken solution/project paths, dependency layout, working-directory assumptions, or clean-build setup.
---

# Build Reproducibility

## Goal
Make a clean-clone Windows + Visual Studio 2022 v143 x64 Debug build/run reproducible before architectural refactoring.

## Workflow
1. Read `CLAUDE.md`, the project analysis, refactor Phase 0, and acceptance criteria.
2. Inspect `.sln`, `.vcxproj`, `.filters`, source/runtime directory layout, relative includes, library paths, working directory, shaders, runtime DLLs, and asset paths.
3. Compare project-listed files with files on disk.
4. Establish one canonical target first: Visual Studio 2022 v143 x64 Debug.
5. Move/copy dependencies only into explicit `third_party/` or documented package locations; do not edit game logic.
6. Document D3DX/DirectX prerequisites rather than silently assuming the author's machine state.
7. Verify the runtime working directory resolves assets and shaders.
8. Run the exact build command if the Windows toolchain is available; otherwise document the precise blocker.
9. Record clean-build steps and remaining external prerequisites.

## Required output
- Build prerequisites
- Repository/project layout changes
- Exact build command or IDE steps attempted
- Success/failure evidence
- Runtime working-directory requirement
- Remaining blockers

## Prohibited in this skill
- C++ architecture refactor
- broad symbol rename
- encoding conversion
- D3DX-to-DirectXMath migration
- gameplay changes
