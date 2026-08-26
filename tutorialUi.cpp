#include "main.h"
#include "renderer.h"
#include "sprit2D.h"
#include "manager.h"
#include "input.h"
#include "player.h"
#include "itemDataLoad.h"
#include "score.h"
#include "weaponDataLoad.h"
#include "enemy.h"
#include "tutorialUi.h"
#include "tutorial.h"

bool TutorialUi::m_EndFlg{};

void TutorialUi::Init()
{
	m_MoveView = new Sprit2D;
	m_Move = new Sprit2D;
	m_Avoidance = new Sprit2D;
	m_Attack = new Sprit2D;
	m_SpecialAttack = new Sprit2D;
	m_Enemy = new Sprit2D;
	m_End = new Sprit2D;

	m_MoveView->Init("asset/texture/mouseinfo.png");
	m_Move->Init("asset/texture/move.png");
	m_Avoidance->Init("asset/texture/avoidance.png");
	m_Attack->Init("asset/texture/attack.png");
	m_SpecialAttack->Init("asset/texture/specialAttack.png");
	m_Enemy->Init("asset/texture/enemy.png");
	m_End->Init("asset/texture/end.png");

	m_Positon = D3DXVECTOR3(480.0f, 450.0f, 0.0f);
	m_Scale = D3DXVECTOR3(400.0f, 200.0f, 0.0f);

	m_MoveViewFlg = true;


	GameObject::Init();
}

void TutorialUi::Uninit()
{
	m_MoveView->Uninit();
	m_Move->Uninit();
	m_Avoidance->Uninit();
	m_Attack->Uninit();
	m_SpecialAttack->Uninit();
	m_Enemy->Uninit();
	m_End->Uninit();

}

void TutorialUi::Update()
{

	GameObject::Update();
}

void TutorialUi::Draw()
{

	//視点操作
	if(m_MoveViewFlg)
		m_MoveView->Draw(m_Positon, m_Scale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

	//移動
	if (Input::GetKeyTrigger(VK_RETURN) && m_MoveViewFlg)
	{
		m_MoveFlg = true;
		m_MoveViewFlg = false;
	}
	//回避
	else if (Input::GetKeyTrigger(VK_RETURN) && m_MoveFlg)
	{
		m_AvoidanceFlg = true;
		m_MoveFlg = false;
	}
	//攻撃
	else if (Input::GetKeyTrigger(VK_RETURN) && m_AvoidanceFlg)
	{
		m_AttackFlg = true;
		m_AvoidanceFlg = false;
	}
	//特殊攻撃
	else if (Input::GetKeyTrigger(VK_RETURN) && m_AttackFlg)
	{
		m_SpecialAttackFlg = true;
		m_AttackFlg = false;
	}
	//敵
	else if (Input::GetKeyTrigger(VK_RETURN) && m_SpecialAttackFlg)
	{
		m_EnemyFlg = true;
		m_SpecialAttackFlg = false;
	}
	//最後
	else if (Input::GetKeyTrigger(VK_RETURN) && m_EnemyFlg)
	{
		m_EnemyFlg = false;
	}

	if (m_MoveFlg)
		m_Move->Draw(m_Positon, m_Scale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

	if (m_AvoidanceFlg)
		m_Avoidance->Draw(m_Positon, m_Scale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

	if (m_AttackFlg)
		m_Attack->Draw(m_Positon, m_Scale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

	if (m_SpecialAttackFlg)
		m_SpecialAttack->Draw(m_Positon, m_Scale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

	if (m_EnemyFlg)
		m_Enemy->Draw(m_Positon, m_Scale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);


	if (Enemy::GetEnemyHp() <= 0)
		m_EndFlg = true;




	if (m_EndFlg)
		m_End->Draw(m_Positon, m_Scale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);

	GameObject::Draw();
}
