#include "itemDataLoad.h"
#include "medicalItem.h"


ItemDataBase* ItemDataLoad::m_ItemData[100]{};
ItemDataBase* ItemDataLoad::m_KeepItemData[100]{};

bool ItemDataLoad::m_DataKeepFlg{};


 void ItemDataLoad::DataLoad(void)
{

	if (!m_DataKeepFlg)
	{
		m_ItemData[0] = new MedicalItem;
	}
	else
	{
		m_ItemData[0] = m_KeepItemData[0];
	}


}