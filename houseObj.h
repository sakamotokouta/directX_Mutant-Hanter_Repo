#pragma once

#include "gameObject.h"

class HouseObj : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	class Scene* m_Scene{};
	class CollisionBox* m_Collision{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};