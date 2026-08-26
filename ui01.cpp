#include "main.h"
#include "renderer.h"
#include "ui01.h"
#include "sprit2D.h"
#include "scene.h"
#include "manager.h"
#include "input.h"
#include "player.h"
#include "itemDataLoad.h"
#include "score.h"
#include "weaponDataLoad.h"
#include "enemy.h"
#include "village.h"
#include "weaponDataLoad.h"

void Ui01::Init()
{

	Scene* scene = Manager::GetScene();
	m_Sprit1 = new Sprit2D;
	m_Sprit3 = new Sprit2D;
	m_Sprit4 = new Sprit2D;
	m_Sprit5 = new Sprit2D;
	m_Sprit6 = new Sprit2D;
	m_Sprit7 = new Sprit2D;
	m_Sprit8 = new Sprit2D;
	m_Sprit9 = new Sprit2D;
	m_Sprit10 = new Sprit2D;
	m_Sprit11 = new Sprit2D;
	m_Sprit12 = new Sprit2D;
	m_Sprit13 = new Sprit2D;
	m_Sprit14 = new Sprit2D;
	m_Sprit15 = new Sprit2D;
	m_Sprit16 = new Sprit2D;
	m_Sprit17 = new Sprit2D;
	m_Sprit18 = new Sprit2D;
	m_Sprit19 = new Sprit2D;

	//アイテムデーターの読み込み
	ItemDataLoad::DataLoad();

	//武器データの読み込み
	WeaponDataLoad::DataLoad();


	m_Sprit1->Init("asset/texture/UI001.png");
	m_Sprit3->Init("asset/texture/UI003.png");
	m_Sprit4->Init("asset/texture/byousin001.png");
	m_Sprit5->Init("asset/texture/sutamina01.png");
	m_Sprit6->Init("asset/texture/hp002.png");
	m_Sprit7->Init("asset/texture/hp01.png");
	m_Sprit8->Init("asset/texture/nameplate002.png");
	m_Sprit9->Init("asset/texture/UI003.png");
	m_Sprit10->Init("asset/texture/nameplate003.png");
	m_Sprit11->Init("asset/texture/Damege.png");
	m_Sprit12->Init("asset/texture/quest01.png");

	m_Sprit13->Init(ItemDataLoad::GetItemBaseIndex(0)->GetItemTextuer());

	m_Sprit14->Init(WeaponDataLoad::GetWeaponDataBaseIndex(WeaponDataLoad::GetWeaponNumber())->GetWeaponSharpnessTextuer());

	m_Sprit15->Init("asset/texture/questclear01.png");

	m_Sprit16->Init("asset/texture/specialattack01.png");

	m_Sprit17->Init("asset/texture/specialattack02.png");

	m_Sprit18->Init("asset/texture/specialattack03.png");

	m_Sprit19->Init("asset/texture/gameover01.png");


	m_Pos1 = D3DXVECTOR3(-100.0f, -120.0f, 0.0f);
	m_Scale1 = D3DXVECTOR3(800.0f, 400.0f, 0.0f);
	m_Rot1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	m_Pos3 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale3 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rot3 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Pos4 = D3DXVECTOR3(43.5f, 40.0f, 0.0f);
	m_Scale4 = D3DXVECTOR3(100.0f, 40.0f, 0.0f);
	m_Rot4 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Pos5 = D3DXVECTOR3(150.0f, 43.0f, 0.0f);
	m_Scale5 = D3DXVECTOR3(360.0f, 40.0f, 0.0f);
	m_Rot5 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Pos6 = D3DXVECTOR3(150.0f, 26.0f, 0.0f);
	m_Scale6 = D3DXVECTOR3(360.0f, 40.0f, 0.0f);
	m_Rot6 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Pos7 = D3DXVECTOR3(150.0f, 26.0f, 0.0f);
	m_Scale7 = D3DXVECTOR3(360.0f, 40.0f, 0.0f);
	m_Rot7 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Pos8 = D3DXVECTOR3(-100.0f, 50.0f, 0.0f);
	m_Scale8 = D3DXVECTOR3(400.0f, 250.0f, 0.0f);
	m_Rot8 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Pos9 = D3DXVECTOR3(65.0f, 155.0f, 0.0f);
	m_Scale9 = D3DXVECTOR3(100.0f, 40.0f, 0.0f);
	m_Rot9 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Pos10 = D3DXVECTOR3(-15.0f, 145.0f, 0.0f);
	m_Scale10 = D3DXVECTOR3(120.0f, 60.0f, 0.0f);
	m_Rot10 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Pos11 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale11 = D3DXVECTOR3(1280.0f, 750.0f, 0.0f);
	m_Rot11 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Pos12 = D3DXVECTOR3(500.0f, 50.0f, 0.0f);
	m_Scale12 = D3DXVECTOR3(900.0f, 600.0f, 0.0f);
	m_Rot12 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Pos13 = D3DXVECTOR3(34.0f, 565.0f, 0.0f);
	m_Scale13 = D3DXVECTOR3(200.0f, 100.0f, 0.0f);
	m_Rot13 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Pos14 = D3DXVECTOR3(35.0f, -55.0f, 0.0f);
	m_Scale14 = D3DXVECTOR3(400.0f, 300.0f, 0.0f);
	m_Rot14 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Pos15 = D3DXVECTOR3(35.0f, -55.0f, 0.0f);
	m_Scale15 = D3DXVECTOR3(400.0f, 300.0f, 0.0f);

	m_Pos16 = D3DXVECTOR3(56.0f, 29.0f, 0.0f);
	m_Scale16 = D3DXVECTOR3(350.0f, 200.0f, 0.0f);

	m_Pos17 = D3DXVECTOR3(56.0f, 29.0f, 0.0f);
	m_Scale17 = D3DXVECTOR3(350.0f, 200.0f, 0.0f);

	m_Pos18 = D3DXVECTOR3(151.0f, 122.0f, 0.0f);
	m_Scale18 = D3DXVECTOR3(0.0f, 15.0f, 0.0f);

	Score* score = scene->GetGameObject<Score>();
	
	if (ItemDataLoad::GetItemBaseIndex(0)->GetItemCount() <= 0)
		score->SetCount(0);


	GameObject::Init();
}

void Ui01::Uninit()
{
	m_Sprit1->Uninit();
	m_Sprit3->Uninit();
	m_Sprit4->Uninit();
	m_Sprit5->Uninit();
	m_Sprit6->Uninit();
	m_Sprit7->Uninit();
	m_Sprit8->Uninit();
	m_Sprit9->Uninit();
	m_Sprit10->Uninit();
	m_Sprit11->Uninit();
	m_Sprit12->Uninit();
	m_Sprit13->Uninit();
	m_Sprit14->Uninit();
	m_Sprit15->Uninit();
	m_Sprit16->Uninit();
	m_Sprit17->Uninit();
	m_Sprit18->Uninit();
	m_Sprit19->Uninit();

	GameObject::Uninit();
}

void Ui01::Update()
{
	//時刻の秒針
	m_Rot4.x += 0.0001f;
	
	if (m_Scale18.x >= 160.0f)
		m_Scale18.x = 160.0f;
	
	GameObject::Update();
}

void Ui01::Draw()
{
	m_Sprit1->Draw(m_Pos1, m_Scale1, m_Rot1,1.0f);
	m_Sprit3->Draw(m_Pos3, m_Scale3, m_Rot3,1.0f);
	m_Sprit4->Draw(m_Pos4, m_Scale4, m_Rot4,1.0f);
	m_Sprit5->Draw(m_Pos5, m_Scale5, m_Rot5, 1.0f);
	m_Sprit6->Draw(m_Pos6, m_Scale6, m_Rot6, 1.0f);
	m_Sprit7->Draw(m_Pos7, m_Scale7, m_Rot7, 1.0f);
	m_Sprit8->Draw(m_Pos8, m_Scale8, m_Rot8, 0.5);
	m_Sprit9->Draw(m_Pos9, m_Scale9, m_Rot9, 1.0f);
	m_Sprit10->Draw(m_Pos10, m_Scale10, m_Rot10,1.0f);

	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();
	Score* score = scene->GetGameObject<Score>();
	Enemy* enemy = scene->GetGameObject<Enemy>();

	if (player->GetDamageFlg())
		m_Sprit11->Draw(m_Pos11, m_Scale11, m_Rot11, 0.4f);

	m_Sprit13->Draw(m_Pos13, m_Scale13, m_Rot13, 1.0f);
	score->SetDrawFlg(true);
	score->SetCount(player->GetItemCount());
	score->SetPosAndScale(160.0f, 648.0f, 30.0f, 30.0f);


	m_Sprit14->Draw(m_Pos14, m_Scale14, m_Rot14, 1.0f);

	if (enemy != NULL)
	{
		if (enemy->GetEnemyState() == ENEMY_STATE_DIE)
			m_ClearFlg = true;

	}

	//クエスト成功時
	if (m_ClearFlg && Village::GetTutorialFlg() == false)
	{
		m_ClearCo++;

		if (m_ClearCo >= 400)
			m_Sprit15->Draw(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);
	}

	//クエスト失敗時
	if (player->GetPlayerEndFlg())
	{
		m_ClearCo++;

		if (m_ClearCo >= 200)
			m_Sprit19->Draw(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

	}

	m_Sprit16->Draw(m_Pos16, m_Scale16, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

	if(m_Scale18.x >= 160.0f)
		m_Sprit17->Draw(m_Pos17, m_Scale17, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

	m_Sprit18->Draw(m_Pos18, m_Scale18, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);


}		
