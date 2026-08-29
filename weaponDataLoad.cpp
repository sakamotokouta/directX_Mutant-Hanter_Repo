#include"scene.h"
#include "manager.h"
#include "weaponDataLoad.h"
#include "weapon00.h"
#include "weapon01.h"
#include "weapon02.h"
#include "weapon03.h"

WeaponDataBase* WeaponDataLoad::m_WeaponData[WEAPON_NUM];
WeaponDataBase* WeaponDataLoad::m_KeepWeaponData[WEAPON_NUM];
bool WeaponDataLoad::m_LoadFinishFlg{};
int WeaponDataLoad::WeaponNumber = 0;

void WeaponDataLoad::DataLoad(void)
{
	//初期化してない場合初期化する
	Weapon00* weapon00 = new Weapon00;
	Weapon01* weapon01 = new Weapon01;
	Weapon02* weapon02 = new Weapon02;
	Weapon03* weapon03 = new Weapon03;

	m_WeaponData[0] = weapon00;
	m_WeaponData[1] = weapon01;
	m_WeaponData[2] = weapon02;
	m_WeaponData[3] = weapon03;

}

void WeaponDataLoad::DataUnLoad(void)
{
	for (int i = 0; i < WEAPON_NUM; i++)
	{
		delete m_WeaponData[i];
	}
}
