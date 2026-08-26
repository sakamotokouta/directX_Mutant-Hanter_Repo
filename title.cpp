#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "title.h"
#include "titleLogo.h"
#include "input.h"
#include "fade.h"
#include "loading.h"
#include "bentiObj.h"
#include "sky.h"
#include "meshField.h"
#include "titlePlayer.h"
#include "titleCamera.h"
#include "titleDome.h"
#include "titleWeapon.h"
#include "audio.h"
#include "village.h"
#include "loading.h"
#include "loadingLogo.h"

TitleLogo* m_logo;

bool Title::m_Flg{};

void Title::Init()
{
	// camera
	AddGameObject<TitleCamera>(0);


	// polygon
	m_logo = AddGameObject<TitleLogo>(2);
	m_Fade = AddGameObject<Fade>(2);

	AddGameObject<MeshField>(1);

	//dome
	TitleDome* o_dome = AddGameObject<TitleDome>(1);
	o_dome->SetScale(D3DXVECTOR3(30.0f, 30.0f, 30.0f));


	//ベンチオブジェクト
	BentiObj* benti = AddGameObject<BentiObj>(1);
	benti->SetPosition(D3DXVECTOR3(-4.5f, 0.0f, 4.0f));
	benti->SetRotation(D3DXVECTOR3(0.0f, 2.2f, 0.0f));
	benti->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	//地面タイル
	Sky* tile = AddGameObject<Sky>(1);
	tile->SetPosition(D3DXVECTOR3(6.5f, 0.0f, 14.0f));
	tile->SetRotation(D3DXVECTOR3(0.0f, 1.6f, 0.0f));
	tile->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	//プレイヤー
	TitlePlayer* player = AddGameObject<TitlePlayer>(1);
	player->SetPosition(D3DXVECTOR3(-1.2f, 1.0f, 5.4f));
	player->SetRotation(D3DXVECTOR3(0.0f, 3.0f, 0.0f));

	TitleWeapon* weapon = AddGameObject<TitleWeapon>(1);
	weapon->SetPosition(D3DXVECTOR3(0.0f, 1.4f, 5.0f));
	weapon->SetRotation(D3DXVECTOR3(3.1f, 1.5f, -0.3f));
	weapon->SetScale(D3DXVECTOR3(0.3f, 0.3f, 0.3f));



	//BGM再生
	m_BGM = AddGameObject<GameObject>(0)->AddComponet<Audio>();
	m_BGM->Load("asset\\audio\\zarlf-idtvj (mp3cut.net).wav");
	m_BGM->Play(true);
	m_BGM->Volume(0.05f);

}

void Title::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger(VK_RETURN))
	{
		m_Fade->FadeOut();
	}
	if (m_Fade->GetFadeFinish())
	{
		Manager::SetScene<Loading>();

	}

	if(Input::GetKeyTrigger('P'))
		m_Flg = true;

}

void Title::Draw()
{
	m_Fade->Draw();

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
