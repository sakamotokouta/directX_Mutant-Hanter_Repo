#include "main.h"
#include "renderer.h"
#include "sprite.h"
#include "villageUi.h"
#include "sprit2D.h"
#include "scene.h"
#include "manager.h"
#include "input.h"
#include "score.h"
#include "score2.h"
#include "score3.h"
#include "itemDataBase.h"
#include "itemDataLoad.h"
#include "weaponDataLoad.h"
#include "fade.h"
#include "title.h"
#include "loading.h"
#include "money.h"
#include "villagePlayerAction.h"
#include "weapon.h"
#include "player.h"
#include "village.h"
#include "audio.h"
#include "weaponStoreUi.h"
#include "generalStoreUi.h"
#include "questDeskUi.h"

bool VillageUi::m_QuestGate{};
bool VillageUi::m_GameSceneFlg{};

void VillageUi::Init()
{

	Scene* scene = Manager::GetScene();


	//アイテムデータの読み込み
	ItemDataLoad::DataLoad();


	//武器のデータ読み込み
	WeaponDataLoad::DataLoad();

	m_Fade = scene->AddGameObject<Fade>(2);

	//お金の初期化
	Money::Init();

	//Sprit2Dの初期化
	m_Pointer = new Sprit2D;
	m_EnerOrRetern = new Sprit2D;
	m_LastSelect = new Sprit2D;
	m_LastSelectPointer = new Sprit2D;
	m_QuestGateLastInfo = new Sprit2D;
	m_VillageInfoSelect01 = new Sprit2D;
	m_VillageInfoSelect02 = new Sprit2D;
	m_WeaponStoreInfo = new Sprit2D;
	m_GeneralStoreInfo = new Sprit2D;
	m_QuestBoardInfo = new Sprit2D;
	m_QuestGateInfo = new Sprit2D;
	m_InfoFinish = new Sprit2D;
	m_TitleLastInfo = new Sprit2D;
	m_TutorialInfo = new Sprit2D;
	m_ItemPic = new Sprit2D;
	m_ChackPic = new Sprit2D;
	m_ChackRavel = new Sprit2D;
	m_ReturnRavel = new Sprit2D;


	m_ConfirmationScore = new Score;
	m_MoeneyNum = new Score;
	m_ItemNum = new Score;


	m_Pointer->Init("asset/texture/pointer.png");
	m_EnerOrRetern->Init("asset/texture/enterOrEsc.png");
	m_LastSelect->Init("asset/texture/LastSelect.png");
	m_LastSelectPointer->Init("asset/texture/LastSelectPointer.png");
	m_QuestGateLastInfo->Init("asset/texture/questgatelastinfo.png");
	m_ItemPic->Init("asset/texture/medicalitem.png");
	m_ChackPic->Init("asset/texture/chackPic.png");
	m_ChackRavel->Init("asset/texture/chackRavel.png");
	m_ReturnRavel->Init("asset/texture/returnRavel.png");
	m_VillageInfoSelect01->Init("asset/texture/villageinfo03.png");
	m_VillageInfoSelect02->Init("asset/texture/villageinfo02.png");
	m_WeaponStoreInfo->Init("asset/texture/weaponsotreinfo.png");
	m_GeneralStoreInfo->Init("asset/texture/generalstoreinfo01.png");
	m_QuestBoardInfo->Init("asset/texture/questboardinfo.png");
	m_QuestGateInfo->Init("asset/texture/questgateinfo.png");
	m_InfoFinish->Init("asset/texture/infofinish.png");
	m_TitleLastInfo->Init("asset/texture/titellastinfo.png");
	m_TutorialInfo->Init("asset/texture/tutorial.png");


	//クエスト出発前の画面
	m_QuestGateLastInfoPos = D3DXVECTOR3(177.0f, 61.0f, 0.0f);
	m_QuestGateLastInfoScale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);

	//村の紹介画面01
	m_VillageInfoSelect01Pos = D3DXVECTOR3(215.0f, 39.0f, 0.0f);
	m_VillageInfoSelect01Scale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);

	//村の紹介画面02
	m_VillageInfoSelect02Pos = D3DXVECTOR3(215.0f, 255.0f, 0.0f);
	m_VillageInfoSelect02Scale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);

	//武器屋の紹介文
	m_WeaponStoreInfoPos = D3DXVECTOR3(215.0f, 255.0f, 0.0f);
	m_WeaponStoreInfoScale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);

	//雑貨屋の紹介文
	m_GeneralStoreInfoPos = D3DXVECTOR3(215.0f, 255.0f, 0.0f);
	m_GeneralStoreInfoScale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);

	//受付嬢の紹介文
	m_QuestBoardInfoPos = D3DXVECTOR3(215.0f, 255.0f, 0.0f);
	m_QuestBoardInfoScale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);

	//クエスト出発門の紹介文
	m_QuestGateInfoPos = D3DXVECTOR3(215.0f, 255.0f, 0.0f);
	m_QuestGateInfoScale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);

	//教官の紹介文
	m_TutorialInfoPos = D3DXVECTOR3(215.0f, 255.0f, 0.0f);
	m_TutorialInfoScale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);


	//チュートリアルの最後の文
	m_InfoFinishPos = D3DXVECTOR3(215.0f, 255.0f, 0.0f);
	m_InfoFinishScale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);

	//タイトルに戻るときの文
	m_TitleLastInfoPos = D3DXVECTOR3(199.0f, 49.0f, 0.0f);
	m_TitleLastInfoScale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);

	//回復薬の数を確認するための回復薬の画像
	m_ItemPicPos = D3DXVECTOR3(144.0f, 514.0f, 0.0f);
	m_ItemPicScale = D3DXVECTOR3(200.0f, 100.0f, 0.0f);

	//残金の確認
	m_ConfirmationMoneyPos = D3DXVECTOR3(774.0f, 239.0f, 0.0f);
	m_ConfirmationMoneyScale = D3DXVECTOR3(30.0f, 30.0f, 0.0f);

	//アイテムの数の確認
	m_ItemNumPos = D3DXVECTOR3(770.0f, 304.0f, 0.0f);
	m_ItemNumScale = D3DXVECTOR3(30.0f, 30.0f, 0.0f);

	//クエスト行く際の最後の矢印
	m_QuestLastPointPos = D3DXVECTOR3(487.0f, 242.0f, 0.0f);	//常時出しておく確認画面を開くための指示
	m_QuestLastPointScale = D3DXVECTOR3(280.0f, 200.0f, 0.0f);

	//確認の時の画像
	m_ChackPicPos = D3DXVECTOR3(270.0f, 68.0f, 0.0f);
	m_ChackPicScale = D3DXVECTOR3(775.0f, 420.0f, 0.0f);

	m_ChackRavelPos = D3DXVECTOR3(-16.0f,528.0f, 0.0f);
	m_ChackRavelScale = D3DXVECTOR3(280.0f, 200.0f, 0.0f);

	//確認が画面を開いたときに出る戻るための指示
	m_ReturnRavelPos = D3DXVECTOR3(-60.0f, 499.0f, 0.0f);
	m_ReturnRavelScale = D3DXVECTOR3(280.0f, 200.0f, 0.0f);

	//数値の描画の初期化
	m_ConfirmationScore->Init();
	m_MoeneyNum->Init();
	m_ItemNum->Init();

	m_WeaponStoreUi = new WeaponStoreUi;
	m_WeaponStoreUi->Init();

	//AudioLoad
	m_SelectSE = AddComponet<Audio>();
	m_SelectSE->Load("asset\\audio\\選択音.wav");
	m_SelectSE->Volume(0.4f);

	m_EnterSE = AddComponet<Audio>();
	m_EnterSE->Load("asset\\audio\\決定音.wav");
	m_EnterSE->Volume(0.4f);

	//鍛冶場のUiクラスの初期化
	WeaponStoreUi* weaponui = scene->AddGameObject<WeaponStoreUi>(2);

	//雑貨屋のUiクラスの初期化
	GeneralStoreUi* generalui = scene->AddGameObject<GeneralStoreUi>(2);

	//クエスト受付のUiクラスの初期化
	QuestDeskUi* questdeskui = scene->AddGameObject<QuestDeskUi>(2);

	GameObject::Init();
}

void VillageUi::Uninit()
{
	m_Pointer->Uninit();
	m_EnerOrRetern->Uninit();
	m_LastSelect->Uninit();
	m_LastSelectPointer->Uninit();
	m_QuestGateLastInfo->Uninit();
	m_WeaponStoreInfo->Uninit();
	m_GeneralStoreInfo->Uninit();
	m_QuestBoardInfo->Uninit();
	m_QuestGateInfo->Uninit();
	m_InfoFinish->Uninit();
	m_TitleLastInfo->Uninit();
	m_TutorialInfo->Uninit();
	m_ItemPic->Uninit();
	m_ChackPic->Uninit();
	m_ChackRavel->Uninit();
	m_ReturnRavel->Uninit();
	m_ConfirmationScore->Uninit();
	m_MoeneyNum->Uninit();
	m_ItemNum->Uninit();


	GameObject::Uninit();
}

void VillageUi::Update()
{
	Scene* scene = Manager::GetScene();
	VillagePlayerAction* vplayer = scene->GetGameObject<VillagePlayerAction>();
	Player* player = scene->GetGameObject<Player>();
	Weapon* vweapon = scene->GetGameObject<Weapon>();


	//常時回復薬が何個あるのかを表示するUI
	if (Input::GetKeyPress('T'))
		m_ConfirmationFlg = true;
	else if (Input::GetKeyPress('R') && m_ConfirmationFlg)
		m_ConfirmationFlg = false;



	//最後の門の処理
	if (QuestDeskUi::GetLevel01RespwanFlg() || QuestDeskUi::GetLevel02RespwanFlg() || QuestDeskUi::GetLevel03RespwanFlg())
	{
		m_QuestGate = true;
	}

	//最後の門に近づいたらクエストに行くかどうかを聞く処理
	if (player->GetPosition().z <= 26.399f && player->GetPosition().z >= 24.681 && player->GetPosition().x >= 3.0f && m_QuestGate)
	{

		m_QuestGateLastFlg = true;
	}
	else
		m_QuestGateLastFlg = false;

		
	if (m_QuestGateLastFlg)
	{
		
		//選択するときのやじるし
		if (Input::GetKeyTrigger(VK_DOWN))
		{
			m_QuestLastPointPos.y += 53.0f;

			if (m_QuestLastPointPos.y >= 295.0f)
				m_QuestLastPointPos.y = 295.0f;

			m_SelectSE->Play();
		}

		if (Input::GetKeyTrigger(VK_UP))
		{
			m_QuestLastPointPos.y -= 53.0f;

			if (m_QuestLastPointPos.y <= 242.0f)
				m_QuestLastPointPos.y = 242.0f;
			m_SelectSE->Play();
		}

		//はいといいえの処理
		if (m_QuestLastPointPos.y >= 291.0f && Input::GetKeyTrigger('F'))
			m_QuestGateLastFlg = false;
		else if (m_QuestLastPointPos.y <= 242.0f && Input::GetKeyTrigger('F'))
		{
			m_Fade->FadeOut();
		}
	}

	//ロード画面に遷移する処理
	if (m_Fade->GetFadeFinish() && m_QuestGate)
	{
		Manager::SetScene<Loading>();
		m_QuestGate = false;
		m_GameSceneFlg = true;
		Village::SetVillageFlg(false);
	}

	
	//村のチュートリアル
	if (vplayer->GetVillageInfoFlg())
	{
		if (Input::GetKeyTrigger('E'))
		{
			m_InfoFirstSelectFlg = true;
			m_LastSelectPointerPos = D3DXVECTOR3(363.0f, 85.0f, 0.0f);
			m_LastSelectPointerScale = D3DXVECTOR3(600, 300.0f, 0.0f);
		}
		
	}
	else if (Input::GetKeyTrigger('R'))
	{
		m_InfoFirstSelectFlg = false;
		m_EnterSE->Play();
	}

	if (m_InfoFirstSelectFlg)
	{
		if (Input::GetKeyTrigger(VK_DOWN) && m_InfoFirstSelectFlg)
		{
			m_LastSelectPointerPos.y += 20.0f; //69
			m_SelectSE->Play();
		}

		if (Input::GetKeyTrigger(VK_UP) && m_InfoFirstSelectFlg)
		{
			m_LastSelectPointerPos.y -= 20.0f;
			m_SelectSE->Play();
		}
	}

	if (Input::GetKeyTrigger('F') && m_InfoFirstSelectFlg && m_LastSelectPointerPos.y == 85.0f)
	{
		m_InfoSecondSelectFlg = true;
		m_InfoFirstSelectFlg = false;
		m_EnterSE->Play();
	}
	else if (Input::GetKeyTrigger('F') && m_InfoFirstSelectFlg && m_LastSelectPointerPos.y == 154.0f)
	{
		m_InfoFirstSelectFlg = false;
		m_TitleLastInfoFlg = true;

		m_EnterSE->Play();
		if (Input::GetKeyTrigger('F') && m_TitleLastInfoFlg)
		{
			m_LastSelectPointerPos = D3DXVECTOR3(522.0f, 160.0f, 0.0f);
			m_LastSelectPointerScale = D3DXVECTOR3(250, 300.0f, 0.0f);
			m_EnterSE->Play();
		}
	}
	else if (Input::GetKeyTrigger('F') && m_TitleLastInfoFlg && m_LastSelectPointerPos.y == 160.0f)
	{
		//タイトルに戻る処理
		m_Fade->FadeOut();
		m_EnterSE->Play();
	}
	else if (Input::GetKeyTrigger('F') && m_TitleLastInfoFlg && m_LastSelectPointerPos.y == 209.0f)
	{
		m_EnterSE->Play();

		if (Input::GetKeyTrigger('F'))
		{
			m_LastSelectPointerPos = D3DXVECTOR3(363.0f, 85.0f, 0.0f);
			m_LastSelectPointerScale = D3DXVECTOR3(600, 300.0f, 0.0f);
			m_EnterSE->Play();

		}

		m_TitleLastInfoFlg = false;
		m_InfoFirstSelectFlg = true;
	}
	else if (Input::GetKeyTrigger('F') && m_InfoSecondSelectFlg )
	{
		m_InfoSecondSelectFlg = false;
		m_WeaponStoreInfoFlg = true;
		m_EnterSE->Play();


	}
	else if (Input::GetKeyTrigger('F') && m_WeaponStoreInfoFlg)
	{
		m_WeaponStoreInfoFlg = false;
		m_GeneralStoreInfoFlg = true;
		m_EnterSE->Play();

	}
	else if (Input::GetKeyTrigger('F') && m_GeneralStoreInfoFlg)
	{
		m_GeneralStoreInfoFlg = false;
		m_QuestBoardInfoFlg = true;
		m_EnterSE->Play();

	}
	else if (Input::GetKeyTrigger('F') && m_QuestBoardInfoFlg)
	{
		m_QuestBoardInfoFlg = false;
		m_TutorialInfoFlg = true;
		m_EnterSE->Play();

	}
	else if (Input::GetKeyTrigger('F') && m_TutorialInfoFlg)
	{
		m_TutorialInfoFlg = false;
		m_QuestGateInfoFlg = true;
		m_EnterSE->Play();

	}
	else if (Input::GetKeyTrigger('F') && m_QuestGateInfoFlg)
	{
		m_QuestGateInfoFlg = false;
		m_InfoFinishFlg = true;
		m_EnterSE->Play();

	}
	else if (Input::GetKeyTrigger('F') && m_InfoFinishFlg)
	{
		m_EnterSE->Play();

		if (Input::GetKeyTrigger('F'))
		{
			m_LastSelectPointerPos = D3DXVECTOR3(363.0f, 85.0f, 0.0f);
			m_LastSelectPointerScale = D3DXVECTOR3(600, 300.0f, 0.0f);
			m_EnterSE->Play();

		}
		m_InfoFinishFlg = false;
		m_InfoFirstSelectFlg = true;
	}

	if (m_Fade->GetFadeFinish() && m_TitleLastInfoFlg)
	{
		Manager::SetScene<Title>();
		Village::SetVillageFlg(false);
	}

	//アイテムデーターをデーターベースへ保存する
	ItemDataLoad::SetKeepItemBase(0, ItemDataLoad::GetItemBaseIndex(0));
	ItemDataLoad::SetDataKeepFlg(true);

	//お金を保存
	Money::SetKeepMoney(Money::GetMoney(), true);

	GameObject::Update();
}

void VillageUi::Draw()
{

	Scene* scene = Manager::GetScene();
	VillagePlayerAction* vplayer = scene->GetGameObject<VillagePlayerAction>();
	Weapon* weapon = scene->GetGameObject<Weapon>();


	if (m_ConfirmationFlg)
	{
		//確認画面
		m_ChackPic->Draw(m_ChackPicPos, m_ChackPicScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

		//回復薬の数
		m_ConfirmationScore->Draw();
		m_ConfirmationScore->SetCount(ItemDataLoad::GetItemBaseIndex(0)->GetItemCount());
		m_ConfirmationScore->SetPosAndScale(m_ItemNumPos.x, m_ItemNumPos.y, m_ItemNumScale.x, m_ItemNumScale.y);

		//残金
		m_MoeneyNum->Draw();
		m_MoeneyNum->SetCount(Money::GetMoney());
		m_MoeneyNum->SetPosAndScale(m_ConfirmationMoneyPos.x, m_ConfirmationMoneyPos.y, m_ConfirmationMoneyScale.x, m_ConfirmationMoneyScale.y);

		m_ReturnRavel->Draw(m_ReturnRavelPos, m_ReturnRavelScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);


	}
	else
	{
		m_ChackRavel->Draw(m_ChackRavelPos, m_ChackRavelScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);
	}


	//クエストゲートのUI
	if (m_QuestGateLastFlg)
	{
		m_QuestGateLastInfo->Draw(m_QuestGateLastInfoPos, m_QuestGateLastInfoScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.8f);
		
		m_LastSelectPointer->Draw(m_QuestLastPointPos, m_QuestLastPointScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);
	}


	//チュートリアルのUI描画
	if (m_InfoFirstSelectFlg)
	{
		m_VillageInfoSelect01->Draw(m_VillageInfoSelect01Pos, m_VillageInfoSelect01Scale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);
		m_LastSelectPointer->Draw(m_LastSelectPointerPos, m_LastSelectPointerScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);
	}


	if (m_InfoSecondSelectFlg)
		m_VillageInfoSelect02->Draw(m_VillageInfoSelect02Pos, m_VillageInfoSelect02Scale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);


	if(m_WeaponStoreInfoFlg)
		m_WeaponStoreInfo->Draw(m_WeaponStoreInfoPos, m_WeaponStoreInfoScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

	if(m_GeneralStoreInfoFlg)
		m_GeneralStoreInfo->Draw(m_GeneralStoreInfoPos, m_GeneralStoreInfoScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

	if (m_QuestBoardInfoFlg)
		m_QuestBoardInfo->Draw(m_QuestBoardInfoPos, m_QuestBoardInfoScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

	if (m_QuestGateInfoFlg)
		m_QuestGateInfo->Draw(m_QuestGateInfoPos, m_QuestGateInfoScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

	if(m_TutorialInfoFlg)
		m_TutorialInfo->Draw(m_TutorialInfoPos, m_TutorialInfoScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

	if (m_InfoFinishFlg)
		m_InfoFinish->Draw(m_InfoFinishPos, m_InfoFinishScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

	if (m_TitleLastInfoFlg)
	{
		m_TitleLastInfo->Draw(m_TitleLastInfoPos, m_TitleLastInfoScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);
		m_LastSelectPointer->Draw(m_LastSelectPointerPos, m_LastSelectPointerScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);
	}




	GameObject::Draw();
}