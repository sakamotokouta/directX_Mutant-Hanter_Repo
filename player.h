#pragma once

#include "model.h"
#include "gameObject.h"
#include <string>
#include "animationModel.h"

#define HP_MAX 350.0f

enum PLAYER_STATE
{
	PLAYER_STATE_GROUND,
	PLAYER_STATE_ATTACK1,
	PLAYER_STATE_ATTACK2,
	PLAYER_STATE_ATTACK3,
	PLAYER_STATE_DAMAGE,
	PLAYER_STATE_AVOIDANCE,
	PLAYER_STATE_SCARED,
	PLAYER_STATE_SHEASH,
	PLAYER_STATE_MOUNT,
	PLAYER_STATE_SETUP,
	PLAYER_STATE_SPECIALATTACK,
	PLAYER_STATE_END,
	PLAYER_STATE_END2,
	PLAYER_STATE_HEAL,
};


class Player : public GameObject
{
private:

	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	PLAYER_STATE m_PlayerState = PLAYER_STATE_GROUND;

	D3DXMATRIX m_RightHnadMatrix{};

	D3DXVECTOR3 m_Velocity{};
	D3DXVECTOR3 m_BonePos{};
	D3DXVECTOR3 m_BoneScale{};
	D3DXVECTOR3 m_RightHandBone{};
	D3DXVECTOR3 m_OldPosition{};
	D3DXVECTOR3 m_EndPos{};

	class AnimationModel* m_Model{};
	class Scene* m_Scene{};
	class Audio* m_DamageSE_1{};
	class Audio* m_DamageSE_2{};
	class Audio* m_HealSE{};
	class Audio* m_AVoiceSE_1{};
	class Audio* m_AVoiceSE_2{};
	class Audio* m_AVoiceSE_3{};
	class Audio* m_AttackSE_1{};
	class Audio* m_AttackSE_2{};
	class Audio* m_AttackSE_3{};
	class Audio* m_SAVoiceSE{};
	class Audio* m_SALandingSE{};
	class Audio* m_SAttackSE_1{};
	class Audio* m_SAttackSE_2{};
	class Audio* m_BGM2{};
	class Audio* m_BGM3{};
	class Audio* m_BGM4{};
	class ItemDataLoad* m_ItemData{};
	class Fade* m_Fade{};
	class CollisionBox* m_Collision{};
	class Weapon* m_Weapon{};


	std::string m_AnimationName;
	std::string m_NextAnimationName;

	float m_BlendRate{};
	float m_Time{};
	float m_Hp{};
	float m_Forward{};

	int m_ItemCo{};
	int m_Count{};
	int m_AattackCo{};
	int m_DamegeCo{};
	int m_SpecialAttackCo{};
	int m_AvoidCo{};
	int m_ScaredCo{};
	int m_MountCo{};
	int m_SetUpCo{};
	int m_GameoverCo{};
	int m_PlayerEndCo{};
	int m_HealCo{};
	int m_StopCo{};
	int m_Attack01Co{};
	int m_Attack02Co{};
	int m_Attack03Co{};

	bool m_MoveFlg{};
	bool m_AttackFlg{};
	bool m_Damage{};
	bool m_RemoteDamage{};
	bool m_DamegeCoFlg{};
	bool m_CountFlg{};
	bool m_Attackstate1{};
	bool m_Attackstate2_1{};
	bool m_Attackstate2_2{};
	bool m_Attackstate3_1{};
	bool m_Attackstate3_2{};
	bool m_AvoidFlg{};
	bool m_ScaredFlg{};
	bool m_ScaredStart{};
	bool m_AttackCoFlg{};
	bool m_Attack01Flg{};
	bool m_Enemyattack01{};
	bool m_Enemyattack02{};
	bool m_IsGround{};
	bool m_FrontAvoid{};
	bool m_LeftAvoid{};
	bool m_RightAvoid{};
	bool m_BackAvoid{};
	bool m_MountFlg01{};
	bool m_MountFlg02{};
	bool m_SetUpFlg01{};
	bool m_SetUpFlg02{};
	bool m_RunBgm1{};
	bool m_RunBgm2{};
	bool m_RunBgm3{};
	bool m_RunBgm4{};
	bool m_SetUpFlg{};
	bool m_MountFlg{};
	bool m_SpecialAttackFlg{};
	bool m_SpecialAttackCoFlg{};
	bool m_SutaminaFlg{};
	static bool m_PlayerEndFlg;
	bool m_HealFlg{};
	bool m_HealAnmFlg{};
	bool m_AttackHit1{};
	bool m_AttackHit2{};
	bool m_AttackHit3{};
	bool m_AttackCoFlg01{};
	bool m_AttackCoFlg02{};
	bool m_AttackCoFlg03{};
	bool m_VillageStopFlg{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void UpdateGround();
	void UpdateAttack1(void);
	void UpdateAttack2(void);
	void UpdateAttack3(void);
	void UpdateDamege(void);
	void UpdateAvoidace(void);
	void UpdateScared(void);
	void UpdateMountMode(void);
	void UpdateSetUpMode(void);
	void UpdateSpecialAttack(void);
	void UpdatePlayerEnd(void);
	void UpdatePlayerEnd2(void);
	void UpdateHeal(void);


	bool GetAttackFlg(void) { return m_AttackFlg; }

	bool GetDamageFlg(void) { return m_Damage; }
	void SetDamegeFlg(bool flg) { m_Damage = flg; }

	std::string GetAnimeName(void) {return m_AnimationName;}

	float GetHP(void) { return m_Hp; }
	void SetHp(float hp) { m_Hp = hp; }

	bool GetScaredFlg(void) { return m_ScaredStart; }
	void SetScaredFlg(bool flg) { m_ScaredStart = flg; }

	D3DXVECTOR3 GetRightHand(void) { return m_RightHandBone; }

	bool GetMoveFlg(void) { return m_MoveFlg; }

	D3DXMATRIX GetPlayerWMatrix(void) { return m_WorldMatrix; }

	D3DXMATRIX GetRightHandMatrix(void) { return m_RightHnadMatrix; }

	AnimationModel* GetAnim(void) { return m_Model; }

	bool GetSowrdMountFlg(void) { return m_MountFlg02; }
	void SetSowrdMountFlg(bool flg) { m_MountFlg02 = flg; }

	bool GetSetUpFlg(void) { return m_SetUpFlg02; }
	void SetSetUpFlg(bool flg) { m_SetUpFlg02 = flg; }

	int GetItemCount(void) { return m_ItemCo; }

	PLAYER_STATE GetPlayerState(void) { return m_PlayerState; }
	void SetPlayerState(PLAYER_STATE state) { m_PlayerState = state; }

	static bool GetPlayerEndFlg(void) { return m_PlayerEndFlg; }


	bool GetPlayerAttackHit1(void) { return m_AttackHit1; }
	bool GetPlayerAttackHit2(void) { return m_AttackHit2; }
	bool GetPlayerAttackHit3(void) { return m_AttackHit3; }

	D3DXVECTOR3 GetOldPosition(void) { return m_OldPosition; }
	void SetOldPosition(D3DXVECTOR3 pos) { m_OldPosition = pos;}
};