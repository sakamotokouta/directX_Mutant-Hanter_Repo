#include "main.h"
#include "renderer.h"
#include "resultLogo.h"
#include "sprite.h"
#include "sprit2D.h"
#include "villageUi.h"
#include "player.h"
#include "money.h"
#include "input.h"
#include "questDeskUi.h"

void ResultLogo::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");


	m_Sprit1 = new Sprit2D;
	m_Sprit2 = new Sprit2D;
	m_Sprit3 = new Sprit2D;
	m_Sprit4 = new Sprit2D;
	m_Sprit5 = new Sprit2D;
	m_Sprit6 = new Sprit2D;
	m_Sprit7 = new Sprit2D;

	m_Sprit1->Init("asset/texture/level1questclear.png");
	m_Sprit2->Init("asset/texture/pushenterkey.png");
	m_Sprit3->Init("asset/texture/level2questclear.png");
	m_Sprit4->Init("asset/texture/level3questclear.png");
	m_Sprit5->Init("asset/texture/gameover001.png");
	m_Sprit6->Init("asset/texture/gameover02.png");
	m_Sprit7->Init("asset/texture/gameover03.png");


	m_Pos1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale1 = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	m_Pos2 = D3DXVECTOR3(349.0f, 271.0f, 0.0f);
	m_Scale2 = D3DXVECTOR3(870.0f, 454.0f, 0.0f);

	m_Pos3 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale3 = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	m_Pos4 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale4 = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	m_Pos5 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale5 = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	m_Pos6 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale6 = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	m_Pos7 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale7 = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);


	//お金の初期化
	Money::Init();

	GameObject::Init();
}

void ResultLogo::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	m_Sprit1->Uninit();
	m_Sprit2->Uninit();

	GameObject::Uninit();
}

void ResultLogo::Update()
{
	Money::SetKeepMoney(Money::GetMoney(), true);
	GameObject::Update();
}

void ResultLogo::Draw()
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	Renderer::SetWorldViewProjection2D();


	//リザルトでゲームシーンのflgをfalseにする処理
	VillageUi::SetGameSceneFlg(false);

	//クエスト1
	if (Player::GetPlayerEndFlg() && QuestDeskUi::GetLevel01RespwanFlg())
	{
		//クエスト失敗時
		m_Sprit5->Draw(m_Pos5, m_Scale5, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

		if(Input::GetKeyTrigger(VK_RETURN))
			QuestDeskUi::SetLevel01RespwanFlg(false);

	}
	else if (QuestDeskUi::GetLevel01RespwanFlg())
	{
		//クエスト成功時
		m_Sprit1->Draw(m_Pos1, m_Scale1, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);
		
		if (Input::GetKeyTrigger(VK_RETURN))
		{
			//クエスト成功時にお金を増やす処理
			m_Level1Reward = 5000;
			Money::SetPlusMoney(m_Level1Reward);
			QuestDeskUi::SetLevel01RespwanFlg(false);
		}
	}

	//クエスト2
	if (Player::GetPlayerEndFlg() && QuestDeskUi::GetLevel02RespwanFlg())
	{
		//クエスト失敗時
		m_Sprit6->Draw(m_Pos6, m_Scale6, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

		if (Input::GetKeyTrigger(VK_RETURN))
			QuestDeskUi::SetLevel02RespwanFlg(false);

	}
	else if (QuestDeskUi::GetLevel02RespwanFlg())
	{
		//クエスト成功時
		m_Sprit3->Draw(m_Pos3, m_Scale3, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);


		if (Input::GetKeyTrigger(VK_RETURN))
		{
			//クエスト成功時にお金を増やす処理
			m_Level2Reward = 5000;
			Money::SetPlusMoney(m_Level2Reward);
			QuestDeskUi::SetLevel02RespwanFlg(false);


		}
	}

	//クエスト3
	if (Player::GetPlayerEndFlg() && QuestDeskUi::GetLevel03RespwanFlg())
	{
		//クエスト失敗時
		m_Sprit7->Draw(m_Pos7, m_Scale7, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

		if(Input::GetKeyTrigger(VK_RETURN))
			QuestDeskUi::SetLevel03RespwanFlg(false);

	}
	else if (QuestDeskUi::GetLevel03RespwanFlg())
	{
		//クエスト成功時
		m_Sprit4->Draw(m_Pos3, m_Scale3, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

		//クエスト成功時にお金を増やす処理
		if (Input::GetKeyTrigger(VK_RETURN))
		{
			//クエスト成功時にお金を増やす処理
			m_Level3Reward = 5000;
			Money::SetPlusMoney(m_Level3Reward);
			QuestDeskUi::SetLevel03RespwanFlg(false);

		}
	}



	m_Sprit2->Draw(m_Pos2, m_Scale2, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_Celar);


	if (m_Celar <= 0.2f)
	{
		m_PulsFlg = true;
		m_Minus = false;
	}

	if (m_Celar >= 0.7f)
	{
		m_Minus = true;
		m_PulsFlg = false;
	}

	if (m_PulsFlg)
		m_Celar += 0.01f;

	if (m_Minus)
		m_Celar -= 0.01f;


	// 仮想関数なので強制的に呼び出す(基底クラスのメゾット呼び出し)
	GameObject::Draw();
}