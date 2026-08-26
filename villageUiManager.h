#pragma once

#include "gameObject.h"
#include "villageUi.h"

class VillageUiManager : public GameObject
{
private:

	static int m_ItemCount;
	int m_ItemAllCount{};
	int m_MoneyCount{};

	class ItemDataLoad* m_ItemDataLoad{};
	class WeaponDataLoad* m_WeaponDataLoad{};
	class Fade* m_Fade{};

	class Audio* m_SelectSE{};
	class Audio* m_EnterSE{};


	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 m_scale;



	//村のuiを管理する配列
	VillageUi* m_VillageArry[100]{};

	//鍛冶場ui

	//雑貨ui

	//クエスト受付ui


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();


};