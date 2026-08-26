#include "main.h"
#include "scene.h"
#include "manager.h"
#include "villagePlayerAction.h"
#include "villageUi.h"
#include "receptionDesk.h"
#include "weaponStoreDesk.h"
#include "generalStoreDesk.h"
#include "villageInfoDesk.h"
#include "instructor.h"
#include "input.h"
#include "player.h"
#include "weaponStoreUi.h"
#include "generalStoreUi.h"
#include "questDeskUi.h"

void VillagePlayerAction::VillageActions(void)
{
	m_Scene = Manager::GetScene();

	WeaponStoreUi* WeaponUi = m_Scene->GetGameObject<WeaponStoreUi>();
	GeneralStoreUi* GeneralUi = m_Scene->GetGameObject<GeneralStoreUi>();
	QuestDeskUi* QuestUi = m_Scene->GetGameObject<QuestDeskUi>();


	//受付嬢との範囲指定
	RECEPTIONDESK* reception = m_Scene->GetGameObject<RECEPTIONDESK>();
	D3DXVECTOR3 questposition = reception->GetPosition();
	//クエストの受注
	if (GetLength(questposition) <= 4.0f)
	{
		m_ReceptionFlg = true;
		if (Input::GetKeyTrigger('E'))
		{
			m_TransactionFlg = true;
			m_QuestFlg = true;
		}
		else if (Input::GetKeyTrigger('R') && QuestUi->GetLevel01Flg() == false
			&& QuestUi->GetLevel02Flg() == false
			&& QuestUi->GetLevel03Flg() == false
			&& QuestUi->GetLastSelectFlg() == false)
		{
			m_TransactionFlg = false;
			m_QuestFlg = false;
		}

	}
	else
		m_ReceptionFlg = false;


	//鍛冶場の範囲指定
	WeaponStoreDesk* weaponsotre = m_Scene->GetGameObject<WeaponStoreDesk>();
	D3DXVECTOR3 weaponposition = weaponsotre->GetPosition();
	if (GetLength(weaponposition) <= 4.0f)
	{
		m_WeaponDeskFlg = true;

		if (Input::GetKeyTrigger('E'))
		{
			m_BlacksmithFlg = true;
			m_TransactionFlg = true;
		}
		else if (Input::GetKeyTrigger('R') && WeaponUi->GetBlackSmithFlg() == false && WeaponUi->GetWeaponChangeFlg() == false)
		{
			m_TransactionFlg = false;
			m_BlacksmithFlg = false;
		}
	}
	else
		m_WeaponDeskFlg = false;


	//雑貨屋の範囲指定
	GeneralStoreDesk* generalsotre = m_Scene->GetGameObject<GeneralStoreDesk>();
	D3DXVECTOR3 generalposition = generalsotre->GetPosition();
	if (GetLength(generalposition) <= 4.0f)
	{
		m_GeneralDeskFlg = true;

		if (Input::GetKeyTrigger('E'))
		{
			m_TransactionFlg = true;
			m_GeneralStoreFlg = true;
		}
		else if (Input::GetKeyTrigger('R') && GeneralUi->GetGeneralStore() == false)
		{
			m_TransactionFlg = false;
			m_GeneralStoreFlg = false;
		}
	}
	else
		m_GeneralDeskFlg = false;


	//村の案内人範囲指定
	VillageInfoDesk* villageinfo = m_Scene->GetGameObject<VillageInfoDesk>();
	D3DXVECTOR3 villageinfoposition = villageinfo->GetPosition();
	if (GetLength(villageinfoposition) <= 4.0f)
	{
		//頭の上の印
		m_VillageInfoPointFlg = true;

		if (Input::GetKeyTrigger('E'))
		{
			//話している途中に動かないようにするフラグ
			m_TransactionFlg = true;

			//UIを表示するためのフラグ
			m_VillageInfoFlg = true;
		}
		else if (Input::GetKeyTrigger('R'))
		{
			m_TransactionFlg = false;

			m_VillageInfoFlg = false;
		}
	}
	else
		m_VillageInfoPointFlg = false;



	//教官との範囲指定
	Instructor* instructor = m_Scene->GetGameObject<Instructor>();
	D3DXVECTOR3 instructorPos = instructor->GetPosition();
	if (GetLength(instructorPos) <= 4.0f)
	{
		m_InstructorFlg = true;
		if (Input::GetKeyTrigger('E'))
		{
			m_TutorialFlg = true;
		}
	}
	else
		m_InstructorFlg = false;

}

float VillagePlayerAction::GetLength(D3DXVECTOR3 targetpos)
{
	D3DXVECTOR3 position = targetpos;
	Player* player = m_Scene->GetGameObject<Player>();

	D3DXVECTOR3 direction = player->GetPosition() - position;
	direction.y = 0.0f;
	float length = D3DXVec3Length(&direction);

	return length;
}
