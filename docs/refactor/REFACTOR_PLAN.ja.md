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
