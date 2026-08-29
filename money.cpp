#include "main.h"
#include "money.h"

int Money::m_Money = 0;
int Money::m_KeepMoney = 0;
bool Money::m_KeepFlg{};

void Money::Init(void)
{
	if (m_KeepFlg)
	{
		m_Money = m_KeepMoney;
	}
	else
	{
		m_Money = MONEY_NUM;
	}
}
