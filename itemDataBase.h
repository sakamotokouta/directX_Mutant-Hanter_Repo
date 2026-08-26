#pragma once
#pragma once

#include "gameObject.h"

class ItemDataBase : public GameObject
{
protected:
	//位置
	D3DXVECTOR3 m_Pos{};
	// サイズ
	D3DXVECTOR3 m_Scale{};
	// 角度
	D3DXVECTOR3 m_Rot{};
	//アイテムの画像
	const char* m_ItemTextuer{};
	//持っている量
	int m_Count = 0;
	//値段
	int m_Price{};

public:

	virtual int GetItemCount(void) = 0;

	virtual void SetItemCount(int co) = 0;

	virtual int GetItemPrice(void) = 0;

	virtual const char* GetItemTextuer(void) = 0;

};