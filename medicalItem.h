#pragma once
#pragma once

#include "gameObject.h"
#include "itemDataBase.h"
#include "villageUi.h"

class MedicalItem : public ItemDataBase
{
protected:

public:

	int GetItemCount(void) {
		if (m_Count <= 0)
			return m_Count = 0;
		else if(m_Count >= 1)
			return m_Count;
	}

	void SetItemCount(int co) {
		m_Count = co;
	}

	int GetItemPrice(void) {
		m_Price = 10;
		return m_Price;
	}

	const char* GetItemTextuer(void) {
		m_ItemTextuer = "asset/texture/medicalitem.png";
		return m_ItemTextuer;
	}
};