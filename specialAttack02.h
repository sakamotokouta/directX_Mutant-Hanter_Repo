#pragma once

#include "gameObject.h"

class SpecialAttack02 : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	D3DXMATRIX m_CollitionMatrix{};


	class Scene* m_Scene{};
	class CollisionBox* m_Collision{};


	bool m_EnemyDamege{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetEnemyDamege(void) { return m_EnemyDamege; }

};
