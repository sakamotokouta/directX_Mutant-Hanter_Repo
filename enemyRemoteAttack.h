#pragma once

#include "gameObject.h"

class EnemyRemoteAttack : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	class Scene* m_Scene{};
	class CollisionBox* m_Collision{};


	bool m_AttackFlg{};

	bool m_DestroyFlg{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetAttackFlg(void) { return m_AttackFlg; }
	void SetAttackFlg(bool flg) { m_AttackFlg = flg; }
	void SetDestoryFlg(bool flg) { m_DestroyFlg = flg; }

};