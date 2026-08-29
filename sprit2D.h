#pragma once

#include "gameObject.h"

class Sprit2D : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_Texture = nullptr;

	int m_Count{};

	D3DXVECTOR3 m_Position;

	float m_Width;

	float m_Height;

public:
	void Init(const char* spritname);
	void Uninit();
	void Update();
	void Draw(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rotation,float clere);
};