#include "main.h"
#include "weaponStoreUi.h"
#include "scene.h"
#include "manager.h"
#include "villagePlayerAction.h"
#include "input.h"
#include "weapon.h"
#include "money.h"
#include "sprit2D.h"
#include "audio.h"
#include "score.h"
#include "weaponDataLoad.h"

void WeaponStoreUi::Init()
{
	Scene* scene = Manager::GetScene();

	m_PlayerAction = scene->GetGameObject<VillagePlayerAction>();
	m_Weapon = scene->GetGameObject<Weapon>();

	m_Pointer = new Sprit2D;
	m_LastSelectPointer = new Sprit2D;
	m_BlacksmithFirstSelect = new Sprit2D;
	m_BlacksmithSecondSelect01 = new Sprit2D;
	m_BlacksmithSecondSelect02 = new Sprit2D;
	m_BlacksmithSecondSelect03 = new Sprit2D;
	m_BlacksmithSelectPointer = new Sprit2D;
	m_WeaponMaterial1 = new Sprit2D;
	m_WeaponMaterial2 = new Sprit2D;
	m_WeaponMaterial3 = new Sprit2D;
	m_BlacksmithPointer = new Sprit2D;
	m_BlacksmithLastInfo = new Sprit2D;
	m_Weapon00Info = new Sprit2D;
	m_Weapon00SharpnessTextuer = new Sprit2D;
	m_Weapon01Info = new Sprit2D;
	m_Weapon01SharpnessTextuer = new Sprit2D;
	m_Weapon02Info = new Sprit2D;
	m_Weapon03Info = new Sprit2D;
	m_Weapon00Sharpp = new Sprit2D;
	m_Weapon01Sharpp = new Sprit2D;
	m_Weapon02Sharpp = new Sprit2D;
	m_Weapon03Sharpp = new Sprit2D;

	m_MoeneyNum = new Score;
	m_BeforeWeapon = new Score;
	m_AfterWeapon = new Score;
	m_AfterWeaponPrice = new Score;

	m_Pointer->Init("asset/texture/pointer.png");
	m_LastSelectPointer->Init("asset/texture/LastSelectPointer.png");
	m_BlacksmithFirstSelect->Init("asset/texture/blacksmithFirstInfo.png");
	m_BlacksmithSecondSelect01->Init("asset/texture/weaponselect01.png");
	m_BlacksmithSecondSelect02->Init("asset/texture/weaponselect02.png");
	m_BlacksmithSecondSelect03->Init("asset/texture/weaponselect03.png");
	m_WeaponMaterial1->Init("asset/texture/weaponselect04.png");
	m_BlacksmithSelectPointer->Init("asset/texture/weaponselectpointer.png");
	m_WeaponMaterial2->Init("asset/texture/weaponsozai02.png");
	m_WeaponMaterial3->Init("asset/texture/weaponsozai03.png");
	m_BlacksmithPointer->Init("asset/texture/blacksmithPointer.png");
	m_BlacksmithLastInfo->Init("asset/texture/weaponLastInfo.png");
	m_Weapon00Info->Init("asset/texture/weapon00Info.png");
	m_Weapon00SharpnessTextuer->Init("asset/texture/weaponsozai03.png");
	m_Weapon01Info->Init("asset/texture/weapon01Info.png");
	m_Weapon01SharpnessTextuer->Init("asset/texture/weapon01Info.png");
	m_Weapon02Info->Init("asset/texture/weapon02Info.png");
	m_Weapon03Info->Init("asset/texture/weapon03Info.png");

	m_Weapon00Sharpp->Init(m_WeaponDataLoad->GetWeaponDataBaseIndex(0)->GetWeaponSharpnessTextuer());
	m_Weapon01Sharpp->Init(m_WeaponDataLoad->GetWeaponDataBaseIndex(1)->GetWeaponSharpnessTextuer());
	m_Weapon02Sharpp->Init(m_WeaponDataLoad->GetWeaponDataBaseIndex(2)->GetWeaponSharpnessTextuer());
	m_Weapon03Sharpp->Init(m_WeaponDataLoad->GetWeaponDataBaseIndex(3)->GetWeaponSharpnessTextuer());

	m_MoeneyNum->Init();
	m_BeforeWeapon->Init();
	m_AfterWeapon->Init();
	m_AfterWeaponPrice->Init();

	//AudioLoad
	m_SelectSE = AddComponet<Audio>();
	m_SelectSE->Load("asset\\audio\\選択音.wav");
	m_SelectSE->Volume(0.4f);

	m_EnterSE = AddComponet<Audio>();
	m_EnterSE->Load("asset\\audio\\決定音.wav");
	m_EnterSE->Volume(0.4f);

	//やじるし
	m_PointerScale = D3DXVECTOR3(200.0f, 100.0f, 0.0f);

	//クエスト最終決定のやじるし
	m_LastSelectPointerPos = D3DXVECTOR3(175.0f, 355.0f, 0.0f);
	m_LastSelectPointerScale = D3DXVECTOR3(250.0f, 250.0f, 0.0f);

	//武器選択画面
	m_BlacksmithFirstSelectPos = D3DXVECTOR3(830.0f, -10.0f, 0.0f);
	m_BlacksmithFirstSelectScale = D3DXVECTOR3(500.0f, 300.0f, 0.0f);


	//武器選択画面01
	m_BlacksmithSecondSelect01Pos = D3DXVECTOR3(600.0f, 50.0f, 0.0f);
	m_BlacksmithSecondSelect01Scale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);

	//武器選択画面02
	m_BlacksmithSecondSelect02Pos = D3DXVECTOR3(-200.0f, 250.0f, 0.0f);
	m_BlacksmithSecondSelect02Scale = D3DXVECTOR3(900.0f, 400.0f, 0.0f);

	//武器選択画面03
	m_BlacksmithSecondSelect03Pos = D3DXVECTOR3(-200.0f, 20.0f, 0.0f);
	m_BlacksmithSecondSelect03Scale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);

	//武器選択画面04
	m_WeaponMaterial1Pos = D3DXVECTOR3(570.0f, 300.0f, 0.0f);
	m_WeaponMaterial1Scale = D3DXVECTOR3(950.0f, 500.0f, 0.0f);

	//武器選択画面やじるし
	m_BlacksmithSelectPointerPos = D3DXVECTOR3(700.0f, 125.0f, 0.0f);
	m_BlacksmithSelectPointerScale = D3DXVECTOR3(700.0f, 150.0f, 0.0f);

	//武器2の素材
	m_WeaponMaterial2Pos = D3DXVECTOR3(570.0f, 300.0f, 0.0f);
	m_WeaponMaterial2Scale = D3DXVECTOR3(950.0f, 500.0f, 0.0f);

	//武器3の素材
	m_WeaponMaterial3Pos = D3DXVECTOR3(570.0f, 300.0f, 0.0f);
	m_WeaponMaterial3Scale = D3DXVECTOR3(950.0f, 500.0f, 0.0f);

	//武器遷移やじるし
	m_BlacksmithPointerPos = D3DXVECTOR3(827.0f, 257.0f, 0.0f);
	m_BlacksmithPointerScale = D3DXVECTOR3(400.0f, 200.0f, 0.0f);

	//武器最後情報
	m_BlacksmithLastInfoPos = D3DXVECTOR3(-198.0f, 42.0f, 0.0f);
	m_BlacksmithLastInfoScale = D3DXVECTOR3(800.0f, 450.0f, 0.0f);


	//武器0の情報
	m_Weapon00InfoPos = D3DXVECTOR3(594.0f, -102.0f, 0.0f);
	m_Weapon00InfoScale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);

	//武器0の切れ味
	m_Weapon00SharpnessTextuerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Weapon00SharpnessTextuerScale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	//武器1の情報
	m_Weapon01InfoPos = D3DXVECTOR3(594.0f, 185.0f, 0.0f);
	m_Weapon01InfoScale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);

	//武器1の切れ味
	m_Weapon01SharpnessTextuerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Weapon01SharpnessTextuerScale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//武器2の情報
	m_Weapon02InfoPos = D3DXVECTOR3(594.0f, 185.0f, 0.0f);
	m_Weapon02InfoScale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);

	//武器3の情報
	m_Weapon03InfoPos = D3DXVECTOR3(594.0f, 185.0f, 0.0f);
	m_Weapon03InfoScale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);

	//武器0の切れ味ゲージ
	m_Weapon00SharppPos = D3DXVECTOR3(854.0f, 81.0f, 0.0f);
	m_Weapon00SharppScale = D3DXVECTOR3(400.0f, 280.0f, 0.0f);

	//武器1の切れ味ゲージ
	m_Weapon01SharppPos = D3DXVECTOR3(854.0f, 81.0f, 0.0f);
	m_Weapon01SharppScale = D3DXVECTOR3(400.0f, 280.0f, 0.0f);

	//武器2の切れ味ゲージ
	m_Weapon02SharppPos = D3DXVECTOR3(854.0f, 81.0f, 0.0f);
	m_Weapon02SharppScale = D3DXVECTOR3(400.0f, 280.0f, 0.0f);

	//武器3の切れ味ゲージ
	m_Weapon03SharppPos = D3DXVECTOR3(854.0f, 81.0f, 0.0f);
	m_Weapon03SharppScale = D3DXVECTOR3(400.0f, 280.0f, 0.0f);

	//武器屋での残金表示
	m_WeaponStorMoneyPos = D3DXVECTOR3(1212.0f, 37.0f, 0.0f);
	m_WeaponStorMoneyScale = D3DXVECTOR3(40.0f, 30.0f, 0.0f);


}

void WeaponStoreUi::Uninit()
{
	m_Pointer->Uninit();
	m_LastSelectPointer->Uninit();
	m_BlacksmithFirstSelect->Uninit();
	m_BlacksmithSecondSelect01->Uninit();
	m_BlacksmithSecondSelect02->Uninit();
	m_BlacksmithSecondSelect03->Uninit();
	m_BlacksmithSelectPointer->Uninit();
	m_WeaponMaterial1->Uninit();
	m_WeaponMaterial2->Uninit();
	m_WeaponMaterial3->Uninit();
	m_BlacksmithPointer->Uninit();
	m_BlacksmithLastInfo->Uninit();
	m_Weapon00Info->Uninit();
	m_Weapon00SharpnessTextuer->Uninit();
	m_Weapon01Info->Uninit();
	m_Weapon01SharpnessTextuer->Uninit();
	m_Weapon02Info->Uninit();
	m_Weapon03Info->Uninit();

}

void WeaponStoreUi::Update()
{
	//ImGui::Checkbox("flg", &m_WeaponChangeFlg);

	if (m_PlayerAction->GetBlacksmithFlg())
	{
		//鍛冶場画面
		m_PointerPos = D3DXVECTOR3(800, 100.0f, 0.0f);

		if (Input::GetKeyTrigger('F') && m_WeaponChangeFlg == false && m_WeaponMaterialFlg1 == false && m_WeaponMaterialFlg2 == false && m_WeaponMaterialFlg3 == false)
		{
			m_BlacksmithSelectPointerPos = D3DXVECTOR3(700.0f, 125.0f, 0.0f);
			m_BlacksmithSelectPointerScale = D3DXVECTOR3(700.0f, 150.0f, 0.0f);
			m_BlecksmithSelect1 = true;
			m_EnterSE->Play();

		}
		else if (Input::GetKeyTrigger('R') && m_BlecksmithSelect1 == true && m_WeaponChangeFlg == false)
		{
			m_WeaponMaterialFlg1 = false;
			m_WeaponMaterialFlg2 = false;
			m_WeaponMaterialFlg3 = false;
			m_BlecksmithSelect1 = false;
			m_BlecksmithSelect2 = false;
			m_EnterSE->Play();
		}


		if (m_BlecksmithSelect1)
		{
			m_BlacksmithFirstSelectPos.x -= 6.0f;
			if (m_BlacksmithFirstSelectPos.x <= 740.0f)
				m_BlacksmithFirstSelectPos.x = 740.0f;

			m_BlacksmithFirstSelectPos.y -= 6.0f;
			if (m_BlacksmithFirstSelectPos.y <= -100.0f)
				m_BlacksmithFirstSelectPos.y = -100.0f;

			if (m_BlacksmithFirstSelectPos.x == 740.0f && m_BlacksmithFirstSelectPos.y == -100)
				m_BlecksmithSelect2 = true;

		}
		else if (m_BlecksmithSelect1 == false && m_BlecksmithSelect3 == false)
		{
			m_BlacksmithFirstSelectPos.x += 7.0f;
			if (m_BlacksmithFirstSelectPos.x >= 830.0f)
				m_BlacksmithFirstSelectPos.x = 830.0f;

			m_BlacksmithFirstSelectPos.y += 7.0f;
			if (m_BlacksmithFirstSelectPos.y >= -10.0f)
				m_BlacksmithFirstSelectPos.y = -10.0f;
		}


		if (m_BlecksmithSelect2)
		{
			if (Input::GetKeyTrigger(VK_DOWN))
			{
				m_BlacksmithSelectPointerPos.y += 30.0f;
				m_SelectSE->Play();
			}

			if (Input::GetKeyTrigger(VK_UP))
			{
				m_BlacksmithSelectPointerPos.y -= 30.0f;
				m_SelectSE->Play();
			}

			if (m_BlacksmithSelectPointerPos.y >= 185.0f)
				m_BlacksmithSelectPointerPos.y = 185.0f;

			if (m_BlacksmithSelectPointerPos.y <= 125.0f)
				m_BlacksmithSelectPointerPos.y = 125.0f;

			//武器1の素材を表示
			if (m_BlacksmithSelectPointerPos.y == 125.0f)
			{
				m_WeaponMaterialFlg1 = true;

				if (Input::GetKeyTrigger('F') && m_WeaponMaterialFlg1 == true)
				{
					m_NextWeapon01Flg = true;
					m_WeaponMaterialFlg1 = false;
					m_EnterSE->Play();
				}
			}
			else
			{
				m_NextWeapon01Flg = false;
				m_WeaponMaterialFlg1 = false;
			}

			//武器2の素材を表示
			if (m_BlacksmithSelectPointerPos.y == 155.0f)
			{
				m_WeaponMaterialFlg2 = true;
				if (Input::GetKeyTrigger('F') && m_WeaponMaterialFlg2 == true)
				{
					m_NextWeapon02Flg = true;
					m_WeaponMaterialFlg2 = false;
					m_EnterSE->Play();

				}
			}
			else
			{
				m_NextWeapon02Flg = false;
				m_WeaponMaterialFlg2 = false;
			}

			//武器3の素材を表示
			if (m_BlacksmithSelectPointerPos.y == 185.0f)
			{
				m_WeaponMaterialFlg3 = true;
				if (Input::GetKeyTrigger('F') && m_WeaponMaterialFlg3 == true)
				{
					m_NextWeapon03Flg = true;
					m_WeaponMaterialFlg3 = false;
					m_EnterSE->Play();

				}
			}
			else
			{
				m_NextWeapon03Flg = false;
				m_WeaponMaterialFlg3 = false;
			}


			if (Input::GetKeyTrigger('F') && m_BlecksmithSelect2 == true)
			{
				//武器変更の最終やじるしの位置指定
				m_LastSelectPointerPos = D3DXVECTOR3(153.0f, 120.0f, 0.0f);
				m_LastSelectPointerScale = D3DXVECTOR3(150.0f, 200.0f, 0.0f);

				//元の画面を消す
				m_BlecksmithSelect1 = false;
				m_BlecksmithSelect2 = false;

				//変更武器の情報を表示
				m_BlecksmithSelect3 = true;

				m_EnterSE->Play();

			}

		}
		else if (m_BlecksmithSelect3)
		{
			m_WeaponChangeFlg = true;

			if (Input::GetKeyTrigger(VK_RIGHT) && m_BlecksmithSelect3)
			{
				m_LastSelectPointerPos.x += 88.0f;
				m_SelectSE->Play();
			}
			else if (Input::GetKeyTrigger(VK_LEFT) && m_BlecksmithSelect3)
			{
				m_LastSelectPointerPos.x -= 88.0f;
				m_SelectSE->Play();
			}

			if (m_LastSelectPointerPos.x <= 153.0f)
				m_LastSelectPointerPos.x = 153.0f;
			if (m_LastSelectPointerPos.x >= 241.0f)
				m_LastSelectPointerPos.x = 241.0f;

		}

		if (m_WeaponChangeFlg && Money::GetMoney() >= 100)
		{
			//最終画面やじるしの位置がはいだった場合Fを押したら武器を換装する所持金が0の場合は購入できない
			//武器1
			if (Input::GetKeyTrigger('F') && m_NextWeapon01Flg == true && m_LastSelectPointerPos.x == 153.0f)
			{
				m_Weapon->SetWeapon(1);
				m_NextWeapon01Flg = false;
				Money::SetMinusMoney(100);
				m_EnterSE->Play();
			}

			//武器2
			if (Input::GetKeyTrigger('F') && m_NextWeapon02Flg == true && m_LastSelectPointerPos.x == 153.0f)
			{
				m_Weapon->SetWeapon(2);
				m_NextWeapon02Flg = false;
				Money::SetMinusMoney(100);
				m_EnterSE->Play();
			}

			//武器3
			if (Input::GetKeyTrigger('F') && m_NextWeapon03Flg == true && m_LastSelectPointerPos.x == 153.0f)
			{
				m_Weapon->SetWeapon(3);
				m_NextWeapon03Flg = false;
				Money::SetMinusMoney(100);
				m_EnterSE->Play();
			}
			//最終画面でどちらでFをおしても戻るようにする処理
			if (Input::GetKeyTrigger('F') && m_BlecksmithSelect3)
			{
				m_NextWeapon01Flg = false;
				m_NextWeapon02Flg = false;
				m_NextWeapon03Flg = false;

				m_BlecksmithSelect3 = false;
				m_WeaponChangeFlg = false;
				m_BlecksmithSelect1 = true;
				m_BlecksmithSelect2 = true;
				m_EnterSE->Play();
			}
		}

		//最終画面でどちらでFをおしても戻るようにする処理
		if (Input::GetKeyTrigger('F') && m_BlecksmithSelect3 && m_LastSelectPointerPos.x != 153.0f)
		{
			m_NextWeapon01Flg = false;
			m_NextWeapon02Flg = false;
			m_NextWeapon03Flg = false;

			m_BlecksmithSelect3 = false;
			m_WeaponChangeFlg = false;
			m_BlecksmithSelect1 = true;
			m_BlecksmithSelect2 = true;
			m_EnterSE->Play();
		}

	}

}

void WeaponStoreUi::Draw()
{

	//鍛冶場のUI
	if (m_PlayerAction->GetBlacksmithFlg())
	{
		if (m_BlecksmithSelect1 == false && m_BlecksmithSelect3 == false)
			m_Pointer->Draw(m_PointerPos, m_PointerScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

		m_BlacksmithFirstSelect->Draw(m_BlacksmithFirstSelectPos, m_BlacksmithFirstSelectScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.5f);
	}


	if (m_BlecksmithSelect2)
	{
		m_BlacksmithSecondSelect01->Draw(m_BlacksmithSecondSelect01Pos, m_BlacksmithSecondSelect01Scale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.8f);
		m_BlacksmithSecondSelect02->Draw(m_BlacksmithSecondSelect02Pos, m_BlacksmithSecondSelect02Scale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.8f);
		m_BlacksmithSecondSelect03->Draw(m_BlacksmithSecondSelect03Pos, m_BlacksmithSecondSelect03Scale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.8f);
		m_BlacksmithSelectPointer->Draw(m_BlacksmithSelectPointerPos, m_BlacksmithSelectPointerScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.3f);

		//残金
		m_MoeneyNum->Draw();
		m_MoeneyNum->SetCount(Money::GetMoney());
		m_MoeneyNum->SetPosAndScale(m_WeaponStorMoneyPos.x, m_WeaponStorMoneyPos.y, m_WeaponStorMoneyScale.x, m_WeaponStorMoneyScale.y);

	}

	if (m_WeaponMaterialFlg1)
		m_WeaponMaterial1->Draw(m_WeaponMaterial1Pos, m_WeaponMaterial1Scale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.8f);

	if (m_WeaponMaterialFlg2)
		m_WeaponMaterial2->Draw(m_WeaponMaterial2Pos, m_WeaponMaterial2Scale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.8f);

	if (m_WeaponMaterialFlg3)
		m_WeaponMaterial3->Draw(m_WeaponMaterial3Pos, m_WeaponMaterial3Scale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.8f);


	//もとから持っている装備がweapon0の場合
	if (m_BlecksmithSelect3 && m_Weapon->GetWeaponData()->GetWeaponModelName() == WEAPON00)
	{

		m_Weapon00InfoPos.y = -33.0f;
		m_Weapon00Info->Draw(m_Weapon00InfoPos, m_Weapon00InfoScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.8f);

		m_Weapon00SharppPos.y = 81.0f;
		m_Weapon00Sharpp->Draw(m_Weapon00SharppPos, m_Weapon00SharppScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

		m_BeforeWeapon->Draw();
		m_BeforeWeapon->SetCount(WeaponDataLoad::GetWeaponDataBaseIndex(0)->GetWeaponAttack());
		m_BeforeWeapon->SetPosAndScale(948.0f, 183.0f, 30.0f, 30.0f);

	}

	//もとから持っている装備がweapon1の場合
	if (m_BlecksmithSelect3 && m_Weapon->GetWeaponData()->GetWeaponModelName() == WEAPON01)
	{
		m_Weapon01InfoPos.y = -33.0f;
		m_Weapon01Info->Draw(m_Weapon01InfoPos, m_Weapon01InfoScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.8f);

		m_Weapon01SharppPos.y = 81.0f;
		m_Weapon01Sharpp->Draw(m_Weapon01SharppPos, m_Weapon01SharppScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

		m_BeforeWeapon->Draw();
		m_BeforeWeapon->SetCount(WeaponDataLoad::GetWeaponDataBaseIndex(1)->GetWeaponAttack());
		m_BeforeWeapon->SetPosAndScale(948.0f, 183.0f, 30.0f, 30.0f);


	}

	//もとから持っている装備がweapon2の場合
	if (m_BlecksmithSelect3 && m_Weapon->GetWeaponData()->GetWeaponModelName() == WEAPON02)
	{

		m_Weapon02InfoPos.y = -33.0f;
		m_Weapon02Info->Draw(m_Weapon02InfoPos, m_Weapon02InfoScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.8f);

		m_Weapon02SharppPos.y = 81.0f;
		m_Weapon02Sharpp->Draw(m_Weapon02SharppPos, m_Weapon02SharppScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

		m_BeforeWeapon->Draw();
		m_BeforeWeapon->SetCount(WeaponDataLoad::GetWeaponDataBaseIndex(2)->GetWeaponAttack());
		m_BeforeWeapon->SetPosAndScale(948.0f, 183.0f, 30.0f, 30.0f);


	}

	//もとから持っている装備がweapon3の場合
	if (m_BlecksmithSelect3 && m_Weapon->GetWeaponData()->GetWeaponModelName() == WEAPON03)
	{

		m_Weapon03InfoPos.y = -33.0f;
		m_Weapon03Info->Draw(m_Weapon03InfoPos, m_Weapon03InfoScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.8f);

		m_Weapon03SharppPos.y = 81.0f;
		m_Weapon03Sharpp->Draw(m_Weapon03SharppPos, m_Weapon03SharppScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

		m_BeforeWeapon->Draw();
		m_BeforeWeapon->SetCount(WeaponDataLoad::GetWeaponDataBaseIndex(3)->GetWeaponAttack());
		m_BeforeWeapon->SetPosAndScale(948.0f, 183.0f, 30.0f, 30.0f);

	}

	if (m_BlecksmithSelect3)
	{
		m_BlacksmithPointer->Draw(m_BlacksmithPointerPos, m_BlacksmithPointerScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);
		m_BlacksmithLastInfo->Draw(m_BlacksmithLastInfoPos, m_BlacksmithLastInfoScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);
		m_LastSelectPointer->Draw(m_LastSelectPointerPos, m_LastSelectPointerScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

	}

	//換装後の武器情報01
	if (m_NextWeapon01Flg && m_NextWeapon02Flg == false)
	{
		m_Weapon01InfoPos.y = 243.0f;
		m_Weapon01Info->Draw(m_Weapon01InfoPos, m_Weapon01InfoScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.8f);

		m_Weapon01SharppPos.y = 360.0f;
		m_Weapon01Sharpp->Draw(m_Weapon01SharppPos, m_Weapon01SharppScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

		m_AfterWeapon->Draw();
		m_AfterWeapon->SetCount(WeaponDataLoad::GetWeaponDataBaseIndex(1)->GetWeaponAttack());
		m_AfterWeapon->SetPosAndScale(948.0f, 460.0f, 30.0f, 30.0f);

		m_AfterWeaponPrice->Draw();
		m_AfterWeaponPrice->SetCount(WeaponDataLoad::GetWeaponDataBaseIndex(1)->GetWeaponPrice());
		m_AfterWeaponPrice->SetPosAndScale(251.0f, 106.0f, 30.0f, 30.0f);


	}

	//換装後の武器情報02
	if (m_NextWeapon02Flg)
	{
		m_Weapon02InfoPos.y = 243.0f;
		m_Weapon02Info->Draw(m_Weapon02InfoPos, m_Weapon02InfoScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.8f);

		m_Weapon02SharppPos.y = 360.0f;
		m_Weapon02Sharpp->Draw(m_Weapon02SharppPos, m_Weapon02SharppScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

		m_AfterWeapon->Draw();
		m_AfterWeapon->SetCount(WeaponDataLoad::GetWeaponDataBaseIndex(2)->GetWeaponAttack());
		m_AfterWeapon->SetPosAndScale(948.0f, 460.0f, 30.0f, 30.0f);

		m_AfterWeaponPrice->Draw();
		m_AfterWeaponPrice->SetCount(WeaponDataLoad::GetWeaponDataBaseIndex(2)->GetWeaponPrice());
		m_AfterWeaponPrice->SetPosAndScale(251.0f, 106.0f, 30.0f, 30.0f);

	}

	//換装後の武器情報03
	if (m_NextWeapon03Flg)
	{
		m_Weapon03InfoPos.y = 243.0f;
		m_Weapon03Info->Draw(m_Weapon03InfoPos, m_Weapon03InfoScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.8f);

		m_Weapon03SharppPos.y = 360.0f;
		m_Weapon03Sharpp->Draw(m_Weapon03SharppPos, m_Weapon03SharppScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

		m_AfterWeapon->Draw();
		m_AfterWeapon->SetCount(WeaponDataLoad::GetWeaponDataBaseIndex(3)->GetWeaponAttack());
		m_AfterWeapon->SetPosAndScale(948.0f, 460.0f, 30.0f, 30.0f);

		m_AfterWeaponPrice->Draw();
		m_AfterWeaponPrice->SetCount(WeaponDataLoad::GetWeaponDataBaseIndex(3)->GetWeaponPrice());
		m_AfterWeaponPrice->SetPosAndScale(251.0f, 106.0f, 30.0f, 30.0f);

	}

}
