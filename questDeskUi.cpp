#include "questDeskUi.h"
#include "manager.h"
#include "sprit2D.h"
#include "villagePlayerAction.h"
#include "score.h"
#include "audio.h"
#include "input.h"
#include "money.h"

bool QuestDeskUi::m_Level1RespwanFlg{};
bool QuestDeskUi::m_Level2RespwanFlg{};
bool QuestDeskUi::m_Level3RespwanFlg{};


void QuestDeskUi::Init()
{

	Scene* scene = Manager::GetScene();

	m_PlayerAction = scene->GetGameObject<VillagePlayerAction>();

	m_MoeneyNum = new Score;

	m_Pointer = new Sprit2D;
	m_QuestChoice01 = new Sprit2D;
	m_QuestChoice02 = new Sprit2D;
	m_QuestChoice03 = new Sprit2D;
	m_Quest01 = new Sprit2D;
	m_Quest02 = new Sprit2D;
	m_Quest03 = new Sprit2D;
	m_EnerOrRetern = new Sprit2D;
	m_LastSelect = new Sprit2D;
	m_LastSelectPointer = new Sprit2D;

	m_Pointer->Init("asset/texture/pointer.png");
	m_QuestChoice01->Init("asset/texture/quest001.png");
	m_QuestChoice02->Init("asset/texture/quest002.png");
	m_QuestChoice03->Init("asset/texture/quest003.png");
	m_Quest01->Init("asset/texture/Quest01Details.png");
	m_Quest02->Init("asset/texture/Quest02Details.png");
	m_Quest03->Init("asset/texture/Quest03Details.png");
	m_EnerOrRetern->Init("asset/texture/enterOrEsc.png");
	m_LastSelect->Init("asset/texture/LastSelect.png");
	m_LastSelectPointer->Init("asset/texture/LastSelectPointer.png");

	//やじるし
	m_PointerPos = D3DXVECTOR3(680.0f, 50.0f, 0.0f);
	m_PointerScale = D3DXVECTOR3(200.0f, 100.0f, 0.0f);

	//クエスト選択1
	m_QuestChoice01Pos = D3DXVECTOR3(680.0f, -100.0f, 0.0f);
	m_QuestChoice01Scale = D3DXVECTOR3(750.0f, 400.0f, 0.0f);

	//クエスト選択2
	m_QuestChoice02Pos = D3DXVECTOR3(680.0f, -20.0f, 0.0f);
	m_QuestChoice02Scale = D3DXVECTOR3(750.0f, 400.0f, 0.0f);

	//クエスト選択3
	m_QuestChoice03Pos = D3DXVECTOR3(680.0f, 60.0f, 0.0f);
	m_QuestChoice03Scale = D3DXVECTOR3(750.0f, 400.0f, 0.0f);

	//クエスト1
	m_Quest01Pos = D3DXVECTOR3(500.0f, 50.0f, 0.0f);
	m_Quest01Scale = D3DXVECTOR3(900.0f, 600.0f, 0.0f);

	//クエスト2
	m_Quest02Pos = D3DXVECTOR3(500.0f, 50.0f, 0.0f);
	m_Quest02Scale = D3DXVECTOR3(900.0f, 600.0f, 0.0f);

	//クエスト3
	m_Quest03Pos = D3DXVECTOR3(500.0f, 50.0f, 0.0f);
	m_Quest03Scale = D3DXVECTOR3(900.0f, 600.0f, 0.0f);

	//決定か戻るかの入力案内
	m_EnerOrReternPos = D3DXVECTOR3(900.0f, 550.0f, 0.0f);
	m_EnerOrReternScale = D3DXVECTOR3(400.0f, 200.0f, 0.0f);

	//クエストの決定案内
	m_LastSelectPos = D3DXVECTOR3(-150.0f, 200.0f, 0.0f);
	m_LastSelectScale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);

	//クエスト最終決定のやじるし
	m_LastSelectPointerPos = D3DXVECTOR3(175.0f, 355.0f, 0.0f);
	m_LastSelectPointerScale = D3DXVECTOR3(250.0f, 250.0f, 0.0f);

	//AudioLoad
	m_SelectSE = AddComponet<Audio>();
	m_SelectSE->Load("asset\\audio\\選択音.wav");
	m_SelectSE->Volume(0.4f);

	m_EnterSE = AddComponet<Audio>();
	m_EnterSE->Load("asset\\audio\\決定音.wav");
	m_EnterSE->Volume(0.4f);

}

void QuestDeskUi::Uninit()
{
	m_Pointer->Uninit();
	m_QuestChoice01->Uninit();
	m_QuestChoice02->Uninit();
	m_QuestChoice03->Uninit();
	m_Quest01->Uninit();
	m_Quest02->Uninit();
	m_Quest03->Uninit();
	m_EnerOrRetern->Uninit();
	m_LastSelect->Uninit();
	m_LastSelectPointer->Uninit();

}

void QuestDeskUi::Update()
{
	//クエスト選択画面
	if (m_PointerLockFlg == false)
	{
		if (Input::GetKeyTrigger(VK_DOWN))
		{
			m_PointerPos.y += 80.0f;
			m_SelectSE->Play();
		}

		if (Input::GetKeyTrigger(VK_UP))
		{
			m_PointerPos.y -= 80.0f;
			m_SelectSE->Play();
		}

	}

	//クエスト最終確認のやじるし
	/*if (m_BlecksmithSelect3 == false && m_ItemLastInfo == false)
	{
	}*/
	if (Input::GetKeyTrigger(VK_DOWN))
	{
		m_LastSelectPointerPos.y += 49.0f;
		m_SelectSE->Play();
	}

	if (Input::GetKeyTrigger(VK_UP))
	{
		m_LastSelectPointerPos.y -= 49.0f;
		m_SelectSE->Play();
	}


	if (Input::GetKeyTrigger('E') && m_PlayerAction->GetQuestFlg())
	{
		m_PointerPos = D3DXVECTOR3(680.0f, 50.0f, 0.0f);
		m_PointerScale = D3DXVECTOR3(200.0f, 100.0f, 0.0f);

		m_LastSelectPointerPos = D3DXVECTOR3(175.0f, 355.0f, 0.0f);
		m_LastSelectPointerScale = D3DXVECTOR3(250.0f, 250.0f, 0.0f);

	}


	//レベル1
	if (m_PointerPos.y == 50 && m_PlayerAction->GetQuestFlg())
	{
		m_QuestChoice01Pos.x = 665.0f;
		if (Input::GetKeyTrigger('F') && m_Level1Flg == false && m_LastSelectFlg == false)
		{
			//最初のクエスト選択画面で選ばれたクエスト
			m_PointerLockFlg = true;
			m_Level1Flg = true;
			m_EnterSE->Play();

		}
		else if (Input::GetKeyTrigger('F') && m_Level1Flg == true && m_LastSelectFlg == false)
		{
			//最終クエスト選択を表示
			m_LastSelectPointerPos.y = 355.0f;
			m_LastSelectFlg = true;
			m_Level1Flg = false;
			m_EnterSE->Play();

		}
		else if (Input::GetKeyTrigger('F') && m_LastSelectFlg == true && m_LastSelectPointerPos.y <= 355.0f && Money::GetMoney() >= 100)
		{
			//クエスト最終選択で"はい"だった場合
			//ここでレベル１のモンスターをリスポーンさせるフラグを立てる
			m_Level1RespwanFlg = true;
			m_LastSelectFlg = false;
			m_PlayerAction->SetQuestFlg(false);
			m_PointerLockFlg = false;
			m_PlayerAction->SetSVillgeStopFlg(false);

			//お金を減らす処理
			Money::SetMinusMoney(100);

			m_EnterSE->Play();

		}
		else if (Input::GetKeyTrigger('F') && m_LastSelectPointerPos.y >= 404.0f && m_Level1Flg == false && m_LastSelectFlg == true)
		{
			//クエスト最終選択で"いいえ"だった場合
			m_LastSelectFlg = false;
			m_Level1Flg = true;

			m_EnterSE->Play();

		}
		else if (Input::GetKeyTrigger('R') && m_Level1Flg == true && m_LastSelectFlg == false)
		{
			//戻る
			m_Level1Flg = false;
			m_PointerLockFlg = false;
			m_EnterSE->Play();

		}

	}
	else
		m_QuestChoice01Pos.x = 680.0f;



	//レベル2
	if (m_PointerPos.y == 130 && m_PlayerAction->GetQuestFlg())
	{
		m_QuestChoice02Pos.x = 665.0f;
		if (Input::GetKeyTrigger('F') && m_Level2Flg == false && m_LastSelectFlg == false)
		{
			//最初のクエスト選択画面で選ばれたクエスト
			m_PointerLockFlg = true;
			m_Level2Flg = true;
			m_EnterSE->Play();

		}
		else if (Input::GetKeyTrigger('F') && m_Level2Flg == true && m_LastSelectFlg == false)
		{
			//最終クエスト選択を表示
			m_LastSelectPointerPos.y = 355.0f;
			m_LastSelectFlg = true;
			m_Level2Flg = false;

			m_EnterSE->Play();

		}
		else if (Input::GetKeyTrigger('F') && m_LastSelectFlg == true && m_LastSelectPointerPos.y <= 355.0f && Money::GetMoney() >= 100)
		{
			//クエスト最終選択で"はい"だった場合
			//ここでレベル１のモンスターをリスポーンさせるフラグを立てる
			m_Level2RespwanFlg = true;
			m_LastSelectFlg = false;
			m_PlayerAction->SetQuestFlg(false);
			m_PointerLockFlg = false;
			m_PlayerAction->SetSVillgeStopFlg(false);

			//お金を減らす処理
			Money::SetMinusMoney(100);

			m_EnterSE->Play();

		}
		else if (Input::GetKeyTrigger('F') && m_LastSelectPointerPos.y >= 404.0f && m_Level2Flg == false && m_LastSelectFlg == true)
		{
			//クエスト最終選択で"いいえ"だった場合
			m_LastSelectFlg = false;
			m_Level2Flg = true;
			m_EnterSE->Play();

		}
		else if (Input::GetKeyTrigger('R') && m_Level2Flg == true && m_LastSelectFlg == false)
		{
			//戻る
			m_Level2Flg = false;
			m_PointerLockFlg = false;
			m_EnterSE->Play();

		}

	}
	else
		m_QuestChoice02Pos.x = 680.0f;


	//レベル3
	if (m_PointerPos.y >= 210 && m_PlayerAction->GetQuestFlg())
	{
		m_QuestChoice03Pos.x = 665.0f;
		if (Input::GetKeyTrigger('F') && m_Level3Flg == false && m_LastSelectFlg == false)
		{
			//最初のクエスト選択画面で選ばれたクエスト
			m_PointerLockFlg = true;
			m_Level3Flg = true;

			m_EnterSE->Play();

		}
		else if (Input::GetKeyTrigger('F') && m_Level3Flg == true && m_LastSelectFlg == false)
		{
			//最終クエスト選択を表示
			m_LastSelectPointerPos.y = 355.0f;
			m_LastSelectFlg = true;
			m_Level3Flg = false;
			m_EnterSE->Play();

		}
		else if (Input::GetKeyTrigger('F') && m_LastSelectFlg == true && m_LastSelectPointerPos.y <= 355.0f && Money::GetMoney() >= 100)
		{
			//クエスト最終選択で"はい"だった場合
			//ここでレベル１のモンスターをリスポーンさせるフラグを立てる
			m_Level3RespwanFlg = true;
			m_LastSelectFlg = false;
			m_PlayerAction->SetQuestFlg(false);
			m_PointerLockFlg = false;
			m_PlayerAction->SetSVillgeStopFlg(false);

			//お金を減らす処理
			Money::SetMinusMoney(100);

			m_EnterSE->Play();

		}
		else if (Input::GetKeyTrigger('F') && m_LastSelectPointerPos.y >= 404.0f && m_Level3Flg == false && m_LastSelectFlg == true)
		{
			//クエスト最終選択で"いいえ"だった場合
			m_LastSelectFlg = false;
			m_Level3Flg = true;
		}
		else if (Input::GetKeyTrigger('R') && m_Level3Flg == true && m_LastSelectFlg == false)
		{
			//戻る
			m_Level3Flg = false;
			m_PointerLockFlg = false;
			m_EnterSE->Play();

		}

	}
	else
		m_QuestChoice03Pos.x = 680.0f;


	//レベル2
	if (m_PointerPos.y == 130)
		m_QuestChoice02Pos.x = 665.0f;
	else
		m_QuestChoice02Pos.x = 680.0f;

	//レベル3
	if (m_PointerPos.y == 210)
		m_QuestChoice03Pos.x = 665.0f;
	else
		m_QuestChoice03Pos.x = 680.0f;



	//最初のクエスト選択やじるしの上限
	if (m_PointerPos.y >= 210)
		m_PointerPos.y = 210;

	//最初のクエスト選択やじるしの下限
	if (m_PointerPos.y <= 50)
		m_PointerPos.y = 50;


	if (m_LastSelectPointerPos.y >= 404.0f)
		m_LastSelectPointerPos.y = 404.0f;

	//クエスト最終選択やじるしの下限
	if (m_LastSelectPointerPos.y <= 355.0f)
		m_LastSelectPointerPos.y = 355.0f;


}

void QuestDeskUi::Draw()
{
	if (m_PlayerAction->GetQuestFlg() && m_Level1Flg == false
		&& m_Level2Flg == false
		&& m_Level3Flg == false
		&& m_LastSelectFlg == false)
	{
		m_Pointer->Draw(m_PointerPos, m_PointerScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);
		m_QuestChoice01->Draw(m_QuestChoice01Pos, m_QuestChoice01Scale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);
		m_QuestChoice02->Draw(m_QuestChoice02Pos, m_QuestChoice02Scale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);
		m_QuestChoice03->Draw(m_QuestChoice03Pos, m_QuestChoice03Scale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

		//残金
		m_MoeneyNum->Draw();
		m_MoeneyNum->SetCount(Money::GetMoney());
		m_MoeneyNum->SetPosAndScale(m_QuestMoneyPos.x, m_QuestMoneyPos.y, m_QuestMoneyScale.x, m_QuestMoneyScale.y);

	}

	//レベル1のクエスト
	if (m_Level1Flg)
		m_Quest01->Draw(m_Quest01Pos, m_Quest01Scale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

	//レベル2のクエスト
	if (m_Level2Flg)
		m_Quest02->Draw(m_Quest02Pos, m_Quest02Scale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

	//レベル3のクエスト
	if (m_Level3Flg)
		m_Quest03->Draw(m_Quest03Pos, m_Quest03Scale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);


	if (m_PlayerAction->GetQuestFlg())
		m_EnerOrRetern->Draw(m_EnerOrReternPos, m_EnerOrReternScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);


	if (m_LastSelectFlg)
	{
		m_LastSelect->Draw(m_LastSelectPos, m_LastSelectScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);
		m_LastSelectPointer->Draw(m_LastSelectPointerPos, m_LastSelectPointerScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);
	}
}
