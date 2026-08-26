# DirectX就活作品 — Codexリファクタリング・ハーネス

これは元ゲームを置き換えるものではなく、**元作品を保護しながらCodexで段階的に改善するためのハーネス**です。提出ZIP全体を棚卸しし、622ファイル、第一者C/C++コード178ファイル、ソースフォルダ内C/C++約20,350行を静的解析した結果を反映しています。

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
- 全622ファイルの棚卸し: [`docs/analysis/FULL_FILE_INVENTORY.csv`](docs/analysis/FULL_FILE_INVENTORY.csv)

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
