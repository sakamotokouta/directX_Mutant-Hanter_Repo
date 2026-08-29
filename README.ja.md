# DirectX就活作品 — Claude Codeリファクタリング・ハーネス

これは元ゲームを置き換えるものではなく、**元作品を保護しながらClaude Codeで段階的に改善するためのハーネス**です。提出ZIP全体を棚卸しし、622ファイル、第一者C/C++コード178ファイル、ソースフォルダ内C/C++約20,350行を静的解析した結果を反映しています。

## 就活で見せるストーリー

1. **Original:** DirectX 11で描画、アニメーション、衝突、戦闘、UI、音声、シーン/ゲームロジックまで自作。
2. **Analysis:** 元コードを隠さず、再現性・所有権・保守性・レガシーAPIの問題を分析。
3. **Refactor:** Claude Codeをハーネスで制御し、挙動を維持したまま段階的に改善。
4. **Evidence:** Before/After、ビルド/実行結果、設計判断、AI利用範囲を証拠として残す。

## `CLAUDE.md` を使う理由

Claude Codeではプロジェクトの継続指示に `CLAUDE.md` を使います。繰り返し手順は `.claude/skills/`、対象ファイルごとの規約は `.claude/rules/`、絶対に守りたい制約はhooks/settingsへ分離します。

`CLAUDE.md`など英語版をClaude Code向け正本とし、日本語版はあなた自身が内容を説明・レビューするためのミラーです。日本語版を自動指示の正本にしないことで、同じ指示の二重読み込みを避けます。

## 最初に読むファイル

- Claude Code入口: [`CLAUDE.md`](CLAUDE.md)
- 人間向け日本語版: [`CLAUDE.ja.md`](CLAUDE.ja.md)
- Claude Code使用方法: [`docs/claude/USAGE.ja.md`](docs/claude/USAGE.ja.md)
- アーキテクチャ: [`ARCHITECTURE.ja.md`](ARCHITECTURE.ja.md)
- 解析結果: [`docs/analysis/PROJECT_ANALYSIS.ja.md`](docs/analysis/PROJECT_ANALYSIS.ja.md)
- リファクタリング計画: [`docs/refactor/REFACTOR_PLAN.ja.md`](docs/refactor/REFACTOR_PLAN.ja.md)
- 完了条件: [`docs/refactor/ACCEPTANCE_CRITERIA.ja.md`](docs/refactor/ACCEPTANCE_CRITERIA.ja.md)
- Claude Code用プロンプト: [`docs/prompts/CLAUDE_TASK_PROMPTS.ja.md`](docs/prompts/CLAUDE_TASK_PROMPTS.ja.md)
- 採用担当者向け見せ方: [`docs/portfolio/REVIEWER_GUIDE.ja.md`](docs/portfolio/REVIEWER_GUIDE.ja.md)

## Claude Code用に追加した仕組み

```text
.claude/
├─ settings.json                  # hook設定
├─ hooks/
│  └─ protect-original.ps1        # archive/original保護
├─ skills/
│  ├─ build-reproducibility/
│  ├─ directx-safe-refactor/
│  └─ portfolio-review/
├─ rules/
│  ├─ cpp-safety.md
│  ├─ shader-safety.md
│  └─ visual-studio-project.md
└─ agents/
   └─ refactor-reviewer.md
```

特に `archive/original/**` は、`CLAUDE.md`の指示だけでなくPreToolUse hookでもClaude Codeからの直接書き込みを防ぎます。

## 最初のClaude Codeセッション

1. このハーネスをプロジェクトルートへ配置。
2. リポジトリルートでClaude Codeを起動。
3. `/memory` で `CLAUDE.md` が読み込まれていることを確認。
4. `/skills` で3つのproject skillを確認。
5. `/hooks` または `/doctor` で設定を確認。
6. 最初は `/build-reproducibility` を実行し、いきなりPlayer分割などへ進まない。

## 重要

このハーネスは「Claudeに全部書き直してもらう」ためではありません。**元コードを自分の成果として残し、自分が改善方針と検証基準を決め、Claude Codeを制御された共同作業者として使ったこと**を見せるためのものです。
