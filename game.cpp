#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "field.h"
#include "camera.h"
#include "player.h"
#include "enemy.h"
#include "sky.h"
#include "explosion.h"
#include "cylinder.h"
#include "box.h"
#include "score.h"
#include "input.h"
#include "result.h"
#include "audio.h"
#include "dome.h"
#include "fade.h"
#include "meshField.h"
#include "ui01.h"
#include "tree.h"
#include "weapon.h"
#include "otomo.h"
#include "title.h"
#include "villageUi.h"
#include "treeObj.h"
#include <time.h>
#include "enemyWeapon.h"
#include "enemyJumpAttack.h"
#include "specialAttack01.h"
#include "specialAttack02.h"
#include "specialAttack03.h"
#include "collitionBox.h"
#include "healEffect.h"
#include "questDeskUi.h"


bool Game::m_LoadFinish = false;
bool Game::m_GameFlg = false;

void Game::Load() 
{
	Tree::Load();
	TreeObj::Load();
	Explosion::Load();
	CollisionBox::Load();
	HealEffect::Load();
	m_LoadFinish = true;
}

void Game::Unload()
{
	m_LoadFinish = false;
	Tree::Unload();
	TreeObj::Unload();
	Explosion::Unload();
	CollisionBox::Unload();
	HealEffect::Unload();

}


void Game::Init()
{

	//ゲームシーンの時にオンにするフラグ
	m_GameFlg = true;

	// camera
	Camera* camera = AddGameObject<Camera>(0);

	//dome
	Dome* o_dome = AddGameObject<Dome>(1);
	o_dome->SetScale(D3DXVECTOR3(300.0f, 300.0f, 300.0f));

	AddGameObject<MeshField>(1);

	AddGameObject<Weapon>(1);

	AddGameObject<EnemyWeapon>(1);


	AddGameObject<Otomo>(1);

	Player* player = AddGameObject<Player>(1);
	player->SetPosition(D3DXVECTOR3(22.655, 2.0f, -14.295f));
	player->SetRotation(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	// enemy
	Enemy* enemy = AddGameObject<Enemy>(1);
	enemy->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 3.0f));
	
	//レベル1
	if (QuestDeskUi::GetLevel01RespwanFlg())
	{
		Enemy::SetEnmeyHp(30.0f);
		enemy->SetEnemyModel(0);
	}
	//レベル2
	if (QuestDeskUi::GetLevel02RespwanFlg())
	{
		Enemy::SetEnmeyHp(60.0f);
		enemy->SetEnemyModel(1);
	}
	//レベル3
	if (QuestDeskUi::GetLevel03RespwanFlg())
	{
		Enemy::SetEnmeyHp(70.0f);
		enemy->SetEnemyModel(2);
	}


	for (int i = 0; i < 20; i++)
	{
		TreeObj* treeobj = AddGameObject<TreeObj>(1);
		treeobj->SetPosition(D3DXVECTOR3(rand() % 90 + (-10), 0.0f, rand() % 40 + (-10)));
		treeobj->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	}

	m_Fade = AddGameObject<Fade>(2);


	AddGameObject<Score>(2);

	Ui01* ui = AddGameObject<Ui01>(2);

	//BGM再生
	m_BGM = AddGameObject<GameObject>(0)->AddComponet<Audio>();
	m_BGM->Load("asset\\audio\\戦闘系04.wav");
	m_BGM->Play(true);
	m_BGM->Volume(0.05f);


}


void Game::Uninit()
{
	Unload();
	Scene::Uninit();
}

void Game::Update()
{
	Scene::Update();
}

void Game::Draw()
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