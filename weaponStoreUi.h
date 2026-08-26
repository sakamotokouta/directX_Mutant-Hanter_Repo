#pragma once

#include "gameObject.h"
#include "villageUi.h"

class WeaponStoreUi : public GameObject
{
private:

	class ItemDataLoad* m_ItemDataLoad{};
	class WeaponDataLoad* m_WeaponDataLoad{};
	class Fade* m_Fade{};

	class Audio* m_SelectSE{};
	class Audio* m_EnterSE{};


	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 m_scale;

	class VillagePlayerAction* m_PlayerAction{};
	class Weapon* m_Weapon{};

	class Score* m_MoeneyNum{};
	class Score* m_BeforeWeapon{};
	class Score* m_AfterWeapon{};
	class Score* m_AfterWeaponPrice{};

	class Sprit2D* m_Pointer;
	class Sprit2D* m_LastSelectPointer;
	class Sprit2D* m_BlacksmithFirstSelect;
	class Sprit2D* m_BlacksmithSecondSelect01;
	class Sprit2D* m_BlacksmithSecondSelect02;
	class Sprit2D* m_BlacksmithSecondSelect03;
	class Sprit2D* m_BlacksmithSelectPointer;
	class Sprit2D* m_WeaponMaterial1;
	class Sprit2D* m_WeaponMaterial2;
	class Sprit2D* m_WeaponMaterial3;
	class Sprit2D* m_BlacksmithPointer;
	class Sprit2D* m_BlacksmithLastInfo;
	class Sprit2D* m_Weapon00Info;
	class Sprit2D* m_Weapon00SharpnessTextuer;
	class Sprit2D* m_Weapon01Info;
	class Sprit2D* m_Weapon01SharpnessTextuer;
	class Sprit2D* m_Weapon02Info;
	class Sprit2D* m_Weapon03Info;
	class Sprit2D* m_Weapon00Sharpp;
	class Sprit2D* m_Weapon01Sharpp;
	class Sprit2D* m_Weapon02Sharpp;
	class Sprit2D* m_Weapon03Sharpp;


	bool m_BlecksmithSelect1{};
	bool m_BlecksmithSelect2{};
	bool m_BlecksmithSelect3{};
	bool m_WeaponMaterialFlg1{};
	bool m_WeaponMaterialFlg2{};
	bool m_WeaponMaterialFlg3{};
	bool m_WeaponChangeFlg{};
	bool m_NextWeapon01Flg{};
	bool m_NextWeapon02Flg{};
	bool m_NextWeapon03Flg{};
	bool m_WeaponStoreInfoFlg{};


	D3DXVECTOR3 m_PointerPos;
	D3DXVECTOR3 m_PointerScale;

	D3DXVECTOR3 m_LastSelectPointerPos;
	D3DXVECTOR3 m_LastSelectPointerScale;

	D3DXVECTOR3 m_BlacksmithFirstSelectPos;
	D3DXVECTOR3 m_BlacksmithFirstSelectScale;

	D3DXVECTOR3 m_BlacksmithSecondSelect01Pos;
	D3DXVECTOR3 m_BlacksmithSecondSelect01Scale;

	D3DXVECTOR3 m_BlacksmithSecondSelect02Pos;
	D3DXVECTOR3 m_BlacksmithSecondSelect02Scale;

	D3DXVECTOR3 m_BlacksmithSecondSelect03Pos;
	D3DXVECTOR3 m_BlacksmithSecondSelect03Scale;

	D3DXVECTOR3 m_BlacksmithSelectPointerPos;
	D3DXVECTOR3 m_BlacksmithSelectPointerScale;

	D3DXVECTOR3 m_WeaponMaterial1Pos;
	D3DXVECTOR3 m_WeaponMaterial1Scale;

	D3DXVECTOR3 m_WeaponMaterial2Pos;
	D3DXVECTOR3 m_WeaponMaterial2Scale;

	D3DXVECTOR3 m_WeaponMaterial3Pos;
	D3DXVECTOR3 m_WeaponMaterial3Scale;

	D3DXVECTOR3 m_BlacksmithPointerPos;
	D3DXVECTOR3 m_BlacksmithPointerScale;

	D3DXVECTOR3 m_BlacksmithLastInfoPos;
	D3DXVECTOR3 m_BlacksmithLastInfoScale;

	D3DXVECTOR3 m_Weapon00InfoPos;
	D3DXVECTOR3 m_Weapon00InfoScale;

	D3DXVECTOR3 m_Weapon00SharpnessTextuerPos;
	D3DXVECTOR3 m_Weapon00SharpnessTextuerScale;

	D3DXVECTOR3 m_Weapon01InfoPos;
	D3DXVECTOR3 m_Weapon01InfoScale;

	D3DXVECTOR3 m_Weapon01SharpnessTextuerPos;
	D3DXVECTOR3 m_Weapon01SharpnessTextuerScale;

	D3DXVECTOR3 m_Weapon02InfoPos;
	D3DXVECTOR3 m_Weapon02InfoScale;

	D3DXVECTOR3 m_Weapon03InfoPos;
	D3DXVECTOR3 m_Weapon03InfoScale;

	D3DXVECTOR3 m_WeaponStorMoneyPos;
	D3DXVECTOR3 m_WeaponStorMoneyScale;

	D3DXVECTOR3 m_Weapon00SharppPos;
	D3DXVECTOR3 m_Weapon00SharppScale;

	D3DXVECTOR3 m_Weapon01SharppPos;
	D3DXVECTOR3 m_Weapon01SharppScale;

	D3DXVECTOR3 m_Weapon02SharppPos;
	D3DXVECTOR3 m_Weapon02SharppScale;

	D3DXVECTOR3 m_Weapon03SharppPos;
	D3DXVECTOR3 m_Weapon03SharppScale;


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetBlackSmithFlg(void) { return m_BlecksmithSelect1; }
	bool GetWeaponChangeFlg(void) { return m_WeaponChangeFlg; }

};