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

//int VillageUi::m_ItemCount{};
//bool VillageUi::m_ItemCountFlg{};
//bool VillageUi::m_Level1RespwanFlg{};
//bool VillageUi::m_Level2RespwanFlg{};
//bool VillageUi::m_Level3RespwanFlg{};
bool VillageUi::m_QuestGate{};
bool VillageUi::m_GameSceneFlg{};

void VillageUi::Init()
{

	Scene* scene = Manager::GetScene();

	//アイテムデータの読み込み
	ItemDataLoad::DataLoad();


	//武器のデータ読み込み
	m_WeaponDataLoad = new WeaponDataLoad;
	m_WeaponDataLoad->DataLoad();

	WeaponDataLoad::DataLoad();

	m_Fade = scene->AddGameObject<Fade>(2);

	//お金の初期化
	Money::Init();

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
	//m_BlacksmithFirstSelect = new Sprit2D;
	//m_BlacksmithSecondSelect01 = new Sprit2D;
	//m_BlacksmithSecondSelect02 = new Sprit2D;
	//m_BlacksmithSecondSelect03 = new Sprit2D;
	m_BlacksmithSelectPointer = new Sprit2D;
	//m_WeaponMaterial1 = new Sprit2D;
	//m_WeaponMaterial2 = new Sprit2D;
	//m_WeaponMaterial3 = new Sprit2D;
	//m_BlacksmithPointer = new Sprit2D;
	//m_BlacksmithLastInfo = new Sprit2D;
	//m_Weapon00Info = new Sprit2D;
	//m_Weapon00SharpnessTextuer = new Sprit2D;
	//m_Weapon01Info = new Sprit2D;
	//m_Weapon01SharpnessTextuer = new Sprit2D;
	//m_Weapon02Info = new Sprit2D;
	//m_Weapon03Info = new Sprit2D;
	//m_GeneralStoreFirstInfo = new Sprit2D;
	//m_GeneralStoreSelectInfo0 = new Sprit2D;
	//m_GeneralStoreSelectInfo1 = new Sprit2D;
	//m_GeneralStoreSelectInfo2 = new Sprit2D;
	//m_GeneralStoreSelectInfo3 = new Sprit2D;
	//m_GeneralStoreLastInfo = new Sprit2D; 
	m_QuestGateLastInfo = new Sprit2D;
	m_Weapon00Sharpp = new Sprit2D;
	m_Weapon01Sharpp = new Sprit2D;
	m_Weapon02Sharpp = new Sprit2D;
	m_Weapon03Sharpp = new Sprit2D;
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


	m_Weapon00Attack = new Score;
	m_Weapon01Attack = new Score;
	m_Weapon02Attack = new Score;
	m_Weapon03Attack = new Score;
	m_Weapon01Price = new Score;
	m_Weapon02Price = new Score;
	m_Weapon03Price = new Score;
	m_ConfirmationScore = new Score;
	m_MoeneyNum = new Score;
	//m_BeforeWeapon = new Score;
	//m_AfterWeapon = new Score;
	//m_AfterWeaponPrice = new Score;
	m_ItemNum = new Score;


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
	//m_BlacksmithFirstSelect->Init("asset/texture/blacksmithFirstInfo.png");
	//m_BlacksmithSecondSelect01->Init("asset/texture/weaponselect01.png");
	//m_BlacksmithSecondSelect02->Init("asset/texture/weaponselect02.png");
	//m_BlacksmithSecondSelect03->Init("asset/texture/weaponselect03.png");
	//m_WeaponMaterial1->Init("asset/texture/weaponselect04.png");
	m_BlacksmithSelectPointer->Init("asset/texture/weaponselectpointer.png");
	//m_WeaponMaterial2->Init("asset/texture/weaponsozai02.png");
	//m_WeaponMaterial3->Init("asset/texture/weaponsozai03.png");
	//m_BlacksmithPointer->Init("asset/texture/blacksmithPointer.png");
	//m_BlacksmithLastInfo->Init("asset/texture/weaponLastInfo.png");
	//m_Weapon00Info->Init("asset/texture/weapon00Info.png");
	//m_Weapon00SharpnessTextuer->Init("asset/texture/weaponsozai03.png");
	//m_Weapon01Info->Init("asset/texture/weapon01Info.png");
	//m_Weapon01SharpnessTextuer->Init("asset/texture/weapon01Info.png");
	//m_Weapon02Info->Init("asset/texture/weapon02Info.png");
	//m_Weapon03Info->Init("asset/texture/weapon03Info.png");
	//m_GeneralStoreFirstInfo->Init("asset/texture/sundriesFirstInfo.png");
	//m_GeneralStoreSelectInfo0->Init("asset/texture/generalstoreInfo.png");
	//m_GeneralStoreSelectInfo1->Init("asset/texture/generalsotreSelectInfo01.png");
	//m_GeneralStoreSelectInfo2->Init("asset/texture/generalsotreSelectInfo02.png");
	//m_GeneralStoreSelectInfo3->Init("asset/texture/generalsotreSelectInfo03.png");
	//m_GeneralStoreLastInfo->Init("asset/texture/generalsotreLastInfo.png");
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


	//m_Weapon00Sharpp->Init(m_WeaponDataLoad->GetWeaponDataBaseIndex(0)->GetWeaponSharpnessTextuer());
	//m_Weapon01Sharpp->Init(m_WeaponDataLoad->GetWeaponDataBaseIndex(1)->GetWeaponSharpnessTextuer());
	//m_Weapon02Sharpp->Init(m_WeaponDataLoad->GetWeaponDataBaseIndex(2)->GetWeaponSharpnessTextuer());
	//m_Weapon03Sharpp->Init(m_WeaponDataLoad->GetWeaponDataBaseIndex(3)->GetWeaponSharpnessTextuer());


	//やじるし
	m_PointerPos = D3DXVECTOR3(680.0f, 50.0f, 0.0f);
	m_PointerScale = D3DXVECTOR3(200.0f, 100.0f, 0.0f);
	m_PointerRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//クエスト選択1
	m_QuestChoice01Pos = D3DXVECTOR3(680.0f, -100.0f, 0.0f);
	m_QuestChoice01Scale = D3DXVECTOR3(750.0f, 400.0f, 0.0f);
	m_QuestChoice01Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//クエスト選択2
	m_QuestChoice02Pos = D3DXVECTOR3(680.0f, -20.0f, 0.0f);
	m_QuestChoice02Scale = D3DXVECTOR3(750.0f, 400.0f, 0.0f);
	m_QuestChoice02Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//クエスト選択3
	m_QuestChoice03Pos = D3DXVECTOR3(680.0f, 60.0f, 0.0f);
	m_QuestChoice03Scale = D3DXVECTOR3(750.0f, 400.0f, 0.0f);
	m_QuestChoice03Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//クエスト1
	m_Quest01Pos = D3DXVECTOR3(500.0f, 50.0f, 0.0f);
	m_Quest01Scale = D3DXVECTOR3(900.0f, 600.0f, 0.0f);
	m_Quest01Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//クエスト2
	m_Quest02Pos = D3DXVECTOR3(500.0f, 50.0f, 0.0f);
	m_Quest02Scale = D3DXVECTOR3(900.0f, 600.0f, 0.0f);
	m_Quest02Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//クエスト3
	m_Quest03Pos = D3DXVECTOR3(500.0f, 50.0f, 0.0f);
	m_Quest03Scale = D3DXVECTOR3(900.0f, 600.0f, 0.0f);
	m_Quest03Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//決定か戻るかの入力案内
	m_EnerOrReternPos = D3DXVECTOR3(900.0f, 550.0f, 0.0f);
	m_EnerOrReternScale = D3DXVECTOR3(400.0f, 200.0f, 0.0f);
	m_EnerOrReternRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//クエストの決定案内
	m_LastSelectPos = D3DXVECTOR3(-150.0f, 200.0f, 0.0f);
	m_LastSelectScale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);
	m_LastSelectRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//クエスト最終決定のやじるし
	m_LastSelectPointerPos = D3DXVECTOR3(175.0f, 355.0f, 0.0f);
	m_LastSelectPointerScale = D3DXVECTOR3(250.0f, 250.0f, 0.0f);
	m_LastSelectPointerRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//武器選択画面
	m_BlacksmithFirstSelectPos = D3DXVECTOR3(830.0f, -10.0f, 0.0f);
	m_BlacksmithFirstSelectScale = D3DXVECTOR3(500.0f, 300.0f, 0.0f);
	m_BlacksmithFirstSelectRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	////武器選択画面01
	//m_BlacksmithSecondSelect01Pos = D3DXVECTOR3(600.0f, 50.0f, 0.0f);
	//m_BlacksmithSecondSelect01Scale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);
	//m_BlacksmithSecondSelect01Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////武器選択画面02
	//m_BlacksmithSecondSelect02Pos = D3DXVECTOR3(-200.0f, 250.0f, 0.0f);
	//m_BlacksmithSecondSelect02Scale = D3DXVECTOR3(900.0f, 400.0f, 0.0f);
	//m_BlacksmithSecondSelect02Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////武器選択画面03
	//m_BlacksmithSecondSelect03Pos = D3DXVECTOR3(-200.0f, 20.0f, 0.0f);
	//m_BlacksmithSecondSelect03Scale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);
	//m_BlacksmithSecondSelect03Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////武器選択画面04
	//m_WeaponMaterial1Pos = D3DXVECTOR3(570.0f, 300.0f, 0.0f);
	//m_WeaponMaterial1Scale = D3DXVECTOR3(950.0f, 500.0f, 0.0f);
	//m_WeaponMaterial1Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//武器選択画面やじるし
	m_BlacksmithSelectPointerPos = D3DXVECTOR3(700.0f, 125.0f, 0.0f);
	m_BlacksmithSelectPointerScale = D3DXVECTOR3(700.0f, 150.0f, 0.0f);
	m_BlacksmithSelectPointerRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	////武器2の素材
	//m_WeaponMaterial2Pos = D3DXVECTOR3(570.0f, 300.0f, 0.0f);
	//m_WeaponMaterial2Scale = D3DXVECTOR3(950.0f, 500.0f, 0.0f);
	//m_WeaponMaterial2Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////武器3の素材
	//m_WeaponMaterial3Pos = D3DXVECTOR3(570.0f, 300.0f, 0.0f);
	//m_WeaponMaterial3Scale = D3DXVECTOR3(950.0f, 500.0f, 0.0f);
	//m_WeaponMaterial3Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////武器遷移やじるし
	//m_BlacksmithPointerPos = D3DXVECTOR3(827.0f, 257.0f, 0.0f);
	//m_BlacksmithPointerScale = D3DXVECTOR3(400.0f, 200.0f, 0.0f);
	//m_BlacksmithPointerRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////武器最後情報
	//m_BlacksmithLastInfoPos = D3DXVECTOR3(-198.0f, 42.0f, 0.0f);
	//m_BlacksmithLastInfoScale = D3DXVECTOR3(800.0f, 450.0f, 0.0f);
	//m_BlacksmithLastInfoRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	////武器0の情報
	//m_Weapon00InfoPos = D3DXVECTOR3(594.0f, -102.0f, 0.0f);
	//m_Weapon00InfoScale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);
	//m_Weapon00InfoRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////武器0の切れ味
	//m_Weapon00SharpnessTextuerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_Weapon00SharpnessTextuerScale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_Weapon00SharpnessTextuerRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	////武器1の情報
	//m_Weapon01InfoPos = D3DXVECTOR3(594.0f, 185.0f, 0.0f);
	//m_Weapon01InfoScale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);
	//m_Weapon01InfoRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////武器1の切れ味
	//m_Weapon01SharpnessTextuerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_Weapon01SharpnessTextuerScale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_Weapon01SharpnessTextuerRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////武器2の情報
	//m_Weapon02InfoPos = D3DXVECTOR3(594.0f, 185.0f, 0.0f);
	//m_Weapon02InfoScale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);
	//m_Weapon02InfoRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////武器3の情報
	//m_Weapon03InfoPos = D3DXVECTOR3(594.0f, 185.0f, 0.0f);
	//m_Weapon03InfoScale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);
	//m_Weapon03InfoRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////雑貨屋の最初の画面
	//m_GeneralStoreFirstInfoPos = D3DXVECTOR3(830.0f, -10.0f, 0.0f);
	//m_GeneralStoreFirstInfoScale = D3DXVECTOR3(500.0f, 300.0f, 0.0f);
	//m_GeneralStoreFirstInfoRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	////雑貨屋のアイテム選択画面1
	//m_GeneralStoreSelectInfoPos0 = D3DXVECTOR3(-198.0f, -33.0f, 0.0f);
	//m_GeneralStoreSelectInfoScale0 = D3DXVECTOR3(900.0f, 500.0f, 0.0f);
	//m_GeneralStoreSelectInfoRot0 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////雑貨屋のアイテム選択画面2
	//m_GeneralStoreSelectInfoPos1 = D3DXVECTOR3(588.0f, -33.0f, 0.0f);
	//m_GeneralStoreSelectInfoScale1 = D3DXVECTOR3(900.0f, 500.0f, 0.0f);
	//m_GeneralStoreSelectInfoRot1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////雑貨屋のアイテム選択画面3
	//m_GeneralStoreSelectInfoPos2 = D3DXVECTOR3(588.0f, 205.0f, 0.0f);
	//m_GeneralStoreSelectInfoScale2 = D3DXVECTOR3(900.0f, 500.0f, 0.0f);
	//m_GeneralStoreSelectInfoRot2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////雑貨屋のアイテム選択画面4
	//m_GeneralStoreSelectInfoPos3 = D3DXVECTOR3(-198.0f, -33.0f, 0.0f);
	//m_GeneralStoreSelectInfoScale3 = D3DXVECTOR3(900.0f, 500.0f, 0.0f);
	//m_GeneralStoreSelectInfoRot3 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////雑貨屋のアイテム最後の選択画面
	//m_GeneralStoreLastInfoPos = D3DXVECTOR3(-198.0f, -33.0f, 0.0f);
	//m_GeneralStoreLastInfoScale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);
	//m_GeneralStoreLastInfoRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//クエスト出発前の画面
	m_QuestGateLastInfoPos = D3DXVECTOR3(177.0f, 61.0f, 0.0f);
	m_QuestGateLastInfoScale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);
	m_QuestGateLastInfoRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////武器0の切れ味ゲージ
	//m_Weapon00SharppPos = D3DXVECTOR3(854.0f, 81.0f, 0.0f);
	//m_Weapon00SharppScale = D3DXVECTOR3(400.0f, 280.0f, 0.0f);
	//m_Weapon00SharppRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////武器1の切れ味ゲージ
	//m_Weapon01SharppPos = D3DXVECTOR3(854.0f, 81.0f, 0.0f);
	//m_Weapon01SharppScale = D3DXVECTOR3(400.0f, 280.0f, 0.0f);
	//m_Weapon01SharppRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////武器2の切れ味ゲージ
	//m_Weapon02SharppPos = D3DXVECTOR3(854.0f, 81.0f, 0.0f);
	//m_Weapon02SharppScale = D3DXVECTOR3(400.0f, 280.0f, 0.0f);
	//m_Weapon02SharppRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////武器3の切れ味ゲージ
	//m_Weapon03SharppPos = D3DXVECTOR3(854.0f, 81.0f, 0.0f);
	//m_Weapon03SharppScale = D3DXVECTOR3(400.0f, 280.0f, 0.0f);
	//m_Weapon03SharppRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

	//武器屋での残金表示
	m_WeaponStorMoneyPos = D3DXVECTOR3(1212.0f, 37.0f, 0.0f);
	m_WeaponStorMoneyScale = D3DXVECTOR3(40.0f, 30.0f, 0.0f);

	//雑貨屋での残金表示
	m_GeneralStoreMoneyPos = D3DXVECTOR3(1212.0f, 37.0f, 0.0f);
	m_GeneralStoreMoneyScale = D3DXVECTOR3(40.0f, 30.0f, 0.0f);

	//クエストでの残金表示
	m_QuestMoneyPos = D3DXVECTOR3(1229.0f, 14.0f, 0.0f);
	m_QuestMoneyScale = D3DXVECTOR3(40.0f, 30.0f, 0.0f);

	//クエスト行く際の最後の矢印
	m_QuestLastPointPos = D3DXVECTOR3(487.0f, 242.0f, 0.0f);
	m_QuestLastPointScale = D3DXVECTOR3(280.0f, 200.0f, 0.0f);

	//確認の時の画像
	m_ChackPicPos = D3DXVECTOR3(270.0f, 68.0f, 0.0f);
	m_ChackPicScale = D3DXVECTOR3(775.0f, 420.0f, 0.0f);

	//常時出しておく確認画面を開くための指示
	m_ChackRavelPos = D3DXVECTOR3(-16.0f,528.0f, 0.0f);
	m_ChackRavelScale = D3DXVECTOR3(280.0f, 200.0f, 0.0f);

	//確認が画面を開いたときに出る戻るための指示
	m_ReturnRavelPos = D3DXVECTOR3(-60.0f, 499.0f, 0.0f);
	m_ReturnRavelScale = D3DXVECTOR3(280.0f, 200.0f, 0.0f);

	//スコアの初期化
	m_Weapon00Attack->Init();
	m_Weapon01Attack->Init();
	m_Weapon02Attack->Init();
	m_Weapon03Attack->Init();
	m_Weapon01Price->Init();
	m_Weapon02Price->Init();
	m_Weapon03Price->Init();
	m_ConfirmationScore->Init();
	m_MoeneyNum->Init();
	//m_BeforeWeapon->Init();
	//m_AfterWeapon->Init();
	//m_AfterWeaponPrice->Init();
	m_ItemNum->Init();

	//m_Level1RespwanFlg = false;
	//m_Level2RespwanFlg = false;
	//m_Level3RespwanFlg = false;

	//m_ItemCount = 1;

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


	GameObject::Init();
}

void VillageUi::Uninit()
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
	//m_BlacksmithFirstSelect->Uninit();
	//m_BlacksmithSecondSelect01->Uninit();
	//m_BlacksmithSecondSelect02->Uninit();
	//m_BlacksmithSecondSelect03->Uninit();
	m_BlacksmithSelectPointer->Uninit();
	//m_WeaponMaterial1->Uninit();
	//m_WeaponMaterial2->Uninit();
	//m_WeaponMaterial3->Uninit();
	//m_BlacksmithPointer->Uninit();
	//m_BlacksmithLastInfo->Uninit();
	//m_Weapon00Info->Uninit();
	//m_Weapon00SharpnessTextuer->Uninit();
	//m_Weapon01Info->Uninit();
	//m_Weapon01SharpnessTextuer->Uninit();
	//m_Weapon02Info->Uninit();
	//m_Weapon03Info->Uninit();
	//m_GeneralStoreSelectInfo0->Uninit();
	//m_GeneralStoreSelectInfo1->Uninit();
	//m_GeneralStoreSelectInfo2->Uninit();
	//m_GeneralStoreSelectInfo3->Uninit();
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

	//m_Weapon00Attack->Uninit();
	//m_Weapon01Attack->Uninit();
	//m_Weapon02Attack->Uninit();
	//m_Weapon03Attack->Uninit();
	//m_Weapon01Price->Uninit();
	//m_Weapon02Price->Uninit();
	//m_Weapon03Price->Uninit();


	//m_Weapon00Sharpp->Uninit();
	//m_Weapon01Sharpp->Uninit();
	//m_Weapon02Sharpp->Uninit();
	//m_Weapon03Sharpp->Uninit();
	m_ConfirmationScore->Uninit();
	m_MoeneyNum->Uninit();
	//m_BeforeWeapon->Uninit();
	//m_AfterWeapon->Uninit();
	//m_AfterWeaponPrice->Uninit();
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


	////クエスト選択画面
	//if (m_PointerLockFlg == false)
	//{
	//	if (Input::GetKeyTrigger(VK_DOWN))
	//	{
	//		m_PointerPos.y += 80.0f;
	//		m_SelectSE->Play();
	//	}

	//	if (Input::GetKeyTrigger(VK_UP))
	//	{
	//		m_PointerPos.y -= 80.0f;
	//		m_SelectSE->Play();
	//	}

	//}

	////クエスト最終確認のやじるし
	//if (m_BlecksmithSelect3 == false && m_ItemLastInfo == false)
	//{
	//	if (Input::GetKeyTrigger(VK_DOWN))
	//	{
	//		m_LastSelectPointerPos.y += 49.0f;
	//		m_SelectSE->Play();
	//	}

	//	if (Input::GetKeyTrigger(VK_UP))
	//	{
	//		m_LastSelectPointerPos.y -= 49.0f;
	//		m_SelectSE->Play();
	//	}

	//}

	//if (Input::GetKeyTrigger('E') && vplayer->GetQuestFlg())
	//{
	//	m_PointerPos = D3DXVECTOR3(680.0f, 50.0f, 0.0f);
	//	m_PointerScale = D3DXVECTOR3(200.0f, 100.0f, 0.0f);

	//	m_LastSelectPointerPos = D3DXVECTOR3(175.0f, 355.0f, 0.0f);
	//	m_LastSelectPointerScale = D3DXVECTOR3(250.0f, 250.0f, 0.0f);

	//}


	////レベル1
	//if (m_PointerPos.y == 50 && vplayer->GetQuestFlg())
	//{
	//	m_QuestChoice01Pos.x = 665.0f;
	//	if (Input::GetKeyTrigger('F')&&m_Level1Flg == false && m_LastSelectFlg == false)
	//	{
	//		//最初のクエスト選択画面で選ばれたクエスト
	//		m_PointerLockFlg = true;
	//		m_Level1Flg = true;
	//		m_EnterSE->Play();

	//	}
	//	else if (Input::GetKeyTrigger('F') && m_Level1Flg == true && m_LastSelectFlg == false)
	//	{
	//		//最終クエスト選択を表示
	//		m_LastSelectPointerPos.y = 355.0f;
	//		m_LastSelectFlg = true;
	//		m_Level1Flg = false;
	//		m_EnterSE->Play();

	//	}
	//	else if (Input::GetKeyTrigger('F') && m_LastSelectFlg == true && m_LastSelectPointerPos.y <= 355.0f && Money::GetMoney() >= 100)
	//	{
	//		//クエスト最終選択で"はい"だった場合
	//		//ここでレベル１のモンスターをリスポーンさせるフラグを立てる
	//		m_Level1RespwanFlg = true;
	//		m_LastSelectFlg = false;
	//		vplayer->SetQuestFlg(false);
	//		m_PointerLockFlg = false;
	//		vplayer->SetSVillgeStopFlg(false);

	//		//お金を減らす処理
	//		Money::SetMinusMoney(100);

	//		m_EnterSE->Play();

	//	}
	//	else if (Input::GetKeyTrigger('F') && m_LastSelectPointerPos.y >= 404.0f && m_Level1Flg == false && m_LastSelectFlg == true)
	//	{
	//		//クエスト最終選択で"いいえ"だった場合
	//		m_LastSelectFlg = false;
	//		m_Level1Flg = true;

	//		m_EnterSE->Play();

	//	}
	//	else if (Input::GetKeyTrigger('R') && m_Level1Flg == true && m_LastSelectFlg == false)
	//	{
	//		//戻る
	//		m_Level1Flg = false;
	//		m_PointerLockFlg = false;
	//		m_EnterSE->Play();

	//	}

	//}
	//else
	//	m_QuestChoice01Pos.x = 680.0f;



	////レベル2
	//if (m_PointerPos.y == 130 && vplayer->GetQuestFlg())
	//{
	//	m_QuestChoice02Pos.x = 665.0f;
	//	if (Input::GetKeyTrigger('F') && m_Level2Flg == false && m_LastSelectFlg == false)
	//	{
	//		//最初のクエスト選択画面で選ばれたクエスト
	//		m_PointerLockFlg = true;
	//		m_Level2Flg = true;
	//		m_EnterSE->Play();

	//	}
	//	else if (Input::GetKeyTrigger('F') && m_Level2Flg == true && m_LastSelectFlg == false)
	//	{
	//		//最終クエスト選択を表示
	//		m_LastSelectPointerPos.y = 355.0f;
	//		m_LastSelectFlg = true;
	//		m_Level2Flg = false;

	//		m_EnterSE->Play();

	//	}
	//	else if (Input::GetKeyTrigger('F') && m_LastSelectFlg == true && m_LastSelectPointerPos.y <= 355.0f && Money::GetMoney() >= 100)
	//	{
	//		//クエスト最終選択で"はい"だった場合
	//		//ここでレベル１のモンスターをリスポーンさせるフラグを立てる
	//		m_Level2RespwanFlg = true;
	//		m_LastSelectFlg = false;
	//		vplayer->SetQuestFlg(false);
	//		m_PointerLockFlg = false;
	//		vplayer->SetSVillgeStopFlg(false);

	//		//お金を減らす処理
	//		Money::SetMinusMoney(100);

	//		m_EnterSE->Play();

	//	}
	//	else if (Input::GetKeyTrigger('F') && m_LastSelectPointerPos.y >= 404.0f && m_Level2Flg == false && m_LastSelectFlg == true)
	//	{
	//		//クエスト最終選択で"いいえ"だった場合
	//		m_LastSelectFlg = false;
	//		m_Level2Flg = true;
	//		m_EnterSE->Play();

	//	}
	//	else if (Input::GetKeyTrigger('R') && m_Level2Flg == true && m_LastSelectFlg == false)
	//	{
	//		//戻る
	//		m_Level2Flg = false;
	//		m_PointerLockFlg = false;
	//		m_EnterSE->Play();

	//	}

	//}
	//else
	//	m_QuestChoice02Pos.x = 680.0f;


	////レベル3
	//if (m_PointerPos.y >= 210 && vplayer->GetQuestFlg())
	//{
	//	m_QuestChoice03Pos.x = 665.0f;
	//	if (Input::GetKeyTrigger('F') && m_Level3Flg == false && m_LastSelectFlg == false)
	//	{
	//		//最初のクエスト選択画面で選ばれたクエスト
	//		m_PointerLockFlg = true;
	//		m_Level3Flg = true;

	//		m_EnterSE->Play();

	//	}
	//	else if (Input::GetKeyTrigger('F') && m_Level3Flg == true && m_LastSelectFlg == false)
	//	{
	//		//最終クエスト選択を表示
	//		m_LastSelectPointerPos.y = 355.0f;
	//		m_LastSelectFlg = true;
	//		m_Level3Flg = false;
	//		m_EnterSE->Play();

	//	}
	//	else if (Input::GetKeyTrigger('F') && m_LastSelectFlg == true && m_LastSelectPointerPos.y <= 355.0f && Money::GetMoney() >= 100)
	//	{
	//		//クエスト最終選択で"はい"だった場合
	//		//ここでレベル１のモンスターをリスポーンさせるフラグを立てる
	//		m_Level3RespwanFlg = true;
	//		m_LastSelectFlg = false;
	//		vplayer->SetQuestFlg(false);
	//		m_PointerLockFlg = false;
	//		vplayer->SetSVillgeStopFlg(false);

	//		//お金を減らす処理
	//		Money::SetMinusMoney(100);

	//		m_EnterSE->Play();

	//	}
	//	else if (Input::GetKeyTrigger('F') && m_LastSelectPointerPos.y >= 404.0f && m_Level3Flg == false && m_LastSelectFlg == true)
	//	{
	//		//クエスト最終選択で"いいえ"だった場合
	//		m_LastSelectFlg = false;
	//		m_Level3Flg = true;
	//	}
	//	else if (Input::GetKeyTrigger('R') && m_Level3Flg == true && m_LastSelectFlg == false)
	//	{
	//		//戻る
	//		m_Level3Flg = false;
	//		m_PointerLockFlg = false;
	//		m_EnterSE->Play();

	//	}

	//}
	//else
	//	m_QuestChoice03Pos.x = 680.0f;


	////レベル2
	//if (m_PointerPos.y == 130)
	//	m_QuestChoice02Pos.x = 665.0f;
	//else
	//	m_QuestChoice02Pos.x = 680.0f;

	////レベル3
	//if (m_PointerPos.y == 210)
	//	m_QuestChoice03Pos.x = 665.0f;
	//else
	//	m_QuestChoice03Pos.x = 680.0f;



	////最初のクエスト選択やじるしの上限
	//if (m_PointerPos.y >= 210)
	//	m_PointerPos.y = 210;

	////最初のクエスト選択やじるしの下限
	//if (m_PointerPos.y <= 50)
	//	m_PointerPos.y = 50;


	////クエスト最終選択やじるしの上限(鍛冶場で使ってないとき)
	//if (m_BlecksmithSelect3 == false && m_ItemLastInfo == false && m_QuestGate == false && m_InfoFirstSelectFlg == false && m_TitleLastInfoFlg == false)
	//{
	//	if (m_LastSelectPointerPos.y >= 404.0f)
	//		m_LastSelectPointerPos.y = 404.0f;

	//	//クエスト最終選択やじるしの下限
	//	if (m_LastSelectPointerPos.y <= 355.0f)
	//		m_LastSelectPointerPos.y = 355.0f;
	//}

	//最後の門の処理
	if (m_Level1RespwanFlg || m_Level2RespwanFlg || m_Level3RespwanFlg)
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


	////クエスト画像選択画面
	//if (vplayer->GetQuestFlg() && m_Level1Flg == false 
	//	                       && m_Level2Flg == false 
	//	                       && m_Level3Flg == false 
	//	                       && m_LastSelectFlg == false)
	//{
	//	m_Pointer->Draw(m_PointerPos, m_PointerScale, m_PointerRot, 1.0f);
	//	m_QuestChoice01->Draw(m_QuestChoice01Pos, m_QuestChoice01Scale, m_QuestChoice01Rot, 1.0f);
	//	m_QuestChoice02->Draw(m_QuestChoice02Pos, m_QuestChoice02Scale, m_QuestChoice02Rot, 1.0f);
	//	m_QuestChoice03->Draw(m_QuestChoice03Pos, m_QuestChoice03Scale, m_QuestChoice03Rot, 1.0f);

	//	//残金
	//	m_MoeneyNum->Draw();
	//	m_MoeneyNum->SetCount(Money::GetMoney());
	//	m_MoeneyNum->SetPosAndScale(m_QuestMoneyPos.x, m_QuestMoneyPos.y, m_QuestMoneyScale.x, m_QuestMoneyScale.y);

	//}

	////レベル1のクエスト
	//if (m_Level1Flg)
	//	m_Quest01->Draw(m_Quest01Pos, m_Quest01Scale, m_Quest01Rot, 1.0f);

	////レベル2のクエスト
	//if (m_Level2Flg)
	//	m_Quest02->Draw(m_Quest02Pos, m_Quest02Scale, m_Quest02Rot, 1.0f);

	////レベル3のクエスト
	//if (m_Level3Flg)
	//	m_Quest03->Draw(m_Quest03Pos, m_Quest03Scale, m_Quest03Rot, 1.0f);


	//if(vplayer->GetQuestFlg())
	//m_EnerOrRetern->Draw(m_EnerOrReternPos, m_EnerOrReternScale, m_EnerOrReternRot, 1.0f);


	//if (m_LastSelectFlg)
	//{
	//	m_LastSelect->Draw(m_LastSelectPos, m_LastSelectScale, m_LastSelectRot, 1.0f);
	//	m_LastSelectPointer->Draw(m_LastSelectPointerPos, m_LastSelectPointerScale, m_LastSelectPointerRot, 1.0f);
	//}


	////雑貨屋のUI
	//if (vplayer->GetGeneralStore())
	//{
	//	if(m_GeneralStoreFlg1 == false)
	//	m_Pointer->Draw(m_PointerPos, m_PointerScale, m_PointerRot, 1.0f);

	//	m_GeneralStoreFirstInfo->Draw(m_GeneralStoreFirstInfoPos, m_GeneralStoreFirstInfoScale, m_GeneralStoreFirstInfoRot, 0.5f);
	//}

	//if (m_GeneralStoreFlg2)
	//{
	//	//残金表示
	//	m_MoeneyNum->Draw();
	//	m_MoeneyNum->SetCount(Money::GetMoney());
	//	m_MoeneyNum->SetPosAndScale(m_GeneralStoreMoneyPos.x, m_GeneralStoreMoneyPos.y, m_GeneralStoreMoneyScale.x, m_GeneralStoreMoneyScale.y);

	//	if (m_ItemNumFlg)
	//	{
	//		m_GeneralStoreSelectInfo3->Draw(m_GeneralStoreSelectInfoPos3, m_GeneralStoreSelectInfoScale3, m_GeneralStoreSelectInfoRot3, 0.8f);

	//		m_ItemNum->Draw();
	//		m_ItemNum->SetCount(m_ItemCount);
	//		m_ItemNum->SetPosAndScale(320, 180, 30.0f, 30.0f);
	//	}
	//	else if (m_ItemLastInfo)
	//	{
	//		m_GeneralStoreLastInfo->Draw(m_GeneralStoreLastInfoPos, m_GeneralStoreLastInfoScale, m_GeneralStoreLastInfoRot, 0.8f);
	//		m_LastSelectPointer->Draw(m_LastSelectPointerPos, m_LastSelectPointerScale, m_LastSelectPointerRot, 1.0f);

	//		m_ItemNum->Draw();
	//		m_ItemNum->SetCount(m_ItemDataLoad->GetItemBaseIndex(0)->GetItemPrice() * m_ItemCount);
	//		m_ItemNum->SetPosAndScale(100.0f, 137.0f, 30.0f, 30.0f);

	//	}
	//	else 
	//	{
	//		m_GeneralStoreSelectInfo0->Draw(m_GeneralStoreSelectInfoPos0, m_GeneralStoreSelectInfoScale0, m_GeneralStoreSelectInfoRot0, 0.8f);
	//	}



	//	m_GeneralStoreSelectInfo1->Draw(m_GeneralStoreSelectInfoPos1, m_GeneralStoreSelectInfoScale1, m_GeneralStoreSelectInfoRot1, 0.8f);
	//	m_GeneralStoreSelectInfo2->Draw(m_GeneralStoreSelectInfoPos2, m_GeneralStoreSelectInfoScale2, m_GeneralStoreSelectInfoRot2, 0.8f);
	//	m_BlacksmithSelectPointer->Draw(m_BlacksmithSelectPointerPos, m_BlacksmithSelectPointerScale, m_BlacksmithSelectPointerRot, 0.3f);
	//}

	if (m_QuestGateLastFlg)
	{
		m_QuestGateLastInfo->Draw(m_QuestGateLastInfoPos, m_QuestGateLastInfoScale, m_QuestGateLastInfoRot, 0.8f);
		
		m_LastSelectPointer->Draw(m_QuestLastPointPos, m_QuestLastPointScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);
	}


	//チュートリアルのUI描画
	if (m_InfoFirstSelectFlg)
	{
		m_VillageInfoSelect01->Draw(m_VillageInfoSelect01Pos, m_VillageInfoSelect01Scale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);
		m_LastSelectPointer->Draw(m_LastSelectPointerPos, m_LastSelectPointerScale, m_LastSelectPointerRot, 1.0f);
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
		m_LastSelectPointer->Draw(m_LastSelectPointerPos, m_LastSelectPointerScale, m_LastSelectPointerRot, 1.0f);
	}




	GameObject::Draw();
}