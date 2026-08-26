# Refactoring Plan

Each phase should be a separate pull request or small commit series. Do not skip validation gates just because a later phase appears more impressive.

## Phase 0 — Freeze and reproduce

Goal: make the original state trustworthy.

- Create `archive/original/` or an `original-submission` Git tag.
- Generate SHA-256 snapshot.
- Repair repository/project path layout without changing C++ behavior.
- Place `third_party/imgui`, `third_party/assimp`, `shaders`, and `assets` in explicit locations.
- Establish Visual Studio 2022 v143 x64 Debug build instructions.
- Record external prerequisites, including legacy D3DX handling.
- Capture manual smoke-test checklist.

Exit gate: another Windows machine can build/run, or every remaining blocker is documented precisely.

## Phase 1 — Mechanical hygiene

- Convert first-party text to UTF-8 in one mechanical change.
- Normalize line endings according to `.editorconfig`.
- Remove build outputs/user-specific files from version control after proving they are generated.
- Resolve `*-DESKTOP-2FSCGV3.*` conflict copies with evidence.
- Add `.gitignore` and third-party/license documentation.

No logic changes.

## Phase 2 — Lifetime foundations

- Add correct virtual destructors to polymorphic bases.
- Replace self-deletion (`delete this`) with scene-owned erase/destruction.
- Introduce explicit ownership for `Scene -> GameObject` and `GameObject -> Component`.
- Fix manually allocated UI child lifetime.
- Preserve observer pointers as non-owning pointers/references where appropriate.

Prefer `std::unique_ptr`; do not force `shared_ptr` unless ownership is genuinely shared.

## Phase 3 — Direct3D resource ownership

- Migrate focused classes from manual COM `Release()` to `Microsoft::WRL::ComPtr`.
- Start with leaf resources (sprites/effects), then renderer/model layers.
- Keep shader filenames, render states, constant-buffer values, and draw order unchanged.

## Phase 4 — Decompose large gameplay/UI functions

Target one class per task.

Suggested order:
1. `Player`
2. `Enemy`
3. `QuestDeskUi`
4. `WeaponStoreUi`
5. `VillageUi`
6. `Renderer::Init`
7. `AnimationModel::Update`

Extraction ideas: input collection, state transition, state update, animation selection, effect spawning, collision resolution, UI navigation, UI drawing.

## Phase 5 — Stronger state and data model

- Convert newly touched state enums to `enum class` where safe.
- Replace clusters of booleans with explicit state only after behavior is characterized.
- Move repeated asset paths and data constants into typed tables/config structs.
- Separate immutable definitions from runtime mutable state.

## Phase 6 — Module and naming cleanup

- Reorganize source into modules (`app`, `core`, `render`, `gameplay`, `ui`, `audio`, `assets`).
- Apply rename map in small batches.
- Correct high-value spelling issues without mixing semantic changes.

## Phase 7 — Optional legacy API modernization

Only after the game is stable and reviewable:

- Plan D3DX math migration to DirectXMath.
- Replace legacy D3DX texture helpers with a modern supported approach where necessary.
- Revisit dependency delivery using supported packages.

Keep this phase separate because it can touch math types throughout gameplay, collision, animation, and rendering.

## Phase 8 — Portfolio hardening

- Update `BEFORE_AFTER_LOG.md` for each major refactor.
- Create architecture diagrams/screenshots outside the code if useful.
- Add build/run instructions for reviewers.
- Add third-party notices and asset provenance.
- Keep a short “What I wrote / What libraries provide” section.
- Provide a short demo video if companies accept it.
