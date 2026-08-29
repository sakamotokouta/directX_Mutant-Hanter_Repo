#pragma once
#pragma once
#pragma once

#include "gameObject.h"
#include "itemDataBase.h"


class ItemDataLoad : public GameObject
{
protected:

	static ItemDataBase* m_ItemData[100];
	static ItemDataBase* m_KeepItemData[100];

	static bool m_DataKeepFlg;


public:

	//武器の情報の読み込み
	static void DataLoad(void);


	//武器情報の呼び出し
	static ItemDataBase* GetItemDataBase(void) { return *m_ItemData; }
	static ItemDataBase* GetItemBaseIndex(int i) { return m_ItemData[i]; }
	static void SetItemBaseIndex(int i) { m_ItemData[i]; }
	static void SetKeepItemBase(int i,ItemDataBase* itemdata) { m_KeepItemData[i] = itemdata; }
	static bool GetDataKeepFlg(void) { return m_DataKeepFlg; }
	static void SetDataKeepFlg(bool flg) { m_DataKeepFlg = flg; }

};