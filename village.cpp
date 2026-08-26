#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "field.h"
#include "input.h"
#include "audio.h"
#include "fade.h"
#include "meshField.h"
#include "tree.h"
#include "village.h"
#include "game.h"
#include "villageUi.h"
#include "score.h"
#include "score2.h"
#include "score3.h"
#include "receptionDesk.h"
#include "recepitionPointer.h"
#include "weaponStoreDesk.h"
#include "generalStoreDesk.h"
#include "loading.h"
#include "generalStoreObj.h"
#include "weaponStoreObj.h"
#include "questBordObj.h"
#include "questGateObj.h"
#include "weaponBoardObj.h"
#include "generalStoreBoardObj.h"
#include "idoObj.h"
#include "bentiObj.h"
#include "houseObj.h"
#include "windmillObj.h"
#include "sky.h"
#include "villageInfoDesk.h"
#include "audio.h"
#include "instructor.h"
#include "tutorial.h"
#include "collitionBox.h"
#include "player.h"
#include "weapon.h"
#include "camera.h"
#include "dome.h"
#include "villagePlayerAction.h"
#include "collitionBox.h"
#include "villageObjCollition.h"

bool Village::m_VLoadFinish{};

bool Village::m_QuestFlg1{};

bool Village::m_TutorialFlg{};

bool Village::m_VillageFlg{};

void Village::Load()
{
	m_VLoadFinish = true;
}

void Village::Unload()
{
	m_VLoadFinish = false;

}


void Village::Init()
{
	//村シーンの時にオンにするフラグ
	m_VillageFlg = true;

	//camera
	AddGameObject<Camera>(0);

	//skydoom
	Dome*dome = AddGameObject<Dome>(1);
	dome->SetScale(D3DXVECTOR3(100.0f, 100.0f, 100.0f));

	//プレイヤーのアクション
	m_VPlayer = AddGameObject<VillagePlayerAction>(1);

	//地面
	AddGameObject<MeshField>(1);

	//地面タイル
	Sky* tile = AddGameObject<Sky>(1);
	tile->SetPosition(D3DXVECTOR3(6.5f, 0.0f, 14.0f));
	tile->SetRotation(D3DXVECTOR3(0.0f, 1.6f, 0.0f));
	tile->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));


	//クエスト受付
	RECEPTIONDESK* reception = AddGameObject<RECEPTIONDESK>(1);
	reception->SetPosition(D3DXVECTOR3(6.5f, 0.0f, 14.0f));
	reception->SetRotation(D3DXVECTOR3(0.0f, 1.6f, 0.0f));


	QuestBordObj* questboard = AddGameObject<QuestBordObj>(1);
	questboard->SetPosition(D3DXVECTOR3(7.5, 0.0f, 16.5f));
	questboard->SetRotation(D3DXVECTOR3(0.0f, 4.4f, 0.0f));
	questboard->SetScale(D3DXVECTOR3(1.5f, 1.3f, 1.0f));

	GeneralStoreBoardObj* generalsotre = AddGameObject<GeneralStoreBoardObj>(1);
	generalsotre->SetPosition(D3DXVECTOR3(5.7f, 0.0f, 10.0f));
	generalsotre->SetRotation(D3DXVECTOR3(0.0f, 4.7f, 0.0f));
	generalsotre->SetScale(D3DXVECTOR3(1.5f, 1.3f, 1.0f));



	//教官
	Instructor* instructor = AddGameObject<Instructor>(1);
	instructor->SetPosition(D3DXVECTOR3(8.0f, 0.0f, 24.0f)); 
	instructor->SetRotation(D3DXVECTOR3(0.0f, 0.3f, 0.0f));


	//鍛冶場
	WeaponStoreDesk* weapon = AddGameObject<WeaponStoreDesk>(1);
	weapon->SetPosition(D3DXVECTOR3(7.5f, 0.0f, -2.0f));
	weapon->SetRotation(D3DXVECTOR3(0.0f, 1.6f, 0.0f));

	WeaponStoreObj* weaponstore = AddGameObject<WeaponStoreObj>(1);
	weaponstore->SetPosition(D3DXVECTOR3(6.7f, 0.0f, -2.0f));
	weaponstore->SetRotation(D3DXVECTOR3(0.0f, 4.7f, 0.0f));
	weaponstore->SetScale(D3DXVECTOR3(1.5f, 1.3f, 1.0f));

	WeaponBordObj* weaponboard = AddGameObject<WeaponBordObj>(1);
	weaponboard->SetPosition(D3DXVECTOR3(5.7f, 0.0f, 1.0f));
	weaponboard->SetRotation(D3DXVECTOR3(0.0f, 4.7f, 0.0f));
	weaponboard->SetScale(D3DXVECTOR3(1.5f, 1.3f, 1.0f));

	//雑貨屋
	GeneralStoreDesk* general = AddGameObject<GeneralStoreDesk>(1);
	general->SetPosition(D3DXVECTOR3(7.4f, 0.0f, 7.0f));
	general->SetRotation(D3DXVECTOR3(0.0f, 1.6f, 0.0f));

	GeneralStoreObj* generalstore1 = AddGameObject<GeneralStoreObj>(1);
	generalstore1->SetPosition(D3DXVECTOR3(6.3f, 0.0f, 7.0f));
	generalstore1->SetRotation(D3DXVECTOR3(0.0f, 4.7f, 0.0f));
	generalstore1->SetScale(D3DXVECTOR3(1.5f, 1.3f, 1.0f));

	//クエストへ行く門
	QuestGateObj* questgate = AddGameObject<QuestGateObj>(1);
	questgate->SetPosition(D3DXVECTOR3(4.0f, 0.0f, 25.5f));
	questgate->SetRotation(D3DXVECTOR3(0.0f, 0.3f, 0.0f));
	questgate->SetScale(D3DXVECTOR3(1.8f, 1.8f, 1.0f));

	//井戸オブジェクト
	IdoObj* ido = AddGameObject<IdoObj>(1);
	ido->SetPosition(D3DXVECTOR3(-0.5, 0.0f, 5.0f));
	ido->SetRotation(D3DXVECTOR3(0.0f, 1.6f, 0.0f));
	ido->SetScale(D3DXVECTOR3(1.3f, 1.3f, 1.3f));

	//ベンチオブジェクト
	BentiObj* benti = AddGameObject<BentiObj>(1);
	benti->SetPosition(D3DXVECTOR3(-9.5f, 0.0f, -1.0f));
	benti->SetRotation(D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	benti->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	//家01
	HouseObj* house = AddGameObject<HouseObj>(1);
	house->SetPosition(D3DXVECTOR3(-9.5f, 0.0f, 15.0f));
	house->SetRotation(D3DXVECTOR3(0.0f, 1.6f, 0.0f));
	house->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	//風車
	WindMillObj* windmill = AddGameObject<WindMillObj>(1);
	windmill->SetPosition(D3DXVECTOR3(-6.5f, 0.0f, 27.0f));
	windmill->SetRotation(D3DXVECTOR3(0.0f, 2.6f, 0.0f));
	windmill->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	//村の案内人
	VillageInfoDesk* villageinfo = AddGameObject<VillageInfoDesk>(1);
	villageinfo->SetPosition(D3DXVECTOR3(-5.0f, 0.0f, -7.0f));
	villageinfo->SetRotation(D3DXVECTOR3(0.0f, 5.6f, 0.0f));
	villageinfo->SetScale(D3DXVECTOR3(0.011f, 0.011f, 0.011f));

	//プレイヤーが村人に一定距離近づくと頭上に表示される矢印
	AddGameObject<RecepitionPointer>(1);

	//プレイヤー
	m_Player = AddGameObject<Player>(1);
	m_Player->SetPosition(D3DXVECTOR3(0.0f, 1.0f, -15.0f));
	m_Player->SetRotation(D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	////武器
	AddGameObject<Weapon>(1);

	//当たり判定の初期化
	villageCillition = AddGameObject<VillageObjCollition>(1);


	m_Fade = AddGameObject<Fade>(2);

	m_VUi = AddGameObject<VillageUi>(2);

	Score* score = AddGameObject<Score>(2);
	Score2* score2 = AddGameObject<Score2>(2);
	Score3* score3 = AddGameObject<Score3>(2);

	m_QuestFlg1 = false;
	m_TutorialFlg = false;

	//BGM再生
	m_BGM = AddGameObject<GameObject>(0)->AddComponet<Audio>();
	m_BGM->Load("asset\\audio\\maou_bgm_fantasy05.wav");
	m_BGM->Play(true);
	m_BGM->Volume(0.05f);

}


void Village::Uninit()
{
	Unload();

	Scene::Uninit();
}

void Village::Update()
{
	Scene::Update();

	//村でのプレイヤーとオブジェクトの当たり判定
	villageCillition->ObjCollition();

	//教官からチュートリアルに行く処理
	if (m_VPlayer->GetTutorialrFlg())
	{
		m_Fade->FadeOut();
		m_TutorialFlg = true;
		m_VillageFlg = false;
	}

	//チュートリアルシーンへのシーン移行
	if(m_Fade->GetFadeFinish() && m_TutorialFlg)
		Manager::SetScene<Loading>();



}

void Village::Draw()
{

	//ライトカメラ構造体の初期化
	LIGHT light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


	//ライトカメラのビュー行列を作成
	D3DXVECTOR3 lightPos = D3DXVECTOR3(-50.0f, 20.0f, -50.0f);
	D3DXVECTOR3 lightTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 lightUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&light.ViewMatrix, &lightPos, &lightTarget, &lightUp);
	//ライトカメラのプロジェクション行列を作成
	D3DXMatrixPerspectiveFovLH(&light.ProjectionMatrix, 1.0f,
		(float)1.0f, 10.0f, 300.0f);


	Renderer::SetLight(light);

	//** 1パス目 シャドウバッファの作成 **//
	Renderer::BeginDepth();

	Renderer::SetDepthViewport();

	//ライトカメラの行列をセット
	Renderer::SetViewMatrix(&light.ViewMatrix);
	Renderer::SetProjectionMatrix(&light.ProjectionMatrix);

	//影を落としたいオブジェクトの描画
	ShadowDraw();

	//** 2パス目 通常の作成 **//
	Renderer::Begin();

	Renderer::SetDefaultViewport();


	light.Enable = false;
	Renderer::SetLight(light);


	Scene::Draw();

}