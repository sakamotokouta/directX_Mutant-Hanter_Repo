#pragma once
#pragma once

#include "scene.h"

class TutorialUi : public GameObject
{
private:

	static 	bool m_EndFlg;


	class Sprit2D* m_MoveView{};
	class Sprit2D* m_Move{};
	class Sprit2D* m_Avoidance{};
	class Sprit2D* m_Attack{};
	class Sprit2D* m_SpecialAttack{};
	class Sprit2D* m_Enemy{};
	class Sprit2D* m_End{};


	D3DXVECTOR3 m_Positon{};
	D3DXVECTOR3 m_Scale{};


	bool m_MoveViewFlg{};
	bool m_MoveFlg{};
	bool m_AvoidanceFlg{};
	bool m_AttackFlg{};
	bool m_SpecialAttackFlg{};
	bool m_EnemyFlg{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	static bool GetTutorialEndFlg(void) { return m_EndFlg; }

};