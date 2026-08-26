---
paths:
  - "**/*.{hlsl,hlsli}"
---

# HLSL Refactor Rules

- Treat register bindings, constant-buffer layout/order, input semantics, texture/sampler bindings, matrix multiplication convention, and shader entry-point names as behavior-critical.
- Do not rename shader files or entry points unless all C++ load sites/project references are updated in the same focused task.
- Do not change lighting coefficients, dissolve thresholds, shadow comparison behavior, or render-state assumptions during a mechanical refactor.
- If shader behavior changes intentionally, capture before/after screenshots or another visual validation artifact.
