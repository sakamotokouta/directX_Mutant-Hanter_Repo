from pathlib import Path
from collections import Counter
from xml.etree import ElementTree as ET
import csv, hashlib, re, difflib, json, textwrap, shutil, os

BASE=Path('/mnt/data/directx_analysis')
ROOT=BASE/'extracted/#U5c31#U8077#U4f5c#U54c1'
SRC=ROOT/'#U30d7#U30ed#U30b0#U30e9#U30e0#U30d5#U30a1#U30a4#U30eb'
RUN=ROOT/'#U5b9f#U884c#U30d5#U30a1#U30a4#U30eb'
OUT=Path('/mnt/data/DirectX_Portfolio_Codex_Harness')
if OUT.exists(): shutil.rmtree(OUT)
OUT.mkdir(parents=True)

def read_text(p):
    b=p.read_bytes()
    for enc in ('utf-8-sig','cp932','shift_jis'):
        try: return b.decode(enc),enc
        except UnicodeDecodeError: pass
    return None,None

def sha256(p):
    h=hashlib.sha256()
    with p.open('rb') as f:
        for ch in iter(lambda:f.read(1024*1024),b''): h.update(ch)
    return h.hexdigest()

def classify(path):
    rel=path.relative_to(ROOT).as_posix()
    if path==ROOT/'solutionfile.sln': return 'solution'
    if SRC in path.parents:
        ext=path.suffix.lower()
        if ext in ('.cpp','.h','.hpp'): return 'project-source'
        if ext in ('.cso',): return 'compiled-shader-copy'
        if ext in ('.dll','.lib'): return 'dependency-binary-copy'
        if ext in ('.vcxproj','.filters','.user'): return 'visual-studio-project'
        if ext=='.ini': return 'configuration'
        return 'source-side-other'
    if RUN in path.parents:
        r=path.relative_to(RUN).as_posix()
        if r.startswith('asset/model/'): return 'asset-model'
        if r.startswith('asset/texture/'): return 'asset-texture'
        if r.startswith('asset/audio/'): return 'asset-audio'
        if r.startswith('assimp/'): return 'third-party-assimp'
        if r.startswith('imgui/'): return 'third-party-imgui'
        if r.startswith('shader/'):
            return 'shader-source' if path.suffix.lower()=='.hlsl' else 'shader-binary'
        if r.startswith('Debug/'): return 'build-artifact-debug'
        if path.suffix.lower() in ('.exe','.dll','.lib','.pdb','.cso'): return 'runtime-binary'
        return 'runtime-other'
    return 'other'

# project listings
proj=SRC/'GM31 23.04.18.vcxproj'
project_listed=set()
if proj.exists():
    root=ET.parse(proj).getroot(); ns={'m':'http://schemas.microsoft.com/developer/msbuild/2003'}
    for tag in ('ClCompile','ClInclude'):
        for e in root.findall(f'.//m:{tag}',ns):
            if e.attrib.get('Include'): project_listed.add(e.attrib['Include'].replace('\\','/'))

# full inventory
rows=[]
for p in sorted(ROOT.rglob('*')):
    if not p.is_file(): continue
    rel=p.relative_to(ROOT).as_posix()
    txt,enc=read_text(p) if p.suffix.lower() in ('.cpp','.h','.hpp','.hlsl','.inl','.sln','.vcxproj','.filters','.user','.ini','.log','.tlog','.lastbuildstate') else (None,None)
    inproj=False
    if SRC in p.parents:
        inproj=p.name in {Path(x).name for x in project_listed}
    rows.append({
        'path':rel,'category':classify(p),'extension':p.suffix.lower(),'size_bytes':p.stat().st_size,
        'sha256':sha256(p),'text_encoding':enc or 'binary/unknown','line_count':len(txt.splitlines()) if txt is not None else '',
        'listed_in_vcxproj':str(inproj).lower() if SRC in p.parents else ''
    })
(OUT/'docs/analysis').mkdir(parents=True)
with (OUT/'docs/analysis/FULL_FILE_INVENTORY.csv').open('w',newline='',encoding='utf-8-sig') as f:
    w=csv.DictWriter(f,fieldnames=rows[0].keys());w.writeheader();w.writerows(rows)

# source metrics
src_rows=[]
source_files=[]
for p in sorted(SRC.iterdir()):
    if p.suffix.lower() not in ('.cpp','.h','.hpp'): continue
    txt,enc=read_text(p); source_files.append(p)
    src_rows.append({
        'file':p.name,'extension':p.suffix.lower(),'encoding':enc,'lines':len(txt.splitlines()),
        'new_count':len(re.findall(r'\bnew\s+[A-Za-z_]',txt)),
        'delete_count':len(re.findall(r'\bdelete\b',txt)),
        'com_release_count':len(re.findall(r'->Release\s*\(',txt)),
        'if_count':len(re.findall(r'\bif\s*\(',txt)),
        'switch_count':len(re.findall(r'\bswitch\s*\(',txt)),
        'asset_path_literals':len(re.findall(r'"(?:asset|shader)[/\\][^"\n]+"',txt)),
        'listed_in_vcxproj':p.name in {Path(x).name for x in project_listed},
        'desktop_conflict_copy':'DESKTOP-2FSCGV3' in p.name,
    })
with (OUT/'docs/analysis/SOURCE_METRICS.csv').open('w',newline='',encoding='utf-8-sig') as f:
    w=csv.DictWriter(f,fieldnames=src_rows[0].keys());w.writeheader();w.writerows(src_rows)

# duplicate report
pairs=[]
for p in SRC.iterdir():
    if 'DESKTOP-2FSCGV3' in p.name and p.suffix.lower() in ('.cpp','.h'):
        base=p.name.replace('-DESKTOP-2FSCGV3',''); q=SRC/base
        if q.exists():
            a,_=read_text(p); b,_=read_text(q)
            pairs.append((p.name,base,difflib.SequenceMatcher(None,a.splitlines(),b.splitlines()).ratio(),len(a.splitlines()),len(b.splitlines())))

# class definition scan
classes=[]
for p in source_files:
    if p.suffix.lower() not in ('.h','.hpp'): continue
    txt,_=read_text(p)
    for m in re.finditer(r'\bclass\s+(\w+)\s*(?:\:\s*public\s+([\w:]+))?\s*\{',txt):
        classes.append((m.group(1),m.group(2) or '',p.name))

# metrics totals
ext_counts=Counter(p.suffix.lower() for p in ROOT.rglob('*') if p.is_file())
cat_counts=Counter(r['category'] for r in rows)
enc_counts=Counter(r['encoding'] for r in src_rows)
loc=sum(r['lines'] for r in src_rows)
new_total=sum(r['new_count'] for r in src_rows); del_total=sum(r['delete_count'] for r in src_rows)
large=sorted(src_rows,key=lambda r:r['lines'],reverse=True)[:15]

# helper write

def wr(rel,txt):
    p=OUT/rel;p.parent.mkdir(parents=True,exist_ok=True);p.write_text(textwrap.dedent(txt).strip()+"\n",encoding='utf-8')

# README EN
wr('README.md',f'''
# DirectX Portfolio — Codex Refactoring Harness

This repository package is a **refactoring harness**, not a replacement for the original game. It was generated after a full inventory and static analysis of the submitted DirectX project ({len(rows)} files, {len(source_files)} first-party C/C++ files, {loc:,} C/C++ lines in the source folder).

## Purpose

The portfolio story should be:

1. **Original implementation:** a self-built DirectX 11 game demonstrating rendering, animation, collision, combat, UI, audio, and scene/gameplay systems.
2. **Engineering analysis:** identify reproducibility, ownership, maintainability, and legacy-API risks without hiding the original code.
3. **Behavior-preserving refactor:** use Codex in small, reviewable phases governed by this harness.
4. **Evidence:** show before/after diffs, build/run checks, architecture notes, and decisions.

## Important naming note

Codex uses **`AGENTS.md`** (plural) as the repository instruction file. `AGENTS.ja.md` is the Japanese human-readable mirror. The English `AGENTS.md` is the canonical agent instruction source to avoid conflicting duplicated instructions.

## Start here

- Agent entry point: [`AGENTS.md`](AGENTS.md)
- Japanese guide: [`README.ja.md`](README.ja.md)
- Architecture: [`ARCHITECTURE.md`](ARCHITECTURE.md)
- Full analysis: [`docs/analysis/PROJECT_ANALYSIS.md`](docs/analysis/PROJECT_ANALYSIS.md)
- Refactor plan: [`docs/refactor/REFACTOR_PLAN.md`](docs/refactor/REFACTOR_PLAN.md)
- Acceptance gates: [`docs/refactor/ACCEPTANCE_CRITERIA.md`](docs/refactor/ACCEPTANCE_CRITERIA.md)
- Codex prompts: [`docs/prompts/CODEX_TASK_PROMPTS.md`](docs/prompts/CODEX_TASK_PROMPTS.md)
- Hiring reviewer guide: [`docs/portfolio/REVIEWER_GUIDE.md`](docs/portfolio/REVIEWER_GUIDE.md)
- All {len(rows)} files: [`docs/analysis/FULL_FILE_INVENTORY.csv`](docs/analysis/FULL_FILE_INVENTORY.csv)

## Recommended portfolio repository layout

```text
portfolio-directx/
├─ AGENTS.md
├─ AGENTS.ja.md
├─ ARCHITECTURE.md
├─ README.md
├─ README.ja.md
├─ archive/
│  └─ original/              # immutable snapshot of the submitted source/project
├─ src/                      # refactored first-party code
├─ shaders/                  # HLSL source
├─ assets/                   # distributable assets only after license review
├─ third_party/
│  ├─ assimp/
│  └─ imgui/
├─ docs/
└─ scripts/
```

Prefer a Git tag such as `original-submission` in addition to `archive/original/`. This gives reviewers both a simple side-by-side comparison and trustworthy history.

## Harness design basis

OpenAI's current Codex guidance treats `AGENTS.md` as persistent repository context, and OpenAI's harness-engineering guidance recommends keeping it short and using it as a table of contents into structured documentation. This package follows that pattern.

References:
- https://openai.com/index/harness-engineering/
- https://openai.com/index/unrolling-the-codex-agent-loop/
- https://openai.com/academy/skills/
''')

wr('README.ja.md',f'''
# DirectX就活作品 — Codexリファクタリング・ハーネス

これは元ゲームを置き換えるものではなく、**元作品を保護しながらCodexで段階的に改善するためのハーネス**です。提出ZIP全体を棚卸しし、{len(rows)}ファイル、第一者C/C++コード{len(source_files)}ファイル、ソースフォルダ内C/C++約{loc:,}行を静的解析した結果を反映しています。

## 就活で見せるストーリー

1. **Original:** 自分で一から作成したDirectX 11ゲーム。
2. **Analysis:** ビルド再現性、メモリ所有権、巨大関数、命名、文字コード、依存関係などを自分で分析。
3. **Refactor:** ハーネスでCodexの変更範囲を制限し、動作を維持したまま段階的に改善。
4. **Evidence:** Before/After、コミット履歴、検証結果、設計判断を提出物として残す。

## `AGENT.md` ではなく `AGENTS.md`

Codexでリポジトリ指示として使う標準ファイル名は **`AGENTS.md`（複数形）** です。英語版 `AGENTS.md` をCodex向けの正本にし、`AGENTS.ja.md` は人間向け日本語ミラーにしています。両方を自動指示として読ませて競合させない方針です。

## 最初に読むファイル

- Codex入口: [`AGENTS.md`](AGENTS.md)
- 日本語版: [`AGENTS.ja.md`](AGENTS.ja.md)
- 解析結果: [`docs/analysis/PROJECT_ANALYSIS.ja.md`](docs/analysis/PROJECT_ANALYSIS.ja.md)
- リファクタリング計画: [`docs/refactor/REFACTOR_PLAN.ja.md`](docs/refactor/REFACTOR_PLAN.ja.md)
- 完了条件: [`docs/refactor/ACCEPTANCE_CRITERIA.ja.md`](docs/refactor/ACCEPTANCE_CRITERIA.ja.md)
- Codex用プロンプト: [`docs/prompts/CODEX_TASK_PROMPTS.ja.md`](docs/prompts/CODEX_TASK_PROMPTS.ja.md)
- 採用担当者向け説明: [`docs/portfolio/REVIEWER_GUIDE.ja.md`](docs/portfolio/REVIEWER_GUIDE.ja.md)
- 全{len(rows)}ファイルの棚卸し: [`docs/analysis/FULL_FILE_INVENTORY.csv`](docs/analysis/FULL_FILE_INVENTORY.csv)

## 推奨リポジトリ構成

```text
portfolio-directx/
├─ AGENTS.md                 # Codex向け正本（英語）
├─ AGENTS.ja.md              # 人間向け日本語版
├─ ARCHITECTURE.md
├─ archive/original/         # 元コードの変更禁止スナップショット
├─ src/                      # 改善後コード
├─ shaders/
├─ assets/
├─ third_party/
├─ docs/
└─ scripts/
```

元コードは `original-submission` のようなGit tagでも固定してください。「AIに全部書かせ直した」ではなく、**自分の実装を自分で分析し、AIを制御する仕組みを作って改善した**ことを見せる構成です。
''')

# AGENTS
wr('AGENTS.md','''
# AGENTS.md — DirectX Portfolio Refactoring Rules

## Mission

Preserve the behavior and authorship evidence of the original DirectX 11 game while improving build reproducibility, maintainability, safety, and reviewer readability through small, auditable changes.

This is a portfolio refactor. **Do not rewrite the game from scratch.** The value is the traceable transformation from original code to improved code.

## Source of truth map

Read only what is relevant to the task, in this order:

1. `docs/analysis/PROJECT_ANALYSIS.md` — observed repository facts and risks.
2. `ARCHITECTURE.md` — current system map and boundaries.
3. `docs/refactor/REFACTOR_PLAN.md` — required phase order.
4. `docs/refactor/ACCEPTANCE_CRITERIA.md` — validation gates.
5. `docs/design-docs/core-beliefs.md` — design constraints.
6. `docs/exec-plans/` — active task plan and decision log.
7. Relevant skill under `.codex/skills/` for repeatable workflows.

Japanese mirrors (`*.ja.md`) are for human review. Treat the English documents as canonical for agent execution unless the user explicitly says otherwise.

## Non-negotiable guardrails

- Never modify `archive/original/**` after the baseline snapshot is created.
- Never combine gameplay changes with refactoring in the same task.
- Never perform a broad rename, encoding conversion, ownership rewrite, and directory move in one patch.
- Keep one primary refactoring theme per task.
- Do not delete an asset, shader, library, or duplicate-looking file until its build/runtime usage is proven.
- Do not claim a build or runtime test passed unless it was actually run.
- If Windows/DirectX execution is unavailable, perform static checks and explicitly report the limitation.
- Preserve visible game behavior unless the task explicitly authorizes a behavior change.
- Preserve original credits and third-party notices. Do not publish assets until licensing is reviewed.
- Do not replace first-party code with a new engine/framework merely to reduce line count.

## Baseline first

Before structural refactoring:

1. Create/verify the immutable original snapshot.
2. Run `scripts/analyze_repository.py` and store the report.
3. Run `scripts/snapshot_tree.py` on the original source.
4. Establish the Windows x64 Debug build command or record why the provided project is not yet reproducible.
5. Capture a manual smoke-test checklist and screenshots/video externally if possible.

## Build target

Primary target: Windows + Visual Studio 2022 toolset (`v143`), x64 Debug first.

The analyzed project uses Direct3D 11 plus legacy D3DX headers/libraries, Assimp, Dear ImGui, XAudio2, and WinMM. Do not modernize all of these at once.

## Change protocol

For every task:

1. Inspect the relevant files and dependency edges.
2. Write/update a focused exec plan under `docs/exec-plans/` when the change spans multiple files or risks behavior.
3. State invariants that must remain true.
4. Make the smallest coherent change.
5. Run the required static/build/manual checks.
6. Update docs only when the code or known facts changed.
7. Report: changed files, behavior impact, validation evidence, remaining risk, and recommended next task.

## Refactoring order

Follow the phase order in `docs/refactor/REFACTOR_PLAN.md`. In particular:

- Fix packaging/build reproducibility before architectural modernization.
- Convert text encoding in a dedicated mechanical commit.
- Resolve conflict-copy files before relying on file names for architecture.
- Introduce RAII/ownership changes before large feature decomposition.
- Split `player.cpp`, UI state logic, animation code, and renderer initialization incrementally.
- Treat D3DX-to-DirectXMath migration as a later, isolated modernization phase.

## C++ rules for touched code

- Prefer explicit ownership: `std::unique_ptr` for sole ownership, references/non-owning pointers for observation.
- Prefer `Microsoft::WRL::ComPtr` for COM ownership when that migration phase is active.
- Add virtual destructors to polymorphic ownership bases before deleting through base pointers.
- Do not introduce new `delete this` patterns.
- Avoid new raw owning `new/delete`.
- Prefer `enum class` for newly introduced state enums.
- Prefer `constexpr` constants over new macros when practical.
- Use `const` correctness and references where it improves intent without broad churn.
- Keep gameplay constants unchanged during mechanical refactors.
- Do not silently change frame timing, collision tolerances, animation frame numbers, or shader constants.

## Naming and file moves

Existing misspellings are known (`collition`, `bace`, `sprit`, `flame`, etc.). Rename only in dedicated tasks with a mapping recorded in `docs/refactor/RENAME_MAP.md`. Keep behavior-only and rename-only diffs separate whenever possible.

## Verification

At minimum run applicable checks from `docs/refactor/ACCEPTANCE_CRITERIA.md`, including:

- harness self-check,
- encoding report,
- duplicate/conflict-copy report,
- source inventory diff,
- Windows build when available,
- manual smoke test for scene transitions, combat, UI, audio, collision, animation, and rendering.

## Portfolio evidence rule

Every meaningful refactor should produce reviewer-friendly evidence. Update `docs/portfolio/BEFORE_AFTER_LOG.md` with:

- problem,
- original code location,
- design decision,
- changed code location,
- measurable or explainable improvement,
- validation evidence,
- what was intentionally not changed.

## Stop conditions

Stop and report instead of guessing when:

- the original baseline cannot be located,
- two conflict-copy files differ materially and there is no evidence which one is canonical,
- an asset/license origin is unknown and publication is requested,
- a dependency path is missing and a build fix would require inventing a version,
- behavior preservation cannot be checked for a high-risk change.
''')

wr('AGENTS.ja.md','''
# AGENTS.ja.md — DirectX就活作品リファクタリング規約

> 人間向け日本語版です。Codex実行時の正本はルートの `AGENTS.md`（英語）です。

## 目的

元のDirectX 11ゲームの動作と「自分で作った証拠」を残したまま、Codexを使ってビルド再現性・保守性・安全性・採用担当者からの読みやすさを段階的に改善する。

**ゲームを一から書き直してはいけません。** 就活上の価値は、元コードから改善後コードまでの追跡可能な変化にあります。

## 参照順

1. `docs/analysis/PROJECT_ANALYSIS.md` — 実際に確認した事実とリスク
2. `ARCHITECTURE.md` — 現在の構造
3. `docs/refactor/REFACTOR_PLAN.md` — 実施フェーズ
4. `docs/refactor/ACCEPTANCE_CRITERIA.md` — 完了条件
5. `docs/design-docs/core-beliefs.md` — 設計上の原則
6. `docs/exec-plans/` — 個別タスク計画
7. `.codex/skills/` — 繰り返し作業の手順

## 絶対ルール

- `archive/original/**` はベースライン作成後に変更しない。
- リファクタリングとゲーム仕様変更を同じタスクで行わない。
- 大量リネーム、文字コード変換、所有権変更、フォルダ移動を一度に行わない。
- 1タスク1主目的を基本にする。
- 使用状況を確認する前にアセット・シェーダー・DLL・重複らしきファイルを削除しない。
- 実行していないビルドやテストを「成功」と報告しない。
- Windows/DirectX環境がなければ静的検証まで行い、未実行項目を明示する。
- 指示がない限り見た目・操作・ゲームバランスを変えない。
- 第三者素材のクレジットとライセンスを保持する。

## 最初に固定するもの

1. 元コードを `archive/original/` とGit tagで固定。
2. `scripts/analyze_repository.py` で棚卸し。
3. `scripts/snapshot_tree.py` でハッシュを保存。
4. Visual Studio 2022 / v143 / x64 Debugのビルド手順を確立、または再現できない理由を記録。
5. シーン遷移・戦闘・UI・音・当たり判定・アニメーション・描画の手動スモークテスト項目を作る。

## 変更手順

各タスクで「対象確認 → 不変条件 → 最小変更 → 検証 → 記録」の順で進めます。複数ファイルにまたがる高リスク変更は `docs/exec-plans/` に計画を残してください。

## C++改善ルール

- 所有権を明示し、単独所有は原則 `std::unique_ptr`。
- COM所有は該当フェーズで `Microsoft::WRL::ComPtr` を検討。
- 基底ポインタ経由で削除される多態クラスにはvirtual destructorを入れる。
- `delete this` を新規追加しない。
- 新しい生の所有 `new/delete` を増やさない。
- 新規state enumは可能なら `enum class`。
- 新規定数は可能なら `constexpr`。
- 機械的リファクタリングではフレーム数、当たり判定閾値、アニメ番号、シェーダ定数を変えない。

## 命名

`collition`, `bace`, `sprit`, `flame` など既知の綴り問題は専用フェーズで変更し、`docs/refactor/RENAME_MAP.md` に旧名→新名を残します。

## 就活提出物として残す証拠

各主要改善は `docs/portfolio/BEFORE_AFTER_LOG.md` に「問題・元コード・判断・改善後・効果・検証・変えなかったもの」を記録してください。
''')

# Architecture
wr('ARCHITECTURE.md','''
# Architecture — Observed Legacy Design

## Runtime flow

```text
WinMain
  -> Manager::Init
      -> Renderer::Init
      -> Input::Init
      -> Audio::InitMaster
      -> ImGui init
      -> Manager::SetScene<Title>()
  -> frame loop (~60 FPS target)
      -> Manager::Update
          -> Input::Update
          -> scene transition
          -> Scene::Update
              -> GameObject::Update
                  -> Component::Update
      -> Manager::Draw
          -> Renderer::Begin
          -> Scene::Draw
          -> ImGui render
          -> Renderer::End
```

## Main subsystems observed

| Subsystem | Representative files | Observed responsibility |
|---|---|---|
| Application/loop | `main.cpp`, `manager.*` | Win32 window, frame pacing, scene lifetime, ImGui frame lifecycle |
| Scene graph | `scene.h`, `gameObject.h`, `component.h` | 3-layer object lists, object/component update/draw, deletion flags |
| Rendering | `renderer.*`, `drawModel.*`, `model.*`, `animationModel.*` | Direct3D 11 device/state, OBJ/Assimp model rendering, dynamic animated vertices |
| Shaders | runtime `shader/*.hlsl` | pixel lighting, rim lighting, shadow mapping, dissolve, unlit textured rendering |
| Animation | `animationModel.*` | Assimp skeletal animation loading, animation blending, CPU skinning |
| Collision | `collitionBox.*`, `villageObjCollition.*` | OBB collision using separating-axis tests |
| Player/combat | `player.*`, `weapon.*`, special attacks, bullets/effects | stateful movement/combat, weapon/effect logic |
| Enemy AI | `enemy.*`, jump/remote attack files | search/found/chase/attack/death state behavior and field-of-view check |
| Game scenes | `title.*`, `game.*`, `village.*`, `tutorial.*`, `result.*`, `loading.*` | scene-specific setup, transitions, gameplay |
| UI/economy | `ui01.*`, `villageUi.*`, `questDeskUi.*`, store UIs, `money.*`, scores | HUD, quest/shop flows, currency/material display |
| Audio/input | `audio.*`, `input.*` | XAudio2 WAV playback and keyboard state polling |
| Assets/deps | runtime `asset/`, `assimp/`, `imgui/` | content and third-party code |

## Notable technical features worth preserving in the portfolio narrative

- Direct3D 11 renderer and Win32 application loop.
- HLSL shadow mapping, rim lighting, dissolve effect, and textured rendering.
- Skeletal animation import/blending with Assimp and CPU skinning.
- OBB collision based on separating axes.
- Multiple gameplay scenes and an object/component abstraction.
- Enemy state behavior including detection/chase/attack variants.
- Combat, weapons, special attacks, quest/store UI, currency/items.
- XAudio2 audio and Dear ImGui integration.

## Architectural pressure points

- Global/static service access (`Manager`, `Renderer`, `Input`, audio master).
- Raw owning pointers across scene objects, components, UI sprites, model data, and COM objects.
- Lifetime is encoded through `Init/Uninit` conventions rather than C++ destructors/RAII.
- `GameObject::Destroy()` self-deletes, while `Scene` also owns object pointers.
- Large update functions mix input, state transitions, animation timing, collision, and side effects.
- Rendering/resource creation is tightly coupled to gameplay object classes.
- Hard-coded asset paths and gameplay coordinates make data ownership unclear.

This document describes the current code; it is not a demand to replace every pattern. Modernization must follow the phased plan.
''')
wr('ARCHITECTURE.ja.md','''
# アーキテクチャ — 現行コードの観測結果

## 実行フロー

```text
WinMain
  -> Manager::Init
      -> Renderer / Input / Audio / ImGui 初期化
      -> Titleシーン予約
  -> 約60FPSのループ
      -> Manager::Update
          -> Input更新
          -> シーン切替
          -> Scene::Update -> GameObject::Update -> Component::Update
      -> Manager::Draw
          -> Renderer::Begin -> Scene::Draw -> ImGui -> Renderer::End
```

## 主なサブシステム

| 分野 | 代表ファイル | 内容 |
|---|---|---|
| アプリ/ループ | `main.cpp`, `manager.*` | Win32、フレーム制御、シーン寿命、ImGui |
| オブジェクト | `scene.h`, `gameObject.h`, `component.h` | 3レイヤ、Update/Draw、削除フラグ |
| 描画 | `renderer.*`, `model.*`, `animationModel.*` | Direct3D 11、OBJ/Assimp、アニメ頂点更新 |
| シェーダ | `shader/*.hlsl` | ピクセルライティング、リム、影、ディゾルブ、2D/非ライティング |
| アニメ | `animationModel.*` | Assimp、ボーン、ブレンド、CPUスキニング |
| 当たり判定 | `collitionBox.*` | 分離軸を使ったOBB判定 |
| 戦闘 | `player.*`, `weapon.*`, 各special attack | 移動、攻撃、武器、特殊攻撃 |
| 敵AI | `enemy.*` 等 | 探索、発見、追跡、攻撃、死亡、視野判定 |
| シーン | title/game/village/tutorial/result/loading | 各ゲームシーン |
| UI/経済 | 各UI、`money.*`, score | HUD、クエスト、店、通貨/アイテム |
| 音/入力 | `audio.*`, `input.*` | XAudio2、キーボード |

## 就活で強みとして説明できる実装

Direct3D 11による描画基盤、HLSLの影/リム/ディゾルブ、Assimpを使ったボーンアニメーションとCPUスキニング、分離軸法によるOBB判定、シーン/ゲームオブジェクト構造、敵AI状態制御、戦闘/武器/クエスト/店舗UI、XAudio2、ImGui統合を自作コード側から確認できました。

## 改善圧力が高い部分

静的サービスへの依存、生ポインタ所有、`Init/Uninit` に依存した寿命管理、`delete this`、巨大Update、描画とゲームロジックの密結合、アセットパスや座標のハードコードです。これらは一括置換せず、フェーズごとに改善します。
''')

# Analysis content
large_table='\n'.join(f"| `{r['file']}` | {r['lines']} | {r['encoding']} | {r['new_count']} | {r['delete_count']} |" for r in large[:12])
cat_table='\n'.join(f"| {k} | {v} |" for k,v in sorted(cat_counts.items(),key=lambda kv:(-kv[1],kv[0])))
dup_table='\n'.join(f"| `{a}` | `{b}` | {ratio:.1%} | {la}/{lb} |" for a,b,ratio,la,lb in pairs) or '| none | none | - | - |'
wr('docs/analysis/PROJECT_ANALYSIS.md',f'''
# Project Analysis — DirectX Job Portfolio

## Scope and method

The entire submitted ZIP was enumerated. Every file is represented in `FULL_FILE_INVENTORY.csv` with path, category, byte size, SHA-256, extension, text encoding where applicable, and Visual Studio project-membership metadata for source-side files. First-party C/C++ files received additional static metrics in `SOURCE_METRICS.csv`.

No Windows DirectX build was executed in this Linux analysis environment, so build/runtime findings below distinguish **observed packaging facts** from behavior that still needs a Windows baseline test.

## Repository facts

- Total files: **{len(rows)}**
- Source-folder first-party C/C++ headers/sources: **{len(source_files)}**
- C/C++ lines in source folder: **{loc:,}**
- Source encodings: **{dict(enc_counts)}**
- Raw `new` occurrences in first-party C/C++: **{new_total}**
- `delete` occurrences: **{del_total}**
- HLSL files in package: **{ext_counts['.hlsl']}**
- Models: **{ext_counts['.fbx']} FBX + {ext_counts['.obj']} OBJ**
- Images: **{ext_counts['.png']} PNG + {ext_counts['.jpg']} JPG + {ext_counts['.jpeg']} JPEG**
- Audio: **{ext_counts['.wav']} WAV**

### Inventory by category

| Category | Files |
|---|---:|
{cat_table}

## What the original work demonstrates

The code is more substantial than a rendering sample. It contains a game loop, scene management, an object/component model, Direct3D 11 rendering, model loading, skeletal animation, CPU skinning, OBB collision, player combat, enemy state behavior, special attacks/effects, title/game/village/tutorial/result scenes, HUD/quest/store flows, XAudio2 audio, and HLSL effects including shadow mapping, rim lighting, and dissolve.

This breadth is a strong portfolio asset. The refactor should make it easier for reviewers to see these systems rather than replacing them.

## Highest-priority findings

### P0 — Build reproducibility/package structure

1. `solutionfile.sln` references project path `GM31 23.04.18\\GM31 23.04.18.vcxproj`, but the submitted package stores the project under a differently named source folder. The solution is therefore not self-consistent as packaged.
2. The `.vcxproj` lists `imgui\\...` files relative to the project directory, but the submitted ImGui sources are under the separate runtime/execution folder. The listed relative paths are missing from the source project directory.
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
{large_table}

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
{dup_table}

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
''')

wr('docs/analysis/PROJECT_ANALYSIS.ja.md',f'''
# プロジェクト解析結果 — DirectX就活作品

## 解析範囲

提出ZIP全体を列挙し、**全{len(rows)}ファイル**を `FULL_FILE_INVENTORY.csv` に記録しました。パス、分類、サイズ、SHA-256、拡張子、判定できる文字コード、ソース側ファイルについては `.vcxproj` 掲載有無も残しています。第一者C/C++コードは `SOURCE_METRICS.csv` で追加解析しています。

この環境はWindows/DirectX実行環境ではないため、実ビルドはしていません。以下では「ファイルから確認できた事実」と「Windowsで確認すべき事項」を分けています。

## 数値

- 全ファイル: **{len(rows)}**
- ソースフォルダの第一者C/C++: **{len(source_files)}ファイル**
- 同C/C++行数: **約{loc:,}行**
- 文字コード: **{dict(enc_counts)}**
- 生 `new`: **{new_total}箇所**
- `delete`: **{del_total}箇所**
- HLSL: **{ext_counts['.hlsl']}ファイル**
- 3Dモデル: **FBX {ext_counts['.fbx']} / OBJ {ext_counts['.obj']}**
- WAV: **{ext_counts['.wav']}**

## 元作品の強み

これは描画サンプルだけではありません。Direct3D 11、Win32ループ、Scene/GameObject/Component、モデル読み込み、Assimpによるボーンアニメーション、**CPUスキニング**、分離軸法による**OBB当たり判定**、プレイヤー戦闘、敵AI、特殊攻撃、複数シーン、HUD/クエスト/店舗、XAudio2、ImGui、HLSLの影・リムライト・ディゾルブまで確認できました。

就活では「AIで作り直した」より、**この自作実装を守りながら設計を改善した**方が価値を説明しやすいです。

## 最優先 P0: ビルド再現性

1. `solutionfile.sln` は `GM31 23.04.18\\GM31 23.04.18.vcxproj` を参照していますが、提出ZIP内の実際のプロジェクト配置と一致していません。
2. `.vcxproj` は `imgui\\...` をプロジェクト相対で参照しますが、実ファイルは別の実行用フォルダ側にあります。
3. `animationModel.h` の `assimp/...` も同様に、ヘッダは実行用フォルダ側にあります。解析したプロジェクト設定から明示的な `AdditionalIncludeDirectories` は確認できませんでした。
4. `.vcxproj` は `v143` ですが、`.sln` ヘッダはVisual Studio 15表記で、提出者/採用担当者に混乱を与えます。
5. `.exe/.pdb/.cso/.dll/debug log` がソースと混在しています。

最初のCodex作業はアーキテクチャ変更ではなく、**Windows x64 Debugを誰でも再現できる提出構成に直すこと**にしてください。

## 最優先 P0: 素材ライセンス/出典

モデル・画像・音声・Assimp・ImGuiを含む一方、ZIP内からライセンス/クレジット文書を確認できませんでした。ファイル名から外部素材と思われるものもあります。これは違反を断定するものではありませんが、**公開GitHubや企業提出前に出典と再配布可否を必ず確認**してください。

確認できない素材は公開版から外す/置き換える方針が安全です。

## P1: メモリ所有権

- `GameObject::Destroy()` が `Uninit(); delete this;` を行い、`Scene::Update()` の `remove_if` から呼ばれています。
- `Scene` が `GameObject*`、`GameObject` が `Component*` を所有して手動deleteしています。
- 多態基底 `Scene` / `GameObject` / `Component` に明示的virtual destructorがありません。
- UIクラスでは多数の `Sprit2D` を `new` していますが、`Uninit()` は `Uninit()` 呼び出しだけで `delete` していないものがあり、所有関係を見る限りリーク候補です。
- Direct3DのCOMオブジェクトも各所で手動 `Release()` されています。

この部分は就活リファクタリングの主役にできます。`unique_ptr` と `ComPtr` を段階的に導入し、**所有者/参照者を説明できるコード**にします。

## P1: 巨大関数

代表例:

- `Player::UpdateGround()` 約494行
- `Renderer::Init()` 約302行
- `QuestDeskUi::Update()` 約258行
- `AnimationModel::Update()` 約240行
- `Player::Update()` 約236行
- `WeaponStoreUi::Update()` 約230行
- `VillageUi::Update()` 約219行
- `CollisionBox::SetOBB()` 約154行

ただし最初に分割すると動作差分の原因追跡が難しくなるため、ビルド/所有権を安定させてから行います。

## P1: PC名付き競合コピー

{chr(10).join(f'- `{a}` vs `{b}`: 行類似度 {ratio:.1%} ({la}/{lb}行)' for a,b,ratio,la,lb in pairs)}

特に `villageUi-DESKTOP-2FSCGV3.cpp` は元名ファイルと大きく異なるため、自動削除禁止です。`.vcxproj` にDESKTOP版が掲載されていないことは手掛かりですが、実動作/Git履歴も確認して正本を決めます。

## P1: CP932/UTF-8混在

第一者コードはCP932とUTF-8 BOMが混在しています。**意味変更なしの専用コミット**でUTF-8へ統一してください。リネームやロジック変更と同時にやるとレビュー不能になります。

## P2: 命名

`collition`, `bace`, `sprit`, `recepition`, `Damege`, `Rondom`, `Flame(Frameの意図と思われる箇所)` などが見られます。これらは就活レビュー時の読みやすさに直結するため改善価値がありますが、専用のrename mapを作って小分けにします。

## P2: D3DXレガシー

`main.h` は `d3dx9.h` / `d3dx11.h` と対応libを使用しています。MicrosoftはD3DXを非推奨/レガシーとしてDirectXMath等への移行を推奨しています。ただしこれは影響範囲が広いため、**後半の独立フェーズ**にします。

## 推奨順序

1. 提出構成とビルド再現性
2. 元コード固定・ハッシュ化
3. 文字コード統一だけ
4. 競合コピー/ビルド生成物整理
5. 所有権・`delete this`・virtual destructor・`unique_ptr`
6. COMの`ComPtr`
7. Player/UI/Renderer/Animationの巨大関数分割
8. state/定数/データの整理
9. フォルダと命名
10. 任意でD3DX→DirectXMath等
11. Before/Afterと採用担当者向け説明

全ファイルの詳細は `FULL_FILE_INVENTORY.csv`、全C/C++の数値は `SOURCE_METRICS.csv` を参照してください。
''')

wr('docs/analysis/DUPLICATE_REPORT.md',f'''
# Conflict-copy report

These files contain machine-name conflict suffixes and have a base-name counterpart.

| Conflict copy | Base | Similarity | Lines conflict/base |
|---|---|---:|---:|
{dup_table}

Policy: do not delete automatically. First check `.vcxproj` membership, runtime behavior, timestamps/Git history if available, and semantic differences. Record the chosen canonical file in `docs/refactor/RENAME_MAP.md` or an exec plan.
''')

# Refactor docs
wr('docs/refactor/REFACTOR_PLAN.md','''
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
''')
wr('docs/refactor/REFACTOR_PLAN.ja.md','''
# リファクタリング実施計画

## Phase 0 — 元状態の固定と再現

元コードをGit tag/`archive/original` で固定し、SHA-256を保存。まずプロジェクトパス、ImGui/Assimp配置、VS2022 v143 x64 Debugビルド、外部前提条件、手動スモークテストを整えます。

## Phase 1 — 機械的整理

CP932→UTF-8、改行、`.gitignore`、生成物整理、PC名付き競合コピーの解決、ライセンス文書を行います。**ロジック変更禁止**です。

## Phase 2 — 寿命/所有権

virtual destructor、`delete this` の撤去、`Scene -> GameObject` と `GameObject -> Component` の `unique_ptr` 化、UI子オブジェクトのリーク候補を修正します。参照だけのポインタまで無理にshared_ptrにしません。

## Phase 3 — Direct3D COM所有

葉の描画クラスから `Microsoft::WRL::ComPtr` へ段階移行。描画順、シェーダ、定数、見た目は変更しません。

## Phase 4 — 巨大関数分割

`Player` → `Enemy` → `QuestDeskUi` → `WeaponStoreUi` → `VillageUi` → `Renderer::Init` → `AnimationModel::Update` の順を推奨します。1クラスずつ、入力/状態遷移/状態処理/アニメ/エフェクト/当たり判定等に抽出します。

## Phase 5 — stateとデータ

boolean群をいきなり消さず、挙動を把握してから明示的stateへ。アセットパスや定数は型付きテーブル/設定へ整理します。

## Phase 6 — モジュール/命名

`app/core/render/gameplay/ui/audio/assets` 等へ整理し、rename mapに従って綴りを小分け修正します。

## Phase 7 — 任意: D3DX近代化

最後にDirectXMath等へ。数学型が広範囲に影響するため、他のリファクタリングと混ぜません。

## Phase 8 — 就活提出仕上げ

Before/After、アーキテクチャ、ビルド手順、素材出典、「自作部分/ライブラリ部分」、可能なら短い動画を整備します。
''')

wr('docs/refactor/ACCEPTANCE_CRITERIA.md','''
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
''')
wr('docs/refactor/ACCEPTANCE_CRITERIA.ja.md','''
# 完了条件

## 全タスク共通

- [ ] 元コードスナップショット未変更
- [ ] 1タスク1主目的
- [ ] 指示していないゲーム仕様/見た目/バランス変更なし
- [ ] 所有権変更を説明できる
- [ ] 新しい「所有目的の生ポインタ」を無説明で増やしていない
- [ ] アセット/シェーダパス変更は理由と検証あり
- [ ] 該当スクリプト実行済み
- [ ] Windowsビルド/実行の実施有無を正直に記録
- [ ] 就活上重要な変更はBefore/Afterログ更新

## 手動スモークテスト

起動/タイトル、シーン遷移、移動/カメラ、通常攻撃、回避/ダメージ/回復、特殊攻撃、敵の索敵/追跡/攻撃/死亡、OBB、アニメ、影/リム/ディゾルブ、HUD、クエスト、武器屋/雑貨屋、村インタラクション、BGM/SE、結果/ゲームオーバー、正常終了を最低限確認します。
''')

wr('docs/refactor/RENAME_MAP.md','''
# Rename Map

Record rename-only work here before applying it.

| Status | Old name | Proposed name | Scope | Reason | Behavior impact |
|---|---|---|---|---|---|
| proposed | `collitionBox.*` / `CollisionBox` references | `collisionBox.*` / `CollisionBox` | file/include names | spelling/readability | none intended |
| proposed | `baceCampObj.*` / `BaceCampObj` | `baseCampObj.*` / `BaseCampObj` | file/type | spelling | none intended |
| proposed | `sprit2D.*` / `Sprit2D` | `sprite2D.*` / `Sprite2D` | file/type | spelling | none intended |
| proposed | `recepitionPointer.*` | `receptionPointer.*` | file/type | spelling | none intended |
| proposed | `GetFlam` / `SetFlam` / `g_Flame` | `GetFrameRate` / `SetFrameRate` / `g_FrameRate` | app timing | clarify likely intent | none intended; verify semantics |

Do not apply all rows at once. Confirm public API/include impact and update this table with the actual commit.
''')

# design docs
wr('docs/design-docs/core-beliefs.md','''
# Core Beliefs

1. **Original authorship is evidence.** Keep the legacy snapshot immutable and visible.
2. **Behavior preservation beats elegance.** A smaller safe diff is better than a beautiful rewrite with unverifiable behavior.
3. **Ownership should be obvious.** Reviewers should be able to tell who destroys an object/resource.
4. **Build reproducibility is a feature.** A reviewer should not need the author's old PC layout.
5. **One axis of change at a time.** Encoding, naming, ownership, behavior, dependency upgrades, and architecture moves should not be mixed.
6. **Documents describe code, not aspirations.** Update architecture docs when facts change.
7. **Third-party boundaries must be explicit.** Separate what the author implemented from Assimp, ImGui, and external assets.
8. **AI is a controlled collaborator.** Codex may propose and implement changes, but harness gates, diffs, tests, and human decisions remain visible.
''')
wr('docs/design-docs/core-beliefs.ja.md','''
# 設計原則

1. 元コードは「自分で作った証拠」として不変で残す。
2. 綺麗さより動作維持を優先する。
3. 誰が解放するか分かる所有権にする。
4. 他PCでビルドできること自体を品質とみなす。
5. 文字コード・命名・所有権・仕様・依存更新・フォルダ移動を混ぜない。
6. ドキュメントは理想ではなく実コードの事実を書く。
7. 自作部分とAssimp/ImGui/外部素材の境界を明示する。
8. Codexは制御された共同作業者とし、差分・検証・判断を残す。
''')

# exec plans
wr('docs/exec-plans/README.md','''
# Exec Plans

Create one Markdown file per non-trivial Codex task: `YYYY-MM-DD-short-task-name.md`.

Use `TEMPLATE.md`. Keep plans current while the task is active; close them with actual validation results, not intended results.
''')
wr('docs/exec-plans/TEMPLATE.md','''
# <Task title>

## Goal

## In scope

## Out of scope

## Observed files/dependencies

## Behavior invariants

## Planned steps

## Validation commands/checks

## Risks and rollback

## Result

## Validation evidence

## Follow-up
''')

# prompts
wr('docs/prompts/CODEX_TASK_PROMPTS.md','''
# Codex Task Prompts

Use these as starting prompts. `AGENTS.md` remains the persistent source of rules.

## 0. First task — baseline only

```text
Read AGENTS.md, docs/analysis/PROJECT_ANALYSIS.md, docs/refactor/REFACTOR_PLAN.md, and docs/refactor/ACCEPTANCE_CRITERIA.md.
Perform Phase 0 only: establish an immutable original snapshot and make the repository/build layout reproducible for Visual Studio 2022 v143 x64 Debug without changing gameplay or C++ logic.

First inspect the .sln/.vcxproj, ImGui/Assimp locations, shader/runtime working-directory assumptions, and D3DX prerequisites. Create an exec plan before edits.
Do not modernize C++, rename classes, convert encoding, or migrate D3DX in this task.
After changes, report exact build commands attempted, whether they succeeded, unresolved blockers, and files changed.
```

## 1. Encoding normalization

```text
Perform only the encoding/line-ending part of Phase 1. Convert first-party C/C++ text to UTF-8 consistently according to .editorconfig. Do not rename symbols, reformat code broadly, or change logic/string contents. Run the encoding checker before and after and summarize any file that cannot be converted losslessly.
```

## 2. Resolve conflict copies

```text
Analyze every *-DESKTOP-2FSCGV3.* conflict copy against its base file. Use vcxproj membership, includes/references, behavior/build evidence, and Git history if available to decide canonical status. Do not delete materially different copies without evidence. Produce an exec plan and a decision table first; then make only conflict-copy cleanup changes.
```

## 3. Remove delete-this ownership

```text
Refactor only the Scene/GameObject destruction path so GameObject never self-deletes. Preserve object update order and the public SetDestroy intent. Introduce the smallest safe owner-managed deletion design, add required virtual destructors, and do not refactor gameplay classes in the same task. Add/update focused tests or static verification where practical and run the manual smoke-test subset that can be executed.
```

## 4. Convert Scene object ownership

```text
After delete-this is removed, migrate Scene's owned GameObject collection to explicit unique ownership. Keep GetGameObject/GetGameObjects observer APIs behavior-compatible unless a small signature change is required and propagated safely. Do not convert unrelated observer pointers to shared_ptr. Validate scene transitions and destruction.
```

## 5. Refactor Player in slices

```text
Characterize Player behavior first. Create a map of Player states, input conditions, animation names/frame counters, spawned effects, and collision side effects. Then extract exactly one responsibility from Player (for example input collection or one state update) without changing constants, state transition order, or animation timing. One responsibility per task.
```

## 6. Portfolio evidence review

```text
Read the original snapshot and current refactored code plus docs/portfolio/BEFORE_AFTER_LOG.md. Identify the five strongest reviewer-facing improvements that are supported by concrete diffs and validation evidence. Do not exaggerate. Update the reviewer guide to clearly separate original author work, third-party dependencies, and AI-assisted refactoring work.
```
''')
wr('docs/prompts/CODEX_TASK_PROMPTS.ja.md','''
# Codex実行用プロンプト

## 0. 最初のタスク — ベースラインのみ

```text
AGENTS.md、docs/analysis/PROJECT_ANALYSIS.md、docs/refactor/REFACTOR_PLAN.md、docs/refactor/ACCEPTANCE_CRITERIA.md を読んでください。
Phase 0だけを実施してください。元コードを不変スナップショットとして固定し、ゲームロジックやC++動作を変えずにVisual Studio 2022 v143 x64 Debugで再現可能なリポジトリ/ビルド配置を作ってください。

最初に.sln/.vcxproj、ImGui/Assimp配置、shader/assetsのworking directory前提、D3DX前提条件を調査し、編集前にexec planを作成してください。
このタスクではC++近代化、クラス名変更、文字コード変換、D3DX移行をしないでください。
最後に実行したビルドコマンド、成功/失敗、未解決ブロッカー、変更ファイルを正確に報告してください。
```

## 1. 文字コードだけ

```text
Phase 1のうち文字コード/改行統一だけを実施してください。第一者C/C++を.editorconfigに従ってUTF-8へ統一し、シンボル名変更、大規模整形、ロジック/文字列内容変更を行わないでください。前後でencoding checkerを実行し、可逆変換できないファイルがあれば列挙してください。
```

## 2. PC名付きコピー

```text
*-DESKTOP-2FSCGV3.* と元名ファイルをすべて比較してください。.vcxproj掲載、include/reference、ビルド/実動作、Git履歴があればそれも使って正本を判定してください。差分が大きいファイルは根拠なしに削除しないでください。最初に判断表を作り、その後この整理だけを実施してください。
```

## 3. delete this撤去

```text
Scene/GameObjectの破棄経路だけをリファクタリングし、GameObjectが自分自身をdeleteしない設計にしてください。Update順とSetDestroyの意味は維持してください。必要なvirtual destructorを追加し、ゲームプレイクラスの整理は同じタスクで行わないでください。
```

## 4. Player分割

```text
まずPlayerのstate、入力条件、アニメ名/フレーム、生成エフェクト、当たり判定副作用を表にしてください。その後、1タスクにつき1責務だけ抽出してください。定数、状態遷移順、アニメタイミングは変えないでください。
```
''')

# portfolio docs
wr('docs/portfolio/REVIEWER_GUIDE.md','''
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

> The original game implementation was created by me. I later designed a Codex harness (`AGENTS.md`, skills, phased acceptance gates, analysis scripts) and used Codex as an AI-assisted refactoring partner. I reviewed the diffs, decided refactoring boundaries, and validated behavior. The repository preserves the original version for comparison.

This is stronger than implying the refactored version was written entirely without assistance or, conversely, implying AI created the original project.

## Suggested review order

1. README/demo media
2. original-vs-refactored architecture summary
3. five selected before/after diffs
4. collision/animation/rendering code as technical highlights
5. harness and validation evidence
6. full history only if the reviewer wants detail
''')
wr('docs/portfolio/REVIEWER_GUIDE.ja.md','''
# 採用担当者向け見せ方

この作品では元コードを隠さず、**自作した非小規模コードを理解し、問題を分析し、AIエージェントを制御して段階改善し、動作を検証できること**を見せます。

## 元実装の見せ場

Win32 + Direct3D 11、HLSLの影/リム/ディゾルブ、AssimpボーンアニメーションとCPUスキニング、OBB分離軸判定、Scene/GameObject/Component、プレイヤー戦闘/敵AI、クエスト/店舗/村UI、XAudio2、ImGuiです。

## 改善後に強調するポイント

1. 作者PC依存からclean cloneで再現できるビルドへ
2. `delete this`/手動寿命から明示的所有権/RAIIへ
3. 200〜500行級Updateを挙動維持のまま責務分割
4. 自作/第三者ライブラリ/素材の境界明確化
5. 実施できた場合のみD3DX等の近代化

## AI利用の説明例

> 元のゲーム実装は自分で作成しました。その後、`AGENTS.md`、skills、段階的な完了条件、解析スクリプトからなるCodex用ハーネスを自分で設計し、Codexをリファクタリングの補助として利用しました。差分のレビュー、改善範囲の判断、動作確認は自分で行い、比較できるよう元版も保存しています。

この説明なら「元作品までAI生成」と誤解されず、AIを開発プロセスに組み込む力も示せます。
''')
wr('docs/portfolio/BEFORE_AFTER_LOG.md','''
# Before / After Evidence Log

| ID | Problem | Original location | Decision | Refactored location/commit | Evidence | Behavior preserved? |
|---|---|---|---|---|---|---|
| 001 | _fill after first refactor_ | | | | | |

For each entry, include a small diff/screenshot/link rather than a long essay.
''')
wr('docs/portfolio/ASSET_LICENSE_CHECKLIST.md','''
# Asset and Third-Party License Checklist

Do not publish the full asset package until this table is completed.

| Item/group | Origin/source URL | Author | License | Redistribution allowed? | Attribution required? | Proof saved? | Public portfolio action |
|---|---|---|---|---|---|---|---|
| Assimp | | | | | | | |
| Dear ImGui | | | | | | | |
| FBX character/animation assets | | | | | | | |
| OBJ environment/weapon assets | | | | | | | |
| Textures/UI images | | | | | | | |
| BGM/SE WAV files | | | | | | | |

If provenance cannot be established, do not guess. Replace, omit, or keep the asset only in a private/non-redistributed review package as permitted by its terms.
''')
wr('docs/portfolio/ASSET_LICENSE_CHECKLIST.ja.md','''
# 素材・第三者ライセンス確認表

この表を埋めるまで、全アセット入りの公開GitHub化はしない方針です。Assimp、ImGui、FBX/OBJ、画像、BGM/SEごとに「入手先URL・作者・ライセンス・再配布可否・クレジット要否・証拠保存先・公開版での扱い」を確認してください。出典不明なら推測せず、置換/非公開/削除を判断します。
''')

# skills
skills={
'directx-safe-refactor':('Behavior-preserving refactoring workflow for the legacy DirectX 11 C++ portfolio project. Use for ownership, decomposition, naming, or architecture refactors while protecting original behavior.', '''
# DirectX Safe Refactor

## Inputs
- Target refactoring objective
- Relevant source files
- Current exec plan if one exists

## Workflow
1. Read root `AGENTS.md` and relevant analysis/refactor docs.
2. Identify owners, observers, global dependencies, asset/shader paths, state transitions, and timing constants touched by the target.
3. Write behavior invariants before editing.
4. Limit the patch to one primary concern.
5. Prefer extraction and ownership clarification over rewrites.
6. Do not change gameplay constants, animation frame values, collision thresholds, render order, shader constants, or asset paths unless explicitly required.
7. Run applicable static checks/build/smoke tests.
8. Update `BEFORE_AFTER_LOG.md` if the change is portfolio-significant.

## Required final report
- Files changed
- Why each change was necessary
- Behavior invariants
- Validation actually run
- Remaining risk
- Next smallest recommended refactor

## Final checks
- Original snapshot unchanged
- No new unexplained owning raw pointer
- No new `delete this`
- No unrelated rename/formatting churn
- No claimed test that was not run
'''),
'build-reproducibility':('Workflow for making the DirectX portfolio build reproducible on a clean Windows/Visual Studio environment without changing gameplay logic.', '''
# Build Reproducibility

## Workflow
1. Inspect `.sln`, `.vcxproj`, source/runtime directory layout, relative includes, library paths, working directory, shaders, and runtime DLLs.
2. Compare project-listed files with files on disk.
3. Move/copy dependencies only into explicit `third_party/` or documented package locations; do not edit game logic.
4. Establish one canonical target first: Visual Studio 2022 v143 x64 Debug.
5. Document D3DX/DirectX prerequisites rather than silently assuming the author's machine state.
6. Verify the runtime working directory resolves `asset/` and `shader/` paths.
7. Record exact clean-build steps and any unresolved external prerequisite.

## Output
- Build prerequisites
- Repository layout changes
- Exact build command/IDE steps
- Success/failure evidence
- Runtime working-directory requirement
- Remaining blockers

## Prohibited
- C++ architecture refactor
- broad symbol rename
- encoding conversion
- D3DX-to-DirectXMath migration
- gameplay changes
'''),
'portfolio-review':('Evidence-first review workflow for presenting the original and refactored DirectX project to hiring reviewers without overstating AI or personal authorship.', '''
# Portfolio Review

## Workflow
1. Compare immutable original and current refactored code.
2. Select improvements only when supported by concrete diffs and validation.
3. Separate three categories clearly: original author implementation, third-party library/asset contributions, AI-assisted refactoring.
4. Prefer five strong before/after examples over dozens of cosmetic changes.
5. Check that build/run instructions are reproducible and licensing notes are complete.
6. Remove exaggerated claims such as “engine from scratch” unless the repository evidence supports the exact scope.

## Reviewer-facing output
- 30-second project summary
- Original technical highlights
- Five refactor highlights
- What Codex did vs what the author decided/reviewed/validated
- How to build/run
- Known limitations
- Third-party notices
''')
}
for name,(desc,body) in skills.items():
    wr(f'.codex/skills/{name}/SKILL.md',f'''---\nname: {name}\ndescription: {desc}\n---\n{body}''')

# ja mirror skill docs
wr('.codex/skills/directx-safe-refactor/SKILL.ja.md','''
# DirectX安全リファクタリング（日本語ミラー）

対象の所有権、参照関係、グローバル依存、アセット/シェーダパス、state遷移、タイミング定数を先に確認し、不変条件を書いてから1主目的だけ変更します。ゲーム定数、アニメフレーム、当たり判定閾値、描画順、シェーダ定数、アセットパスは明示指示なしに変えません。変更後は実際に行った検証だけを報告し、就活上重要ならBefore/Afterログを更新します。
''')
wr('.codex/skills/build-reproducibility/SKILL.ja.md','''
# ビルド再現性（日本語ミラー）

`.sln/.vcxproj`、実ファイル配置、include/lib、working directory、shader、DLLを確認し、まずVS2022 v143 x64 Debugだけを正本として再現可能にします。このskillではC++設計変更、rename、文字コード変換、D3DX移行、ゲーム仕様変更を行いません。
''')
wr('.codex/skills/portfolio-review/SKILL.ja.md','''
# 就活レビュー（日本語ミラー）

元版と改善版の具体的diff/検証に基づき、強いBefore/Afterを5件程度選びます。「元から自分が実装した部分」「第三者ライブラリ/素材」「Codex補助で改善した部分」を分離し、AI利用も誇張/隠蔽せず説明します。
''')

# editorconfig/gitignore
wr('.editorconfig','''
root = true

[*]
charset = utf-8
end_of_line = crlf
insert_final_newline = true
trim_trailing_whitespace = true

[*.md]
end_of_line = lf
trim_trailing_whitespace = false

[*.{sln,vcxproj,filters}]
end_of_line = crlf
''')
wr('.gitignore','''
# Visual Studio
.vs/
**/Debug/
**/Release/
**/x64/
**/x86/
*.user
*.suo
*.pdb
*.idb
*.tlog
*.lastbuildstate
*.log

# Build outputs
*.exe
*.obj
*.ilk

# Keep intentional runtime DLL/CSO only through explicit allow-list decisions.
# Do not blindly ignore third-party runtime DLLs required by the demo.

# OS/editor conflict artifacts
*-DESKTOP-*.cpp
*-DESKTOP-*.h
.DS_Store
Thumbs.db
''')

# scripts
wr('scripts/analyze_repository.py',r'''
#!/usr/bin/env python3
"""Create a deterministic repository inventory without external dependencies."""
from pathlib import Path
import argparse, csv, hashlib

def digest(path):
    h=hashlib.sha256()
    with path.open('rb') as f:
        for chunk in iter(lambda:f.read(1024*1024),b''): h.update(chunk)
    return h.hexdigest()

def detect_text(path):
    data=path.read_bytes()
    for enc in ('utf-8-sig','utf-8','cp932'):
        try: return enc, len(data.decode(enc).splitlines())
        except UnicodeDecodeError: pass
    return 'binary/unknown',''

def main():
    ap=argparse.ArgumentParser(); ap.add_argument('root',type=Path); ap.add_argument('-o','--output',type=Path,default=Path('inventory.csv')); a=ap.parse_args()
    rows=[]
    for p in sorted(a.root.rglob('*')):
        if not p.is_file(): continue
        enc,lines=detect_text(p) if p.suffix.lower() in {'.cpp','.h','.hpp','.hlsl','.md','.sln','.vcxproj','.filters','.ini'} else ('binary/unknown','')
        rows.append({'path':p.relative_to(a.root).as_posix(),'size_bytes':p.stat().st_size,'extension':p.suffix.lower(),'sha256':digest(p),'encoding':enc,'lines':lines})
    a.output.parent.mkdir(parents=True,exist_ok=True)
    with a.output.open('w',newline='',encoding='utf-8-sig') as f:
        w=csv.DictWriter(f,fieldnames=rows[0].keys());w.writeheader();w.writerows(rows)
    print(f'wrote {len(rows)} files to {a.output}')
if __name__=='__main__': main()
''')
wr('scripts/snapshot_tree.py',r'''
#!/usr/bin/env python3
"""Snapshot file SHA-256 hashes so archive/original can be proven unchanged."""
from pathlib import Path
import argparse, hashlib, json

def digest(p):
    h=hashlib.sha256()
    with p.open('rb') as f:
        for c in iter(lambda:f.read(1024*1024),b''):h.update(c)
    return h.hexdigest()

def main():
    ap=argparse.ArgumentParser();ap.add_argument('root',type=Path);ap.add_argument('-o','--output',type=Path,default=Path('snapshot.json'));a=ap.parse_args()
    data={p.relative_to(a.root).as_posix():digest(p) for p in sorted(a.root.rglob('*')) if p.is_file()}
    a.output.write_text(json.dumps(data,indent=2,ensure_ascii=False),encoding='utf-8')
    print(f'wrote {len(data)} hashes to {a.output}')
if __name__=='__main__':main()
''')
wr('scripts/compare_snapshot.py',r'''
#!/usr/bin/env python3
from pathlib import Path
import argparse, hashlib, json, sys

def digest(p):
    h=hashlib.sha256()
    with p.open('rb') as f:
        for c in iter(lambda:f.read(1024*1024),b''):h.update(c)
    return h.hexdigest()

def main():
    ap=argparse.ArgumentParser();ap.add_argument('root',type=Path);ap.add_argument('snapshot',type=Path);a=ap.parse_args()
    old=json.loads(a.snapshot.read_text(encoding='utf-8'))
    now={p.relative_to(a.root).as_posix():digest(p) for p in sorted(a.root.rglob('*')) if p.is_file()}
    added=sorted(set(now)-set(old));removed=sorted(set(old)-set(now));changed=sorted(k for k in set(old)&set(now) if old[k]!=now[k])
    for label,items in [('ADDED',added),('REMOVED',removed),('CHANGED',changed)]:
        for x in items: print(label,x)
    if added or removed or changed: sys.exit(1)
    print('snapshot matches')
if __name__=='__main__':main()
''')
wr('scripts/check_text_encoding.py',r'''
#!/usr/bin/env python3
from pathlib import Path
import argparse, sys

def main():
    ap=argparse.ArgumentParser();ap.add_argument('root',type=Path);a=ap.parse_args();bad=[];legacy=[]
    for p in sorted(a.root.rglob('*')):
        if p.suffix.lower() not in {'.cpp','.h','.hpp','.hlsl'}: continue
        b=p.read_bytes()
        try:b.decode('utf-8-sig');continue
        except UnicodeDecodeError:pass
        try:b.decode('cp932');legacy.append(p);continue
        except UnicodeDecodeError:bad.append(p)
    for p in legacy:print('CP932',p)
    for p in bad:print('UNKNOWN',p)
    if bad:sys.exit(2)
    if legacy:sys.exit(1)
    print('all target text is UTF-8 compatible')
if __name__=='__main__':main()
''')
wr('scripts/check_no_desktop_duplicates.py',r'''
#!/usr/bin/env python3
from pathlib import Path
import argparse,sys
ap=argparse.ArgumentParser();ap.add_argument('root',type=Path);a=ap.parse_args()
files=[p for p in a.root.rglob('*') if p.is_file() and '-DESKTOP-' in p.name]
for p in files:print(p)
if files:sys.exit(1)
print('no machine-name conflict copies found')
''')
wr('scripts/verify_harness.py',r'''
#!/usr/bin/env python3
from pathlib import Path
import sys
root=Path(__file__).resolve().parents[1]
required=[
 'AGENTS.md','AGENTS.ja.md','ARCHITECTURE.md','README.md','README.ja.md',
 'docs/analysis/PROJECT_ANALYSIS.md','docs/analysis/PROJECT_ANALYSIS.ja.md',
 'docs/analysis/FULL_FILE_INVENTORY.csv','docs/analysis/SOURCE_METRICS.csv',
 'docs/refactor/REFACTOR_PLAN.md','docs/refactor/ACCEPTANCE_CRITERIA.md',
 'docs/prompts/CODEX_TASK_PROMPTS.md',
 '.codex/skills/directx-safe-refactor/SKILL.md',
 '.codex/skills/build-reproducibility/SKILL.md',
 '.codex/skills/portfolio-review/SKILL.md']
missing=[x for x in required if not (root/x).exists()]
if missing:
 print('missing:');[print(' -',x) for x in missing];sys.exit(1)
print('harness structure OK')
''')

# source catalog: group based on filename tokens
categories={
 'core/app': ['main','manager','scene','gameObject','component','input'],
 'render/model': ['renderer','drawModel','model','animationModel','meshField','field','sky','dome','box','cylinder','sprite','sprit2D','spritefield','trail'],
 'player/combat': ['player','weapon','bullet','specialAttack','attackPrediction','explosion','healEffect'],
 'enemy': ['enemy','otomo'],
 'scene': ['title','game','village','tutorial','result','loading'],
 'ui/economy': ['Ui','ui','score','money','DataLoad','DataBase','medicalItem','Desk','Pointer'],
 'world-objects': ['Obj','tree','windmill','house','benti','ido','Gate','Bord','Board'],
}
def source_cat(name):
 stem=Path(name).stem
 for c,toks in categories.items():
  if any(tok in stem for tok in toks):return c
 return 'other'
cat_lines=[]
for r in src_rows:
 cat_lines.append(f"| `{r['file']}` | {source_cat(r['file'])} | {r['lines']} | {r['encoding']} | {'yes' if r['listed_in_vcxproj'] else 'no'} |")
wr('docs/analysis/SOURCE_CATALOG.md','''
# First-party Source Catalog

This catalog covers every `.cpp/.h/.hpp` file in the submitted source folder. Detailed metrics are in `SOURCE_METRICS.csv`.

| File | Heuristic area | Lines | Encoding | In vcxproj |
|---|---|---:|---|---|
'''+"\n".join(cat_lines))

# current observations JSON for scripts/repro
obs={'total_files':len(rows),'source_files':len(source_files),'source_loc':loc,'source_encodings':dict(enc_counts),'raw_new':new_total,'delete':del_total,'categories':dict(cat_counts),'duplicate_pairs':[{'conflict':a,'base':b,'similarity':ratio,'conflict_lines':la,'base_lines':lb} for a,b,ratio,la,lb in pairs]}
(OUT/'docs/analysis/OBSERVATIONS.json').write_text(json.dumps(obs,indent=2,ensure_ascii=False),encoding='utf-8')

# copy analysis-generation script itself
shutil.copy2(BASE/'build_harness.py',OUT/'scripts/_generation_reference.py')
print(OUT)
