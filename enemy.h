#pragma once

#include "gameObject.h"
#include <string>
#include "animationModel.h"

#define ATTACK_RANGE 7.0f
#define CHASE_RANGE	10.0f
#define MIDDLE_RANGE 3.0f

enum ENEMY_STATE
{
	ENEMY_STATE_ROARING,
	ENEMY_STATE_SACH,
	ENEMY_STATE_FOUND,
	ENEMY_STATE_DIE,
	ENEMY_STATE_REMOTEATTACK,
	ENEMY_STATE_JUMPATTACK,
	ENEMY_STATE_ATTACK,
	ENEMY_STATE_CHASE,

};

class Enemy : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;
	ID3D11ShaderResourceView* m_DisolveTexture = nullptr;

	D3DXMATRIX m_Matrix{};
	D3DXVECTOR3 m_Velocity{};
	D3DXVECTOR3 m_Direction01{};
	D3DXVECTOR3 m_Direction02{};


	class Scene* m_Scene{};
	class AnimationModel* m_Model{};
	class Audio* m_JABarkSE{};
	class Audio* m_JALandingSE{};
	class Audio* m_RAttackSE{};
	class Audio* m_DamageBarkSE{};
	class Audio* m_BarkSE{};
	class Player* m_Player{};
	class Fade* m_Fade{};
	class CollisionBox* m_Collision{};

	float m_BlendRate{};
	float m_Time{};
	float m_ViewDistance = 5.0f; // 視野距離
	float m_EnemyDistance = 10.0f;
	static float m_EnemyHp;
	float m_Threshold{};
	float m_Length{};

	D3DXCOLOR m_RimColor = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

	std::string m_AnimationName;
	std::string m_NextAnimationName;

	bool m_Bgm1Flg{};
	bool m_Siya;
	bool m_FoundFlg{};
	bool m_Attackflg{};
	bool m_TurnFlg{};
	bool m_ActionFlg{};
	bool m_ActionFlg02{};
	bool m_Damage{};
	bool m_Roarigflg{};
	bool m_RoringStart{};
	bool m_GameClar{};
	bool m_Animflg{};
	bool m_EnemyJumpFlg{};
	bool m_PlayerDetectFlg{};
	bool m_EnemyHitFlg{};
	bool m_JampAttackOBjFlg{};

	const char* m_EnemyModel[100]{};

	int m_MoveCo{};
	int m_RunCo{};
	int m_ActionCount{};
	int m_DamegeCo{};
	int m_EnemyActionRondomNum{};
	int m_Rot1{};
	int m_Rot2{};
	int m_Damegeflg{};
	int attacPCo{};
	int m_RoarigCo{};
	int m_EnemyModelCo{};
	int m_EnemyJumpCo{};
	int m_EnemyFirstAttackCo{};
	int m_EnemyHitOnlyCo{};
	int m_EnemyHitOnlyCoMax = 284;

	int m_EnemyCount{};

	ENEMY_STATE m_EnemyState = ENEMY_STATE_SACH;

	D3DXVECTOR3 m_BonePos{};
	D3DXVECTOR3 m_BoneScale{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	bool IsInFieldOfView(const D3DXVECTOR3& origin, D3DXVECTOR3& direction, float fieldOfViewRadians, float viewDistance);
	void UpdateEnemyRoaring(void);
	void UpdateEnemySach(void);
	void UpdateEnemyFound(void);
	void UpdateEnemyDie(void);
	void UpdateEnemyRemoteAttack(void);
	void UpdateEnemyJumpAttack(void);
	void UpdateEnemyAttack(void);
	void UpdateEnemyChase(void);

	bool GetRoringFlg(void) { return m_Roarigflg; }


	AnimationModel* GetAnim(void) { return m_Model; }

	ENEMY_STATE GetEnemyState(void) { return m_EnemyState; }

	bool GetAttackFlg(void) { return m_Attackflg; }

	void SetEnemyModel(int co) {
		m_EnemyModelCo = co;
		m_Model->Load(m_EnemyModel[m_EnemyModelCo]);
	}

	static float GetEnemyHp(void) { return m_EnemyHp; }
	static void SetEnmeyHp(float hp) { m_EnemyHp = hp; }
	static void SetEnmeyMuinusHp(float hp) { m_EnemyHp -= hp; }

	D3DXVECTOR3 GetPlayerDirection01(void);
	D3DXVECTOR3 GetPlayerDirection02(void);
	float GetPlayerLenth(void);
	bool GetEnemyHitFlg(void) { return m_EnemyHitFlg; }
	void SetEnemyHitFlg(bool flg) { m_EnemyHitFlg = flg; }

};

