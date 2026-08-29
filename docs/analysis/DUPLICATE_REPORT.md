# Conflict-copy report

These files contain machine-name conflict suffixes and have a base-name counterpart.

| Conflict copy | Base | Similarity | Lines conflict/base |
|---|---|---:|---:|
| `villageUi-DESKTOP-2FSCGV3.cpp` | `villageUi.cpp` | 58.9% | 1206/520 |
| `questDeskUi-DESKTOP-2FSCGV3.h` | `questDeskUi.h` | 91.3% | 83/90 |
| `questDeskUi-DESKTOP-2FSCGV3.cpp` | `questDeskUi.cpp` | 87.4% | 357/412 |

Policy: do not delete automatically. First check `.vcxproj` membership, runtime behavior, timestamps/Git history if available, and semantic differences. Record the chosen canonical file in `docs/refactor/RENAME_MAP.md` or an exec plan.

## Resolution (Phase 1, see `docs/exec-plans/2026-08-27-phase1-mechanical-hygiene.md`)

`grep -n "villageUi\|questDeskUi" "GM31 23.04.18.vcxproj"` shows only `villageUi.cpp`, `questDeskUi.cpp`, and `questDeskUi.h` are referenced by any `ClCompile`/`ClInclude` item — none of the three `*-DESKTOP-2FSCGV3.*` copies are part of the build in any configuration. The `-DESKTOP-2FSCGV3` suffix matches OneDrive's automatic "conflicted copy" naming (this project has always lived under OneDrive), not an intentional alternate implementation. Combined with a full clean `MSBuild /t:Rebuild` succeeding using only the base files, this is sufficient evidence that the base files are canonical and the suffixed copies are inert leftovers. **Decision: delete all three source conflict copies** (`villageUi-DESKTOP-2FSCGV3.cpp`, `questDeskUi-DESKTOP-2FSCGV3.cpp`, `questDeskUi-DESKTOP-2FSCGV3.h`). They remain recoverable from the `original-submission` git tag.

The 8 `*-DESKTOP-2FSCGV3.cso` compiled-shader conflict copies (`DepthShadowMappingPS/VS`, `pixelLightingRimPS/VS` at root; `shader/unlitTexturePS/VS`, `shader/vertexLightingPS/VS`) all correspond to `FxCompile` items with a `Debug|x64` `ObjectFileOutput`, and a full clean rebuild in this session regenerated the canonical (non-suffixed) `.cso` for every one of them. These are binary build byproducts of a different machine, not authored content. **Decision: delete all 8**, and add `*.cso` to `.gitignore` going forward since regeneration from tracked `.hlsl` sources is now proven.
