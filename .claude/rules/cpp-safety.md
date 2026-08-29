---
paths:
  - "**/*.{h,hpp,cpp,cxx}"
---

# C++ Safety and Behavior-Preservation Rules

- First determine whether each pointer is owning or observing before changing its type.
- Prefer `std::unique_ptr` only for genuine sole ownership; do not convert observer pointers to `shared_ptr` as a shortcut.
- Do not introduce new raw owning `new/delete` or `delete this`.
- Add/verify virtual destructors before deleting polymorphic objects through base pointers.
- Keep Update/Draw ordering, scene transitions, collision thresholds, animation frame values, and gameplay constants unchanged during structural refactors.
- Separate mechanical cleanup from semantic behavior changes.
- When splitting a large function, preserve branch/state-transition order unless a behavior change is explicitly approved.
- Do not broadly reformat untouched legacy code; keep diffs reviewable.
