# Codex版からClaude Code版への主な変更

このClaude Code版は単純なファイル名置換ではありません。主な変更は以下です。

1. `AGENTS.md` を廃止し、Claude Codeが標準で読む `CLAUDE.md` を正本化。
2. `.codex/skills/` を `.claude/skills/` へ移し、`/build-reproducibility`、`/directx-safe-refactor`、`/portfolio-review` として直接呼び出せる構成へ変更。
3. 常時読み込む必要がないC++/HLSL/Visual Studio固有ルールを `.claude/rules/` へ分離。
4. 高リスクrefactor後の独立確認用に、読み取り専用 `refactor-reviewer` subagentを追加。
5. `archive/original/**` へのClaude Code直接書き込みを防ぐPreToolUse hookを追加。
6. AI利用説明、Reviewer Guide、Task Prompts、Core BeliefsをClaude Code前提へ更新。
7. `CLAUDE.local.md` と `.claude/settings.local.json` をGit対象外に追加し、PC固有情報を共有ハーネスから分離。

英語のactive filesをClaude Code向け正本、日本語版を人間向けミラーとしています。日本語ミラーを `.claude/rules/` に置かないのは、同じルールの二重読み込みを防ぐためです。
