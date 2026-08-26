# プロジェクト解析結果 — DirectX就活作品

## 解析範囲

提出ZIP全体を列挙し、**全622ファイル**を `FULL_FILE_INVENTORY.csv` に記録しました。パス、分類、サイズ、SHA-256、拡張子、判定できる文字コード、ソース側ファイルについては `.vcxproj` 掲載有無も残しています。第一者C/C++コードは `SOURCE_METRICS.csv` で追加解析しています。

この環境はWindows/DirectX実行環境ではないため、実ビルドはしていません。以下では「ファイルから確認できた事実」と「Windowsで確認すべき事項」を分けています。

## 数値

- 全ファイル: **622**
- ソースフォルダの第一者C/C++: **178ファイル**
- 同C/C++行数: **約20,350行**
- 文字コード: **{'cp932': 102, 'utf-8-sig': 76}**
- 生 `new`: **222箇所**
- `delete`: **38箇所**
- HLSL: **11ファイル**
- 3Dモデル: **FBX 41 / OBJ 34**
- WAV: **25**

## 元作品の強み

これは描画サンプルだけではありません。Direct3D 11、Win32ループ、Scene/GameObject/Component、モデル読み込み、Assimpによるボーンアニメーション、**CPUスキニング**、分離軸法による**OBB当たり判定**、プレイヤー戦闘、敵AI、特殊攻撃、複数シーン、HUD/クエスト/店舗、XAudio2、ImGui、HLSLの影・リムライト・ディゾルブまで確認できました。

就活では「AIで作り直した」より、**この自作実装を守りながら設計を改善した**方が価値を説明しやすいです。

## 最優先 P0: ビルド再現性

1. `solutionfile.sln` は `GM31 23.04.18\GM31 23.04.18.vcxproj` を参照していますが、提出ZIP内の実際のプロジェクト配置と一致していません。
2. `.vcxproj` は `imgui\...` をプロジェクト相対で参照しますが、実ファイルは別の実行用フォルダ側にあります。
3. `animationModel.h` の `assimp/...` も同様に、ヘッダは実行用フォルダ側にあります。解析したプロジェクト設定から明示的な `AdditionalIncludeDirectories` は確認できませんでした。
4. `.vcxproj` は `v143` ですが、`.sln` ヘッダはVisual Studio 15表記で、提出者/採用担当者に混乱を与えます。
5. `.exe/.pdb/.cso/.dll/debug log` がソースと混在しています。

最初のClaude Code作業はアーキテクチャ変更ではなく、**Windows x64 Debugを誰でも再現できる提出構成に直すこと**にしてください。

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

- `villageUi-DESKTOP-2FSCGV3.cpp` vs `villageUi.cpp`: 行類似度 58.9% (1206/520行)
- `questDeskUi-DESKTOP-2FSCGV3.h` vs `questDeskUi.h`: 行類似度 91.3% (83/90行)
- `questDeskUi-DESKTOP-2FSCGV3.cpp` vs `questDeskUi.cpp`: 行類似度 87.4% (357/412行)

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
