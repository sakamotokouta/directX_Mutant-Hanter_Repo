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
