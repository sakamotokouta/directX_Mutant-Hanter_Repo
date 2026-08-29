#pragma once

#include "gameObject.h"

class QuestDeskUi : public GameObject
{
private:

	bool m_PointerLockFlg{};
	bool m_Level1Flg;
	bool m_Level2Flg;
	bool m_Level3Flg;
	bool m_LastSelectFlg{};

	static bool m_Level1RespwanFlg;
	static bool m_Level2RespwanFlg;
	static bool m_Level3RespwanFlg;


	class Audio* m_SelectSE{};
	class Audio* m_EnterSE{};

	class VillagePlayerAction* m_PlayerAction{};

	class Score* m_MoeneyNum{};

	class Sprit2D* m_Pointer;
	class Sprit2D* m_QuestChoice01;
	class Sprit2D* m_QuestChoice02;
	class Sprit2D* m_QuestChoice03;
	class Sprit2D* m_Quest01;
	class Sprit2D* m_Quest02;
	class Sprit2D* m_Quest03;
	class Sprit2D* m_EnerOrRetern;
	class Sprit2D* m_LastSelect;
	class Sprit2D* m_LastSelectPointer;

	D3DXVECTOR3 m_Quest01Pos;
	D3DXVECTOR3 m_Quest01Scale;

	D3DXVECTOR3 m_Quest02Pos;
	D3DXVECTOR3 m_Quest02Scale;

	D3DXVECTOR3 m_Quest03Pos;
	D3DXVECTOR3 m_Quest03Scale;

	D3DXVECTOR3 m_PointerPos;
	D3DXVECTOR3 m_PointerScale;

	D3DXVECTOR3 m_QuestChoice01Pos;
	D3DXVECTOR3 m_QuestChoice01Scale;

	D3DXVECTOR3 m_QuestChoice02Pos;
	D3DXVECTOR3 m_QuestChoice02Scale;

	D3DXVECTOR3 m_QuestChoice03Pos;
	D3DXVECTOR3 m_QuestChoice03Scale;

	D3DXVECTOR3 m_EnerOrReternPos;
	D3DXVECTOR3 m_EnerOrReternScale;

	D3DXVECTOR3 m_LastSelectPos;
	D3DXVECTOR3 m_LastSelectScale;

	D3DXVECTOR3 m_LastSelectPointerPos;
	D3DXVECTOR3 m_LastSelectPointerScale;

	D3DXVECTOR3 m_QuestMoneyPos;
	D3DXVECTOR3 m_QuestMoneyScale;


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	static bool GetLevel01RespwanFlg(void) { return m_Level1RespwanFlg; }
	static bool GetLevel02RespwanFlg(void) { return m_Level2RespwanFlg; }
	static bool GetLevel03RespwanFlg(void) { return m_Level3RespwanFlg; }
	static void SetLevel01RespwanFlg(bool flg) { m_Level1RespwanFlg = flg; }
	static void SetLevel02RespwanFlg(bool flg) { m_Level2RespwanFlg = flg; }
	static void SetLevel03RespwanFlg(bool flg) { m_Level3RespwanFlg = flg; }

	bool GetLevel01Flg(void) { return m_Level1Flg; }
	bool GetLevel02Flg(void) { return m_Level2Flg; }
	bool GetLevel03Flg(void) { return m_Level3Flg; }
	bool GetLastSelectFlg(void) { return m_LastSelectFlg; }

};