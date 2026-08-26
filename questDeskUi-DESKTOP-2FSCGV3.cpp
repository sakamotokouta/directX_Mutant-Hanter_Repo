#include "questDeskUi.h"
#include "input.h"
#include "manager.h"
#include "scene.h"
#include "audio.h"
#include "money.h"
#include "villagePlayerAction.h"
#include "sprit2D.h"
#include "score.h"

bool QuestDeskUi::m_Level1RespwanFlg{};
bool QuestDeskUi::m_Level2RespwanFlg{};
bool QuestDeskUi::m_Level3RespwanFlg{};


void QuestDeskUi::Init()
{
	Scene* scene = Manager::GetScene();
	m_PlayerAction = scene->GetGameObject<VillagePlayerAction>();

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

	m_MoeneyNum = new Score;

	m_MoeneyNum->Init();

	m_Level1RespwanFlg = false;
	m_Level2RespwanFlg = false;
	m_Level3RespwanFlg = false;

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


	//クエスト最終選択やじるしの上限(鍛冶場で使ってないとき)
	//if (m_BlecksmithSelect3 == false && m_ItemLastInfo == false && m_QuestGate == false && m_InfoFirstSelectFlg == false && m_TitleLastInfoFlg == false)
	//{
	//}

	if (m_LastSelectPointerPos.y >= 404.0f)
		m_LastSelectPointerPos.y = 404.0f;

	//クエスト最終選択やじるしの下限
	if (m_LastSelectPointerPos.y <= 355.0f)
		m_LastSelectPointerPos.y = 355.0f;

}

void QuestDeskUi::Draw()
{
	//クエスト画像選択画面
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
