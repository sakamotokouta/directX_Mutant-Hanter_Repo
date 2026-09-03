#include "generalStoreUi.h"
#include "scene.h"
#include "manager.h"
#include "sprit2D.h"
#include "villagePlayerAction.h"
#include "input.h"
#include "audio.h"
#include "money.h"
#include "itemDataLoad.h"
#include "score.h"


void GeneralStoreUi::Init()
{
	Scene* scene = Manager::GetScene();

	m_Pointer = new Sprit2D;
	m_GeneralStoreFirstInfo = new Sprit2D;
	m_GeneralStoreSelectInfo0 = new Sprit2D;
	m_GeneralStoreSelectInfo1 = new Sprit2D;
	m_GeneralStoreSelectInfo2 = new Sprit2D;
	m_GeneralStoreSelectInfo3 = new Sprit2D;
	m_GeneralStoreLastInfo = new Sprit2D;
	m_SelectPointer = new Sprit2D;
	m_LastSelectPointer = new Sprit2D;

	m_PlayerAction = scene->GetGameObject<VillagePlayerAction>();

	m_ItemNum = new Score;
	m_MoeneyNum = new Score;

	m_Pointer->Init("asset/texture/pointer.png");
	m_GeneralStoreFirstInfo->Init("asset/texture/sundriesFirstInfo.png");
	m_GeneralStoreSelectInfo0->Init("asset/texture/generalstoreInfo.png");
	m_GeneralStoreSelectInfo1->Init("asset/texture/generalsotreSelectInfo01.png");
	m_GeneralStoreSelectInfo2->Init("asset/texture/generalsotreSelectInfo02.png");
	m_GeneralStoreSelectInfo3->Init("asset/texture/generalsotreSelectInfo03.png");
	m_GeneralStoreLastInfo->Init("asset/texture/generalsotreLastInfo.png");
	m_SelectPointer->Init("asset/texture/weaponselectpointer.png");
	m_LastSelectPointer->Init("asset/texture/LastSelectPointer.png");

	m_ItemNum->Init();
	m_MoeneyNum->Init();


	//やじるし
	m_PointerScale = D3DXVECTOR3(200.0f, 100.0f, 0.0f);

	//雑貨屋の最初の画面
	m_GeneralStoreFirstInfoPos = D3DXVECTOR3(830.0f, -10.0f, 0.0f);
	m_GeneralStoreFirstInfoScale = D3DXVECTOR3(500.0f, 300.0f, 0.0f);


	//雑貨屋のアイテム選択画面1
	m_GeneralStoreSelectInfoPos0 = D3DXVECTOR3(-198.0f, -33.0f, 0.0f);
	m_GeneralStoreSelectInfoScale0 = D3DXVECTOR3(900.0f, 500.0f, 0.0f);

	//雑貨屋のアイテム選択画面2
	m_GeneralStoreSelectInfoPos1 = D3DXVECTOR3(588.0f, -33.0f, 0.0f);
	m_GeneralStoreSelectInfoScale1 = D3DXVECTOR3(900.0f, 500.0f, 0.0f);

	//雑貨屋のアイテム選択画面3
	m_GeneralStoreSelectInfoPos2 = D3DXVECTOR3(588.0f, 205.0f, 0.0f);
	m_GeneralStoreSelectInfoScale2 = D3DXVECTOR3(900.0f, 500.0f, 0.0f);

	//雑貨屋のアイテム選択画面4
	m_GeneralStoreSelectInfoPos3 = D3DXVECTOR3(-198.0f, -33.0f, 0.0f);
	m_GeneralStoreSelectInfoScale3 = D3DXVECTOR3(900.0f, 500.0f, 0.0f);

	//雑貨屋のアイテム最後の選択画面
	m_GeneralStoreLastInfoPos = D3DXVECTOR3(-198.0f, -33.0f, 0.0f);
	m_GeneralStoreLastInfoScale = D3DXVECTOR3(900.0f, 500.0f, 0.0f);

	//アイテム選択の目印
	m_SelectPointerPos = D3DXVECTOR3(700.0f, 125.0f, 0.0f);
	m_SelectPointerScale = D3DXVECTOR3(700.0f, 150.0f, 0.0f);

	//最終決定のやじるし
	m_LastSelectPointerPos = D3DXVECTOR3(175.0f, 355.0f, 0.0f);
	m_LastSelectPointerScale = D3DXVECTOR3(250.0f, 250.0f, 0.0f);

	//雑貨屋での残金表示
	m_GeneralStoreMoneyPos = D3DXVECTOR3(1212.0f, 37.0f, 0.0f);
	m_GeneralStoreMoneyScale = D3DXVECTOR3(40.0f, 30.0f, 0.0f);

	//AudioLoad
	m_SelectSE = AddComponet<Audio>();
	m_SelectSE->Load("asset\\audio\\chice.wav");
	m_SelectSE->Volume(0.4f);

	m_EnterSE = AddComponet<Audio>();
	m_EnterSE->Load("asset\\audio\\direction.wav");
	m_EnterSE->Volume(0.4f);

	//アイテムのカウントを1に初期化
	m_ItemCount = 1;

}

void GeneralStoreUi::Uninit()
{
	m_Pointer->Uninit();
	m_GeneralStoreSelectInfo0->Uninit();
	m_GeneralStoreSelectInfo1->Uninit();
	m_GeneralStoreSelectInfo2->Uninit();
	m_GeneralStoreSelectInfo3->Uninit();

}

void GeneralStoreUi::Update()
{

	if (m_PlayerAction->GetGeneralStore())
	{
		m_PointerPos = D3DXVECTOR3(800, 100.0f, 0.0f);

		if (m_PlayerAction->GetGeneralStore() && Input::GetKeyTrigger('F'))
		{
			//アイテムを選択した時の目印
			m_SelectPointerPos = D3DXVECTOR3(688.0f, 68.0f, 0.0f);
			m_SelectPointerScale = D3DXVECTOR3(700.0f, 200.0f, 0.0f);
			m_GeneralStoreFlg1 = true;
			m_EnterSE->Play();
		}
		else if (Input::GetKeyTrigger('R') && m_ItemNumFlg == false && m_ItemLastInfo == false)
		{
			m_GeneralStoreFlg1 = false;
			m_GeneralStoreFlg2 = false;
			m_EnterSE->Play();
		}

		if (m_GeneralStoreFlg1)
		{
			m_GeneralStoreFirstInfoPos.x -= 6.0f;
			if (m_GeneralStoreFirstInfoPos.x <= 700.0f)
				m_GeneralStoreFirstInfoPos.x = 700.0f;

			m_GeneralStoreFirstInfoPos.y -= 6.0f;
			if (m_GeneralStoreFirstInfoPos.y <= -100.0f)
				m_GeneralStoreFirstInfoPos.y = -100.0f;

			if (m_GeneralStoreFirstInfoPos.x == 700.0f && m_GeneralStoreFirstInfoPos.y == -100)
				m_GeneralStoreFlg2 = true;
		}
		else if (m_GeneralStoreFlg1 == false)
		{
			m_GeneralStoreFirstInfoPos.x += 7.0f;
			if (m_GeneralStoreFirstInfoPos.x >= 830.0f)
				m_GeneralStoreFirstInfoPos.x = 830.0f;

			m_GeneralStoreFirstInfoPos.y += 7.0f;
			if (m_GeneralStoreFirstInfoPos.y >= -10.0f)
				m_GeneralStoreFirstInfoPos.y = -10.0f;
		}

		if (m_GeneralStoreFlg2)
		{
			if (Input::GetKeyTrigger('F') && m_ItemNumFlg == false && m_ItemLastInfo == false && Money::GetMoney() >= 10)
			{
				m_ItemCount = 1;
				m_ItemNumFlg = true;
				m_EnterSE->Play();
			}
			else if (Input::GetKeyTrigger('F') && m_ItemNumFlg && m_ItemCount >= 1)
			{
				m_ItemNumFlg = false;
				m_ItemLastInfo = true;


				m_LastSelectPointerPos = D3DXVECTOR3(127.0f, 133.0f, 0.0f);
				m_LastSelectPointerScale = D3DXVECTOR3(240.0f, 200.0f, 0.0f);

				m_EnterSE->Play();


			}
			else if (Input::GetKeyTrigger('F') && m_ItemLastInfo)
			{
				if (m_LastSelectPointerPos.x <= 127.0f)
				{
					m_ItemCountFlg = true;
					m_ItemAllCount += m_ItemCount;
					Money::SetMinusMoney(m_ItemCount * 10);
					ItemDataLoad::GetItemBaseIndex(0)->SetItemCount(m_ItemAllCount);
					m_EnterSE->Play();

				}
				m_ItemLastInfo = false;
				m_ItemNumFlg = false;
			}



			if (m_ItemNumFlg)
			{
				if (Input::GetKeyTrigger(VK_UP) && m_ItemNumFlg && (Money::GetMoney() / 10) > m_ItemCount)
				{
					m_ItemCount++;

					if (m_ItemCount >= 50)
						m_ItemCount = 50;
					m_SelectSE->Play();

				}

				if (Input::GetKeyTrigger(VK_DOWN) && m_ItemNumFlg)
				{
					m_ItemCount--;
					if (m_ItemCount <= 1)
						m_ItemCount = 1;

					m_SelectSE->Play();

				}

			}
			else if (m_ItemLastInfo)
			{

				if (Input::GetKeyTrigger(VK_RIGHT) && m_ItemLastInfo)
				{
					m_LastSelectPointerPos.x += 144.0f;
					m_SelectSE->Play();

				}

				if (m_LastSelectPointerPos.x >= 271.0f)
					m_LastSelectPointerPos.x = 271.0f;


				if (Input::GetKeyTrigger(VK_LEFT) && m_ItemLastInfo)
				{
					m_LastSelectPointerPos.x -= 144.0f;
					m_SelectSE->Play();

				}


				if (m_LastSelectPointerPos.x <= 127.0f)
					m_LastSelectPointerPos.x = 127.0f;
			}
		}

	}
}

void GeneralStoreUi::Draw()
{

	//雑貨屋のUI
	if (m_PlayerAction->GetGeneralStore())
	{
		if (m_GeneralStoreFlg1 == false)
			m_Pointer->Draw(m_PointerPos, m_PointerScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

		m_GeneralStoreFirstInfo->Draw(m_GeneralStoreFirstInfoPos, m_GeneralStoreFirstInfoScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.5f);
	}

	if (m_GeneralStoreFlg2)
	{
		//残金表示
		m_MoeneyNum->Draw();
		m_MoeneyNum->SetCount(Money::GetMoney());
		m_MoeneyNum->SetPosAndScale(m_GeneralStoreMoneyPos.x, m_GeneralStoreMoneyPos.y, m_GeneralStoreMoneyScale.x, m_GeneralStoreMoneyScale.y);

		if (m_ItemNumFlg)
		{
			m_GeneralStoreSelectInfo3->Draw(m_GeneralStoreSelectInfoPos3, m_GeneralStoreSelectInfoScale3, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.8f);

			m_ItemNum->Draw();
			m_ItemNum->SetCount(m_ItemCount);
			m_ItemNum->SetPosAndScale(320, 180, 30.0f, 30.0f);
		}
		else if (m_ItemLastInfo)
		{
			m_GeneralStoreLastInfo->Draw(m_GeneralStoreLastInfoPos, m_GeneralStoreLastInfoScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.8f);
			m_LastSelectPointer->Draw(m_LastSelectPointerPos, m_LastSelectPointerScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

			m_ItemNum->Draw();
			m_ItemNum->SetCount(ItemDataLoad::GetItemBaseIndex(0)->GetItemPrice() * m_ItemCount);
			m_ItemNum->SetPosAndScale(100.0f, 137.0f, 30.0f, 30.0f);

		}
		else
		{
			m_GeneralStoreSelectInfo0->Draw(m_GeneralStoreSelectInfoPos0, m_GeneralStoreSelectInfoScale0, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.8f);
		}



		m_GeneralStoreSelectInfo1->Draw(m_GeneralStoreSelectInfoPos1, m_GeneralStoreSelectInfoScale1, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.8f);
		m_GeneralStoreSelectInfo2->Draw(m_GeneralStoreSelectInfoPos2, m_GeneralStoreSelectInfoScale2, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.8f);
		m_SelectPointer->Draw(m_SelectPointerPos, m_SelectPointerScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.3f);
	}

}
