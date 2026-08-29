# Claude Codeハーネスの使い方

## 1. `CLAUDE.md` の読み込み確認

リポジトリルートでClaude Codeを起動し、`/memory` を実行します。ルートの `CLAUDE.md` が読み込まれていることを確認してください。`CLAUDE.ja.md` は人間向けで、自動指示ファイルにはしていません。

## 2. Skillsの確認

`/skills` で次の3つを確認します。

- `/build-reproducibility`
- `/directx-safe-refactor`
- `/portfolio-review`

Skillは `.claude/skills/<name>/SKILL.md` にあります。作業手順を確実に適用したい場合は明示的に `/skill-name` で呼び出してください。

## 3. Rulesの確認

`.claude/rules/` は対象ファイルを読んだ時だけ効くルールです。

- C/C++: 所有権、RAII、挙動維持
- HLSL: shaderの定数・binding・描画結果維持
- Visual Studio project: `.sln/.vcxproj`、依存パス、x64 Debug再現性

日本語ミラーは `docs/claude/rules-ja/` に置き、自動読み込みによる二重指示を避けています。

## 4. 元コード保護hook

`.claude/settings.json` から `.claude/hooks/protect-original.ps1` をPreToolUse hookとして呼びます。

Windowsでは `/hooks` または `/doctor` で有効になっているか確認してください。Claude Codeの `Write` / `Edit` による `archive/original/**` への書き込みと、同パスを対象にした代表的なshell破壊操作をブロックします。

意図的にhookを迂回しないでください。元版を更新する必要が生じた場合は既存baselineを書き換えず、新しいbaselineとして履歴を残します。

## 5. 読み取り専用サブエージェント

リスクの高い複数ファイル変更後は `refactor-reviewer` を使って独立レビューさせます。このagentは編集ではなく、問題点・挙動リスク・検証漏れの発見に使います。

`/agents` で確認できます。

## 6. 推奨順序

1. `/build-reproducibility`
2. Phase 1の機械的整理
3. `/directx-safe-refactor` で1テーマずつ変更
4. 高リスク変更は `refactor-reviewer`
5. ビルド/スモークテスト
6. `BEFORE_AFTER_LOG.md` 更新
7. 提出前に `/portfolio-review`

## 7. よく使う確認コマンド

- `/memory`: CLAUDE.md/rules/memory
- `/skills`: Skill一覧
- `/agents`: subagent一覧
- `/hooks`: hook一覧
- `/doctor`: 設定診断

## 8. PC固有情報

個人の絶対パスや環境固有設定は `CLAUDE.local.md` または `.claude/settings.local.json` に置き、Gitへ含めないでください。共有 `CLAUDE.md` に作者PCの絶対パスを書かないことが重要です。
