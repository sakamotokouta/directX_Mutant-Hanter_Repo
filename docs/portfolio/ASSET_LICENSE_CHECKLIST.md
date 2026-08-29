# Asset and Third-Party License Checklist

Do not publish the full asset package until this table is completed.

| Item/group | Origin/source URL | Author | License | Redistribution allowed? | Attribution required? | Proof saved? | Public portfolio action |
|---|---|---|---|---|---|---|---|
| Assimp (`assimp/*.h`, `assimp-vc143-mt.dll/.lib`) | https://github.com/assimp/assimp | Assimp contributors | BSD 3-Clause (well-known, stable license for this project) | Yes, with attribution/copyright notice | Yes | No — vendored as loose headers with **no LICENSE file copied in** | Add the upstream `LICENSE` file into `assimp/` before any public share; verify against the exact source version if known |
| Dear ImGui (`imgui/*`) | https://github.com/ocornut/imgui | Omar Cornut / ImGui contributors | MIT (well-known, stable license for this project) | Yes, with copyright/license notice retained | Yes | No — vendored as loose source with **no LICENSE file copied in** | Add the upstream `LICENSE.txt` into `imgui/` before any public share |
| FBX character/animation assets (`asset/model/*.fbx`) | Unknown to this refactor pass | Unknown | Unknown | **Unverified** | **Unverified** | No | Filenames (`Mutant Idle.fbx`, `Breathing Idle.fbx`, `Kachujin G Rosales.fbx`, `Warrok W Kurniawan.fbx`, etc.) match Adobe Mixamo's default naming convention, which is a *hint*, not proof — confirm the original download/export and Mixamo's terms (or the actual source) before any public redistribution |
| OBJ environment/weapon assets (`asset/model/*.obj/.mtl`) | Unknown to this refactor pass | Unknown | Unknown | **Unverified** | **Unverified** | No | Do not publish until origin is confirmed |
| Textures/UI images (`asset/model/*.png/.jpg`) | Unknown to this refactor pass | Unknown | Unknown | **Unverified** | **Unverified** | No | Do not publish until origin is confirmed |
| BGM/SE WAV files (`asset/audio/*.wav`) | Unknown to this refactor pass | Unknown | Unknown | **Unverified** | **Unverified** | No | Filenames suggest at least one Japanese royalty-free SE/BGM library (e.g. `maou_bgm_*`); confirm the specific library's terms before any public redistribution |

If provenance cannot be established, do not guess. Replace, omit, or keep the asset only in a private/non-redistributed review package as permitted by its terms.

This table was populated mechanically from filenames and known upstream facts about Assimp/Dear ImGui during Phase 1 (see `docs/exec-plans/2026-08-27-phase1-mechanical-hygiene.md`). It is a starting point for a human license review, not a completed clearance — nothing here should be treated as permission to publish.
