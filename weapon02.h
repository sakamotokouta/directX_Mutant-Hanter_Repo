#pragma once

#include "gameObject.h"
#include "weaponDataBase.h"

class Weapon02 : public WeaponDataBase
{
private:

public:

	//武器をしまっているとき
	//位置
	D3DXVECTOR3 GetWeaponMountPosition(void) {
		m_Pos = D3DXVECTOR3(2.0f, -1.0f, 30.0f);
		return m_Pos;
	}
	//サイズ
	D3DXVECTOR3 GetWeaponMountScale(void) {
		m_Scale = D3DXVECTOR3(30.0f, 30.0f, 30.0f);

		return m_Scale;
	}
	//角度
	D3DXVECTOR3 GetWeaponMountRotation(void) {
		m_Rot = D3DXVECTOR3(-3.0f, 0.0f, 2.7f);
		return m_Rot;
	}

	//武器を構えているとき
	//位置
	D3DXVECTOR3 GetWeaponSetUpPosition(void) {
		m_Pos = D3DXVECTOR3(46.0f, 8.0f, 13.0f);
		return m_Pos;
	}
	//サイズ
	D3DXVECTOR3 GetWeaponSetUpScale(void) {
		m_Scale = D3DXVECTOR3(40.0f, 40.0f, 40.0f);

		return m_Scale;
	}
	//角度
	D3DXVECTOR3 GetWeaponSetUpRotation(void) {
		m_Rot = D3DXVECTOR3(3.0f, 6.0f, 1.6f);
		return m_Rot;
	}



	//モデルの名前
	const char* GetWeaponModelName(void) {
		m_ModelName = "asset\\model\\sowrd0002.obj";
		return m_ModelName;
	}
	//攻撃力
	float GetWeaponAttack(void) {
		m_Attack = 200.0f;
		return m_Attack;
	}
	//切れ味
	float GetWeaponSharpness(void) {
		m_Sharpness = 100.0f;
		return m_Sharpness;
	}
	//切れ味画像
	const char* GetWeaponSharpnessTextuer(void) {
		m_SharpnessTextuer = "asset/texture/weapon02sharp.png";
		return m_SharpnessTextuer;
	}
	//値段
	int GetWeaponPrice(void) {
		m_Price = 100;
		return m_Price;
	}
	//トレイルの位置
	D3DXVECTOR3 GetTrailPositon(void) {
		m_TrailPos = D3DXVECTOR3(0.5f, -1.8f, 0.5f);
		return m_TrailPos;
	}

};