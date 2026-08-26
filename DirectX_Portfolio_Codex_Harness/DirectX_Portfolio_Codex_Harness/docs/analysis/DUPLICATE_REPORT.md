# Conflict-copy report

These files contain machine-name conflict suffixes and have a base-name counterpart.

| Conflict copy | Base | Similarity | Lines conflict/base |
|---|---|---:|---:|
| `villageUi-DESKTOP-2FSCGV3.cpp` | `villageUi.cpp` | 58.9% | 1206/520 |
| `questDeskUi-DESKTOP-2FSCGV3.h` | `questDeskUi.h` | 91.3% | 83/90 |
| `questDeskUi-DESKTOP-2FSCGV3.cpp` | `questDeskUi.cpp` | 87.4% | 357/412 |

Policy: do not delete automatically. First check `.vcxproj` membership, runtime behavior, timestamps/Git history if available, and semantic differences. Record the chosen canonical file in `docs/refactor/RENAME_MAP.md` or an exec plan.
