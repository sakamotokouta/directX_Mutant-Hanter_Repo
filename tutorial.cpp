#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "audio.h"
#include "fade.h"
#include "tutorial.h"
#include "camera.h"
#include "dome.h"
#include "player.h"
#include "meshField.h"
#include "enemy.h"
#include "ui01.h"
#include "weapon.h"
#include "enemyWeapon.h"
#include "score.h"
#include "explosion.h"
#include "tutorial.h"
#include "tutorialUi.h"
#include "village.h"
#include "collitionBox.h"
#include "trail.h"


bool Tutorial::m_TLoadFinish{};
bool Tutorial::m_TutorialFlg{};


void Tutorial::Load()
{
	Explosion::Load();
	CollisionBox::Load();
	SwordTopVertex::Load();
	Explosion::Load();
	m_TLoadFinish = true;
}

void Tutorial::Unload()
{
	m_TLoadFinish = false;
	Explosion::Unload();
	CollisionBox::Unload();
	SwordTopVertex::Unload();
	Explosion::Unload();

}


void Tutorial::Init()
{
	m_TutorialFlg = true;

	// camera
	Camera* camera = AddGameObject<Camera>(0);

	//dome
	Dome* o_dome = AddGameObject<Dome>(1);
	o_dome->SetScale(D3DXVECTOR3(300.0f, 300.0f, 300.0f));

	//地面
	AddGameObject<MeshField>(1);

	//プレイヤーの武器
	AddGameObject<Weapon>(1);

	//敵の攻撃の当たり判定
	AddGameObject<EnemyWeapon>(1);

	//player
	Player* player = AddGameObject<Player>(1);
	player->SetPosition(D3DXVECTOR3(22.655, 1.0f, -14.295f));
	player->SetRotation(D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	// enemy
	Enemy* enemy = AddGameObject<Enemy>(1);
	enemy->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 3.0f));


	m_Fade = AddGameObject<Fade>(2);

	AddGameObject<Score>(2);

	Ui01* ui = AddGameObject<Ui01>(2);

	AddGameObject<TutorialUi>(2);

}


void Tutorial::Uninit()
{
	Unload();
	Scene::Uninit();
}

void Tutorial::Update()
{
	if (Input::GetKeyTrigger(VK_RETURN) && TutorialUi::GetTutorialEndFlg())
	{
		Village::SetTutorialFlg(false);
		m_Fade->FadeOut();
	}

	if (m_Fade->GetFadeFinish())
	{
		Manager::SetScene<Village>();
		m_TutorialFlg = false;
	}

	Scene::Update();

}

void Tutorial::Draw()
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