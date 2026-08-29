#pragma once
#pragma once

#include "gameObject.h"

#define MONEY_NUM 1000

class Money : public GameObject
{
private:
	static int m_Money;
	static int m_KeepMoney;
	static bool m_KeepFlg;
public:
	static void Init(void);
	static int GetMoney(void) { return m_Money; }
	static void SetMoney(int money) { m_Money = money; }
	static void SetMinusMoney(int money) { 
		m_Money -=money; 
		if (m_Money <= 0)
			m_Money = 0;
	}
	static void SetPlusMoney(int money) { 
		m_Money += money; 
		//上限9999
		if (m_Money >= 9999)
			m_Money = 9999;
	}
	static void SetKeepMoney(int money,bool keepflg) { 
		m_KeepMoney = money; 
		m_KeepFlg = keepflg;
	}

};