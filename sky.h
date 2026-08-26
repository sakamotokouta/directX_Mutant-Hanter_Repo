#pragma once

#include "gameObject.h"

class Sky : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	D3DXVECTOR3 m_pos{};
	D3DXVECTOR3 m_scale{};

	class SpriteField* tile{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};