#pragma once
#pragma once

#include "gameObject.h"

class VillagePlayerAction : public GameObject
{

private:

	class Scene* m_Scene{};

	bool m_QuestFlg{};
	bool m_BlacksmithFlg{};
	bool m_GeneralStoreFlg{};
	bool m_ReceptionFlg{};
	bool m_WeaponDeskFlg{};
	bool m_GeneralDeskFlg{};
	bool m_TransactionFlg{};
	bool m_VillageInfoFlg{};
	bool m_VillageInfoPointFlg{};
	bool m_InstructorFlg{};
	bool m_TutorialFlg{};

public:

	//プレイヤーの村でのメインアクション関数
	void VillageActions(void);

	//プレイヤーとの距離測定関数
	float GetLength(D3DXVECTOR3 targetpos);

	bool GetQuestFlg(void) { return m_QuestFlg; }
	void SetQuestFlg(bool flg) { m_QuestFlg = flg; }

	bool GetBlacksmithFlg(void) { return m_BlacksmithFlg; }
	void SetBlacksmithFlg(bool flg) { m_BlacksmithFlg = flg; }

	bool GetGeneralStore(void) { return m_GeneralStoreFlg; }
	void SetGeneralStore(bool flg) { m_GeneralStoreFlg = flg; }

	bool GetReceptionFlg(void) { return m_ReceptionFlg; }
	bool GetWeaponDeskFlg(void) { return m_WeaponDeskFlg; }
	bool GetGeneralDeskFlg(void) { return m_GeneralDeskFlg; }

	bool GetSVillgeStopFlg(void) { return m_TransactionFlg; }
	void SetSVillgeStopFlg(bool flg) { m_TransactionFlg = flg; }

	bool GetVillageInfoFlg(void) { return m_VillageInfoFlg; }

	bool GetVillageInfoPointFlg(void) { return m_VillageInfoPointFlg; }

	bool GetInstructorFlg(void) { return m_InstructorFlg; }
	bool SetInstructorFlg(bool flg) { m_InstructorFlg = flg; }

	bool GetTutorialrFlg(void) { return m_TutorialFlg; }

};