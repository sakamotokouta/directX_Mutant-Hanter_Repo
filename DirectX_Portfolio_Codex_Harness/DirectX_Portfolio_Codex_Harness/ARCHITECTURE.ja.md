# アーキテクチャ — 現行コードの観測結果

## 実行フロー

```text
WinMain
  -> Manager::Init
      -> Renderer / Input / Audio / ImGui 初期化
      -> Titleシーン予約
  -> 約60FPSのループ
      -> Manager::Update
          -> Input更新
          -> シーン切替
          -> Scene::Update -> GameObject::Update -> Component::Update
      -> Manager::Draw
          -> Renderer::Begin -> Scene::Draw -> ImGui -> Renderer::End
```

## 主なサブシステム

| 分野 | 代表ファイル | 内容 |
|---|---|---|
| アプリ/ループ | `main.cpp`, `manager.*` | Win32、フレーム制御、シーン寿命、ImGui |
| オブジェクト | `scene.h`, `gameObject.h`, `component.h` | 3レイヤ、Update/Draw、削除フラグ |
| 描画 | `renderer.*`, `model.*`, `animationModel.*` | Direct3D 11、OBJ/Assimp、アニメ頂点更新 |
| シェーダ | `shader/*.hlsl` | ピクセルライティング、リム、影、ディゾルブ、2D/非ライティング |
| アニメ | `animationModel.*` | Assimp、ボーン、ブレンド、CPUスキニング |
| 当たり判定 | `collitionBox.*` | 分離軸を使ったOBB判定 |
| 戦闘 | `player.*`, `weapon.*`, 各special attack | 移動、攻撃、武器、特殊攻撃 |
| 敵AI | `enemy.*` 等 | 探索、発見、追跡、攻撃、死亡、視野判定 |
| シーン | title/game/village/tutorial/result/loading | 各ゲームシーン |
| UI/経済 | 各UI、`money.*`, score | HUD、クエスト、店、通貨/アイテム |
| 音/入力 | `audio.*`, `input.*` | XAudio2、キーボード |

## 就活で強みとして説明できる実装

Direct3D 11による描画基盤、HLSLの影/リム/ディゾルブ、Assimpを使ったボーンアニメーションとCPUスキニング、分離軸法によるOBB判定、シーン/ゲームオブジェクト構造、敵AI状態制御、戦闘/武器/クエスト/店舗UI、XAudio2、ImGui統合を自作コード側から確認できました。

## 改善圧力が高い部分

静的サービスへの依存、生ポインタ所有、`Init/Uninit` に依存した寿命管理、`delete this`、巨大Update、描画とゲームロジックの密結合、アセットパスや座標のハードコードです。これらは一括置換せず、フェーズごとに改善します。
