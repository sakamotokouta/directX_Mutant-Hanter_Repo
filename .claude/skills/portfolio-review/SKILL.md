---
name: portfolio-review
description: Evidence-first review workflow for presenting the original and refactored DirectX project to hiring reviewers. Use before GitHub publication, portfolio submission, README polishing, or when selecting before/after refactoring examples and describing Claude Code assistance.
---

# Portfolio Review

## Workflow
1. Compare the immutable original and current refactored code.
2. Select improvements only when supported by concrete diffs and validation.
3. Separate three categories clearly: original author implementation, third-party library/asset contributions, and Claude Code-assisted refactoring.
4. Prefer five strong before/after examples over dozens of cosmetic changes.
5. Check that build/run instructions are reproducible and licensing notes are complete.
6. Check that AI disclosure is accurate and does not imply Claude created the original work.
7. Remove exaggerated claims such as “engine from scratch” unless repository evidence supports the exact scope.

## Reviewer-facing output
- 30-second project summary
- Original technical highlights
- Five refactor highlights
- What Claude Code assisted with vs what the author decided/reviewed/validated
- How to build/run
- Known limitations
- Third-party notices and asset provenance status
