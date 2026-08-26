#pragma once
#pragma once

#include "gameObject.h"

class EnemyJumpAttack : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	class CollisionBox* m_Collision{};
	class Scene* m_Scene{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};