#pragma once

#include "gameObject.h"
#include "villageUi.h"

class GeneralStoreUi : public GameObject
{
private:

	int m_ItemCount{};
	int m_ItemAllCount{};
	int m_MoneyCount{};

	class Audio* m_SelectSE{};
	class Audio* m_EnterSE{};

	bool m_ItemCountFlg{};
	bool m_GeneralStoreFlg1{};
	bool m_GeneralStoreFlg2{};
	bool m_ItemNumFlg{};
	bool m_ItemLastInfo{};

	class VillagePlayerAction* m_PlayerAction{};

	class Sprit2D* m_Pointer;
	class Sprit2D* m_GeneralStoreFirstInfo;
	class Sprit2D* m_GeneralStoreSelectInfo0;
	class Sprit2D* m_GeneralStoreSelectInfo1;
	class Sprit2D* m_GeneralStoreSelectInfo2;
	class Sprit2D* m_GeneralStoreSelectInfo3;
	class Sprit2D* m_GeneralStoreLastInfo;
	class Sprit2D* m_SelectPointer;
	class Sprit2D* m_LastSelectPointer;

	class Score* m_ItemNum{};
	class Score* m_MoeneyNum{};


	D3DXVECTOR3 m_PointerPos;
	D3DXVECTOR3 m_PointerScale;

	D3DXVECTOR3 m_GeneralStoreFirstInfoPos;
	D3DXVECTOR3 m_GeneralStoreFirstInfoScale;

	D3DXVECTOR3 m_GeneralStoreSelectInfoPos0;
	D3DXVECTOR3 m_GeneralStoreSelectInfoScale0;

	D3DXVECTOR3 m_GeneralStoreSelectInfoPos1;
	D3DXVECTOR3 m_GeneralStoreSelectInfoScale1;

	D3DXVECTOR3 m_GeneralStoreSelectInfoPos2;
	D3DXVECTOR3 m_GeneralStoreSelectInfoScale2;

	D3DXVECTOR3 m_GeneralStoreSelectInfoPos3;
	D3DXVECTOR3 m_GeneralStoreSelectInfoScale3;

	D3DXVECTOR3 m_GeneralStoreLastInfoPos;
	D3DXVECTOR3 m_GeneralStoreLastInfoScale;

	D3DXVECTOR3 m_SelectPointerPos;
	D3DXVECTOR3 m_SelectPointerScale;

	D3DXVECTOR3 m_LastSelectPointerPos;
	D3DXVECTOR3 m_LastSelectPointerScale;

	D3DXVECTOR3 m_GeneralStoreMoneyPos;
	D3DXVECTOR3 m_GeneralStoreMoneyScale;


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetGeneralStore(void) { return m_GeneralStoreFlg1; }
	
};