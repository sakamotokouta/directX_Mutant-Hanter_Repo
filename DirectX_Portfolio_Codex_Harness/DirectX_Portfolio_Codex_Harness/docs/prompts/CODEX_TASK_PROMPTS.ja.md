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
