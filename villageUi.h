#pragma once

#include "gameObject.h"

class VillageUi : public GameObject
{
private:

	int m_ItemAllCount{};
	int m_MoneyCount{};

	class Fade* m_Fade{};

	class Audio* m_SelectSE{};
	class Audio* m_EnterSE{};


	bool m_ItemNumFlg{};
	bool m_ItemLastInfo{};
	bool m_QuestGateLastFlg{};
	bool m_InfoFirstSelectFlg{};
	bool m_InfoSecondSelectFlg{};
	bool m_WeaponStoreInfoFlg{};
	bool m_GeneralStoreInfoFlg{};
	bool m_QuestBoardInfoFlg{};
	bool m_QuestGateInfoFlg{};
	bool m_InfoFinishFlg{};
	bool m_TitleLastInfoFlg{};
	bool m_TutorialInfoFlg{};
	bool m_ConfirmationFlg{};
	bool m_QuestGateLastPointFlg{};

	static bool m_QuestGate;
	static bool m_GameSceneFlg;

	class WeaponStoreUi* m_WeaponStoreUi{};

	class Score* m_ConfirmationScore{};
	class Score* m_MoeneyNum{};
	class Score* m_ItemNum{};


	class Sprit2D* m_Pointer;
	class Sprit2D* m_EnerOrRetern;
	class Sprit2D* m_LastSelect;
	class Sprit2D* m_LastSelectPointer;
	class Sprit2D* m_QuestGateLastInfo;
	class Sprit2D* m_VillageInfoSelect01;
	class Sprit2D* m_VillageInfoSelect02;
	class Sprit2D* m_WeaponStoreInfo;
	class Sprit2D* m_GeneralStoreInfo;
	class Sprit2D* m_QuestBoardInfo;
	class Sprit2D* m_QuestGateInfo;
	class Sprit2D* m_InfoFinish;
	class Sprit2D* m_TutorialInfo;
	class Sprit2D* m_TitleLastInfo;
	class Sprit2D* m_ItemPic;
	class Sprit2D* m_ChackPic;
	class Sprit2D* m_ChackRavel;
	class Sprit2D* m_ReturnRavel;



	D3DXVECTOR3 m_PointerPos;
	D3DXVECTOR3 m_PointerScale;

	D3DXVECTOR3 m_EnerOrReternPos;
	D3DXVECTOR3 m_EnerOrReternScale;

	D3DXVECTOR3 m_LastSelectPos;
	D3DXVECTOR3 m_LastSelectScale;

	D3DXVECTOR3 m_LastSelectPointerPos;
	D3DXVECTOR3 m_LastSelectPointerScale;

	D3DXVECTOR3 m_QuestGateLastInfoPos;
	D3DXVECTOR3 m_QuestGateLastInfoScale;

	D3DXVECTOR3 m_VillageInfoSelect01Pos;
	D3DXVECTOR3 m_VillageInfoSelect01Scale;

	D3DXVECTOR3 m_VillageInfoSelect02Pos;
	D3DXVECTOR3 m_VillageInfoSelect02Scale;

	D3DXVECTOR3 m_WeaponStoreInfoPos;
	D3DXVECTOR3 m_WeaponStoreInfoScale;

	D3DXVECTOR3 m_GeneralStoreInfoPos;
	D3DXVECTOR3 m_GeneralStoreInfoScale;

	D3DXVECTOR3 m_QuestBoardInfoPos;
	D3DXVECTOR3 m_QuestBoardInfoScale;

	D3DXVECTOR3 m_QuestGateInfoPos;
	D3DXVECTOR3 m_QuestGateInfoScale;

	D3DXVECTOR3 m_InfoFinishPos;
	D3DXVECTOR3 m_InfoFinishScale;

	D3DXVECTOR3 m_TitleLastInfoPos;
	D3DXVECTOR3 m_TitleLastInfoScale;

	D3DXVECTOR3 m_TutorialInfoPos;
	D3DXVECTOR3 m_TutorialInfoScale;

	D3DXVECTOR3 m_ItemPicPos;
	D3DXVECTOR3 m_ItemPicScale;

	D3DXVECTOR3 m_ConfirmationMoneyPos;
	D3DXVECTOR3 m_ConfirmationMoneyScale;

	D3DXVECTOR3 m_ItemNumPos;
	D3DXVECTOR3 m_ItemNumScale;

	D3DXVECTOR3 m_QuestLastPointPos;
	D3DXVECTOR3 m_QuestLastPointScale;

	D3DXVECTOR3 m_ChackPicPos;
	D3DXVECTOR3 m_ChackPicScale;

	D3DXVECTOR3 m_ChackRavelPos;
	D3DXVECTOR3 m_ChackRavelScale;

	D3DXVECTOR3 m_ReturnRavelPos;
	D3DXVECTOR3 m_ReturnRavelScale;


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	static bool GetNextGameFlg(void) { return m_QuestGate; }
	static void SetNextGameFlg(bool flg) { m_QuestGate = flg; }

	static bool GetGameSceneFlg(void) { return m_GameSceneFlg; }
	static void SetGameSceneFlg(bool flg) { m_GameSceneFlg = flg; }


	bool GetWeaponSotreInfoFlg(void) { return m_WeaponStoreInfoFlg; }
	bool GetGeneralSotreInfoFlg(void) { return m_GeneralStoreInfoFlg; }
	bool GetQuestBoardInfoFlg(void) { return m_QuestBoardInfoFlg; }
	bool GetQuestGateInfoFlg(void) { return m_QuestGateInfoFlg; }
	bool GetTutorialInfoFlg(void) { return m_TutorialInfoFlg; }

};