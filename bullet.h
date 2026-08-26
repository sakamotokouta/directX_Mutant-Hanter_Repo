#pragma once

#include "gameObject.h"

class Bullet : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;
	D3DXVECTOR3 m_Velocity{};  // ‘¬“x

	class Scene* m_Scene{};
	class CollisionBox* m_Collision{};
	class Otomo* m_Otomo{};

	bool m_EnemyDamegeFlg{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetVelocity(D3DXVECTOR3 forward)
	{
		m_Velocity = forward;
	}

	bool GetEnemyDamegeFlg(void) { return m_EnemyDamegeFlg; }

};