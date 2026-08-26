#pragma once

#include "gameObject.h"
#include "weaponDataBase.h"

class Weapon00 : public WeaponDataBase
{
private:

public:

	//武器をしまっているとき
	//位置
	D3DXVECTOR3 GetWeaponMountPosition(void) {
		m_Pos = D3DXVECTOR3(-30.0f, 90.0f, -10.0f);
		return m_Pos;
	}
	//サイズ
	D3DXVECTOR3 GetWeaponMountScale(void) {
		m_Scale = D3DXVECTOR3(30.0f, 30.0f, 30.0f);
		
		return m_Scale;
	}
	//角度
	D3DXVECTOR3 GetWeaponMountRotation(void) {
		m_Rot = D3DXVECTOR3(2.6f, 1.5f, 0.0f);
		return m_Rot;
	}

	//武器を構えているとき
	//位置
	D3DXVECTOR3 GetWeaponSetUpPosition(void) {
		m_Pos = D3DXVECTOR3(-15.0f, 30.0f, -30.0f);
		return m_Pos;
	}
	//サイズ
	D3DXVECTOR3 GetWeaponSetUpScale(void) {
		m_Scale = D3DXVECTOR3(25.0f, 40.0f, 25.0f);

		return m_Scale;
	}
	//角度
	D3DXVECTOR3 GetWeaponSetUpRotation(void) {
		m_Rot = D3DXVECTOR3(2.0f, 0.0f, 5.0f);
		return m_Rot;
	}

	//モデルの名前
	const char* GetWeaponModelName(void) {
		m_ModelName = "asset\\model\\sword003.obj";
		return m_ModelName;
	}
	//攻撃力
	float GetWeaponAttack(void) {
		m_Attack = 100.0f;
		return m_Attack;
	}
	//切れ味
	float GetWeaponSharpness(void) {
		m_Sharpness = 100.0f;
		return m_Sharpness;
	}
	//切れ味画像
	const char* GetWeaponSharpnessTextuer(void) {
		m_SharpnessTextuer = "asset/texture/weapon00sharp.png";
		return m_SharpnessTextuer;
	}
	//値段
	int GetWeaponPrice(void) {
		m_Price = 100;
		return m_Price;
	}
	//トレイルの位置
	D3DXVECTOR3 GetTrailPositon(void){
		m_TrailPos = D3DXVECTOR3(-1.0f, 5.0f, 1.0f);
		return m_TrailPos;
	}

};