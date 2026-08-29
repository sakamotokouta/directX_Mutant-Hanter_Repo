#pragma once

#include "gameObject.h"
#include <string>
#include "animationModel.h"

enum OTOMO_STATE
{
	OTOMO_WALK,
	OTOMO_IDLE,
	OTOMO_ATTACK,
};

class Otomo : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;
	ID3D11ShaderResourceView* m_DisolveTexture = nullptr;

	OTOMO_STATE m_OtomoState = OTOMO_IDLE;

	class AnimationModel* m_Model{};

	class Player* m_Player{};

	class Fade* m_Fade{};

	class Scene* m_Scene{};

	float m_BlendRate{};

	float m_Time;

	std::string m_AnimationName;
	std::string m_NextAnimationName;

	const aiScene* m_AiScene;

	float m_EnemyHp;

	bool m_Siya;

	D3DXMATRIX m_WorldMatrix{};
	D3DXVECTOR3 m_BonePos{};
	D3DXVECTOR3 m_BoneScale{};

	D3DXVECTOR3 m_Direction01{};
	float m_Length01{};

	D3DXVECTOR3 m_Direction02{};
	float m_Length02{};

	int m_BulletCo{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void UpdateIdle();
	void UpdateWalk();
	void UpdateAttack();

};

