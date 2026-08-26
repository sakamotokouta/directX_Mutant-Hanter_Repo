#pragma once
#pragma once
#pragma once

#include "gameObject.h"
#include "weaponDataBase.h"

#define WEAPON_NUM 4

class WeaponDataLoad : public GameObject
{
protected:

	static WeaponDataBase* m_WeaponData[WEAPON_NUM];
	static bool m_LoadFinishFlg;
	static WeaponDataBase* m_KeepWeaponData[WEAPON_NUM];
	static int WeaponNumber;

public:

	//武器の情報の読み込み
	static void DataLoad(void);
	static void DataUnLoad(void);


	//武器情報の呼び出し
	static WeaponDataBase* GetWeaponDataBase(void) { return *m_WeaponData; }
	static WeaponDataBase* GetWeaponDataBaseIndex(int i) { return m_WeaponData[i]; }
	static int GetWeaponNumber(void) { return WeaponNumber; }
	static void SetWeaponNumber(int num) { WeaponNumber = num; }

};