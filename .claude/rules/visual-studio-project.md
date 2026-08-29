---
paths:
  - "**/*.{sln,vcxproj,vcxproj.filters,props,targets}"
---

# Visual Studio Project Rules

- Primary target is Visual Studio 2022, MSVC v143, x64 Debug first.
- Prefer project-relative include/library/runtime paths over author-machine absolute paths.
- Do not silently invent missing dependency versions.
- Keep source membership and on-disk files consistent; investigate conflict-copy files before removal.
- Build-layout fixes must not include gameplay/C++ architecture refactors.
- Record any required Windows SDK, D3DX, Assimp, ImGui, XAudio2, or runtime DLL prerequisite explicitly.
