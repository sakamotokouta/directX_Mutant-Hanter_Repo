# `.claude/settings.json` / Hooks 日本語説明

Claude Codeの現行仕様では、絶対に守りたい制約は`CLAUDE.md`だけでなくhookで強制できます。このハーネスではPreToolUseで`Edit|Write|Bash|PowerShell`を監視し、`archive/original/**`への直接書き込みや代表的な破壊コマンドを`protect-original.ps1`で拒否します。

DirectX作品の主対象がWindowsであるためPowerShell版を正式設定にしています。WSL/macOS上でClaude Codeを使う場合は同等のshell/Python hookへ差し替え、`/hooks`または`/doctor`で有効性を確認してください。
