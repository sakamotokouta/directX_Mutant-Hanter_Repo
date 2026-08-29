# Reviewer Guide

## What this portfolio is intended to demonstrate

This project intentionally contains both the original implementation and a refactored evolution. The goal is not to hide student/early-career code; it is to show the ability to understand a non-trivial self-built codebase, identify risk, control an AI coding agent, improve architecture incrementally, and verify behavior.

## Original implementation highlights

- Win32 + Direct3D 11 application and renderer
- HLSL rendering effects: shadow mapping, rim lighting, dissolve
- Assimp-based skeletal animation and animation blending with CPU skinning
- OBB collision/separating-axis implementation
- Scene/GameObject/Component structure
- Player combat and multiple enemy behaviors
- Quest/store/village UI and game-state flows
- XAudio2 and Dear ImGui integration

## Refactoring highlights to surface when completed

Prioritize evidence such as:

1. Reproducible clean-clone build instead of author-PC-relative layout.
2. Explicit ownership/RAII replacing self-deletion and leak-prone manual lifetime.
3. Smaller state-specific functions replacing 200–500 line update functions while preserving behavior.
4. Clear third-party and asset provenance boundaries.
5. Modern supported dependency/math migration, only if completed with validation.

## Authorship disclosure

Use wording similar to:

> The original game implementation was created by me. I later designed a Claude Code harness (`CLAUDE.md`, project skills, path-scoped rules, hooks, phased acceptance gates, and analysis scripts) and used Claude Code as an AI-assisted refactoring partner. I decided the refactoring boundaries, reviewed the diffs, and validated behavior. The repository preserves the original version for comparison.

This is stronger than implying the refactored version was written entirely without assistance or, conversely, implying AI created the original project.

## Suggested review order

1. README/demo media
2. original-vs-refactored architecture summary
3. five selected before/after diffs
4. collision/animation/rendering code as technical highlights
5. harness and validation evidence
6. full history only if the reviewer wants detail
