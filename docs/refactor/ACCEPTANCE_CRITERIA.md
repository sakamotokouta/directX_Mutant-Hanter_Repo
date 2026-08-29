# Acceptance Criteria

## Every task

- [ ] Original snapshot is unchanged.
- [ ] Task has one primary refactoring objective.
- [ ] No unrequested gameplay/visual/balance change.
- [ ] Changed ownership is documented.
- [ ] No newly introduced unexplained raw owning pointer.
- [ ] No asset/shader path change without a verified packaging reason.
- [ ] Relevant scripts were run.
- [ ] Windows build/run result is reported truthfully.
- [ ] `BEFORE_AFTER_LOG.md` updated for portfolio-significant changes.

## Phase 0 build gate

- [ ] `.sln` opens without broken project path.
- [ ] x64 Debug project resolves ImGui and Assimp paths.
- [ ] DirectX/D3DX prerequisites are documented.
- [ ] Shader source and compiled shader expectations are documented.
- [ ] Working directory for runtime assets is documented.
- [ ] Clean clone build instructions exist.

## Mechanical encoding gate

- [ ] All targeted first-party sources are valid UTF-8.
- [ ] No identifiers/string literal bytes changed unexpectedly.
- [ ] No code-format/logic edits mixed into encoding commit.

## Lifetime gate

- [ ] No `delete this` remains in refactored ownership path.
- [ ] Polymorphic deletion is safe.
- [ ] Owner/observer relationships are clear.
- [ ] UI child allocations are destroyed exactly once.
- [ ] COM resource release is exactly once or delegated to `ComPtr`.

## Manual smoke test

At minimum verify:

- [ ] launch/title
- [ ] scene transition/load
- [ ] player movement/camera/input
- [ ] normal attack chain
- [ ] avoidance/damage/heal
- [ ] special attacks
- [ ] enemy detect/chase/attack/death
- [ ] OBB collision behavior
- [ ] animation playback/blending
- [ ] shadow/rim/dissolve rendering
- [ ] HUD
- [ ] quest UI
- [ ] weapon/general store UI
- [ ] village interaction
- [ ] audio/BGM/SE
- [ ] result/game-over path
- [ ] clean exit
