# Claude Code実行用プロンプト

## 0. 最初のタスク — ベースラインのみ

```text
/build-reproducibility を使ってください。
Phase 0だけを実施し、元コードを不変スナップショットとして固定して、ゲームロジック/C++動作を変えずVisual Studio 2022 v143 x64 Debugで再現可能な配置を作ってください。

.sln/.vcxproj、ImGui/Assimp、shader/assetsのworking directory、D3DX前提を確認してください。リスクのある複数ファイル変更前にexec planを作成してください。
このタスクではC++近代化、クラス名変更、文字コード変換、D3DX移行を行わないでください。
最後に、実行したビルドコマンド、成功/失敗、未解決ブロッカー、変更ファイルを正確に報告してください。
```

## 1. 文字コードだけ

```text
Phase 1のうち文字コード/改行統一だけを実施してください。第一者C/C++を.editorconfigに従ってUTF-8へ統一し、シンボル名変更、大規模整形、ロジック/文字列内容変更を行わないでください。前後でencoding checkerを実行し、可逆変換できないファイルがあれば列挙してください。
```

## 2. PC名付きコピー

```text
*-DESKTOP-2FSCGV3.* と元名ファイルをすべて比較してください。.vcxproj掲載、include/reference、ビルド/実動作、Git履歴があればそれも使って正本を判定してください。差分が大きいファイルは根拠なしに削除しないでください。最初に判断表を作り、その後この整理だけを実施してください。
```

## 3. `delete this`撤去

```text
/directx-safe-refactor を使ってください。
Scene/GameObjectの破棄経路だけをリファクタリングし、GameObjectが自分自身をdeleteしない設計にしてください。Update順とSetDestroyの意味は維持してください。必要なvirtual destructorを追加し、ゲームプレイクラスの整理は同じタスクで行わないでください。最後にrefactor-reviewerで独立レビューしてください。
```

## 4. Scene所有権

```text
/directx-safe-refactor を使ってください。
delete this撤去後、Sceneが所有するGameObject collectionだけを明示的なunique ownershipへ移行してください。GetGameObject/GetGameObjectsはobserver APIとして可能な限り互換維持し、無関係なobserver pointerをshared_ptrへ変えないでください。scene transition/destructionを確認し、最後にrefactor-reviewerを使ってください。
```

## 5. Player分割

```text
/directx-safe-refactor を使ってください。
まずPlayerのstate、入力条件、アニメ名/フレーム、生成エフェクト、当たり判定副作用を表にしてください。その後、1タスクにつき1責務だけ抽出してください。定数、状態遷移順、アニメタイミングは変えないでください。高リスクなsliceごとにrefactor-reviewerを使ってください。
```

## 6. 就活向け証拠レビュー

```text
/portfolio-review を使ってください。
元版と現在版、docs/portfolio/BEFORE_AFTER_LOG.mdを比較し、具体diffと検証証拠がある強い改善を5件選んでください。「元から自分が実装」「第三者ライブラリ/素材」「Claude Code補助で改善」を明確に分け、誇張しないでください。
```
