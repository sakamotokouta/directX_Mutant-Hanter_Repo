# Project Analysis — DirectX Job Portfolio

## Scope and method

The entire submitted ZIP was enumerated. Every file is represented in `FULL_FILE_INVENTORY.csv` with path, category, byte size, SHA-256, extension, text encoding where applicable, and Visual Studio project-membership metadata for source-side files. First-party C/C++ files received additional static metrics in `SOURCE_METRICS.csv`.

No Windows DirectX build was executed in this Linux analysis environment, so build/runtime findings below distinguish **observed packaging facts** from behavior that still needs a Windows baseline test.

## Repository facts

- Total files: **622**
- Source-folder first-party C/C++ headers/sources: **178**
- C/C++ lines in source folder: **20,350**
- Source encodings: **{'cp932': 102, 'utf-8-sig': 76}**
- Raw `new` occurrences in first-party C/C++: **222**
- `delete` occurrences: **38**
- HLSL files in package: **11**
- Models: **41 FBX + 34 OBJ**
- Images: **121 PNG + 23 JPG + 1 JPEG**
- Audio: **25 WAV**

### Inventory by category

| Category | Files |
|---|---:|
| project-source | 178 |
| asset-model | 157 |
| asset-texture | 93 |
| third-party-assimp | 92 |
| asset-audio | 25 |
| third-party-imgui | 16 |
| compiled-shader-copy | 12 |
| runtime-binary | 12 |
| shader-source | 11 |
| build-artifact-debug | 10 |
| shader-binary | 8 |
| visual-studio-project | 3 |
| dependency-binary-copy | 2 |
| configuration | 1 |
| runtime-other | 1 |
| solution | 1 |

## What the original work demonstrates

The code is more substantial than a rendering sample. It contains a game loop, scene management, an object/component model, Direct3D 11 rendering, model loading, skeletal animation, CPU skinning, OBB collision, player combat, enemy state behavior, special attacks/effects, title/game/village/tutorial/result scenes, HUD/quest/store flows, XAudio2 audio, and HLSL effects including shadow mapping, rim lighting, and dissolve.

This breadth is a strong portfolio asset. The refactor should make it easier for reviewers to see these systems rather than replacing them.

## Highest-priority findings

### P0 — Build reproducibility/package structure

1. `solutionfile.sln` references project path `GM31 23.04.18\GM31 23.04.18.vcxproj`, but the submitted package stores the project under a differently named source folder. The solution is therefore not self-consistent as packaged.
2. The `.vcxproj` lists `imgui\...` files relative to the project directory, but the submitted ImGui sources are under the separate runtime/execution folder. The listed relative paths are missing from the source project directory.
3. `animationModel.h` includes `assimp/...`, while the Assimp headers are also packaged under the runtime/execution folder. No explicit `AdditionalIncludeDirectories` was observed in the project settings extracted during analysis.
4. The project uses toolset `v143`/Windows 10, but the solution header identifies Visual Studio 15. This is not necessarily fatal, but it is confusing for reviewers and should be regenerated or documented.
5. Compiled artifacts (`.exe`, `.pdb`, `.cso`, `.dll`, debug logs) are mixed with source/package content.

**Portfolio implication:** Phase 0 should first create a clean, reproducible repository layout and a documented x64 Debug build before deep refactoring.

### P0 — Third-party/content licensing evidence is missing

No license/credits/readme file was found alongside the included models, textures, audio, Assimp copy, or ImGui copy. Several asset names look externally sourced. This does not prove a licensing problem, but publishing the whole project to employers/GitHub without provenance documentation is risky.

Create a `THIRD_PARTY_NOTICES.md` and asset provenance table before public distribution. If an asset license cannot be verified, replace or omit that asset from the public portfolio package while retaining private evidence where permitted.

### P1 — Ownership/lifetime safety

Observed patterns include raw owning pointers, explicit `new/delete`, COM `Release`, and manual `Init/Uninit` conventions.

Specific high-risk examples:

- `GameObject::Destroy()` calls `Uninit(); delete this;` and is invoked inside `Scene::Update()`'s `remove_if` predicate. Self-deletion makes lifetime reasoning fragile.
- `Scene` owns `GameObject*` and manually deletes them; `GameObject` owns `Component*` and manually deletes them.
- Polymorphic base classes `Scene`, `GameObject`, and `Component` do not define explicit virtual destructors in the observed code.
- Several UI classes allocate many `Sprit2D` objects with `new`, but their `Uninit()` methods call `Uninit()` without corresponding `delete`, indicating likely heap leaks unless ownership exists elsewhere (none is evident in those fields).
- Direct3D COM objects are released manually across many classes, increasing error-path and partial-init risk.

### P1 — Large functions and mixed responsibilities

| File | Lines | Encoding | `new` | `delete` |
|---|---:|---|---:|---:|
| `player.cpp` | 1513 | cp932 | 1 | 1 |
| `villageUi-DESKTOP-2FSCGV3.cpp` | 1206 | cp932 | 65 | 0 |
| `enemy.cpp` | 866 | cp932 | 1 | 1 |
| `weaponStoreUi.cpp` | 606 | cp932 | 26 | 0 |
| `renderer.cpp` | 578 | cp932 | 2 | 2 |
| `animationModel.cpp` | 557 | cp932 | 5 | 5 |
| `model.cpp` | 551 | cp932 | 8 | 8 |
| `villageUi.cpp` | 520 | cp932 | 22 | 0 |
| `questDeskUi.cpp` | 412 | cp932 | 11 | 0 |
| `questDeskUi-DESKTOP-2FSCGV3.cpp` | 357 | cp932 | 11 | 0 |
| `weapon.cpp` | 353 | cp932 | 2 | 1 |
| `generalStoreUi.cpp` | 296 | cp932 | 11 | 0 |

Notable function sizes found by static brace scanning include approximately:

- `Player::UpdateGround()` — ~494 lines
- `Renderer::Init()` — ~302 lines
- `QuestDeskUi::Update()` — ~258 lines
- `AnimationModel::Update()` — ~240 lines
- `Player::Update()` — ~236 lines
- `WeaponStoreUi::Update()` — ~230 lines
- `VillageUi::Update()` — ~219 lines in the canonical-looking non-DESKTOP copy
- `CollisionBox::SetOBB()` — ~154 lines

These functions are strong candidates for extraction **after** baseline safety work.

### P1 — Conflict-copy / duplicate files

| Conflict copy | Base copy | Line similarity | Lines |
|---|---|---:|---:|
| `villageUi-DESKTOP-2FSCGV3.cpp` | `villageUi.cpp` | 58.9% | 1206/520 |
| `questDeskUi-DESKTOP-2FSCGV3.h` | `questDeskUi.h` | 91.3% | 83/90 |
| `questDeskUi-DESKTOP-2FSCGV3.cpp` | `questDeskUi.cpp` | 87.4% | 357/412 |

The `villageUi-DESKTOP-2FSCGV3.cpp` copy is materially different from `villageUi.cpp`, so it must not be auto-deleted. Determine canonical behavior from project membership, build history, executable behavior, and/or Git history before cleanup. The project file does not list the DESKTOP copies, which is useful evidence but not sufficient by itself for destructive deletion.

### P1 — Encoding and line-ending consistency

The first-party C/C++ tree mixes CP932 and UTF-8-with-BOM. Comments contain Japanese text. Convert to UTF-8 in a dedicated mechanical commit with **no semantic edits**, then verify byte-level diffs are limited to encoding/line endings where expected.

### P2 — Naming/readability

Examples observed in identifiers/files include `collitionBox`, `baceCampObj`, `sprit2D`, `recepitionPointer`, `Sutamina`, `Damege`, `Rondom`, `Flame` where `Frame` appears intended, and various abbreviated flags/counters. These make review harder but should be fixed in controlled rename-only batches with a mapping.

### P2 — Legacy DirectX utility dependency

`main.h` includes `d3dx9.h` and `d3dx11.h` and links `d3dx9.lib`/`d3dx11.lib`. Microsoft documents D3DX as deprecated/legacy and recommends DirectXMath and other modern replacements. For a portfolio, migrating can be valuable, but it should be a **late isolated phase**, not mixed into behavior-preserving structural refactors.

Microsoft references:
- https://learn.microsoft.com/en-us/windows/win32/dxmath/pg-xnamath-migration-d3dx
- https://learn.microsoft.com/en-us/windows/win32/direct3d11/d3d11-graphics-reference-d3dx11

### P2 — Hard-coded data and UI state complexity

Many asset paths, UI coordinates, animation frame values, quest conditions, prices, and flags are embedded directly in code. The store/quest UI classes contain many individual sprite pointers and booleans. A later refactor can introduce data tables/config structs and explicit state types, but this should follow ownership cleanup to avoid simultaneous logic changes.

## Recommended refactoring targets, in order

1. Packaging/build reproducibility and dependency layout.
2. Immutable original snapshot + automated inventory/hashes.
3. Encoding/line ending normalization only.
4. Conflict-copy resolution and build-artifact cleanup.
5. Ownership model: virtual destructors, remove `delete this`, `unique_ptr` for object/component/UI ownership.
6. COM lifetime with `ComPtr` in focused layers.
7. Break up `Player`, UI, `Renderer::Init`, and animation update using extraction while preserving constants/order.
8. Introduce stronger state types and centralized constants/data.
9. Improve module/directory boundaries and naming.
10. Optional D3DX modernization to DirectXMath/modern helper libraries.
11. Portfolio documentation and before/after evidence.

## What not to do

- Do not ask Codex to “modernize the whole project” in one prompt.
- Do not remove all raw pointers indiscriminately; distinguish owners from observers.
- Do not replace custom systems with an engine or framework.
- Do not change combat timing, animation frames, collision math, shaders, and file layout in the same patch.
- Do not publish third-party assets before license/provenance review.

## Complete machine-readable evidence

- `FULL_FILE_INVENTORY.csv`: all submitted files.
- `SOURCE_METRICS.csv`: all first-party `.cpp/.h/.hpp` source-side files.
- `DUPLICATE_REPORT.md`: conflict-copy details.
