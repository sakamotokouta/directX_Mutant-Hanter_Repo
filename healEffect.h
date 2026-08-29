#pragma once

#include "gameObject.h"

#define EFFECT_X 10
#define EFFECT_Y 1

class HealEffect : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	static ID3D11Buffer* m_VertexBuffer;
	static ID3D11ShaderResourceView* m_Texture;

	int m_Count{};
	int m_TimeCount{};

	D3DXVECTOR4 m_Color{};

public:

	static void Load();
	static void Unload();
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetColor(D3DXVECTOR4 color) { m_Color = color; }
};