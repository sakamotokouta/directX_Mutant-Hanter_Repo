#pragma once
#pragma once

#include "gameObject.h"

class WeaponDataBase : public GameObject
{
protected:
	//位置
	D3DXVECTOR3 m_Pos{};
	// サイズ
	D3DXVECTOR3 m_Scale{};
	//トレイルの位置
	D3DXVECTOR3 m_TrailPos{};
	// 角度
	D3DXVECTOR3 m_Rot{};
	//モデル
	const char* m_ModelName{};
	//攻撃力
	float m_Attack{};
	//切れ味
	float m_Sharpness{};
	//切れ味の画像
	const char* m_SharpnessTextuer{};
	//値段
	int m_Price{};

public:

	//剣をしまっているときの位置、サイズ、角度
	virtual D3DXVECTOR3 GetWeaponMountPosition(void) = 0;
	virtual D3DXVECTOR3 GetWeaponMountScale(void) = 0;
	virtual D3DXVECTOR3 GetWeaponMountRotation(void) = 0;

	//剣を構えているときの位置、サイズ、角度
	virtual D3DXVECTOR3 GetWeaponSetUpPosition(void) = 0;
	virtual D3DXVECTOR3 GetWeaponSetUpScale(void) = 0;
	virtual D3DXVECTOR3 GetWeaponSetUpRotation(void) = 0;

	virtual const char* GetWeaponModelName(void) = 0;
	virtual float GetWeaponAttack(void) = 0;
	virtual float GetWeaponSharpness(void) = 0;
	virtual const char* GetWeaponSharpnessTextuer(void) = 0;
	virtual int GetWeaponPrice(void) = 0;

	//トレイルの位置の取得
	virtual D3DXVECTOR3 GetTrailPositon(void) = 0;


};